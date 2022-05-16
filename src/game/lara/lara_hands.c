#include "game/lara/lara_hands.h"

#include "game/matrix.h"
#include "global/const.h"
#include "global/stubs.h"
#include "global/types.h"
#include "global/vars.h"

#include <stdint.h>

static void Lara_AddJointPos(struct ITEM_INFO *item, int32_t mesh);

static void Lara_AddJointPos(struct ITEM_INFO *item, int32_t mesh)
{
    int16_t room_num = item->room_num;
    GetFloor(
        (g_MatrixPtr->_03 >> W2V_SHIFT) + item->pos.x,
        (g_MatrixPtr->_13 >> W2V_SHIFT) + item->pos.y,
        (g_MatrixPtr->_23 >> W2V_SHIFT) + item->pos.z, &room_num);
    g_IsJointUnderwater[mesh] = (g_Rooms[room_num].flags & RF_UNDERWATER) != 0;
    g_GotJointPos[mesh] = 1;
}

void Lara_GetHandAbsPosition(
    struct PHD_VECTOR *vec, enum LARA_BODY_PART body_part)
{
    struct ITEM_INFO *item = g_LaraItem;

    int32_t size;
    int16_t *frame;
    int16_t *frmptr[2];
    if (g_Lara.hit_direction < 0) {
        int32_t rate;
        int32_t frac = GetFrames(item, frmptr, &rate);
        if (frac) {
            Lara_GetHandAbsPosition_I(
                item, vec, frmptr[0], frmptr[1], frac, rate, body_part);
            return;
        }
        frame = frmptr[0];
    } else {
        switch (g_Lara.hit_direction) {
        case DIR_EAST:
            frame = g_Anims[LA_SPAZ_RIGHT].frame_ptr;
            size = g_Anims[LA_SPAZ_RIGHT].interpolation >> 8;
            break;

        case DIR_SOUTH:
            frame = g_Anims[LA_SPAZ_BACK].frame_ptr;
            size = g_Anims[LA_SPAZ_BACK].interpolation >> 8;
            break;

        case DIR_WEST:
            frame = g_Anims[LA_SPAZ_LEFT].frame_ptr;
            size = g_Anims[LA_SPAZ_LEFT].interpolation >> 8;
            break;

        default:
            frame = g_Anims[LA_SPAZ_FORWARD].frame_ptr;
            size = g_Anims[LA_SPAZ_FORWARD].interpolation >> 8;
            break;
        }
        frame += g_Lara.hit_frame * size;
    }

    Matrix_PushUnit();
    g_MatrixPtr->_03 = 0;
    g_MatrixPtr->_13 = 0;
    g_MatrixPtr->_23 = 0;
    Matrix_RotYXZ(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);
    Matrix_Push();

    struct OBJECT_INFO *obj = &g_Objects[item->object_num];
    int32_t *bone = &g_Bones[obj->bone_index];
    int16_t *rotation = frame + 9;

    Matrix_TranslateRel(frame[6], frame[7], frame[8]);
    Matrix_RotYXZSuperpack(&rotation, 0);
    if (!g_GotJointPos[LM_HIPS]) {
        Lara_AddJointPos(item, LM_HIPS);
    }

    if (body_part == LBP_LEFT_FOOT) {
        Matrix_TranslateRel(bone[1], bone[2], bone[3]);
        Matrix_RotYXZSuperpack(&rotation, 0);
        if (!g_GotJointPos[LM_THIGH_L]) {
            Lara_AddJointPos(item, LM_THIGH_L);
        }

        Matrix_TranslateRel(bone[5], bone[6], bone[7]);
        Matrix_RotYXZSuperpack(&rotation, 0);
        if (!g_GotJointPos[LM_CALF_L]) {
            Lara_AddJointPos(item, LM_CALF_L);
        }

        Matrix_TranslateRel(bone[9], bone[10], bone[11]);
        Matrix_RotYXZSuperpack(&rotation, 0);
        if (!g_GotJointPos[LM_FOOT_L]) {
            Lara_AddJointPos(item, LM_FOOT_L);
        }

    } else if (body_part == LBP_RIGHT_FOOT) {
        Matrix_TranslateRel(bone[13], bone[14], bone[15]);
        Matrix_RotYXZSuperpack(&rotation, 3);
        if (!g_GotJointPos[LM_THIGH_R]) {
            Lara_AddJointPos(item, LM_THIGH_R);
        }

        Matrix_TranslateRel(bone[17], bone[18], bone[19]);
        Matrix_RotYXZSuperpack(&rotation, 0);
        if (!g_GotJointPos[LM_CALF_R]) {
            Lara_AddJointPos(item, LM_CALF_R);
        }

        Matrix_TranslateRel(bone[21], bone[22], bone[23]);
        Matrix_RotYXZSuperpack(&rotation, 0);
        if (!g_GotJointPos[LM_FOOT_R]) {
            Lara_AddJointPos(item, LM_FOOT_R);
        }

    } else if (body_part != LBP_LARA_HIPS) {
        Matrix_TranslateRel(bone[25], bone[26], bone[27]);

        enum LARA_STATE lara_state =
            g_Items[g_Lara.weapon_item].current_anim_state;
        if (g_Lara.weapon_item != NO_ITEM && g_Lara.gun_type == LGT_M16
            && (lara_state == LS_WALK || lara_state == LS_STOP
                || lara_state == LS_POSE)) {
            rotation =
                &g_Lara.right_arm.frame_base
                     [g_Lara.right_arm.frame_num
                          * (g_Anims[g_Lara.right_arm.anim_num].interpolation
                             >> 8)
                      + 9];
            Matrix_RotYXZSuperpack(&rotation, 7);
        } else {
            Matrix_RotYXZSuperpack(&rotation, 6);
        }
        Matrix_RotYXZ(
            g_Lara.torso_y_rot, g_Lara.torso_x_rot, g_Lara.torso_z_rot);

        if (!g_GotJointPos[LM_TORSO]) {
            Lara_AddJointPos(item, LM_TORSO);
        }

        if (body_part == LBP_LARA_HEAD) {
            Matrix_TranslateRel(bone[53], bone[54], bone[55]);
            Matrix_RotYXZSuperpack(&rotation, 6);
            Matrix_RotYXZ(
                g_Lara.head_y_rot, g_Lara.head_x_rot, g_Lara.head_z_rot);
            if (!g_GotJointPos[LM_HEAD]) {
                Lara_AddJointPos(item, LM_HEAD);
            }
        }

        if (body_part == LBP_LEFT_HAND || body_part == LBP_RIGHT_HAND) {
            enum LARA_GUN_TYPE fire_arms;
            switch (g_Lara.gun_status) {
            case LGS_READY:
            case LGS_SPECIAL:
            case LGS_DRAW:
            case LGS_UNDRAW:
                fire_arms = g_Lara.gun_type;
                break;
            default:
                fire_arms = LGT_UNARMED;
                break;
            }

            if (body_part == LBP_LEFT_HAND) {
                Matrix_TranslateRel(bone[41], bone[42], bone[43]);

                switch (fire_arms) {
                case LGT_UNARMED:
                case LGT_FLARE:
                    if (g_Lara.flare_control_left) {
                        rotation =
                            &g_Lara.left_arm.frame_base
                                 [(g_Lara.left_arm.frame_num
                                   - g_Anims[g_Lara.left_arm.anim_num]
                                         .frame_base)
                                      * (g_Anims[g_Lara.left_arm.anim_num]
                                             .interpolation
                                         >> 8)
                                  + 9];
                        Matrix_RotYXZSuperpack(&rotation, 11);
                    } else {
                        Matrix_RotYXZSuperpack(&rotation, 3);
                    }
                    break;

                case LGT_PISTOLS:
                case LGT_MAGNUMS:
                case LGT_UZIS:
                    g_MatrixPtr->_00 = g_MatrixPtr[-1]._00;
                    g_MatrixPtr->_01 = g_MatrixPtr[-1]._01;
                    g_MatrixPtr->_02 = g_MatrixPtr[-1]._02;
                    g_MatrixPtr->_10 = g_MatrixPtr[-1]._10;
                    g_MatrixPtr->_11 = g_MatrixPtr[-1]._11;
                    g_MatrixPtr->_12 = g_MatrixPtr[-1]._12;
                    g_MatrixPtr->_20 = g_MatrixPtr[-1]._20;
                    g_MatrixPtr->_21 = g_MatrixPtr[-1]._21;
                    g_MatrixPtr->_22 = g_MatrixPtr[-1]._22;

                    Matrix_RotYXZ(
                        g_Lara.left_arm.y_rot, g_Lara.left_arm.x_rot,
                        g_Lara.left_arm.z_rot);
                    rotation =
                        &g_Lara.left_arm.frame_base
                             [(g_Lara.left_arm.frame_num
                               - g_Anims[g_Lara.left_arm.anim_num].frame_base)
                                  * (g_Anims[g_Lara.left_arm.anim_num]
                                         .interpolation
                                     >> 8)
                              + 9];
                    Matrix_RotYXZSuperpack(&rotation, 11);
                    break;

                case LGT_SHOTGUN:
                case LGT_HARPOON:
                case LGT_ROCKET:
                case LGT_GRENADE:
                case LGT_M16:
                    Matrix_RotYXZSuperpack(&rotation, 3);
                    break;

                default:
                    Matrix_RotYXZSuperpack(&rotation, 3);
                    break;
                }
                if (!g_GotJointPos[LM_UARM_L]) {
                    Lara_AddJointPos(item, LM_UARM_L);
                }

                Matrix_TranslateRel(bone[45], bone[46], bone[47]);
                Matrix_RotYXZSuperpack(&rotation, 0);
                if (!g_GotJointPos[LM_LARM_L]) {
                    Lara_AddJointPos(item, LM_LARM_L);
                }

                Matrix_TranslateRel(bone[49], bone[50], bone[51]);
                Matrix_RotYXZSuperpack(&rotation, 0);
                if (!g_GotJointPos[LM_HAND_L]) {
                    Lara_AddJointPos(item, LM_HAND_L);
                }

            } else if (body_part == LBP_RIGHT_HAND) {
                Matrix_TranslateRel(bone[29], bone[30], bone[31]);

                switch (fire_arms) {
                case LGT_UNARMED:
                case LGT_FLARE:
                    Matrix_RotYXZSuperpack(&rotation, 0);
                    break;

                case LGT_PISTOLS:
                case LGT_MAGNUMS:
                case LGT_UZIS:
                    g_MatrixPtr->_00 = g_MatrixPtr[-1]._00;
                    g_MatrixPtr->_01 = g_MatrixPtr[-1]._01;
                    g_MatrixPtr->_02 = g_MatrixPtr[-1]._02;
                    g_MatrixPtr->_10 = g_MatrixPtr[-1]._10;
                    g_MatrixPtr->_11 = g_MatrixPtr[-1]._11;
                    g_MatrixPtr->_12 = g_MatrixPtr[-1]._12;
                    g_MatrixPtr->_20 = g_MatrixPtr[-1]._20;
                    g_MatrixPtr->_21 = g_MatrixPtr[-1]._21;
                    g_MatrixPtr->_22 = g_MatrixPtr[-1]._22;
                    Matrix_RotYXZ(
                        g_Lara.right_arm.y_rot, g_Lara.right_arm.x_rot,
                        g_Lara.right_arm.z_rot);
                    rotation =
                        &g_Lara.right_arm.frame_base
                             [(g_Lara.right_arm.frame_num
                               - g_Anims[g_Lara.right_arm.anim_num].frame_base)
                                  * (g_Anims[g_Lara.right_arm.anim_num]
                                         .interpolation
                                     >> 8)
                              + 9];
                    Matrix_RotYXZSuperpack(&rotation, 8);
                    break;

                case LGT_SHOTGUN:
                case LGT_HARPOON:
                case LGT_ROCKET:
                case LGT_GRENADE:
                case LGT_M16:
                    rotation = &g_Lara.right_arm.frame_base
                                    [g_Lara.right_arm.frame_num
                                         * (g_Anims[g_Lara.right_arm.anim_num]
                                                .interpolation
                                            >> 8)
                                     + 9];
                    Matrix_RotYXZSuperpack(&rotation, 8);
                    break;

                default:
                    break;
                }
                if (!g_GotJointPos[LM_UARM_R]) {
                    Lara_AddJointPos(item, LM_UARM_R);
                }

                Matrix_TranslateRel(bone[33], bone[34], bone[35]);
                Matrix_RotYXZSuperpack(&rotation, 0);
                if (!g_GotJointPos[LM_LARM_R]) {
                    Lara_AddJointPos(item, LM_LARM_R);
                }

                Matrix_TranslateRel(bone[37], bone[38], bone[39]);
                Matrix_RotYXZSuperpack(&rotation, 0);
                if (!g_GotJointPos[LM_HAND_R]) {
                    Lara_AddJointPos(item, LM_HAND_R);
                }
            }
        }
    }

    Matrix_TranslateRel(vec->x, vec->y, vec->z);
    vec->x = (g_MatrixPtr->_03 >> W2V_SHIFT) + item->pos.x;
    vec->y = (g_MatrixPtr->_13 >> W2V_SHIFT) + item->pos.y;
    vec->z = (g_MatrixPtr->_23 >> W2V_SHIFT) + item->pos.z;

    Matrix_Pop();
    Matrix_Pop();
}

void Lara_GetHandAbsPosition_I(
    struct ITEM_INFO *item, struct PHD_VECTOR *vec, int16_t *frame1,
    int16_t *frame2, int32_t frac, int32_t rate, enum LARA_BODY_PART body_part)
{
    Matrix_PushUnit();
    g_MatrixPtr->_03 = 0;
    g_MatrixPtr->_13 = 0;
    g_MatrixPtr->_23 = 0;
    Matrix_RotYXZ(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);

    Matrix_Push();
    Matrix_Push();

    struct OBJECT_INFO *obj = &g_Objects[item->object_num];
    int32_t *bone = &g_Bones[obj->bone_index];
    int16_t *rotation1 = frame1 + 9;
    int16_t *rotation2 = frame2 + 9;

    Matrix_InitInterpolate(frac, rate);

    Matrix_TranslateRel_ID(
        frame1[6], frame1[7], frame1[8], frame2[6], frame2[7], frame2[8]);
    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
    if (!g_GotJointPos[LM_HIPS]) {
        Lara_AddJointPos(item, LM_HIPS);
    }

    if (body_part == LBP_LEFT_FOOT) {
        Matrix_TranslateRel_I(bone[1], bone[2], bone[3]);
        Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
        if (!g_GotJointPos[LM_THIGH_L]) {
            Lara_AddJointPos(item, LM_THIGH_L);
        }

        Matrix_TranslateRel_I(bone[5], bone[6], bone[7]);
        Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
        if (!g_GotJointPos[LM_CALF_L]) {
            Lara_AddJointPos(item, LM_CALF_L);
        }

        Matrix_TranslateRel_I(bone[9], bone[10], bone[11]);
        Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
        if (!g_GotJointPos[LM_FOOT_L]) {
            Lara_AddJointPos(item, LM_FOOT_L);
        }

    } else if (body_part == LBP_RIGHT_FOOT) {
        Matrix_TranslateRel_I(bone[13], bone[14], bone[15]);
        Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 3);
        if (!g_GotJointPos[LM_THIGH_R]) {
            Lara_AddJointPos(item, LM_THIGH_R);
        }

        Matrix_TranslateRel_I(bone[17], bone[18], bone[19]);
        Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
        if (!g_GotJointPos[LM_CALF_R]) {
            Lara_AddJointPos(item, LM_CALF_R);
        }

        Matrix_TranslateRel_I(bone[21], bone[22], bone[23]);
        Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
        if (!g_GotJointPos[LM_FOOT_R]) {
            Lara_AddJointPos(item, LM_FOOT_R);
        }

    } else if (body_part != LBP_LARA_HIPS) {
        Matrix_TranslateRel_I(bone[25], bone[26], bone[27]);

        enum LARA_STATE lara_state =
            g_Items[g_Lara.weapon_item].current_anim_state;
        if (g_Lara.weapon_item != NO_ITEM && g_Lara.gun_type == LGT_M16
            && (lara_state == LS_WALK || lara_state == LS_STOP
                || lara_state == LS_POSE)) {
            rotation1 =
                &g_Lara.right_arm.frame_base
                     [g_Lara.right_arm.frame_num
                          * (g_Anims[g_Lara.right_arm.anim_num].interpolation
                             >> 8)
                      + 9];
            rotation2 = rotation1;
            Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 7);
        } else {
            Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 6);
        }
        Matrix_RotYXZ_I(
            g_Lara.torso_y_rot, g_Lara.torso_x_rot, g_Lara.torso_z_rot);

        if (!g_GotJointPos[LM_TORSO]) {
            Lara_AddJointPos(item, LM_TORSO);
        }

        if (body_part == LBP_LARA_HEAD) {
            Matrix_TranslateRel_I(bone[53], bone[54], bone[55]);
            Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 6);
            Matrix_RotYXZ_I(
                g_Lara.head_y_rot, g_Lara.head_x_rot, g_Lara.head_z_rot);
            if (!g_GotJointPos[LM_HEAD]) {
                Lara_AddJointPos(item, LM_HEAD);
            }
        }

        if (body_part == LBP_LEFT_HAND || body_part == LBP_RIGHT_HAND) {
            enum LARA_GUN_TYPE fire_arms;
            switch (g_Lara.gun_status) {
            case LGS_READY:
            case LGS_SPECIAL:
            case LGS_DRAW:
            case LGS_UNDRAW:
                fire_arms = g_Lara.gun_type;
                break;
            default:
                fire_arms = LGT_UNARMED;
                break;
            }

            if (body_part == LBP_LEFT_HAND) {
                Matrix_TranslateRel_I(bone[41], bone[42], bone[43]);

                switch (fire_arms) {
                case LGT_UNARMED:
                case LGT_FLARE:
                    if (g_Lara.flare_control_left) {
                        rotation1 =
                            &g_Lara.left_arm.frame_base
                                 [(g_Lara.left_arm.frame_num
                                   - g_Anims[g_Lara.left_arm.anim_num]
                                         .frame_base)
                                      * (g_Anims[g_Lara.left_arm.anim_num]
                                             .interpolation
                                         >> 8)
                                  + 9];
                        rotation2 = rotation1;
                        Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 11);
                    } else {
                        Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 3);
                    }
                    if (!g_GotJointPos[LM_UARM_L]) {
                        Lara_AddJointPos(item, LM_UARM_L);
                    }

                    Matrix_TranslateRel_I(bone[45], bone[46], bone[47]);
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
                    if (!g_GotJointPos[LM_LARM_L]) {
                        Lara_AddJointPos(item, LM_LARM_L);
                    }

                    Matrix_TranslateRel_I(bone[49], bone[50], bone[51]);
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
                    if (!g_GotJointPos[LM_HAND_L]) {
                        Lara_AddJointPos(item, LM_HAND_L);
                    }
                    break;

                case LGT_PISTOLS:
                case LGT_MAGNUMS:
                case LGT_UZIS:
                    Matrix_InterpolateArms();
                    Matrix_RotYXZ(
                        g_Lara.left_arm.y_rot, g_Lara.left_arm.x_rot,
                        g_Lara.left_arm.z_rot);
                    rotation1 =
                        &g_Lara.left_arm.frame_base
                             [(g_Lara.left_arm.frame_num
                               - g_Anims[g_Lara.left_arm.anim_num].frame_base)
                                  * (g_Anims[g_Lara.left_arm.anim_num]
                                         .interpolation
                                     >> 8)
                              + 9];
                    Matrix_RotYXZSuperpack(&rotation1, 11);

                    Matrix_TranslateRel(bone[45], bone[46], bone[47]);
                    Matrix_RotYXZSuperpack(&rotation1, 0);

                    Matrix_TranslateRel(bone[49], bone[50], bone[51]);
                    Matrix_RotYXZSuperpack(&rotation1, 0);

                    Matrix_TranslateRel(vec->x, vec->y, vec->z);
                    vec->x = (g_MatrixPtr->_03 >> W2V_SHIFT) + item->pos.x;
                    vec->y = (g_MatrixPtr->_13 >> W2V_SHIFT) + item->pos.y;
                    vec->z = (g_MatrixPtr->_23 >> W2V_SHIFT) + item->pos.z;
                    goto cleanup;
                    break;

                case LGT_SHOTGUN:
                case LGT_HARPOON:
                case LGT_ROCKET:
                case LGT_GRENADE:
                case LGT_M16:
                    rotation1 = &g_Lara.right_arm.frame_base
                                     [g_Lara.right_arm.frame_num
                                          * (g_Anims[g_Lara.right_arm.anim_num]
                                                 .interpolation
                                             >> 8)
                                      + 9];
                    rotation2 = rotation1;
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 11);

                    Matrix_TranslateRel_I(bone[45], bone[46], bone[47]);
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);

                    Matrix_TranslateRel_I(bone[49], bone[50], bone[51]);
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
                    break;

                default:
                    break;
                }

            } else if (body_part == LBP_RIGHT_HAND) {
                switch (fire_arms) {
                case LGT_UNARMED:
                case LGT_FLARE:
                    Matrix_TranslateRel_I(bone[29], bone[30], bone[31]);
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
                    if (!g_GotJointPos[LM_UARM_R]) {
                        Lara_AddJointPos(item, LM_UARM_R);
                    }

                    Matrix_TranslateRel_I(bone[33], bone[34], bone[35]);
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
                    if (!g_GotJointPos[LM_LARM_R]) {
                        Lara_AddJointPos(item, LM_LARM_R);
                    }

                    Matrix_TranslateRel_I(bone[37], bone[38], bone[39]);
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
                    if (!g_GotJointPos[LM_HAND_R]) {
                        Lara_AddJointPos(item, LM_HAND_R);
                    }
                    break;

                case LGT_PISTOLS:
                case LGT_MAGNUMS:
                case LGT_UZIS:
                    Matrix_TranslateRel_I(bone[29], bone[30], bone[31]);
                    Matrix_InterpolateArms();
                    Matrix_RotYXZ(
                        g_Lara.right_arm.y_rot, g_Lara.right_arm.x_rot,
                        g_Lara.right_arm.z_rot);
                    rotation1 =
                        &g_Lara.right_arm.frame_base
                             [(g_Lara.right_arm.frame_num
                               - g_Anims[g_Lara.right_arm.anim_num].frame_base)
                                  * (g_Anims[g_Lara.right_arm.anim_num]
                                         .interpolation
                                     >> 8)
                              + 9];
                    Matrix_RotYXZSuperpack(&rotation1, 8);

                    Matrix_TranslateRel(bone[33], bone[34], bone[35]);
                    Matrix_RotYXZSuperpack(&rotation1, 0);

                    Matrix_TranslateRel(bone[37], bone[38], bone[39]);
                    Matrix_RotYXZSuperpack(&rotation1, 0);

                    Matrix_TranslateRel(vec->x, vec->y, vec->z);
                    vec->x = (g_MatrixPtr->_03 >> W2V_SHIFT) + item->pos.x;
                    vec->y = (g_MatrixPtr->_13 >> W2V_SHIFT) + item->pos.y;
                    vec->z = (g_MatrixPtr->_23 >> W2V_SHIFT) + item->pos.z;
                    goto cleanup;
                    break;

                case LGT_SHOTGUN:
                case LGT_HARPOON:
                case LGT_ROCKET:
                case LGT_GRENADE:
                case LGT_M16:
                    Matrix_TranslateRel_I(bone[29], bone[30], bone[31]);
                    rotation1 = &g_Lara.right_arm.frame_base
                                     [g_Lara.right_arm.frame_num
                                          * (g_Anims[g_Lara.right_arm.anim_num]
                                                 .interpolation
                                             >> 8)
                                      + 9];
                    rotation2 = rotation1;
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 8);

                    Matrix_TranslateRel_I(bone[33], bone[34], bone[35]);
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);

                    Matrix_TranslateRel_I(bone[37], bone[38], bone[39]);
                    Matrix_RotYXZSuperpack_I(&rotation1, &rotation2, 0);
                    break;

                default:
                    break;
                }
            }
        }
    }

    Matrix_TranslateRel_I(vec->x, vec->y, vec->z);
    Matrix_Interpolate();
    vec->x = (g_MatrixPtr->_03 >> W2V_SHIFT) + item->pos.x;
    vec->y = (g_MatrixPtr->_13 >> W2V_SHIFT) + item->pos.y;
    vec->z = (g_MatrixPtr->_23 >> W2V_SHIFT) + item->pos.z;

cleanup:
    Matrix_Pop();
    Matrix_Pop();
    Matrix_Pop();
}
