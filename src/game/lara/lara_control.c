#include "game/lara/lara_control.h"

#include "game/lara/lara_look.h"
#include "global/const.h"
#include "global/stubs.h"
#include "global/vars.h"

void Lara_HandleAboveWater(struct ITEM_INFO *item, struct COLL_INFO *coll)
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
            Gun_Control();
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
        Lara_BaddieCollision(item, coll);
        if (g_Lara.skidoo == NO_ITEM) {
            g_LaraCollisionRoutines[item->current_anim_state](item, coll);
        }
    }

    Item_UpdateRoom(item, -LARA_HEIGHT / 2);

    Gun_Control();

    g_LaraOnPad = 0;
    Room_TestTriggers(coll->trigger, 0);
    if (!g_LaraOnPad) {
        g_LaraItem->item_flags[1] = 0;
    }
}

void Lara_HandleUnderwater(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    coll->bad_pos = NO_BAD_POS;
    coll->bad_neg = -LARA_HEIGHT_UW;
    coll->bad_ceiling = LARA_HEIGHT_UW;
    coll->old.x = item->pos.x;
    coll->old.y = item->pos.y;
    coll->old.z = item->pos.z;
    coll->radius = LARA_RADIUS_UW;
    coll->trigger = NULL;
    coll->slopes_are_walls = 0;
    coll->slopes_are_pits = 0;
    coll->lava_is_pit = 0;
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 1;

    if ((g_Input & IN_LOOK) && g_Lara.look) {
        Lara_LookLeftRight();
    } else {
        Lara_ResetLook();
    }
    g_Lara.look = 1;

    if (g_Lara.extra_anim) {
        g_LaraExtraControlRoutines[item->current_anim_state](item, coll);
    } else {
        g_LaraControlRoutines[item->current_anim_state](item, coll);
    }

    if (item->pos.z_rot < -2 * LARA_LEAN_UNDO) {
        item->pos.z_rot += 2 * LARA_LEAN_UNDO;
    } else if (item->pos.z_rot > 2 * LARA_LEAN_UNDO) {
        item->pos.z_rot -= 2 * LARA_LEAN_UNDO;
    } else {
        item->pos.z_rot = 0;
    }

    if (item->pos.x_rot < -85 * DEG_1) {
        item->pos.x_rot = -85 * DEG_1;
    } else if (item->pos.x_rot > 85 * DEG_1) {
        item->pos.x_rot = 85 * DEG_1;
    }

    if (item->pos.z_rot < -LARA_LEAN_MAX_UW) {
        item->pos.z_rot = -LARA_LEAN_MAX_UW;
    } else if (item->pos.z_rot > LARA_LEAN_MAX_UW) {
        item->pos.z_rot = LARA_LEAN_MAX_UW;
    }

    if (g_Lara.turn_rate < -LARA_TURN_UNDO) {
        g_Lara.turn_rate += LARA_TURN_UNDO;
    } else if (g_Lara.turn_rate > LARA_TURN_UNDO) {
        g_Lara.turn_rate -= LARA_TURN_UNDO;
    } else {
        g_Lara.turn_rate = 0;
    }
    item->pos.y_rot += g_Lara.turn_rate;

    if (g_Lara.current_active && g_Lara.water_status != LWS_CHEAT) {
        Lara_WaterCurrent(coll);
    }
    Lara_Animate(item);

    item->pos.y -=
        (phd_sin(item->pos.x_rot) * item->fall_speed) >> (W2V_SHIFT + 2);
    item->pos.x +=
        (((phd_sin(item->pos.y_rot) * item->fall_speed) >> (W2V_SHIFT + 2))
         * phd_cos(item->pos.x_rot))
        >> W2V_SHIFT;
    item->pos.z +=
        (((phd_cos(item->pos.y_rot) * item->fall_speed) >> (W2V_SHIFT + 2))
         * phd_cos(item->pos.x_rot))
        >> W2V_SHIFT;

    if (!g_Lara.extra_anim) {
        if (g_Lara.water_status != LWS_CHEAT) {
            Lara_BaddieCollision(item, coll);
        }
        if (g_Lara.skidoo == NO_ITEM) {
            g_LaraCollisionRoutines[item->current_anim_state](item, coll);
        }
    }

    Item_UpdateRoom(item, 0);

    Gun_Control();

    g_LaraOnPad = 0;
    Room_TestTriggers(coll->trigger, 0);
    if (!g_LaraOnPad) {
        g_LaraItem->item_flags[1] = 0;
    }
}

void Lara_HandleSurface(struct ITEM_INFO *item, struct COLL_INFO *coll)
{
    g_Camera.target_elevation = -22 * DEG_1;

    coll->bad_pos = NO_BAD_POS;
    coll->bad_neg = -STEP_L / 2;
    coll->bad_ceiling = 100;
    coll->old.x = item->pos.x;
    coll->old.y = item->pos.y;
    coll->old.z = item->pos.z;
    coll->radius = LARA_RADIUS_SURF;
    coll->trigger = NULL;
    coll->slopes_are_walls = 0;
    coll->slopes_are_pits = 0;
    coll->lava_is_pit = 0;
    coll->enable_spaz = 0;
    coll->enable_baddie_push = 0;

    if ((g_Input & IN_LOOK) && g_Lara.look) {
        Lara_LookLeftRight();
    } else {
        Lara_ResetLook();
    }
    g_Lara.look = 1;

    g_LaraControlRoutines[item->current_anim_state](item, coll);

    if (item->pos.z_rot < -2 * LARA_LEAN_UNDO) {
        item->pos.z_rot += 2 * LARA_LEAN_UNDO;
    } else if (item->pos.z_rot > 2 * LARA_LEAN_UNDO) {
        item->pos.z_rot -= 2 * LARA_LEAN_UNDO;
    } else {
        item->pos.z_rot = 0;
    }

    if (g_Lara.current_active && g_Lara.water_status != LWS_CHEAT) {
        Lara_WaterCurrent(coll);
    }
    Lara_Animate(item);

    item->pos.x +=
        (phd_sin(g_Lara.move_angle) * item->fall_speed) >> (W2V_SHIFT + 2);
    item->pos.z +=
        (phd_cos(g_Lara.move_angle) * item->fall_speed) >> (W2V_SHIFT + 2);

    Lara_BaddieCollision(item, coll);
    if (g_Lara.skidoo == NO_ITEM) {
        g_LaraCollisionRoutines[item->current_anim_state](item, coll);
    }

    Item_UpdateRoom(item, 100);

    Gun_Control();

    g_LaraOnPad = 0;
    Room_TestTriggers(coll->trigger, 0);
    if (!g_LaraOnPad) {
        g_LaraItem->item_flags[1] = 0;
    }
}

void Lara_CheatGetStuff(void)
{
    Inv_AddItem(O_M16_ITEM);
    Inv_AddItem(O_SHOTGUN_ITEM);
    Inv_AddItem(O_UZI_ITEM);
    Inv_AddItem(O_MAGNUM_ITEM);
    Inv_AddItem(O_GUN_ITEM);
    Inv_AddItem(O_ROCKET_GUN_ITEM);
    Inv_AddItem(O_GRENADE_GUN_ITEM);

    Inv_AddItem(O_FLAREBOX_ITEM);
    Inv_AddItem(O_MEDI_ITEM);
    Inv_AddItem(O_BIGMEDI_ITEM);

    g_Lara.magnums.ammo = 250;
    g_Lara.uzis.ammo = 1000;
    g_Lara.shotgun.ammo = 300;
    g_Lara.m16.ammo = 300;
    g_Lara.grenade.ammo = 1000;
}
