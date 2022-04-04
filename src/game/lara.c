#include "game/lara.h"

#include "global/const.h"
#include "global/stubs.h"
#include "global/vars.h"
#include "util.h"

static PHD_ANGLE m_OldSlopeAngle = 1;

static PHD_ANGLE Lara_SnapAngle(PHD_ANGLE angle, PHD_ANGLE snap);

static PHD_ANGLE Lara_SnapAngle(PHD_ANGLE angle, PHD_ANGLE snap)
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

void Lara_GetCollisionInfo(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->facing = g_Lara.move_angle;
    GetCollisionInfo(
        coll, item->pos.x, item->pos.y, item->pos.z, item->room_num,
        LARA_HEIGHT);
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

void Lara_AboveWater(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->old.x = item->pos.x;
    coll->old.y = item->pos.y;
    coll->old.z = item->pos.z;
    coll->old_anim_state = item->current_anim_state;
    coll->old_anim_num = item->anim_num;
    coll->old_frame_num = item->frame_num;
    coll->radius = LARA_RADIUS;
    coll->trigger = NULL;
    coll->slopes_are_walls = 0;
    coll->slopes_are_pits = 0;
    coll->lava_is_pit = 0;
    coll->enable_baddie_push = 1;
    coll->enable_spaz = 1;

    if ((g_Input & IN_LOOK) && !g_Lara.extra_anim && g_Lara.look) {
        Lara_LookLeftRight();
    } else {
        Lara_ResetLook();
    }

    g_Lara.look = 1;

    if (g_Lara.skidoo != NO_ITEM) {
        switch (g_Items[g_Lara.skidoo].object_num) {
        case O_KAYAK:
            if (Kayak_Control()) {
                return;
            }
            break;

        case O_QUADBIKE:
            if (QuadBike_Control()) {
                return;
            }
            break;

        case O_UPV:
            if (UPV_Control()) {
                return;
            }
            break;

        case O_BIG_GUN:
            if (BigGun_Control(coll)) {
                return;
            }
            break;

        case O_MINECART:
            if (MineCart_Control()) {
                return;
            }
            break;

        default:
            Lara_Gun();
            return;
        }
    }

    if (g_Lara.extra_anim) {
        g_LaraExtraControlRoutines[item->current_anim_state](item, coll);
    } else {
        g_LaraControlRoutines[item->current_anim_state](item, coll);
    }

    if (item->pos.z_rot < -LARA_LEAN_UNDO) {
        item->pos.z_rot += LARA_LEAN_UNDO;
    } else if (item->pos.z_rot > LARA_LEAN_UNDO) {
        item->pos.z_rot -= LARA_LEAN_UNDO;
    } else {
        item->pos.z_rot = 0;
    }

    if (g_Lara.turn_rate < -LARA_TURN_UNDO) {
        g_Lara.turn_rate += LARA_TURN_UNDO;
    } else if (g_Lara.turn_rate > LARA_TURN_UNDO) {
        g_Lara.turn_rate -= LARA_TURN_UNDO;
    } else {
        g_Lara.turn_rate = 0;
    }
    item->pos.y_rot += g_Lara.turn_rate;

    Lara_Animate(item);

    if (!g_Lara.extra_anim) {
        LaraBaddieCollision(item, coll);
        if (g_Lara.skidoo == NO_ITEM) {
            g_LaraCollisionRoutines[item->current_anim_state](item, coll);
        }
    }

    UpdateLaraRoom(item, -LARA_HEIGHT / 2);

    Lara_Gun();

    g_LaraOnPad = 0;
    TestTriggers(coll->trigger, 0);
    if (!g_LaraOnPad) {
        g_LaraItem->item_flags[1] = 0;
    }
}
