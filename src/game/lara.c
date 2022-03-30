#include "game/lara.h"

#include "global/const.h"
#include "global/stubs.h"
#include "global/vars.h"
#include "util.h"

#define FALL_DAMAGE_START 140
#define FALL_DAMAGE_LENGTH 14

static bool m_JumpOK = true;

static void Lara_State_FastFallFriction(struct ITEM_INFO *item);

static void Lara_State_FastFallFriction(struct ITEM_INFO *item)
{
    item->speed = (item->speed * 95) / 100;
}

void Lara_State_ForwardJump(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->goal_anim_state == LS_SWAN_DIVE
        || item->goal_anim_state == LS_REACH) {
        item->goal_anim_state = LS_FORWARD_JUMP;
    }

    if (item->goal_anim_state != LS_DEATH && item->goal_anim_state != LS_STOP
        && item->goal_anim_state != LS_RUN) {
        if ((g_Input & IN_ACTION) && g_Lara.gun_status == LG_ARMLESS) {
            item->goal_anim_state = LS_REACH;
        }
        if ((g_Input & IN_ROLL) || (g_Input & IN_BACK)) {
            item->goal_anim_state = LS_TWIST;
        }
        if ((g_Input & IN_SLOW) && g_Lara.gun_status == LG_ARMLESS) {
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
        CLAMPL(item->pos.z_rot, -LARA_LEAN_MAX_RATE);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        item->pos.z_rot += LARA_LEAN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_FAST_TURN);
        CLAMPG(item->pos.z_rot, +LARA_LEAN_MAX_RATE);
    }

    if (item->anim_num == LA_START_RUN) {
        m_JumpOK = 0;
    } else if (item->anim_num == LA_RUN || item->frame_num == 4) {
        m_JumpOK = 1;
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
    if (g_Lara.gun_status == LG_READY && g_Lara.water_status != LWS_WADE) {
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
    if (g_Lara.gun_status == LG_READY && g_Lara.water_status != LWS_WADE) {
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
    if (item->fall_speed == FALL_DAMAGE_START + FALL_DAMAGE_LENGTH) {
        SoundEffect(SFX_LARA_FALL, &item->pos, 0);
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

    if ((g_Input & IN_LEFT) || (g_Input & IN_STEPL)) {
        item->goal_anim_state = LS_HANG_LEFT;
    } else if ((g_Input & IN_RIGHT) || (g_Input & IN_STEPR)) {
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

    if (!(g_Input & IN_STEPR)) {
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

    if (!(g_Input & IN_STEPL)) {
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
    if ((g_Input & IN_ACTION) && g_Lara.gun_status == LG_ARMLESS) {
        item->goal_anim_state = LS_REACH;
    }
}

void Lara_State_HangLeft(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = CAMERA_HANG_ANGLE;
    g_Camera.target_elevation = CAMERA_HANG_ELEVATION;
    if (!(g_Input & IN_LEFT) && !(g_Input & IN_STEPL)) {
        item->goal_anim_state = LS_HANG;
    }
}

void Lara_State_HangRight(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;
    g_Camera.target_angle = CAMERA_HANG_ANGLE;
    g_Camera.target_elevation = CAMERA_HANG_ELEVATION;
    if (!(g_Input & IN_RIGHT) && !(g_Input & IN_STEPR)) {
        item->goal_anim_state = LS_HANG;
    }
}

void Lara_State_SlideBack(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (!(g_Input & IN_JUMP) && !(g_Input & IN_FORWARD)) {
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
        g_Lara.gun_status = LG_ARMLESS;
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
        CLAMPL(item->pos.z_rot, -LARA_LEAN_MAX_RATE / div);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        item->pos.z_rot += LARA_LEAN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_FAST_TURN / div);
        CLAMPG(item->pos.z_rot, +LARA_LEAN_MAX_RATE / div);
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
        AnimateLara(item);
        item->gravity_status = 1;
        item->speed = 100;
        item->fall_speed = 40;
        g_Lara.move_angle = item->pos.y_rot;
    }
}

void Lara_StateExtra_Breath(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    item->goal_anim_state = LS_STOP;
    item->current_anim_state = LS_STOP;
    item->anim_num = LA_BREATH;
    item->frame_num = g_Anims[LA_BREATH].frame_base;
    g_Lara.gun_status = LG_ARMLESS;

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
    GetLaraCollisionInfo(item, coll);

    int16_t room_num = item->room_num;
    struct FLOOR_INFO *floor =
        GetFloor(item->pos.x, item->pos.y, item->pos.z, &room_num);
    int32_t height = GetHeight(floor, item->pos.x, item->pos.y, item->pos.z);

    item->pos.y_rot += 1024;
    item->pos.y = height + 384;
    g_Lara.death_count++;

    if (!(g_Wibble & 3)) {
        TriggerWaterfallMist(
            item->pos.x, item->pos.y, item->pos.z, GetRandomControl() & 0xFFF);
    }
}
