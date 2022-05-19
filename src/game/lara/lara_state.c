#include "game/lara/lara_state.h"

#include "game/lara/lara_look.h"
#include "game/lara/lara_misc.h"
#include "game/random.h"
#include "global/const.h"
#include "global/stubs.h"
#include "global/types.h"
#include "global/vars.h"
#include "util.h"

#include <stdbool.h>
#include <stdint.h>

static bool m_JumpOK = true;

static void Lara_State_FastFallFriction(struct ITEM_INFO *item);

static void Lara_State_FastFallFriction(struct ITEM_INFO *item)
{
    item->speed = (item->speed * 95) / 100;
}

void Lara_State_Duck(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 1;
    coll->enable_baddie_push = 1;
    g_Lara.is_ducked = 1;

    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_ALL_FOURS;
        return;
    }

    if (Lara_TestSlide(item, coll)) {
        return;
    }

    if (g_Input & IN_LOOK) {
        Lara_LookUpDown();
    }

    if (((g_Input & IN_FORWARD) || (g_Input & IN_BACK))
        && g_Lara.gun_status == LGS_ARMLESS
        && item->frame_num > g_Anims[LA_DUCK_BREATHE].frame_base + 10) {
        g_Lara.torso_x_rot = 0;
        g_Lara.torso_y_rot = 0;
        item->goal_anim_state = LS_ALL_FOURS;
    }
}

void Lara_State_AllFours(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_DEATH;
        return;
    }
    if (g_Input & IN_LOOK) {
        Lara_LookUpDown();
    }

    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 1;

    if (item->anim_num == LA_DUCK_TO_CRAWL) {
        g_Lara.gun_status = LGS_HANDS_BUSY;
    }
    if (!Lara_TestSlide(item, coll)) {
        g_Camera.target_elevation = -23 * DEG_1;
    }
}

void Lara_State_AllFoursTurnLeft(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_ALL_FOURS;
        return;
    }

    coll->enable_spaz = 0;
    coll->enable_baddie_push = 1;
    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;
    g_Camera.target_elevation = -23 * DEG_1;

    if (Lara_TestSlide(item, coll)) {
        return;
    }

    item->pos.y_rot -= DEG_1 + (DEG_1 / 2);
    if (!(g_Input & IN_LEFT)) {
        item->goal_anim_state = LS_ALL_FOURS;
    }
}

void Lara_State_AllFoursTurnRight(
    struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_ALL_FOURS;
        return;
    }

    coll->enable_spaz = 0;
    coll->enable_baddie_push = 1;
    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;
    g_Camera.target_elevation = -23 * DEG_1;

    if (Lara_TestSlide(item, coll)) {
        return;
    }

    item->pos.y_rot += DEG_1 + (DEG_1 / 2);
    if (!(g_Input & IN_RIGHT)) {
        item->goal_anim_state = LS_ALL_FOURS;
    }
}

void Lara_State_Crawl(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_ALL_FOURS;
        return;
    }
    if (g_Input & IN_LOOK) {
        Lara_LookUpDown();
    }

    coll->enable_spaz = 0;
    coll->enable_baddie_push = 1;
    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;
    g_Camera.target_elevation = -23 * DEG_1;

    if (Lara_TestSlide(item, coll)) {
        return;
    }

    if (!(g_Input & IN_FORWARD)
        || (!(g_Input & IN_DUCK) && !g_Lara.keep_ducked)) {
        item->goal_anim_state = LS_ALL_FOURS;
    } else if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_JUMP_TURN);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        CLAMPG(g_Lara.turn_rate, LARA_JUMP_TURN);
    }
}

void Lara_State_CrawlB(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_ALL_FOURS;
        return;
    }
    if (g_Input & IN_LOOK) {
        Lara_LookUpDown();
    }

    coll->enable_spaz = 0;
    coll->enable_baddie_push = 1;
    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;
    g_Camera.target_elevation = -23 * DEG_1;

    if (Lara_TestSlide(item, coll)) {
        return;
    }

    if (!(g_Input & IN_BACK)) {
        item->goal_anim_state = LS_ALL_FOURS;
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_JUMP_TURN);
    } else if (g_Input & IN_LEFT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        CLAMPG(g_Lara.turn_rate, LARA_JUMP_TURN);
    }
}

void Lara_State_Dash(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_RUN;
        return;
    }

    if (!g_DashTimer || !(g_Input & IN_DASH)
        || g_Lara.water_status == LWS_WADE) {
        item->goal_anim_state = LS_RUN;
        return;
    }

    g_DashTimer--;
    if (g_Input & IN_DUCK) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        item->pos.z_rot -= LARA_LEAN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_SLOW_TURN);
        CLAMPL(item->pos.z_rot, -LARA_LEAN_MAX_DASH);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        item->pos.z_rot += LARA_LEAN_RATE;
        CLAMPG(g_Lara.turn_rate, LARA_SLOW_TURN);
        CLAMPG(item->pos.z_rot, LARA_LEAN_MAX_DASH);
    }

    if ((g_Input & IN_JUMP) && !item->gravity_status) {
        item->goal_anim_state = LS_DASH_DIVE;
    } else if (g_Input & IN_FORWARD) {
        item->goal_anim_state = g_Input & IN_SLOW ? LS_WALK : LS_DASH;
    } else if (!(g_Input & IN_LEFT) && !(g_Input & IN_RIGHT)) {
        item->goal_anim_state = LS_STOP;
    }
}

void Lara_State_DashDive(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->goal_anim_state != LS_DEATH && item->goal_anim_state != LS_STOP
        && item->goal_anim_state != LS_RUN
        && item->fall_speed > LARA_FAST_FALL_SPEED) {
        item->goal_anim_state = LS_FAST_FALL;
    }
}

void Lara_State_MonkeyHang(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;

    if (g_Lara.can_monkey_swing) {
        if (g_Input & IN_ACTION && item->hit_points > 0) {
            g_Camera.target_angle = CAMERA_HANG_ANGLE;
            g_Camera.target_elevation = CAMERA_HANG_ELEVATION;
        } else {
            Lara_MonkeySwingFall(item);
        }
    } else if (g_Input & IN_LOOK) {
        Lara_LookUpDown();
    }
}

void Lara_State_MonkeySwing(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_MONKEY_HANG;
        return;
    }

    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;

    if (g_Input & IN_FORWARD) {
        item->goal_anim_state = LS_MONKEY_SWING;
    } else {
        item->goal_anim_state = LS_MONKEY_HANG;
    }

    if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_JUMP_TURN);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        CLAMPG(g_Lara.turn_rate, LARA_JUMP_TURN);
    }
}

void Lara_State_MonkeyLeft(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_MONKEY_HANG;
        return;
    }

    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;
    g_Camera.target_elevation = 10 * DEG_1;

    if (g_Input & IN_STEP_L) {
        item->goal_anim_state = LS_MONKEY_L;
    } else {
        item->goal_anim_state = LS_MONKEY_HANG;
    }
}

void Lara_State_MonkeyRight(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_MONKEY_HANG;
        return;
    }

    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;
    g_Camera.target_elevation = 10 * DEG_1;

    if (g_Input & IN_STEP_R) {
        item->goal_anim_state = LS_MONKEY_R;
    } else {
        item->goal_anim_state = LS_MONKEY_HANG;
    }
}

void Lara_State_HangTurnLeft(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_MONKEY_HANG;
        return;
    }

    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;
    g_Camera.target_elevation = 10 * DEG_1;
    item->pos.y_rot -= DEG_1 + DEG_1 / 2;

    if (!(g_Input & IN_LEFT)) {
        item->goal_anim_state = LS_MONKEY_HANG;
    }
}

void Lara_State_HangTurnRight(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_MONKEY_HANG;
        return;
    }

    g_Lara.torso_x_rot = 0;
    g_Lara.torso_y_rot = 0;
    g_Camera.target_elevation = 10 * DEG_1;
    item->pos.y_rot += DEG_1 + DEG_1 / 2;

    if (!(g_Input & IN_RIGHT)) {
        item->goal_anim_state = LS_MONKEY_HANG;
    }
}

void Lara_State_Monkey180(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    item->goal_anim_state = LS_MONKEY_HANG;
}

void Lara_State_Stop(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_DEATH;
        return;
    }

    if (item->anim_num != 226 && item->anim_num != 228) {
        Sound_StopEffect(SFX_LARA_SLIPPING);
    }

    if (g_Input & IN_ROLL && g_Lara.water_status != LWS_WADE) {
        item->current_anim_state = LS_ROLL;
        item->goal_anim_state = LS_STOP;
        item->anim_num = LA_ROLL;
        item->frame_num = g_Anims[LA_ROLL].frame_base + 2;
        return;
    }

    if (g_Input & IN_DUCK && g_Lara.water_status != LWS_WADE
        && item->current_anim_state == LS_STOP
        && (g_Lara.gun_status == LGS_ARMLESS || g_Lara.gun_type == LGT_UNARMED
            || g_Lara.gun_type == LGT_PISTOLS || g_Lara.gun_type == LGT_MAGNUMS
            || g_Lara.gun_type == LGT_UZIS || g_Lara.gun_type == LGT_FLARE)) {
        item->goal_anim_state = LS_DUCK;
        return;
    }

    item->goal_anim_state = LS_STOP;
    if (g_Input & IN_LOOK) {
        Lara_LookUpDown();
    }

    int16_t fheight = NO_HEIGHT;
    int16_t rheight = NO_HEIGHT;
    if (g_Input & IN_FORWARD) {
        fheight = Lara_FloorFront(item, item->pos.y_rot, LARA_RADIUS + 4);
    } else if (g_Input & IN_BACK) {
        rheight =
            Lara_FloorFront(item, item->pos.y_rot + DEG_180, LARA_RADIUS + 4);
    }

    if (g_Rooms[item->room_num].flags & RF_SWAMP) {
        if (g_Input & IN_LEFT) {
            item->goal_anim_state = LS_TURN_L;
        } else if (g_Input & IN_RIGHT) {
            item->goal_anim_state = LS_TURN_R;
        }
    } else {
        if (g_Input & IN_STEP_L) {
            int16_t height = Lara_FloorFront(
                item, item->pos.y_rot - DEG_90, LARA_RADIUS + 48);
            int16_t ceiling = Lara_CeilingFront(
                item, item->pos.y_rot - DEG_90, LARA_RADIUS + 48);
            if (height < 128 && height > -128 && g_HeightType != HT_BIG_SLOPE
                && ceiling <= 0) {
                item->goal_anim_state = LS_STEP_LEFT;
            }
        } else if (g_Input & IN_STEP_R) {
            int16_t height = Lara_FloorFront(
                item, item->pos.y_rot + DEG_90, LARA_RADIUS + 48);
            int16_t ceiling = Lara_CeilingFront(
                item, item->pos.y_rot + DEG_90, LARA_RADIUS + 48);
            if (height < 128 && height > -128 && g_HeightType != HT_BIG_SLOPE
                && ceiling <= 0) {
                item->goal_anim_state = LS_STEP_RIGHT;
            }
        } else if (g_Input & IN_LEFT) {
            item->goal_anim_state = LS_TURN_L;
        } else if (g_Input & IN_RIGHT) {
            item->goal_anim_state = LS_TURN_R;
        }
    }

    if (g_Lara.water_status == LWS_WADE) {
        if (g_Input & IN_JUMP && !(g_Rooms[item->room_num].flags & RF_SWAMP)) {
            item->goal_anim_state = LS_COMPRESS;
        }

        if (g_Input & IN_FORWARD) {
            bool wade = false;
            if (g_Rooms[item->room_num].flags & RF_SWAMP) {
                if (fheight > -(LARA_STEP_UP_HEIGHT - 1)) {
                    Lara_State_Wade(item, coll);
                    wade = true;
                }
            } else {
                if (fheight < LARA_STEP_UP_HEIGHT - 1
                    && fheight > -(LARA_STEP_UP_HEIGHT - 1)) {
                    Lara_State_Wade(item, coll);
                    wade = true;
                }
            }

            if (!wade) {
                g_Lara.move_angle = item->pos.y_rot;
                coll->bad_pos = NO_BAD_POS;
                coll->bad_neg = -LARA_STEP_UP_HEIGHT;
                coll->bad_ceiling = 0;
                coll->slopes_are_walls = 1;
                coll->radius = LARA_RADIUS + 2;
                Lara_GetCollisionInfo(item, coll);
                if (Lara_TestVault(item, coll)) {
                    return;
                }
                coll->radius = LARA_RADIUS;
            }
        } else if (g_Input & IN_BACK) {
            if (rheight < LARA_STEP_UP_HEIGHT - 1
                && rheight > -(LARA_STEP_UP_HEIGHT - 1)) {
                Lara_State_Back(item, coll);
            }
        }
    } else if (g_Input & IN_JUMP) {
        item->goal_anim_state = LS_COMPRESS;
    } else if (g_Input & IN_FORWARD) {
        int32_t height =
            Lara_FloorFront(item, item->pos.y_rot, LARA_RADIUS + 4);
        int32_t ceiling =
            Lara_CeilingFront(item, item->pos.y_rot, LARA_RADIUS + 4);
        if (g_HeightType == HT_BIG_SLOPE && height < 0) {
            item->goal_anim_state = LS_STOP;
        } else if (ceiling > 0) {
            item->goal_anim_state = LS_STOP;
        } else if (g_Input & IN_SLOW) {
            Lara_State_Walk(item, coll);
        } else {
            Lara_State_Run(item, coll);
        }
    } else if (g_Input & IN_BACK) {
        if (g_Input & IN_SLOW) {
            if (rheight < LARA_STEP_UP_HEIGHT - 1
                && rheight > -(LARA_STEP_UP_HEIGHT - 1)
                && g_HeightType != HT_BIG_SLOPE) {
                Lara_State_Back(item, coll);
            }
        } else if (rheight > -(LARA_STEP_UP_HEIGHT - 1)) {
            item->goal_anim_state = LS_FAST_BACK;
        }
    }
}

void Lara_State_JumpUp(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->fall_speed > LARA_FAST_FALL_SPEED) {
        item->goal_anim_state = LS_FAST_FALL;
    }
}

void Lara_State_ForwardJump(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->goal_anim_state == LS_SWAN_DIVE
        || item->goal_anim_state == LS_REACH) {
        item->goal_anim_state = LS_FORWARD_JUMP;
    }

    if (item->goal_anim_state != LS_DEATH && item->goal_anim_state != LS_STOP
        && item->goal_anim_state != LS_RUN) {
        if ((g_Input & IN_ACTION) && g_Lara.gun_status == LGS_ARMLESS) {
            item->goal_anim_state = LS_REACH;
        }
        if ((g_Input & IN_ROLL) || (g_Input & IN_BACK)) {
            item->goal_anim_state = LS_TWIST;
        }
        if ((g_Input & IN_SLOW) && g_Lara.gun_status == LGS_ARMLESS) {
            item->goal_anim_state = LS_SWAN_DIVE;
        }
        if (item->fall_speed > LARA_FAST_FALL_SPEED) {
            item->goal_anim_state = LS_FAST_FALL;
        }
    }

    if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_JUMP_TURN);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_JUMP_TURN);
    }
}

void Lara_State_Walk(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_SLOW_TURN);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_SLOW_TURN);
    }

    if (g_Input & IN_FORWARD) {
        if (g_Lara.water_status == LWS_WADE) {
            item->goal_anim_state = LS_WADE;
        } else if (g_Input & IN_SLOW) {
            item->goal_anim_state = LS_WALK;
        } else {
            item->goal_anim_state = LS_RUN;
        }
    } else {
        item->goal_anim_state = LS_STOP;
    }
}

void Lara_State_Run(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_DEATH;
        return;
    }

    if (g_Input & IN_ROLL) {
        item->anim_num = LA_ROLL;
        item->current_anim_state = LS_ROLL;
        item->goal_anim_state = LS_STOP;
        item->frame_num = g_Anims[LA_ROLL].frame_base + 2;
        return;
    }

    if (g_Input & IN_DASH && g_DashTimer == LARA_DASH_TIME) {
        item->goal_anim_state = LS_DASH;
        return;
    }

    if (g_Input & IN_DUCK && g_Lara.water_status != LWS_WADE) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        item->pos.z_rot -= LARA_LEAN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_FAST_TURN);
        CLAMPL(item->pos.z_rot, -LARA_LEAN_MAX);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        item->pos.z_rot += LARA_LEAN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_FAST_TURN);
        CLAMPG(item->pos.z_rot, +LARA_LEAN_MAX);
    }

    if (item->anim_num == LA_START_RUN) {
        m_JumpOK = false;
    } else if (item->anim_num == LA_RUN || item->frame_num == 4) {
        m_JumpOK = true;
    }

    if ((g_Input & IN_JUMP) && m_JumpOK && !item->gravity_status) {
        item->goal_anim_state = LS_FORWARD_JUMP;
        return;
    }

    if (!(g_Input & IN_FORWARD)) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    if (g_Lara.water_status == LWS_WADE) {
        item->goal_anim_state = LS_WADE;
    } else if (g_Input & IN_SLOW) {
        item->goal_anim_state = LS_WALK;
    } else {
        item->goal_anim_state = LS_RUN;
    }
}

void Lara_State_FastBack(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    item->goal_anim_state = LS_STOP;

    if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_MED_TURN);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_MED_TURN);
    }
}

void Lara_State_TurnRight(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    g_Lara.turn_rate += LARA_TURN_RATE;
    if (g_Lara.gun_status == LGS_READY && g_Lara.water_status != LWS_WADE) {
        item->goal_anim_state = LS_FAST_TURN;
    } else if (g_Lara.turn_rate > LARA_SLOW_TURN) {
        if (g_Input & IN_SLOW || g_Lara.water_status == LWS_WADE) {
            g_Lara.turn_rate = LARA_SLOW_TURN;
        } else {
            item->goal_anim_state = LS_FAST_TURN;
        }
    }

    if (g_Input & IN_FORWARD) {
        if (g_Lara.water_status == LWS_WADE) {
            item->goal_anim_state = LS_WADE;
        } else if (g_Input & IN_SLOW) {
            item->goal_anim_state = LS_WALK;
        } else {
            item->goal_anim_state = LS_RUN;
        }
    } else if (!(g_Input & IN_RIGHT)) {
        item->goal_anim_state = LS_STOP;
    }
}

void Lara_State_TurnLeft(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    g_Lara.turn_rate -= LARA_TURN_RATE;
    if (g_Lara.gun_status == LGS_READY && g_Lara.water_status != LWS_WADE) {
        item->goal_anim_state = LS_FAST_TURN;
    } else if (g_Lara.turn_rate < -LARA_SLOW_TURN) {
        if (g_Input & IN_SLOW || g_Lara.water_status == LWS_WADE) {
            g_Lara.turn_rate = -LARA_SLOW_TURN;
        } else {
            item->goal_anim_state = LS_FAST_TURN;
        }
    }

    if (g_Input & IN_FORWARD) {
        if (g_Lara.water_status == LWS_WADE) {
            item->goal_anim_state = LS_WADE;
        } else if (g_Input & IN_SLOW) {
            item->goal_anim_state = LS_WALK;
        } else {
            item->goal_anim_state = LS_RUN;
        }
    } else if (!(g_Input & IN_LEFT)) {
        item->goal_anim_state = LS_STOP;
    }
}

void Lara_State_Death(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
}

void Lara_State_FastFall(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    Lara_State_FastFallFriction(item);
    if (item->fall_speed == LARA_FALL_DAMAGE_START + LARA_FALL_DAMAGE_LENGTH) {
        Sound_PlayEffect(SFX_LARA_FALL, &item->pos, 0);
    }
}

void Lara_State_Hang(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    if (g_Input & IN_LOOK) {
        Lara_LookUpDown();
    }

    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = CAMERA_HANG_ANGLE;
    g_Camera.target_elevation = CAMERA_HANG_ELEVATION;

    if ((g_Input & IN_LEFT) || (g_Input & IN_STEP_L)) {
        item->goal_anim_state = LS_HANG_LEFT;
    } else if ((g_Input & IN_RIGHT) || (g_Input & IN_STEP_R)) {
        item->goal_anim_state = LS_HANG_RIGHT;
    }
}

void Lara_State_Reach(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Camera.target_angle = CAMERA_REACH_ANGLE;
    if (item->fall_speed > LARA_FAST_FALL_SPEED) {
        item->goal_anim_state = LS_FAST_FALL;
    }
}

void Lara_State_Splat(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;
}

void Lara_State_Compress(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (g_Lara.water_status != LWS_WADE) {
        if ((g_Input & IN_FORWARD)
            && (Lara_FloorFront(item, item->pos.y_rot, 256)
                >= -LARA_STEP_UP_HEIGHT)) {
            item->goal_anim_state = LS_FORWARD_JUMP;
            g_Lara.move_angle = item->pos.y_rot;
        } else if (
            (g_Input & IN_LEFT)
            && (Lara_FloorFront(item, item->pos.y_rot - DEG_90, 256)
                >= -LARA_STEP_UP_HEIGHT)) {
            item->goal_anim_state = LS_LEFT_JUMP;
            g_Lara.move_angle = item->pos.y_rot - DEG_90;
        } else if (
            (g_Input & IN_RIGHT)
            && (Lara_FloorFront(item, item->pos.y_rot + DEG_90, 256)
                >= -LARA_STEP_UP_HEIGHT)) {
            item->goal_anim_state = LS_RIGHT_JUMP;
            g_Lara.move_angle = item->pos.y_rot + DEG_90;
        } else if (
            (g_Input & IN_BACK)
            && (Lara_FloorFront(item, item->pos.y_rot + DEG_180, 256)
                >= -LARA_STEP_UP_HEIGHT)) {
            item->goal_anim_state = LS_BACK_JUMP;
            g_Lara.move_angle = item->pos.y_rot + DEG_180;
        }
    }

    if (item->fall_speed > LARA_FAST_FALL_SPEED) {
        item->goal_anim_state = LS_FAST_FALL;
    }
}

void Lara_State_Back(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    if ((g_Input & IN_BACK)
        && ((g_Input & IN_SLOW) || g_Lara.water_status == LWS_WADE)) {
        item->goal_anim_state = LS_BACK;
    } else {
        item->goal_anim_state = LS_STOP;
    }

    if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_SLOW_TURN);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_SLOW_TURN);
    }
}

void Lara_State_FastTurn(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    if (g_Lara.turn_rate < 0) {
        g_Lara.turn_rate = -LARA_FAST_TURN;
        if (!(g_Input & IN_LEFT)) {
            item->goal_anim_state = LS_STOP;
        }
    } else {
        g_Lara.turn_rate = LARA_FAST_TURN;
        if (!(g_Input & IN_RIGHT)) {
            item->goal_anim_state = LS_STOP;
        }
    }
}

void Lara_State_StepRight(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;

    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    if (!(g_Input & IN_STEP_R)) {
        item->goal_anim_state = LS_STOP;
    }

    if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_SLOW_TURN);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_SLOW_TURN);
    }
}

void Lara_State_StepLeft(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;

    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    if (!(g_Input & IN_STEP_L)) {
        item->goal_anim_state = LS_STOP;
    }

    if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_SLOW_TURN);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_SLOW_TURN);
    }
}

void Lara_State_Slide(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Camera.flags = CAMERA_NO_CHUNKY;
    g_Camera.target_elevation = CAMERA_SLIDE_ELEVATION;
    if ((g_Input & IN_JUMP) && !(g_Input & IN_BACK)) {
        item->goal_anim_state = LS_FORWARD_JUMP;
    }
}

void Lara_State_BackJump(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Camera.target_angle = CAMERA_BACKJUMP_ANGLE;

    if (item->fall_speed > LARA_FAST_FALL_SPEED) {
        item->goal_anim_state = LS_FAST_FALL;
    } else if (item->goal_anim_state == LS_RUN) {
        item->goal_anim_state = LS_STOP;
    } else if (
        ((g_Input & IN_FORWARD) || (g_Input & IN_ROLL))
        && item->goal_anim_state != LS_STOP) {
        item->goal_anim_state = LS_TWIST;
    }
}

void Lara_State_RightJump(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;
    if (item->fall_speed > LARA_FAST_FALL_SPEED) {
        item->goal_anim_state = LS_FAST_FALL;
    } else if ((g_Input & IN_LEFT) && item->goal_anim_state != LS_STOP) {
        item->goal_anim_state = LS_TWIST;
    }
}

void Lara_State_LeftJump(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;
    if (item->fall_speed > LARA_FAST_FALL_SPEED) {
        item->goal_anim_state = LS_FAST_FALL;
    } else if ((g_Input & IN_RIGHT) && item->goal_anim_state != LS_STOP) {
        item->goal_anim_state = LS_TWIST;
    }
}

void Lara_State_FallBack(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->fall_speed > LARA_FAST_FALL_SPEED) {
        item->goal_anim_state = LS_FAST_FALL;
    }
    if ((g_Input & IN_ACTION) && g_Lara.gun_status == LGS_ARMLESS) {
        item->goal_anim_state = LS_REACH;
    }
}

void Lara_State_HangLeft(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = CAMERA_HANG_ANGLE;
    g_Camera.target_elevation = CAMERA_HANG_ELEVATION;
    if (!(g_Input & IN_LEFT) && !(g_Input & IN_STEP_L)) {
        item->goal_anim_state = LS_HANG;
    }
}

void Lara_State_HangRight(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = CAMERA_HANG_ANGLE;
    g_Camera.target_elevation = CAMERA_HANG_ELEVATION;
    if (!(g_Input & IN_RIGHT) && !(g_Input & IN_STEP_R)) {
        item->goal_anim_state = LS_HANG;
    }
}

void Lara_State_SlideBack(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (g_Input & IN_JUMP && !(g_Input & IN_FORWARD)) {
        item->goal_anim_state = LS_BACK_JUMP;
    }
}

void Lara_State_PushBlock(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.flags = CAMERA_FOLLOW_CENTRE;
    g_Camera.target_angle = CAMERA_PUSHBLOCK_ANGLE;
    g_Camera.target_elevation = CAMERA_PUSHBLOCK_ELEVATION;
}

void Lara_State_PushPullReady(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = CAMERA_PUSHPULL_ANGLE;
    if (!(g_Input & IN_ACTION)) {
        item->goal_anim_state = LS_STOP;
    }
}

void Lara_State_Pickup(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = CAMERA_PICKUP_ANGLE;
    g_Camera.target_elevation = CAMERA_PICKUP_ELEVATION;
    g_Camera.target_distance = CAMERA_PICKUP_DISTANCE;
}

void Lara_State_PickupFlare(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = CAMERA_PICKUPFLARE_ANGLE;
    g_Camera.target_elevation = CAMERA_PICKUPFLARE_ELEVATION;
    g_Camera.target_distance = CAMERA_PICKUPFLARE_DISTANCE;
    if (item->frame_num == g_Anims[item->anim_num].frame_end - 1) {
        g_Lara.gun_status = LGS_ARMLESS;
    }
}

void Lara_State_SwitchOn(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = CAMERA_SWITCHON_ANGLE;
    g_Camera.target_elevation = CAMERA_SWITCHON_ELEVATION;
    g_Camera.target_distance = CAMERA_SWITCHON_DISTANCE;
    g_Camera.speed = CAMERA_SWITCHON_SPEED;
}

void Lara_State_UseKey(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Lara.look = 0;
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = CAMERA_USEKEY_ANGLE;
    g_Camera.target_elevation = CAMERA_USEKEY_ELEVATION;
    g_Camera.target_distance = CAMERA_USEKEY_DISTANCE;
}

void Lara_State_Special(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Camera.flags = CAMERA_FOLLOW_CENTRE;
    g_Camera.target_angle = CAMERA_EXTRA_ANGLE;
    g_Camera.target_elevation = CAMERA_EXTRA_ELEVATION;
}

void Lara_State_SwanDive(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 1;
    if (item->fall_speed > LARA_FAST_FALL_SPEED
        && item->goal_anim_state != LS_DIVE) {
        item->goal_anim_state = LS_FAST_DIVE;
    }
}

void Lara_State_FastDive(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 1;
    if ((g_Input & IN_ROLL) && item->goal_anim_state == LS_FAST_DIVE) {
        item->goal_anim_state = LS_TWIST;
    }
    Lara_State_FastFallFriction(item);
}

void Lara_State_Null(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
}

void Lara_State_WaterOut(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.flags = CAMERA_FOLLOW_CENTRE;
}

void Lara_State_Wade(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = LS_STOP;
        return;
    }

    g_Camera.target_elevation = CAMERA_WADE_ELEVATION;

    bool is_swamp = g_Rooms[item->room_num].flags & RF_SWAMP;
    int32_t div = is_swamp ? 2 : 1;

    if (g_Input & IN_LEFT) {
        g_Lara.turn_rate -= LARA_TURN_RATE;
        item->pos.z_rot -= LARA_LEAN_RATE;
        CLAMPL(g_Lara.turn_rate, -LARA_FAST_TURN / div);
        CLAMPL(item->pos.z_rot, -LARA_LEAN_MAX / div);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        item->pos.z_rot += LARA_LEAN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_FAST_TURN / div);
        CLAMPG(item->pos.z_rot, +LARA_LEAN_MAX / div);
    }

    if ((g_Input & IN_FORWARD)) {
        if (g_Lara.water_status == LWS_ABOVE_WATER && !is_swamp) {
            item->goal_anim_state = LS_RUN;
        } else {
            item->goal_anim_state = LS_WADE;
        }
    } else {
        item->goal_anim_state = LS_STOP;
    }
}

void Lara_State_DeathSlide(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Camera.target_angle = 12740;

    int16_t room_num = item->room_num;
    struct FLOOR_INFO *floor =
        GetFloor(item->pos.x, item->pos.y, item->pos.z, &room_num);
    GetHeight(floor, item->pos.x, item->pos.y, item->pos.z);
    coll->trigger = g_TriggerIndex;

    if (!(g_Input & IN_ACTION)) {
        item->goal_anim_state = LS_FORWARD_JUMP;
        Lara_Animate(item);
        item->gravity_status = 1;
        item->speed = 100;
        item->fall_speed = 40;
        g_Lara.move_angle = item->pos.y_rot;
    }
}

void Lara_State_ClimbLeft(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = -30 * DEG_1;
    g_Camera.target_elevation = -15 * DEG_1;
    if (!(g_Input & IN_LEFT) && !(g_Input & IN_STEP_L)) {
        item->goal_anim_state = LS_CLIMB_STNC;
    }
}

void Lara_StateExtra_Breath(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    item->goal_anim_state = LS_STOP;
    item->current_anim_state = LS_STOP;
    item->anim_num = LA_BREATH;
    item->frame_num = g_Anims[LA_BREATH].frame_base;
    g_Lara.gun_status = LGS_ARMLESS;

    g_Camera.type = CT_CHASE;
    AlterFOV(DEG_1 * GAME_FOV);

    g_Lara.extra_anim = 0;
}

void Lara_StateExtra_SharkKill(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Camera.target_angle = DEG_1 * 160;
    g_Camera.target_distance = WALL_L * 3;
    g_Lara.hit_direction = -1;

    if (item->frame_num == g_Anims[item->anim_num].frame_end) {
        int32_t water_height = GetWaterHeight(
            item->pos.x, item->pos.y, item->pos.z, item->room_num);
        if (water_height != NO_HEIGHT && water_height < item->pos.y - 100) {
            item->pos.y -= 5;
        }
    }
    if (item->frame_num < g_Anims[item->anim_num].frame_end - 30) {
        g_Lara.death_count = 1;
    }
}

void Lara_StateExtra_AirLock(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Camera.target_angle = DEG_1 * 80;
    g_Camera.target_elevation = DEG_1 * -25;
}

void Lara_StateExtra_GongBong(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Camera.target_angle = DEG_1 * -25;
    g_Camera.target_elevation = DEG_1 * -20;
    g_Camera.target_distance = WALL_L * 3;
}

void Lara_StateExtra_TRexDeath(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Camera.flags = CAMERA_FOLLOW_CENTRE;
    g_Camera.target_angle = DEG_1 * 170;
    g_Camera.target_elevation = DEG_1 * -25;
    g_Lara.hit_direction = -1;

    if (item->frame_num < g_Anims[item->anim_num].frame_end - 30) {
        g_Lara.death_count = 1;
    }
}

void Lara_StateExtra_StartAnim(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    int16_t room_num = item->room_num;
    struct FLOOR_INFO *floor =
        GetFloor(item->pos.x, item->pos.y, item->pos.z, &room_num);
    GetHeight(floor, item->pos.x, item->pos.y, item->pos.z);
    TestTriggers(g_TriggerIndex, 0);
}

void Lara_StateExtra_TrainKill(struct ITEM_INFO *item, struct COLL_INFO *col)
{
    g_Lara.hit_direction = -1;

    int16_t room_num = item->room_num;
    struct FLOOR_INFO *floor =
        GetFloor(item->pos.x, item->pos.y, item->pos.z, &room_num);
    item->pos.y = GetHeight(floor, item->pos.x, item->pos.y, item->pos.z);

    if (item->frame_num < g_Anims[item->anim_num].frame_end - 30) {
        g_Lara.death_count = 1;
    }

    item->gravity_status = 0;
    item->hit_points = -1;
}

void Lara_StateExtra_RapidsDrown(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    Lara_GetCollisionInfo(item, coll);

    int16_t room_num = item->room_num;
    struct FLOOR_INFO *floor =
        GetFloor(item->pos.x, item->pos.y, item->pos.z, &room_num);
    int32_t height = GetHeight(floor, item->pos.x, item->pos.y, item->pos.z);

    item->pos.y_rot += 1024;
    item->pos.y = height + LARA_STEP_UP_HEIGHT;
    g_Lara.death_count++;

    if (!(g_Wibble & 3)) {
        TriggerWaterfallMist(
            item->pos.x, item->pos.y, item->pos.z, Random_GetControl() & 0xFFF);
    }
}
