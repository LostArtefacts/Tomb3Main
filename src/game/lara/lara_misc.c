#include "game/lara/lara_misc.h"

#include "global/const.h"
#include "global/stubs.h"
#include "global/vars.h"
#include "util.h"

#define CLIMB_HEIGHT (STEP_L * 2) // = 512
#define CLIMB_SHIFT 70
#define CLIMB_HANG 900

static PHD_ANGLE m_OldSlopeAngle = 1;

PHD_ANGLE Lara_SnapAngle(PHD_ANGLE angle, PHD_ANGLE snap)
{
    if (angle >= -snap && angle <= snap) {
        return 0;
    } else if (angle >= DEG_90 - snap && angle <= DEG_90 + snap) {
        return DEG_90;
    } else if (angle >= DEG_180 - 1 - snap || angle <= -(DEG_180 - 1) + snap) {
        return DEG_180;
    } else if (angle >= -DEG_90 - snap && angle <= -DEG_90 + snap) {
        return -DEG_90;
    }
    return angle;
}

enum DIRECTION Lara_AngleToDirection(PHD_ANGLE angle)
{
    return (enum DIRECTION)(uint16_t)(angle + DEG_45) / DEG_90;
}

void Lara_GetCollisionInfo(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->facing = g_Lara.move_angle;
    GetCollisionInfo(
        coll, item->pos.x, item->pos.y, item->pos.z, item->room_num,
        LARA_HEIGHT);
}

void Lara_SlideSlope(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->bad_pos = NO_BAD_POS;
    coll->bad_neg = -512;
    coll->bad_ceiling = 0;

    Lara_GetCollisionInfo(item, coll);
    if (Lara_HitCeiling(item, coll)) {
        return;
    }
    Lara_DeflectEdge(item, coll);

    if (coll->mid_floor > 200) {
        if (item->current_anim_state == LS_SLIDE) {
            item->current_anim_state = LS_FORWARD_JUMP;
            item->goal_anim_state = LS_FORWARD_JUMP;
            item->anim_num = LA_FALL_DOWN;
            item->frame_num = g_Anims[LA_FALL_DOWN].frame_base;
        } else {
            item->current_anim_state = LS_FALL_BACK;
            item->goal_anim_state = LS_FALL_BACK;
            item->anim_num = LA_FALL_BACK;
            item->frame_num = g_Anims[LA_FALL_BACK].frame_base;
        }

        Sound_StopEffect(SFX_LARA_SLIPPING);
        item->fall_speed = 0;
        item->gravity_status = 1;
        return;
    }

    Lara_TestSlide(item, coll);
    item->pos.y += coll->mid_floor;

    if (ABS(coll->tilt_x) <= 2 && ABS(coll->tilt_z) <= 2) {
        item->goal_anim_state = LS_STOP;
        Sound_StopEffect(SFX_LARA_SLIPPING);
    }
}

bool Lara_HitCeiling(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (coll->coll_type != COLL_TOP && coll->coll_type != COLL_CLAMP) {
        return false;
    }

    item->pos.x = coll->old.x;
    item->pos.y = coll->old.y;
    item->pos.z = coll->old.z;
    item->current_anim_state = LS_STOP;
    item->goal_anim_state = LS_STOP;
    item->anim_num = LA_STOP;
    item->frame_num = g_Anims[LA_STOP].frame_base;
    item->gravity_status = 0;
    item->fall_speed = 0;
    item->speed = 0;
    return true;
}

bool Lara_DeflectEdge(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    switch (coll->coll_type) {
    case COLL_FRONT:
    case COLL_TOP_FRONT:
        ShiftItem(item, coll);
        item->current_anim_state = LS_STOP;
        item->goal_anim_state = LS_STOP;
        item->gravity_status = 0;
        item->speed = 0;
        return true;

    case COLL_LEFT:
        ShiftItem(item, coll);
        item->pos.y_rot += LARA_DEF_ADD_EDGE;
        return false;

    case COLL_RIGHT:
        ShiftItem(item, coll);
        item->pos.y_rot -= LARA_DEF_ADD_EDGE;
        return false;

    default:
        return false;
    }
}

void Lara_DeflectEdgeJump(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    ShiftItem(item, coll);

    switch (coll->coll_type) {
    case COLL_FRONT:
    case COLL_TOP_FRONT:
        if (g_Lara.climb_status && item->speed == 2) {
            return;
        }

        if (coll->mid_floor > 512) {
            item->current_anim_state = LS_FAST_FALL;
            item->goal_anim_state = LS_FAST_FALL;
            item->anim_num = LA_FAST_SPLAT;
            item->frame_num = g_Anims[LA_FAST_SPLAT].frame_base + 1;
        } else if (coll->mid_floor <= 128) {
            item->current_anim_state = LS_LAND;
            item->goal_anim_state = LS_LAND;
            item->anim_num = LA_LAND;
            item->frame_num = g_Anims[LA_LAND].frame_base;
        }
        item->speed /= 4;
        g_Lara.move_angle += DEG_180;
        if (item->fall_speed <= 0) {
            item->fall_speed = 1;
        }
        break;

    case COLL_LEFT:
        item->pos.y_rot += LARA_DEF_ADD_EDGE;
        break;

    case COLL_RIGHT:
        item->pos.y_rot -= LARA_DEF_ADD_EDGE;
        break;

    case COLL_TOP:
        if (item->fall_speed <= 0) {
            item->fall_speed = 1;
        }
        break;

    case COLL_CLAMP:
        item->pos.z -= (100 * phd_cos(coll->facing)) >> W2V_SHIFT;
        item->pos.x -= (100 * phd_sin(coll->facing)) >> W2V_SHIFT;
        item->speed = 0;
        coll->mid_floor = 0;
        if (item->fall_speed <= 0) {
            item->fall_speed = 16;
        }
        break;

    default:
        break;
    }
}

bool Lara_DeflectEdgeDuck(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (coll->coll_type == COLL_FRONT || coll->coll_type == COLL_TOP_FRONT) {
        ShiftItem(item, coll);
        item->speed = 0;
        item->gravity_status = 0;
        return true;
    } else if (coll->coll_type == COLL_LEFT) {
        ShiftItem(item, coll);
        item->pos.y_rot += LARA_DUCK_DEFLECT;
    } else if (coll->coll_type == COLL_RIGHT) {
        ShiftItem(item, coll);
        item->pos.y_rot -= LARA_DUCK_DEFLECT;
    }
    return false;
}

void Lara_SlideEdgeJump(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    ShiftItem(item, coll);

    switch (coll->coll_type) {
    case COLL_LEFT:
        item->pos.y_rot += LARA_DEF_ADD_EDGE;
        break;

    case COLL_RIGHT:
        item->pos.y_rot -= LARA_DEF_ADD_EDGE;
        break;

    case COLL_TOP:
    case COLL_TOP_FRONT:
        if (item->fall_speed <= 0) {
            item->fall_speed = 1;
        }
        break;

    case COLL_CLAMP:
        item->pos.z -= (100 * phd_cos(coll->facing)) >> W2V_SHIFT;
        item->pos.x -= (100 * phd_sin(coll->facing)) >> W2V_SHIFT;
        item->speed = 0;
        coll->mid_floor = 0;
        if (item->fall_speed <= 0) {
            item->fall_speed = 16;
        }
        break;

    default:
        break;
    }
}

bool Lara_TestVault(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (!(g_Input & IN_ACTION) || g_Lara.gun_status != LGS_ARMLESS
        || coll->coll_type != COLL_FRONT) {
        return false;
    }

    PHD_ANGLE angle = Lara_SnapAngle(item->pos.y_rot, LARA_VAULT_ANGLE);
    if (angle % DEG_90 != 0) {
        return false;
    }

    int32_t hdif = coll->front_floor;
    bool slope = ABS(coll->left_floor2 - coll->right_floor2) >= LARA_SLOPE_DIF;

    if (hdif >= (-STEP_L * 2 - STEP_L / 2)
        && hdif <= (-STEP_L * 2 + STEP_L / 2)) {
        if (slope || (coll->front_floor - coll->front_ceiling < 0)
            || (coll->left_floor2 - coll->left_ceiling2 < 0)
            || (coll->right_floor2 - coll->right_ceiling2 < 0)) {
            return false;
        }

        if ((g_Rooms[item->room_num].flags & RF_SWAMP)
            && g_Lara.water_surface_dist < -768) {
            return false;
        }

        item->current_anim_state = LS_NULL;
        item->goal_anim_state = LS_STOP;
        item->anim_num = LA_VAULT_12;
        item->frame_num = g_Anims[LA_VAULT_12].frame_base;
        item->pos.y += hdif + STEP_L * 2;
        g_Lara.gun_status = LGS_HANDS_BUSY;
    } else if (
        hdif >= (-STEP_L * 3 - STEP_L / 2)
        && hdif <= (-STEP_L * 3 + STEP_L / 2)) {
        if (slope || (coll->front_floor - coll->front_ceiling < 0)
            || (coll->left_floor2 - coll->left_ceiling2 < 0)
            || (coll->right_floor2 - coll->right_ceiling2 < 0)) {
            return false;
        }

        if ((g_Rooms[item->room_num].flags & RF_SWAMP)
            && g_Lara.water_surface_dist < -768) {
            return false;
        }

        item->current_anim_state = LS_NULL;
        item->goal_anim_state = LS_STOP;
        item->anim_num = LA_VAULT_34;
        item->frame_num = g_Anims[LA_VAULT_34].frame_base;
        item->pos.y += hdif + STEP_L * 3;
        g_Lara.gun_status = LGS_HANDS_BUSY;
    } else if (
        !slope && hdif >= (-STEP_L * 7 - STEP_L / 2)
        && hdif <= (-STEP_L * 4 + STEP_L / 2)) {
        if (g_Rooms[item->room_num].flags & RF_SWAMP) {
            return false;
        }

        item->current_anim_state = LS_STOP;
        item->goal_anim_state = LS_UP_JUMP;
        item->anim_num = LA_STOP;
        item->frame_num = g_Anims[LA_STOP].frame_base;
        g_Lara.calc_fall_speed =
            -(int16_t)(phd_sqrt((int32_t)(-2 * GRAVITY * (hdif + 800))) + 3);
        Lara_Animate(item);
    } else if (
        g_Lara.climb_status && hdif <= (-STEP_L * 8 + STEP_L / 2)
        && g_Lara.water_status != LWS_WADE
        && coll->left_floor2 <= (-STEP_L * 8 + STEP_L / 2)
        && coll->right_floor2 <= (-STEP_L * 8)
        && coll->mid_ceiling <= (-STEP_L * 8 + STEP_L / 2 + LARA_HEIGHT)) {
        item->current_anim_state = LS_STOP;
        item->goal_anim_state = LS_UP_JUMP;
        item->anim_num = LA_STOP;
        item->frame_num = g_Anims[LA_STOP].frame_base;
        g_Lara.calc_fall_speed = -116;
        Lara_Animate(item);
    } else if (
        g_Lara.climb_status
        && (hdif < -STEP_L * 4 || coll->front_ceiling >= LARA_HEIGHT - STEP_L)
        && (coll->mid_ceiling <= -STEP_L * 5 + LARA_HEIGHT)) {
        ShiftItem(item, coll);
        if (Lara_TestClimbStance(item, coll)) {
            item->current_anim_state = LS_STOP;
            item->goal_anim_state = LS_CLIMB_STNC;
            item->anim_num = LA_STOP;
            item->frame_num = g_Anims[LA_STOP].frame_base;
            Lara_Animate(item);
            item->pos.y_rot = angle;
            g_Lara.gun_status = LGS_HANDS_BUSY;
            return true;
        }
        return false;
    } else {
        return false;
    }

    item->pos.y_rot = angle;
    ShiftItem(item, coll);
    return true;
}

void Lara_TestHang(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    enum DIRECTION dir = Lara_AngleToDirection(item->pos.y_rot);

    coll->bad_pos = NO_BAD_POS;
    coll->bad_neg = NO_BAD_NEG;
    coll->bad_ceiling = 0;
    Lara_GetCollisionInfo(item, coll);

    bool flag = coll->front_floor < 200;
    item->gravity_status = 0;
    item->fall_speed = 0;
    g_Lara.move_angle = item->pos.y_rot;

    switch (dir) {
    case DIR_NORTH:
        item->pos.z += 4;
        break;

    case DIR_EAST:
        item->pos.x += 4;
        break;

    case DIR_SOUTH:
        item->pos.z -= 4;
        break;

    case DIR_WEST:
        item->pos.x -= 4;
        break;
    }

    coll->bad_pos = NO_BAD_POS;
    coll->bad_neg = -LARA_STEP_UP_HEIGHT;
    coll->bad_ceiling = 0;
    Lara_GetCollisionInfo(item, coll);

    if (g_Lara.climb_status) {
        if (!(g_Input & IN_ACTION) || item->hit_points <= 0) {
            item->current_anim_state = LS_FORWARD_JUMP;
            item->goal_anim_state = LS_FORWARD_JUMP;
            item->anim_num = LA_FALL_DOWN;
            item->frame_num = g_Anims[LA_FALL_DOWN].frame_base;
            item->pos.y += 256;
            item->gravity_status = 1;
            item->speed = 2;
            item->fall_speed = 1;
            g_Lara.gun_status = LGS_ARMLESS;
            return;
        }

        if (!Lara_TestHangOnClimbWall(item, coll)) {
            item->pos.x = coll->old.x;
            item->pos.y = coll->old.y;
            item->pos.z = coll->old.z;
            item->current_anim_state = LS_HANG;
            item->goal_anim_state = LS_HANG;
            item->anim_num = LA_GRAB_LEDGE;
            item->frame_num = g_Anims[LA_GRAB_LEDGE].frame_base + 21;
            return;
        }

        if (item->anim_num == LA_GRAB_LEDGE
            && item->frame_num == g_Anims[LA_GRAB_LEDGE].frame_base + 21) {
            if (Lara_TestClimbStance(item, coll)) {
                item->goal_anim_state = LS_CLIMB_STNC;
            }
        }
        return;
    }

    if (!(g_Input & IN_ACTION) || item->hit_points <= 0
        || coll->front_floor > 0) {
        item->current_anim_state = LS_UP_JUMP;
        item->goal_anim_state = LS_UP_JUMP;
        item->anim_num = LA_STOP_HANG;
        item->frame_num = g_Anims[LA_STOP_HANG].frame_base + 9;

        int16_t *bounds = GetBoundsAccurate(item);
        item->pos.y += bounds[3];
        item->pos.x += coll->shift.x;
        item->pos.z += coll->shift.z;
        item->gravity_status = 1;
        item->speed = 2;
        item->fall_speed = 1;
        g_Lara.gun_status = LGS_ARMLESS;
        return;
    }

    int16_t *bounds = GetBoundsAccurate(item);
    int32_t hdif = coll->front_floor - bounds[2];

    if (ABS(coll->left_floor2 - coll->right_floor2) >= LARA_SLOPE_DIF
        || coll->mid_ceiling >= 0 || coll->coll_type != COLL_FRONT || flag
        || coll->hit_static || hdif < -LARA_SLOPE_DIF
        || hdif > LARA_SLOPE_DIF) {
        item->pos.x = coll->old.x;
        item->pos.y = coll->old.y;
        item->pos.z = coll->old.z;
        if (item->current_anim_state == LS_HANG_LEFT
            || item->current_anim_state == LS_HANG_RIGHT) {
            item->current_anim_state = LS_HANG;
            item->goal_anim_state = LS_HANG;
            item->anim_num = LA_GRAB_LEDGE;
            item->frame_num = g_Anims[LA_GRAB_LEDGE].frame_base + 21;
        }
        return;
    }

    switch (dir) {
    case DIR_NORTH:
    case DIR_SOUTH:
        item->pos.z += coll->shift.z;
        break;

    case DIR_EAST:
    case DIR_WEST:
        item->pos.x += coll->shift.x;
        break;
    }

    item->pos.y += hdif;
}

bool Lara_TestHangOnClimbWall(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (!g_Lara.climb_status || item->fall_speed < 0) {
        return false;
    }

    enum DIRECTION dir = Lara_AngleToDirection(item->pos.y_rot);
    switch (dir) {
    case DIR_NORTH:
    case DIR_SOUTH:
        item->pos.z += coll->shift.z;
        break;

    case DIR_EAST:
    case DIR_WEST:
        item->pos.x += coll->shift.x;
        break;
    }

    int32_t shift;
    int16_t *bounds = GetBoundsAccurate(item);

    if (!Lara_TestClimbPos(
            item, coll->radius, coll->radius, bounds[2], bounds[3] - bounds[2],
            &shift)) {
        return false;
    }

    if (!Lara_TestClimbPos(
            item, coll->radius, -coll->radius, bounds[2], bounds[3] - bounds[2],
            &shift)) {
        return false;
    }

    int32_t result = Lara_TestClimbPos(
        item, coll->radius, 0, bounds[2], bounds[3] - bounds[2], &shift);
    if (result == 0) {
        return false;
    } else if (result == 1) {
        return true;
    } else {
        item->pos.y += shift;
        return true;
    }
}

bool Lara_TestHangJump(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (!(g_Input & IN_ACTION) || g_Lara.gun_status != LGS_ARMLESS
        || coll->hit_static) {
        return false;
    }

    if (g_Lara.can_monkey_swing && coll->coll_type == COLL_TOP) {
        g_Lara.head_x_rot = 0;
        g_Lara.head_y_rot = 0;
        g_Lara.torso_x_rot = 0;
        g_Lara.torso_y_rot = 0;
        item->current_anim_state = LS_MONKEY_HANG;
        item->goal_anim_state = LS_MONKEY_HANG;
        item->anim_num = LA_GRAB_LEDGE_IN;
        item->frame_num = g_Anims[LA_GRAB_LEDGE_IN].frame_base;
        item->gravity_status = 0;
        item->speed = 0;
        item->fall_speed = 0;
        g_Lara.gun_status = LGS_HANDS_BUSY;
        return true;
    }

    if (coll->mid_ceiling > -LARA_STEP_UP_HEIGHT || coll->mid_floor < 200
        || coll->coll_type != COLL_FRONT) {
        return false;
    }

    int32_t edge;
    int32_t edge_catch = Lara_TestEdgeCatch(item, coll, &edge);
    if (!edge_catch
        || (edge_catch < 0 && !Lara_TestHangOnClimbWall(item, coll))) {
        return false;
    }

    PHD_ANGLE angle = Lara_SnapAngle(item->pos.y_rot, LARA_HANG_ANGLE);
    if (angle % DEG_90 != 0) {
        return false;
    }

    if (Lara_TestHangSwingIn(item, angle)) {
        g_Lara.head_x_rot = 0;
        g_Lara.head_y_rot = 0;
        g_Lara.torso_x_rot = 0;
        g_Lara.torso_y_rot = 0;
        item->current_anim_state = LS_MONKEY_HANG;
        item->goal_anim_state = LS_MONKEY_HANG;
        item->anim_num = LA_GRAB_LEDGE_IN;
        item->frame_num = g_Anims[LA_GRAB_LEDGE_IN].frame_base;
    } else {
        item->current_anim_state = LS_HANG;
        item->goal_anim_state = LS_HANG;
        item->anim_num = LA_GRAB_LEDGE;
        item->frame_num = g_Anims[LA_GRAB_LEDGE].frame_base;
    }

    int16_t *bounds = GetBoundsAccurate(item);
    if (edge_catch > 0) {
        item->pos.y += coll->front_floor - bounds[2];
        item->pos.x += coll->shift.x;
        item->pos.z += coll->shift.z;
    } else {
        item->pos.y = edge - bounds[2];
    }

    item->pos.y_rot = angle;
    item->gravity_status = 1;
    item->speed = 2;
    item->fall_speed = 1;
    g_Lara.gun_status = LGS_HANDS_BUSY;
    return true;
}

bool Lara_TestHangSwingIn(struct ITEM_INFO *item, PHD_ANGLE angle)
{
    int32_t x = item->pos.x;
    int32_t y = item->pos.y;
    int32_t z = item->pos.z;
    int16_t room_num = item->room_num;

    switch (angle) {
    case 0:
        z += 256;
        break;
    case DEG_90:
        x += 256;
        break;
    case -DEG_90:
        x -= 256;
        break;
    case -DEG_180:
        z -= 256;
        break;
    }

    struct FLOOR_INFO *floor = GetFloor(x, y, z, &room_num);
    int32_t h = GetHeight(floor, x, y, z);
    int32_t c = GetCeiling(floor, x, y, z);
    return h != NO_HEIGHT && h - y > 0 && c - y < -400 && y - 819 - c > -72;
}

bool Lara_TestClimbStance(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    int32_t shift_r;
    int32_t result_r = Lara_TestClimbPos(
        item, coll->radius, coll->radius + LARA_CLIMB_WIDTH_R, -700, STEP_L * 2,
        &shift_r);
    if (result_r != 1) {
        return false;
    }

    int32_t shift_l;
    int32_t result_l = Lara_TestClimbPos(
        item, coll->radius, -coll->radius - LARA_CLIMB_WIDTH_L, -700,
        STEP_L * 2, &shift_l);
    if (result_l != 1) {
        return false;
    }

    if (shift_r) {
        if (shift_l) {
            if ((shift_l < 0) != (shift_r < 0)) {
                return false;
            }

            if (shift_r < 0 && shift_l < shift_r) {
                shift_r = shift_l;
            } else if (shift_r > 0 && shift_l > shift_r) {
                shift_r = shift_l;
            }
        }

        item->pos.y += shift_r;
    } else if (shift_l) {
        item->pos.y += shift_l;
    }

    return true;
}

bool Lara_TestSlide(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (ABS(coll->tilt_x) <= 2 && ABS(coll->tilt_z) <= 2) {
        return false;
    }

    PHD_ANGLE angle = 0;
    if (coll->tilt_x > 2) {
        angle = -DEG_90;
    } else if (coll->tilt_x < -2) {
        angle = DEG_90;
    }

    if (coll->tilt_z > 2 && coll->tilt_z > ABS(coll->tilt_x)) {
        angle = DEG_180;
    } else if (coll->tilt_z < -2 && -coll->tilt_z > ABS(coll->tilt_x)) {
        angle = 0;
    }

    ShiftItem(item, coll);

    PHD_ANGLE angle_diff = angle - item->pos.y_rot;
    if (angle_diff >= -DEG_90 && angle_diff <= DEG_90) {
        if (item->current_anim_state != LS_SLIDE || m_OldSlopeAngle != angle) {
            item->current_anim_state = LS_SLIDE;
            item->goal_anim_state = LS_SLIDE;
            item->anim_num = LA_SLIDE;
            item->frame_num = g_Anims[LA_SLIDE].frame_base;
            item->pos.y_rot = angle;
            g_Lara.move_angle = angle;
            m_OldSlopeAngle = angle;
        }
    } else {
        if (item->current_anim_state != LS_SLIDE_BACK
            || m_OldSlopeAngle != angle) {
            item->current_anim_state = LS_SLIDE_BACK;
            item->goal_anim_state = LS_SLIDE_BACK;
            item->anim_num = LA_SLIDE_BACK;
            item->frame_num = g_Anims[LA_SLIDE_BACK].frame_base;
            item->pos.y_rot = angle + DEG_180;
            g_Lara.move_angle = angle;
            m_OldSlopeAngle = angle;
        }
    }

    return true;
}

bool Lara_LandedBad(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    int32_t old_y = item->pos.y;
    int16_t room_num = item->room_num;
    struct FLOOR_INFO *floor =
        GetFloor(item->pos.x, item->pos.y, item->pos.z, &room_num);
    int32_t height =
        GetHeight(floor, item->pos.x, item->pos.y - LARA_HEIGHT, item->pos.z);
    item->floor = height;
    item->pos.y = height;
    if (ABS(old_y - item->pos.y) > STEP_L) {
        item->pos.y = old_y;
    }

    g_LaraOnPad = 0;
    TestTriggers(g_TriggerIndex, 0);
    if (!g_LaraOnPad) {
        g_LaraItem->item_flags[1] = 0;
    }
    item->pos.y = old_y;

    int32_t land_speed = item->fall_speed - LARA_FALL_DAMAGE_START;
    if (land_speed <= 0) {
        return false;
    }

    if (land_speed > LARA_FALL_DAMAGE_LENGTH) {
        item->hit_points = -1;
    } else {
        item->hit_points -= (LARA_HIT_POINTS * land_speed * land_speed)
            / (LARA_FALL_DAMAGE_LENGTH * LARA_FALL_DAMAGE_LENGTH);
    }

    return item->hit_points <= 0;
}

int32_t Lara_TestWall(
    struct ITEM_INFO *item, int32_t front, int32_t right, int32_t down)
{
    int32_t x = item->pos.x;
    int32_t y = item->pos.y + down;
    int32_t z = item->pos.z;
    int16_t room_num = item->room_num;

    enum DIRECTION dir = Lara_AngleToDirection(item->pos.y_rot);
    switch (dir) {
    case DIR_NORTH:
        x -= right;
        break;
    case DIR_EAST:
        z -= right;
        break;
    case DIR_SOUTH:
        x += right;
        break;
    case DIR_WEST:
        z += right;
        break;
    }

    GetFloor(x, y, z, &room_num);

    switch (dir) {
    case DIR_NORTH:
        z += front;
        break;
    case DIR_EAST:
        x += front;
        break;
    case DIR_SOUTH:
        z -= front;
        break;
    case DIR_WEST:
        x -= front;
        break;
    }

    struct FLOOR_INFO *floor = GetFloor(x, y, z, &room_num);
    int32_t h = GetHeight(floor, x, y, z);
    int32_t c = GetCeiling(floor, x, y, z);

    if (h == NO_HEIGHT) {
        return 1;
    }
    if (h - y <= 0 || c - y >= 0) {
        return 2;
    }
    return 0;
}

int16_t Lara_FloorFront(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t dist)
{
    int32_t x = item->pos.x + ((dist * phd_sin(ang)) >> W2V_SHIFT);
    int32_t y = item->pos.y - LARA_HEIGHT;
    int32_t z = item->pos.z + ((dist * phd_cos(ang)) >> W2V_SHIFT);
    int16_t room_num = item->room_num;

    struct FLOOR_INFO *floor = GetFloor(x, y, z, &room_num);
    int32_t height = GetHeight(floor, x, y, z);

    if (height != NO_HEIGHT) {
        height -= item->pos.y;
    }

    return height;
}

void Lara_MonkeySwingFall(struct ITEM_INFO *item)
{
    item->goal_anim_state = LS_UP_JUMP;
    item->current_anim_state = LS_UP_JUMP;
    item->anim_num = LA_STOP_HANG;
    item->frame_num = g_Anims[LA_STOP_HANG].frame_base + 9;
    item->gravity_status = 1;
    item->speed = 2;
    item->fall_speed = 1;
    item->pos.y += STEP_L;
    g_Lara.gun_status = LGS_ARMLESS;
}

int16_t Lara_CeilingFront(struct ITEM_INFO *item, PHD_ANGLE ang, int32_t dist)
{
    int32_t x = item->pos.x + ((dist * phd_sin(ang)) >> W2V_SHIFT);
    int32_t y = item->pos.y - LARA_HEIGHT;
    int32_t z = item->pos.z + ((dist * phd_cos(ang)) >> W2V_SHIFT);
    int16_t room_num = item->room_num;

    struct FLOOR_INFO *floor = GetFloor(x, y, z, &room_num);
    int32_t height = GetCeiling(floor, x, y, z);

    if (height != NO_HEIGHT) {
        height -= item->pos.y - LARA_HEIGHT;
    }

    return height;
}

bool Lara_Fallen(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (coll->mid_floor <= LARA_STEP_UP_HEIGHT
        || g_Lara.water_status == LWS_WADE) {
        return false;
    }

    item->gravity_status = 1;
    item->fall_speed = 0;
    item->current_anim_state = LS_FORWARD_JUMP;
    item->goal_anim_state = LS_FORWARD_JUMP;
    item->anim_num = LA_FALL_DOWN;
    item->frame_num = g_Anims[LA_FALL_DOWN].frame_base;
    return true;
}

int32_t Lara_TestEdgeCatch(
    struct ITEM_INFO *item, struct COLL_INFO *coll, int32_t *edge)
{
    int16_t *bounds = GetBoundsAccurate(item);
    int32_t hdif = coll->front_floor - bounds[2];

    if ((hdif < 0 && hdif + item->fall_speed < 0)
        || (hdif > 0 && hdif + item->fall_speed > 0)) {
        hdif = item->pos.y + bounds[2];

        if (!(((hdif + item->fall_speed) ^ hdif) & ~(STEP_L - 1))) {
            return 0;
        }

        if (item->fall_speed > 0) {
            *edge = (hdif + item->fall_speed) & ~(STEP_L - 1);
        } else {
            *edge = hdif & ~(STEP_L - 1);
        }

        return -1;
    }

    return ABS(coll->left_floor2 - coll->right_floor2) < LARA_SLOPE_DIF ? 1 : 0;
}

int32_t Lara_TestClimb(
    int32_t x, int32_t y, int32_t z, int32_t x_front, int32_t z_front,
    int32_t item_height, int16_t item_room, int32_t *shift)
{
    bool hang = true;

    *shift = 0;
    if (!g_Lara.climb_status) {
        return 0;
    }

    int16_t room_num = item_room;
    struct FLOOR_INFO *floor = GetFloor(x, y - STEP_L / 2, z, &room_num);
    int32_t height = GetHeight(floor, x, y, z);
    if (height == NO_HEIGHT) {
        return 0;
    }

    height -= y + item_height + STEP_L / 2;
    if (height < -CLIMB_SHIFT) {
        return 0;
    } else if (height < 0) {
        *shift = height;
    }

    int32_t ceiling = GetCeiling(floor, x, y, z) - y;
    if (ceiling > CLIMB_SHIFT) {
        return 0;
    } else if (ceiling > 0) {
        if (*shift) {
            return 0;
        }
        *shift = ceiling;
    }

    if (item_height + height < CLIMB_HANG) {
        hang = false;
    }

    floor = GetFloor(x + x_front, y, z + z_front, &room_num);
    height = GetHeight(floor, x + x_front, y, z + z_front);
    if (height != NO_HEIGHT) {
        height -= y;
    }

    if (height > CLIMB_SHIFT) {
        ceiling = GetCeiling(floor, x + x_front, y, z + z_front) - y;
        if (ceiling >= CLIMB_HEIGHT) {
            return 1;
        } else if (ceiling > CLIMB_HEIGHT - CLIMB_SHIFT) {
            if (*shift > 0) {
                return hang ? -1 : 0;
            }
            *shift = ceiling - CLIMB_HEIGHT;
            return 1;
        } else if (ceiling > 0) {
            return hang ? -1 : 0;
        } else if (ceiling > -CLIMB_SHIFT && hang && *shift <= 0) {
            if (*shift > ceiling) {
                *shift = ceiling;
            }
            return -1;
        } else {
            return 0;
        }
    } else if (height > 0) {
        if (*shift < 0) {
            return 0;
        }
        if (height > *shift) {
            *shift = height;
        }
    }

    room_num = item_room;
    floor = GetFloor(x, y + item_height, z, &room_num);
    floor = GetFloor(x + x_front, y + item_height, z + z_front, &room_num);
    ceiling = GetCeiling(floor, x + x_front, y + item_height, z + z_front);
    if (ceiling == NO_HEIGHT) {
        return 1;
    }

    ceiling -= y;
    if (ceiling <= height) {
        return 1;
    }

    if (ceiling >= CLIMB_HEIGHT) {
        return 1;
    } else if (ceiling > CLIMB_HEIGHT - CLIMB_SHIFT && *shift <= 0) {
        *shift = ceiling - CLIMB_HEIGHT;
        return 1;
    } else {
        return hang ? -1 : 0;
    }
}

int32_t Lara_TestClimbUpPos(
    struct ITEM_INFO *item, int32_t front, int32_t right, int32_t *shift,
    int32_t *ledge)
{
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t x_front = 0;
    int32_t z_front = 0;

    y = item->pos.y - CLIMB_HEIGHT - STEP_L;

    switch ((uint16_t)(item->pos.y_rot + DEG_45) / DEG_90) {
    case DIR_NORTH:
        z = item->pos.z + front;
        x = item->pos.x + right;
        z_front = 4;
        break;
    case DIR_EAST:
        x = item->pos.x + front;
        z = item->pos.z - right;
        x_front = 4;
        break;
    case DIR_SOUTH:
        z = item->pos.z - front;
        x = item->pos.x - right;
        z_front = -4;
        break;
    default:
        x = item->pos.x - front;
        z = item->pos.z + right;
        x_front = -4;
        break;
    }

    *shift = 0;

    int16_t room_num = item->room_num;
    struct FLOOR_INFO *floor = GetFloor(x, y, z, &room_num);
    int32_t ceiling = GetCeiling(floor, x, y, z) - (y - STEP_L);

    if (ceiling > CLIMB_SHIFT) {
        return 0;
    } else if (ceiling > 0) {
        *shift = ceiling;
    }

    floor = GetFloor(x + x_front, y, z + z_front, &room_num);
    int32_t height = GetHeight(floor, x + x_front, y, z + z_front);
    if (height == NO_HEIGHT) {
        *ledge = NO_HEIGHT;
        return 1;
    }

    height -= y;
    *ledge = height;

    if (height > STEP_L / 2) {
        ceiling = GetCeiling(floor, x + x_front, y, z + z_front) - y;
        if (ceiling >= CLIMB_HEIGHT) {
            return 1;
        } else if (height - ceiling > LARA_HEIGHT) {
            *shift = height;
            return -1;
        } else {
            return 0;
        }
    } else if (height > 0 && height > *shift) {
        *shift = height;
    }

    room_num = item->room_num;
    floor = GetFloor(x, y + CLIMB_HEIGHT, z, &room_num);
    floor = GetFloor(x + x_front, y + CLIMB_HEIGHT, z + z_front, &room_num);
    ceiling = GetCeiling(floor, x + x_front, y + CLIMB_HEIGHT, z + z_front) - y;
    if (ceiling <= height) {
        return 1;
    }

    if (ceiling >= CLIMB_HEIGHT) {
        return 1;
    }

    return 0;
}

int32_t Lara_TestClimbPos(
    struct ITEM_INFO *item, int32_t front, int32_t right, int32_t origin,
    int32_t height, int32_t *shift)
{
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t x_front = 0;
    int32_t z_front = 0;

    y = item->pos.y + origin;

    switch ((uint16_t)(item->pos.y_rot + DEG_45) / DEG_90) {
    case DIR_NORTH:
        z = item->pos.z + front;
        x = item->pos.x + right;
        z_front = 4;
        break;
    case DIR_EAST:
        x = item->pos.x + front;
        z = item->pos.z - right;
        x_front = 4;
        break;
    case DIR_SOUTH:
        z = item->pos.z - front;
        x = item->pos.x - right;
        z_front = -4;
        break;
    default:
        x = item->pos.x - front;
        z = item->pos.z + right;
        x_front = -4;
        break;
    }

    return Lara_TestClimb(
        x, y, z, x_front, z_front, height, item->room_num, shift);
}
