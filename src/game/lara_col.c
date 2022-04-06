#include "game/lara.h"

#include "global/const.h"
#include "global/stubs.h"
#include "global/vars.h"

void Lara_Col_Duck(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    item->gravity_status = 0;
    item->fall_speed = 0;
    g_Lara.move_angle = item->pos.y_rot;
    coll->facing = g_Lara.move_angle;
    coll->radius = LARA_DUCK_RADIUS;
    coll->bad_pos = LARA_STEP_UP_HEIGHT;
    coll->bad_neg = -LARA_STEP_UP_HEIGHT;
    coll->bad_ceiling = 0;
    coll->slopes_are_walls = 1;

    GetCollisionInfo(
        coll, item->pos.x, item->pos.y, item->pos.z, item->room_num,
        LARA_DUCK_HEIGHT);

    if (Lara_Fallen(item, coll)) {
        g_Lara.gun_status = LGS_ARMLESS;
        return;
    }

    g_Lara.keep_ducked = coll->mid_ceiling >= -(LARA_HEIGHT - LARA_DUCK_HEIGHT);

    ShiftItem(item, coll);
    item->pos.y += coll->mid_floor;

    if ((!(g_Input & IN_DUCK) || g_Lara.water_status == LWS_WADE)
        && !g_Lara.keep_ducked && item->anim_num == LA_DUCK_BREATHE) {
        item->goal_anim_state = LS_STOP;
    }
}

void Lara_Col_AllFours(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    item->gravity_status = 0;
    item->fall_speed = 0;

    if (item->goal_anim_state == LS_CRAWL_TO_HANG) {
        return;
    }

    g_Lara.move_angle = item->pos.y_rot;
    coll->facing = g_Lara.move_angle;
    coll->radius = LARA_DUCK_RADIUS;
    coll->bad_pos = +(STEP_L - 1);
    coll->bad_neg = -(STEP_L - 1);
    coll->bad_ceiling = LARA_DUCK_HEIGHT;
    coll->slopes_are_walls = 1;
    coll->slopes_are_pits = 1;

    GetCollisionInfo(
        coll, item->pos.x, item->pos.y, item->pos.z, item->room_num,
        LARA_DUCK_HEIGHT);

    if (Lara_Fallen(item, coll)) {
        g_Lara.gun_status = LGS_ARMLESS;
        return;
    }

    g_Lara.keep_ducked = coll->mid_ceiling >= -(LARA_HEIGHT - LARA_DUCK_HEIGHT);

    ShiftItem(item, coll);
    item->pos.y += coll->mid_floor;

    if ((!(g_Input & IN_DUCK) && !g_Lara.keep_ducked) || (g_Input & IN_DRAW)) {
        item->goal_anim_state = LS_DUCK;
        return;
    }

    if (item->anim_num != LA_ALL_FOURS && item->anim_num != LA_ALL_FOURS_2) {
        return;
    }

    if (g_Input & IN_FORWARD) {
        int16_t height = Lara_FloorFront(item, item->pos.y_rot, 256);
        if (height < +(STEP_L - 1) && height > -(STEP_L - 1)
            && g_HeightType != HT_BIG_SLOPE) {
            item->goal_anim_state = LS_CRAWL;
        }
    } else if (g_Input & IN_BACK) {
        int16_t height = Lara_CeilingFront(item, item->pos.y_rot, -300);
        if (height == NO_HEIGHT || height > 256) {
            return;
        }

        height = Lara_FloorFront(item, item->pos.y_rot, -300);
        if (height < +(STEP_L - 1) && height > -(STEP_L - 1)
            && g_HeightType != HT_BIG_SLOPE) {
            item->goal_anim_state = LS_CRAWL_BACK;
        } else if (
            g_Input & IN_ACTION && height > 768
            && !GetStaticObjects(
                item, item->pos.y_rot + 0x8000, 512, 50, 300)) {

            enum DIRECTION dir = Lara_AngleToDirection(item->pos.y_rot);
            switch (dir) {
            case DIR_NORTH:
                item->pos.z = (item->pos.z & ~(WALL_L - 1)) + 225;
                item->pos.y_rot = 0;
                break;
            case DIR_EAST:
                item->pos.x = (item->pos.x & ~(WALL_L - 1)) + 225;
                item->pos.y_rot = DEG_90;
                break;
            case DIR_SOUTH:
                item->pos.z = (item->pos.z | (WALL_L - 1)) - 225;
                item->pos.y_rot = DEG_180;
                break;
            case DIR_WEST:
                item->pos.x = (item->pos.x | (WALL_L - 1)) - 225;
                item->pos.y_rot = DEG_270;
                break;
            }
            item->goal_anim_state = LS_CRAWL_TO_HANG;
        }
    } else if (g_Input & IN_LEFT) {
        item->current_anim_state = LS_ALL_FOURS_TURN_L;
        item->goal_anim_state = LS_ALL_FOURS_TURN_L;
        item->anim_num = LA_ALL_FOURS_TURN_L;
        item->frame_num = g_Anims[LA_ALL_FOURS_TURN_L].frame_base;
    } else if (g_Input & IN_RIGHT) {
        item->current_anim_state = LS_ALL_FOURS_TURN_R;
        item->goal_anim_state = LS_ALL_FOURS_TURN_R;
        item->anim_num = LA_ALL_FOURS_TURN_R;
        item->frame_num = g_Anims[LA_ALL_FOURS_TURN_R].frame_base;
    }
}

void Lara_Col_AllFoursTurnLR(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    GetCollisionInfo(
        coll, item->pos.x, item->pos.y, item->pos.z, item->room_num,
        LARA_DUCK_HEIGHT);
}

void Lara_Col_Crawl(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    item->gravity_status = 0;
    item->fall_speed = 0;

    g_Lara.move_angle = item->pos.y_rot;
    coll->facing = g_Lara.move_angle;
    coll->radius = LARA_DUCK_RADIUS;
    coll->bad_pos = +(STEP_L - 1);
    coll->bad_neg = -(STEP_L - 1);
    coll->bad_ceiling = LARA_DUCK_HEIGHT;
    coll->slopes_are_walls = 1;
    coll->slopes_are_pits = 1;

    GetCollisionInfo(
        coll, item->pos.x, item->pos.y, item->pos.z, item->room_num,
        LARA_DUCK_HEIGHT);

    if (Lara_DeflectEdgeDuck(item, coll)) {
        item->current_anim_state = LS_ALL_FOURS;
        item->goal_anim_state = LS_ALL_FOURS;
        if (item->anim_num != LA_ALL_FOURS) {
            item->anim_num = LA_ALL_FOURS;
            item->frame_num = g_Anims[LA_ALL_FOURS].frame_base;
        }
    } else if (Lara_Fallen(item, coll)) {
        g_Lara.gun_status = LGS_ARMLESS;
    } else {
        ShiftItem(item, coll);
        item->pos.y += coll->mid_floor;
    }
}

void Lara_Col_CrawlB(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    item->fall_speed = 0;
    item->gravity_status = 0;

    g_Lara.move_angle = item->pos.y_rot + DEG_180;
    coll->facing = g_Lara.move_angle;
    coll->radius = LARA_CRAWL_RADIUS;
    coll->bad_pos = STEP_L - 1;
    coll->bad_neg = -(STEP_L - 1);
    coll->bad_ceiling = LARA_DUCK_HEIGHT;
    coll->slopes_are_walls = 1;
    coll->slopes_are_pits = 1;

    GetCollisionInfo(
        coll, item->pos.x, item->pos.y, item->pos.z, item->room_num,
        LARA_DUCK_HEIGHT);

    if (Lara_DeflectEdgeDuck(item, coll)) {
        item->current_anim_state = LS_ALL_FOURS;
        item->goal_anim_state = LS_ALL_FOURS;
        if (item->anim_num != LA_ALL_FOURS) {
            item->anim_num = LA_ALL_FOURS;
            item->frame_num = g_Anims[LA_ALL_FOURS].frame_base;
        }
    } else if (Lara_Fallen(item, coll)) {
        g_Lara.gun_status = LGS_ARMLESS;
    } else {
        ShiftItem(item, coll);
        item->pos.y += coll->mid_floor;
        g_Lara.move_angle = item->pos.y_rot;
    }
}

void Lara_Col_Crawl2Hang(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->anim_num != 302) {
        return;
    }

    item->fall_speed = 512;
    item->pos.y |= (STEP_L - 1);

    g_Lara.move_angle = item->pos.y_rot;
    coll->facing = g_Lara.move_angle;
    coll->bad_pos = NO_BAD_POS;
    coll->bad_neg = -LARA_STEP_UP_HEIGHT;
    coll->bad_ceiling = BAD_JUMP_CEILING;

    GetCollisionInfo(
        coll, item->pos.x, item->pos.y, item->pos.z, item->room_num, 870);

    int32_t edge;
    int32_t edge_catch = Lara_TestEdgeCatch(item, coll, &edge);
    if (!edge_catch
        || (edge_catch < 0 && !Lara_TestHangOnClimbWall(item, coll))) {
        return;
    }

    PHD_ANGLE angle = Lara_SnapAngle(item->pos.y_rot, LARA_HANG_ANGLE);
    if (angle % DEG_90 != 0) {
        return;
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
}
