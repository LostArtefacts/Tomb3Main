#include "game/lara.h"

#include "global/const.h"
#include "global/stubs.h"
#include "global/vars.h"
#include "util.h"

#define LARA_FALL_DAMAGE_START 140
#define LARA_FALL_DAMAGE_LENGTH 14

static PHD_ANGLE m_OldSlopeAngle = 1;
static bool m_JumpOK = true;

static PHD_ANGLE Lara_SnapAngle(PHD_ANGLE angle, PHD_ANGLE snap);
static enum DIRECTION Lara_AngleToDirection(PHD_ANGLE angle);
static void Lara_State_FastFallFriction(struct ITEM_INFO *item);

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

static enum DIRECTION Lara_AngleToDirection(PHD_ANGLE angle)
{
    return (enum DIRECTION)(uint16_t)(angle + DEG_45) / DEG_90;
}

static void Lara_State_FastFallFriction(struct ITEM_INFO *item)
{
    item->speed = (item->speed * 95) / 100;
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
    if (!(g_Input & IN_ACTION) || g_Lara.gun_status != LG_ARMLESS
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
        g_Lara.gun_status = LG_HANDSBUSY;
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
        g_Lara.gun_status = LG_HANDSBUSY;
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
        && coll->mid_ceiling <= (-STEP_L * 8 + STEP_L / 2 + LARA_HITE)) {
        item->current_anim_state = LS_STOP;
        item->goal_anim_state = LS_UP_JUMP;
        item->anim_num = LA_STOP;
        item->frame_num = g_Anims[LA_STOP].frame_base;
        g_Lara.calc_fall_speed = -116;
        Lara_Animate(item);
    } else if (
        g_Lara.climb_status
        && (hdif < -STEP_L * 4 || coll->front_ceiling >= LARA_HITE - STEP_L)
        && (coll->mid_ceiling <= -STEP_L * 5 + LARA_HITE)) {
        ShiftItem(item, coll);
        if (Lara_TestClimbStance(item, coll)) {
            item->current_anim_state = LS_STOP;
            item->goal_anim_state = LS_CLIMB_STNC;
            item->anim_num = LA_STOP;
            item->frame_num = g_Anims[LA_STOP].frame_base;
            Lara_Animate(item);
            item->pos.y_rot = angle;
            g_Lara.gun_status = LG_HANDSBUSY;
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
        coll, item->pos.x, item->pos.y, item->pos.z, item->room_num, LARA_HITE);
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
            g_Lara.gun_status = LG_ARMLESS;
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
        g_Lara.gun_status = LG_ARMLESS;
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
    if (!(g_Input & IN_ACTION) || g_Lara.gun_status != LG_ARMLESS
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
        g_Lara.gun_status = LG_HANDSBUSY;
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
    g_Lara.gun_status = LG_HANDSBUSY;
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

    UpdateLaraRoom(item, -LARA_HITE / 2);

    Lara_Gun();

    g_LaraOnPad = 0;
    TestTriggers(coll->trigger, 0);
    if (!g_LaraOnPad) {
        g_LaraItem->item_flags[1] = 0;
    }
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

    if (g_Input & IN_FORWARD && g_Input & IN_BACK
        && g_Lara.gun_status == LG_ARMLESS
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
        g_Lara.gun_status = LG_HANDSBUSY;
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
        CLAMPL(item->pos.z_rot, -LARA_LEAN_MAX);
    } else if (g_Input & IN_RIGHT) {
        g_Lara.turn_rate += LARA_TURN_RATE;
        item->pos.z_rot += LARA_LEAN_RATE;
        CLAMPG(g_Lara.turn_rate, +LARA_FAST_TURN);
        CLAMPG(item->pos.z_rot, +LARA_LEAN_MAX);
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
