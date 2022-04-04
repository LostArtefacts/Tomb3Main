#include "game/lara.h"

#include "global/const.h"
#include "global/stubs.h"
#include "global/vars.h"

void Lara_Col_Duck(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    item->gravity_status = 0;
    item->fall_speed = 0;
    g_Lara.move_angle = item->pos.y_rot;
    coll->facing = item->pos.y_rot;
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
