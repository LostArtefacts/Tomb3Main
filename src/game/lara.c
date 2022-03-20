#include "game/lara.h"

#include "global/const.h"
#include "global/vars.h"

void Lara_AsForwardJump(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->goal_anim_state == AS_SWANDIVE
        || item->goal_anim_state == AS_REACH) {
        item->goal_anim_state = AS_FORWARDJUMP;
    }
    if (item->goal_anim_state != AS_DEATH && item->goal_anim_state != AS_STOP
        && item->goal_anim_state != AS_RUN) {
        if ((g_Input & IN_ACTION) && !g_Lara.gun_status) {
            item->goal_anim_state = AS_REACH;
        }
        if ((g_Input & IN_ROLL) || (g_Input & IN_BACK)) {
            item->goal_anim_state = AS_TWIST;
        }
        if ((g_Input & IN_SLOW) && !g_Lara.gun_status) {
            item->goal_anim_state = AS_SWANDIVE;
        }
        if (item->fallspeed > LARA_FASTFALL_SPEED) {
            item->goal_anim_state = AS_FASTFALL;
        }
    }
    if (g_Input & IN_LEFT) {
        g_Lara.target_angles[1] -= LARA_TURN_UNDO;
        if (g_Lara.target_angles[1] < -546) {
            g_Lara.target_angles[1] = -546;
        }
    } else if (g_Input & IN_RIGHT) {
        g_Lara.target_angles[1] += LARA_TURN_UNDO;
        if (g_Lara.target_angles[1] > 546) {
            g_Lara.target_angles[1] = 546;
        }
    }
}
