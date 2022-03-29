#pragma once
#pragma pack(push, 1)

#include <stdint.h>

typedef int16_t PHD_ANGLE;

// clang-format off
enum INPUT_STATE {
    IN_FORWARD     = 1,
    IN_BACK        = (1 << 1),
    IN_LEFT        = (1 << 2),
    IN_RIGHT       = (1 << 3),
    IN_JUMP        = (1 << 4),
    IN_DRAW        = (1 << 5),
    IN_ACTION      = (1 << 6),
    IN_SLOW        = (1 << 7),
    IN_OPTION      = (1 << 8),
    IN_LOOK        = (1 << 9),
    IN_STEPL       = (1 << 10),
    IN_STEPR       = (1 << 11),
    IN_ROLL        = (1 << 12),
    IN_PAUSE       = (1 << 13),
    IN_DEBUG_A     = (1 << 14),
    IN_DEBUG_B     = (1 << 15),
    IN_DEBUG_C     = (1 << 16),
    IN_DEBUG_D     = (1 << 17),
    IN_DEBUG_E     = (1 << 18),
    IN_DEBUG_F     = (1 << 19),
    IN_SELECT      = (1 << 20),
    IN_DESELECT    = (1 << 21),
    IN_SAVE        = (1 << 22),
    IN_LOAD        = (1 << 23),
    IN_STEPSHIFT   = (1 << 24),
    IN_LOOKLEFT    = (1 << 25),
    IN_LOOKRIGHT   = (1 << 26),
    IN_LOOKFORWARD = (1 << 27),
    IN_LOOKBACK    = (1 << 28),
    IN_DUCK        = (1 << 29),
    IN_DASH        = (1 << 30),
};

enum ROOM_FLAG {
    RF_UNDERWATER  = 1,
    RF_OUTSIDE     = 8,
    RF_DYNAMIC_LIT = 16,
    RF_NOT_INSIDE  = 32,
    RF_INSIDE      = 64,
    RF_SWAMP       = 128,
};

enum SOUND_EFFECT_ID {
    SFX_LARA_FALL = 30,
};

enum CAMERA_TYPE {
    CT_CHASE = 0,
    CT_FIXED = 1,
    CT_LOOK = 2,
    CT_COMBAT = 3,
    CT_CINEMATIC = 4,
    CT_HEAVY = 5,
};

enum LARA_WATER_STATE {
    LWS_ABOVE_WATER = 0,
    LWS_UNDERWATER  = 1,
    LWS_SURFACE     = 2,
    LWS_CHEAT       = 3,
    LWS_WADE        = 4,
};

enum LARA_GUN_STATE {
    LG_ARMLESS   = 0,
    LG_HANDSBUSY = 1,
    LG_DRAW      = 2,
    LG_UNDRAW    = 3,
    LG_READY     = 4,
    LG_SPECIAL   = 5,
};

enum LARA_ANIM {
    LA_RUN                = 0,
    LA_WALK               = 1,
    LA_STOP_L             = 2,
    LA_STOP_R             = 3,
    LA_START_RUN          = 6,
    LA_STOP               = 11,
    LA_FAST_FALL          = 23,
    LA_LAND_FAR           = 24,
    LA_STOP_HANG          = 28,
    LA_LAND               = 31,
    LA_FAST_SPLAT         = 32,
    LA_FALL_DOWN          = 34,
    LA_VAULT_34           = 42,
    LA_VAULT_12           = 50,
    LA_HIT_WALL_L         = 53,
    LA_HIT_WALL_R         = 54,
    LA_RUN_STEP_UP_R      = 55,
    LA_RUN_STEP_UP_L      = 56,
    LA_WALK_STEP_UP_L     = 57,
    LA_WALK_STEP_UP_R     = 58,
    LA_WALK_STEP_DOWN_R   = 59,
    LA_WALK_STEP_DOWN_L   = 60,
    LA_BACK_STEP_DOWN_L   = 61,
    LA_BACK_STEP_DOWN_R   = 62,
    LA_SLIDE              = 70,
    LA_COMPRESS           = 73,
    LA_SWIM_GLIDE         = 87,
    LA_FALL_BACK          = 93,
    LA_GRAB_LEDGE         = 96,
    LA_HANG               = 96,
    LA_START_HANG         = 96,
    LA_BREATH             = 103,
    LA_SLIDE_BACK         = 104,
    LA_TREAD              = 108,
    LA_SURF_CLIMB         = 111,
    LA_JUMP_IN            = 112,
    LA_SURF_TREAD         = 114,
    LA_SURF_SWIM          = 116,
    LA_SURF_DIVE          = 119,
    LA_SPAZ_FORWARD       = 125,
    LA_SPAZ_BACK          = 126,
    LA_SPAZ_R             = 127,
    LA_SPAZ_L             = 128,
    LA_ROLLING_BALL_DEATH = 139,
    LA_SURF_TREAD_BACK    = 140,
    LA_SURF_BACK          = 141,
    LA_SURF_L             = 143,
    LA_SURF_R             = 144,
    LA_ROLL               = 146,
    LA_SPIKE_DEATH        = 149,
    LA_GRAB_LEDGE_IN      = 150,
    LA_CLIMBING           = 161,
    LA_CLIMB_UP_R         = 162,
    LA_CLIMB_UP_L         = 163,
    LA_CLIMB_STILL        = 164,
    LA_CLIMB_DOWN_R       = 166,
    LA_CLIMB_DOWN_L       = 167,
    LA_CLIMB_DOWN         = 168,
    LA_CLIMB_R            = 170,
    LA_CLIMB_L            = 171,
    LA_SURF_TO_WADE2      = 176,
    LA_UW_TO_WADE         = 176,
    LA_WADE               = 177,
    LA_HANG_UP            = 187,
    LA_HANG_DOWN          = 188,
    LA_THROW_FLARE        = 189,
    LA_SURF_TO_WADE       = 190,
    LA_SURF_TO_STAND      = 191,
    LA_SWIM_TO_QSTAND     = 192,
    LA_SURF_TO_QSTAND     = 193,
    LA_CLIMB_TO_HANG      = 194,
    LA_GRAB_R             = 201,
    LA_GRAB_L             = 202,
    LA_WATER_ROLL         = 203,
    LA_PICKUP_FLARE_UW    = 206,
    LA_STAND_TO_DUCK      = 218,
    LA_DUCK_ROLL          = 219,
    LA_DUCK_BREATHE       = 223,
    LA_DASH               = 224,
    LA_DASH_DIVE          = 231,
    LA_MONKEY_HANG        = 235,
    LA_MONKEY_SWING       = 237,
};

enum LARA_STATE {
    LS_WALK            = 0,
    LS_RUN             = 1,
    LS_STOP            = 2,
    LS_FORWARD_JUMP    = 3,
    LS_POSE            = 4,
    LS_FAST_BACK       = 5,
    LS_TURN_R          = 6,
    LS_TURN_L          = 7,
    LS_DEATH           = 8,
    LS_FAST_FALL       = 9,
    LS_HANG            = 10,
    LS_REACH           = 11,
    LS_SPLAT           = 12,
    LS_TREAD           = 13,
    LS_LAND            = 14,
    LS_COMPRESS        = 15,
    LS_BACK            = 16,
    LS_SWIM            = 17,
    LS_GLIDE           = 18,
    LS_NULL            = 19,
    LS_FAST_TURN       = 20,
    LS_STEP_RIGHT      = 21,
    LS_STEP_LEFT       = 22,
    LS_HIT             = 23,
    LS_SLIDE           = 24,
    LS_BACK_JUMP       = 25,
    LS_RIGHT_JUMP      = 26,
    LS_LEFT_JUMP       = 27,
    LS_UP_JUMP         = 28,
    LS_FALL_BACK       = 29,
    LS_HANG_LEFT       = 30,
    LS_HANG_RIGHT      = 31,
    LS_SLIDE_BACK      = 32,
    LS_SURF_TREAD      = 33,
    LS_SURF_SWIM       = 34,
    LS_DIVE            = 35,
    LS_PUSH_BLOCK      = 36,
    LS_PULL_BLOCK      = 37,
    LS_PUSH_PULL_READY = 38,
    LS_PICKUP          = 39,
    LS_SWITCH_ON       = 40,
    LS_SWITCH_OFF      = 41,
    LS_USE_KEY         = 42,
    LS_USE_PUZZLE      = 43,
    LS_UW_DEATH        = 44,
    LS_ROLL            = 45,
    LS_SPECIAL         = 46,
    LS_SURF_BACK       = 47,
    LS_SURF_LEFT       = 48,
    LS_SURF_RIGHT      = 49,
    LS_USE_MIDAS       = 50,
    LS_DIE_MIDAS       = 51,
    LS_SWAN_DIVE       = 52,
    LS_FAST_DIVE       = 53,
    LS_GYMNAST         = 54,
    LS_WATER_OUT       = 55,
    LS_CLIMB_STNC      = 56,
    LS_CLIMBING        = 57,
    LS_CLIMB_LEFT      = 58,
    LS_CLIMB_END       = 59,
    LS_CLIMB_RIGHT     = 60,
    LS_CLIMB_DOWN      = 61,
    LS_LARA_TEST1      = 62,
    LS_LARA_TEST2      = 63,
    LS_LARA_TEST3      = 64,
    LS_WADE            = 65,
    LS_WATER_ROLL      = 66,
    LS_FLARE_PICKUP    = 67,
    LS_TWIST           = 68,
    LS_KICK            = 69,
    LS_DEATHS_LIDE     = 70,
    LS_DUCK            = 71,
    LS_DUCK_ROLL       = 72,
    LS_DASH            = 73,
    LS_DASH_DIVE       = 74,
    LS_MONKEY_SWING    = 75,
    LS_MONKEYF         = 76,
    LS_LAST            = 77,
};
// clang-format on

struct PHD_3DPOS {
    int32_t x;
    int32_t y;
    int32_t z;
    PHD_ANGLE x_rot;
    PHD_ANGLE y_rot;
    PHD_ANGLE z_rot;
};

struct PHD_VECTOR {
    int32_t x;
    int32_t y;
    int32_t z;
};

struct GAME_VECTOR {
    int32_t x;
    int32_t y;
    int32_t z;
    int16_t room_num;
    int16_t box_num;
};

struct ROOM_INFO {
    int16_t *data;
    int16_t *door;
    struct FLOOR_INFO *floor;
    struct LIGHT_INFO *light;
    struct MESH_INFO *mesh;
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t min_floor;
    int32_t max_ceiling;
    int16_t x_size;
    int16_t y_size;
    int16_t ambient;
    int16_t lighting;
    int16_t num_lights;
    int16_t num_meshes;
    int16_t reverb_type;
    char mesh_effect;
    char bound_active;
    int16_t left;
    int16_t right;
    int16_t top;
    int16_t bottom;
    int16_t test_left;
    int16_t test_right;
    int16_t test_top;
    int16_t test_bottom;
    int16_t item_num;
    int16_t fx_num;
    int16_t flipped_room;
    uint16_t flags;
};

struct OBJECT_VECTOR {
    int32_t x;
    int32_t y;
    int32_t z;
    int16_t data;
    int16_t flags;
};

struct CAMERA_INFO {
    struct GAME_VECTOR pos;
    struct GAME_VECTOR target;
    int32_t type; // CAMERA_TYPE
    int32_t old_type; // CAMERA_TYPE
    int32_t shift;
    int32_t flags;
    int32_t fixed_camera;
    int32_t number_frames;
    int32_t bounce;
    int32_t underwater;
    int32_t target_distance;
    int32_t target_square;
    int16_t target_angle;
    int16_t actual_angle;
    int16_t target_elevation;
    int16_t box;
    int16_t number;
    int16_t last;
    int16_t timer;
    int16_t speed;
    int32_t min_ypos;
    struct ITEM_INFO *item;
    struct ITEM_INFO *last_item;
    struct OBJECT_VECTOR *fixed;
    int32_t mike_at_lara;
    struct PHD_VECTOR mike_pos;
};

struct COLL_INFO {
    int32_t mid_floor;
    int32_t mid_ceiling;
    int32_t mid_type;
    int32_t front_floor;
    int32_t front_ceiling;
    int32_t front_type;
    int32_t left_floor;
    int32_t left_ceiling;
    int32_t left_type;
    int32_t right_floor;
    int32_t right_ceiling;
    int32_t right_type;
    int32_t left_floor2;
    int32_t left_ceiling2;
    int32_t left_type2;
    int32_t right_floor2;
    int32_t right_ceiling2;
    int32_t right_type2;
    int32_t radius;
    int32_t bad_pos;
    int32_t bad_neg;
    int32_t bad_ceiling;
    struct PHD_VECTOR shift;
    struct PHD_VECTOR old;
    int16_t old_anim_state;
    int16_t old_anim_num;
    int16_t old_frame_num;
    int16_t facing;
    int16_t quadrant;
    int16_t coll_type;
    int16_t *trigger;
    signed char tilt_x;
    signed char tilt_z;
    char hit_by_baddie;
    char hit_static;
    uint16_t slopes_are_walls : 2;
    uint16_t slopes_are_pits : 1;
    uint16_t lava_is_pit : 1;
    uint16_t enable_baddie_push : 1;
    uint16_t enable_spaz : 1;
};

struct RGB888 {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct ANIM_INFO {
    int16_t *frame_ptr;
    int16_t interpolation;
    int16_t current_anim_state;
    int32_t velocity;
    int32_t acceleration;
    int16_t frame_base;
    int16_t frame_end;
    int16_t jump_anim_num;
    int16_t jump_frame_num;
    int16_t number_changes;
    int16_t change_index;
    int16_t number_commands;
    int16_t command_index;
};

struct ITEM_LIGHT {
    struct PHD_VECTOR sun_pos;
    struct PHD_VECTOR bulb_pos;
    struct PHD_VECTOR dynamic_pos;
    struct RGB888 sun_color;
    int8_t init;
    struct RGB888 bulb_color;
    uint8_t ambient;
    struct RGB888 dynamic_color;
    uint8_t pad2;
};

struct FX_INFO {
    struct PHD_3DPOS pos;
    int16_t room_num;
    int16_t object_num;
    int16_t next_fx;
    int16_t next_active;
    int16_t speed;
    int16_t fall_speed;
    int16_t frame_num;
    int16_t counter;
    int16_t shade;
    int16_t flag1;
    int16_t flag2;
};

struct ITEM_INFO {
    int32_t floor;
    uint32_t touch_bits;
    uint32_t mesh_bits;
    int16_t object_num;
    int16_t current_anim_state;
    int16_t goal_anim_state;
    int16_t required_anim_state;
    int16_t anim_num;
    int16_t frame_num;
    int16_t room_num;
    int16_t next_item;
    int16_t next_active;
    int16_t speed;
    int16_t fall_speed;
    int16_t hit_points;
    uint16_t box_num;
    int16_t timer;
    int16_t flags;
    int16_t shade;
    int16_t shade_b;
    int16_t carried_item;
    int16_t after_death;
    uint16_t fired_weapon;
    int16_t item_flags[4];
    void *data;
    struct PHD_3DPOS pos;
    struct ITEM_LIGHT il;
    uint16_t active : 1;
    uint16_t status : 2;
    uint16_t gravity_status : 1;
    uint16_t hit_status : 1;
    uint16_t collidable : 1;
    uint16_t looked_at : 1;
    uint16_t dynamic_light : 1;
    uint16_t clear_body : 1;
    uint16_t ai_bits : 5;
    uint16_t really_active : 1;
};

struct AI_INFO {
    int16_t zone_num;
    int16_t enemy_zone;
    int32_t distance;
    int32_t ahead, bite;
    int16_t angle;
    int16_t enemy_facing;
};

struct LOT_INFO {
    struct BOX_NODE *node;
    int16_t head;
    int16_t tail;
    uint16_t search_num;
    uint16_t block_mask;
    int16_t step;
    int16_t drop;
    int16_t fly;
    int16_t zone_count;
    int16_t target_box;
    int16_t required_box;
    struct PHD_VECTOR target;
};

struct CREATURE_INFO {
    int16_t head_rotation;
    int16_t neck_rotation;
    int16_t maximum_turn;
    int16_t flags;
    int16_t item_num;
    int32_t mood;
    struct LOT_INFO LOT;
    struct PHD_VECTOR target;
    struct ITEM_INFO *enemy;
};

struct LARA_ARM {
    int16_t *frame_base;
    int16_t frame_num;
    int16_t anim_num;
    int16_t lock;
    PHD_ANGLE y_rot;
    PHD_ANGLE x_rot;
    PHD_ANGLE z_rot;
    int16_t flash_gun;
};

struct AMMO_INFO {
    int32_t ammo;
};

struct LARA_INFO {
    int16_t item_num;
    int16_t gun_status;
    int16_t gun_type;
    int16_t request_gun_type;
    int16_t last_gun_type;
    int16_t calc_fall_speed;
    int16_t water_status;
    int16_t climb_status;
    int16_t pose_count;
    int16_t hit_frame;
    int16_t hit_direction;
    int16_t air;
    int16_t dive_count;
    int16_t death_count;
    int16_t current_active;
    int16_t current_xvel;
    int16_t current_yvel;
    int16_t current_zvel;
    int16_t spaz_effect_count;
    int16_t flare_age;
    int16_t skidoo;
    int16_t weapon_item;
    int16_t back_gun;
    int16_t flare_frame;
    int16_t poisoned;
    int16_t electric;
    uint16_t flare_control_left : 1;
    uint16_t flare_control_right : 1;
    uint16_t extra_anim : 1;
    uint16_t look : 1;
    uint16_t burn : 1;
    uint16_t keep_ducked : 1;
    uint16_t can_monkey_swing : 1;
    uint16_t mine_l : 1;
    uint16_t mine_r : 1;
    uint16_t burn_green : 1;
    uint16_t is_ducked : 1;
    uint16_t has_fired : 1;
    int32_t water_surface_dist;
    struct PHD_VECTOR last_pos;
    struct FX_INFO *spaz_effect;
    int32_t mesh_effects;
    int16_t *mesh_ptrs[15];
    struct ITEM_INFO *target;
    PHD_ANGLE target_angles[2];
    PHD_ANGLE turn_rate;
    PHD_ANGLE move_angle;
    PHD_ANGLE head_y_rot;
    PHD_ANGLE head_x_rot;
    PHD_ANGLE head_z_rot;
    PHD_ANGLE torso_y_rot;
    PHD_ANGLE torso_x_rot;
    PHD_ANGLE torso_z_rot;
    struct LARA_ARM left_arm;
    struct LARA_ARM right_arm;
    struct AMMO_INFO pistols;
    struct AMMO_INFO magnums;
    struct AMMO_INFO uzis;
    struct AMMO_INFO shotgun;
    struct AMMO_INFO harpoon;
    struct AMMO_INFO rocket;
    struct AMMO_INFO grenade;
    struct AMMO_INFO m16;
    struct CREATURE_INFO *creature;
};

#pragma pack(pop)
