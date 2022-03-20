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
        if ((g_Input & IN_ACTION) && g_Lara.gun_status == LG_ARMLESS) {
            item->goal_anim_state = AS_REACH;
        }
        if ((g_Input & IN_ROLL) || (g_Input & IN_BACK)) {
            item->goal_anim_state = AS_TWIST;
        }
        if ((g_Input & IN_SLOW) && g_Lara.gun_status == LG_ARMLESS) {
            item->goal_anim_state = AS_SWANDIVE;
        }
        if (item->fallspeed > LARA_FASTFALL_SPEED) {
            item->goal_anim_state = AS_FASTFALL;
        }
    }

    // TODO: g_Lara.target_angles[1] should be turn_rate
    if (g_Input & IN_LEFT) {
        g_Lara.target_angles[1] -= LARA_TURN_RATE;
        if (g_Lara.target_angles[1] < -546) {
            g_Lara.target_angles[1] = -546;
        }
    } else if (g_Input & IN_RIGHT) {
        g_Lara.target_angles[1] += LARA_TURN_RATE;
        if (g_Lara.target_angles[1] > 546) {
            g_Lara.target_angles[1] = 546;
        }
    }
}

void Lara_AsWalk(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    if (item->hit_points <= 0) {
        item->goal_anim_state = AS_STOP;
        return;
    }

    // TODO: g_Lara.target_angles[1] should be turn_rate
    if (g_Input & IN_LEFT) {
        g_Lara.target_angles[1] -= LARA_TURN_RATE;
        if (g_Lara.target_angles[1] < -LARA_SLOW_TURN)
            g_Lara.target_angles[1] = -LARA_SLOW_TURN;
    } else if (g_Input & IN_RIGHT) {
        g_Lara.target_angles[1] += LARA_TURN_RATE;
        if (g_Lara.target_angles[1] > LARA_SLOW_TURN)
            g_Lara.target_angles[1] = LARA_SLOW_TURN;
    }

    if (g_Input & IN_FORWARD) {
        if (g_Lara.water_status == LWS_WADE) {
            item->goal_anim_state = AS_WADE;
        } else if (g_Input & IN_SLOW) {
            item->goal_anim_state = AS_WALK;
        } else {
            item->goal_anim_state = AS_RUN;
        }
    } else {
        item->goal_anim_state = AS_STOP;
    }
}
