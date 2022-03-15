#define MAX_REQLINES 40
#define MAX_LEVELS 24
#pragma pack(push, 1)

typedef int16_t PHD_ANGLE;
typedef uint16_t SG_COL;

struct PHD_3DPOS {
    int32_t x;
    int32_t y;
    int32_t z;
    PHD_ANGLE x_rot;
    PHD_ANGLE y_rot;
    PHD_ANGLE z_rot;
};

struct SPHERE {
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t r;
};

struct PHD_MATRIX {
    int32_t _00;
    int32_t _01;
    int32_t _02;
    int32_t _03;
    int32_t _10;
    int32_t _11;
    int32_t _12;
    int32_t _13;
    int32_t _20;
    int32_t _21;
    int32_t _22;
    int32_t _23;
};

struct PHD_VECTOR {
    int32_t x;
    int32_t y;
    int32_t z;
};

enum OBJECT_ID {
    O_INVALID = -1,
    O_LARA = 0,
    O_PISTOLS,
    O_HAIR,
    O_SHOTGUN,
    O_MAGNUM,
    O_UZI,
    O_M16,
    O_ROCKET_GUN,
    O_GRENADE_GUN,
    O_HARPOON_GUN,
    O_FLARE,
    O_VEHICLE_ANIM,
    O_VEHICLE_EXTRA,
    O_LARA_EXTRA,
    O_KAYAK,
    O_BOAT,
    O_QUADBIKE,
    O_MINECART,
    O_BIGGUN,
    O_UPV,
    O_TRIBEAXE,
    O_BLOWPIPE,
    O_DOG,
    O_SMALL_RAT,
    O_KILL_ALL_TRIGGERS,
    O_WHALE,
    O_DIVER,
    O_CROW,
    O_TIGER,
    O_VULTURE,
    O_TARGETS,
    O_BOO_MUTANT,
    O_CROCODILE,
    O_BUTTERFLY,
    O_COMPY,
    O_LIZARD_MAN,
    O_TRIBEBOSS,
    O_STHPAC_MERCENARY,
    O_CARCASS,
    O_OILRED,
    O_WHITE_SOLDIER,
    O_HUSKIE,
    O_BURNT_MUTANT,
    O_WILLARD,
    O_MUTANT1,
    O_MUTANT2,
    O_MUTANT3,
    O_FLYING_MUTANT_EMITTER,
    O_RAPTOR_EMITTER,
    O_WILLARD_BOSS,
    O_FLAMETHROWER_BLOKE,
    O_LON_MERCENARY1,
    O_LON_MERCENARY2,
    O_PUNK1,
    O_PUNK2,
    O_WATER_BLOKE,
    O_SECURITY_GUARD,
    O_LON_BOSS,
    O_ELECTRIC_CLEANER,
    O_FLOATING_CORPSE,
    O_MP1,
    O_MP2,
    O_BOB,
    O_SWAT_GUN,
    O_ROBOT_SENTRY_GUN,
    O_CIVVIE,
    O_SECURITY_LASER_ALARM,
    O_SECURITY_LASER_DEADLY,
    O_SECURITY_LASER_KILLER,
    O_COBRA,
    O_SHIVA,
    O_MONKEY,
    O_BEAR_TRAP,
    O_TONY,
    O_AI_GUARD,
    O_AI_AMBUSH,
    O_AI_PATROL1,
    O_AI_MODIFY,
    O_AI_FOLLOW,
    O_AI_PATROL2,
    O_AI_X1,
    O_AI_X2,
    O_AI_X3,
    O_FALLING_BLOCK,
    O_FALLING_BLOCK2,
    O_FALLING_PLANK,
    O_PENDULUM,
    O_SPIKES,
    O_ROLLING_BALL,
    O_BIG_ROLLING_BALL,
    O_DARTS,
    O_DART_EMITTER,
    O_HOMING_DART_EMITTER,
    O_DRAW_BRIDGE,
    O_TEETH_TRAP,
    O_LIFT,
    O_MOVING_BAR,
    O_MOVABLE_BLOCK,
    O_MOVABLE_BLOCK2,
    O_MOVABLE_BLOCK3,
    O_MOVABLE_BLOCK4,
    O_SMASH_WINDOW,
    O_SMASH_OBJECT1,
    O_SMASH_OBJECT2,
    O_SMASH_OBJECT3,
    O_SAW,
    O_HOOK,
    O_FALLING_CEILING1,
    O_SPINNING_BLADE,
    O_CIRCULAR_BLADE,
    O_TRAIN,
    O_BLADE,
    O_AVALANCHE,
    O_ICICLES,
    O_SPIKE_WALL,
    O_SPRING_BOARD,
    O_CEILING_SPIKES,
    O_AIRLOCK_SWITCH,
    O_SMALL_SWITCH,
    O_FAN,
    O_SMALL_FAN,
    O_SWING_BOX,
    O_MESHSWAP1,
    O_MESHSWAP2,
    O_MESHSWAP3,
    O_BORDERS,
    O_OILDRUMS,
    O_DEATH_SLIDE,
    O_PUSH_SWITCH,
    O_SWITCH_TYPE1,
    O_SWITCH_TYPE2,
    O_DOOR_TYPE1,
    O_DOOR_TYPE2,
    O_DOOR_TYPE3,
    O_DOOR_TYPE4,
    O_DOOR_TYPE5,
    O_DOOR_TYPE6,
    O_DOOR_TYPE7,
    O_DOOR_TYPE8,
    O_TRAPDOOR,
    O_TRAPDOOR2,
    O_BIGTRAPDOOR,
    O_BRIDGE_FLAT,
    O_BRIDGE_TILT1,
    O_BRIDGE_TILT2,
    O_PASSPORT_OPTION,
    O_MAP_OPTION,
    O_PHOTO_OPTION,
    O_PLAYER_1,
    O_PLAYER_2,
    O_PLAYER_3,
    O_PLAYER4,
    O_PLAYER_5,
    O_PLAYER_6,
    O_PLAYER_7,
    O_PLAYER_8,
    O_PLAYER_9,
    O_PLAYER_10,
    O_PASSPORT_CLOSED,
    O_MAP_CLOSED,
    O_GUN_ITEM,
    O_SHOTGUN_ITEM,
    O_MAGNUM_ITEM,
    O_UZI_ITEM,
    O_HARPOON_ITEM,
    O_M16_ITEM,
    O_ROCKET_GUN_ITEM,
    O_GRENADE_GUN_ITEM,
    O_GUN_AMMO_ITEM,
    O_SG_AMMO_ITEM,
    O_MAG_AMMO_ITEM,
    O_UZI_AMMO_ITEM,
    O_HARPOON_AMMO_ITEM,
    O_M16_AMMO_ITEM,
    O_ROCKET_AMMO_ITEM,
    O_GRENADE_AMMO_ITEM,
    O_MEDI_ITEM,
    O_BIGMEDI_ITEM,
    O_FLAREBOX_ITEM,
    O_FLARE_ITEM,
    O_SAVEGAME_CRYSTAL_ITEM,
    O_DETAIL_OPTION,
    O_SOUND_OPTION,
    O_CONTROL_OPTION,
    O_GAMMA_OPTION,
    O_GUN_OPTION,
    O_SHOTGUN_OPTION,
    O_MAGNUM_OPTION,
    O_UZI_OPTION,
    O_HARPOON_OPTION,
    O_M16_OPTION,
    O_ROCKET_OPTION,
    O_GRENADE_OPTION,
    O_GUN_AMMO_OPTION,
    O_SG_AMMO_OPTION,
    O_MAG_AMMO_OPTION,
    O_UZI_AMMO_OPTION,
    O_HARPOON_AMMO_OPTION,
    O_M16_AMMO_OPTION,
    O_ROCKET_AMMO_OPTION,
    O_GRENADE_AMMO_OPTION,
    O_MEDI_OPTION,
    O_BIGMEDI_OPTION,
    O_FLAREBOX_OPTION,
    O_SAVEGAME_CRYSTAL_OPTION,
    O_PUZZLE_ITEM1,
    O_PUZZLE_ITEM2,
    O_PUZZLE_ITEM3,
    O_PUZZLE_ITEM4,
    O_PUZZLE_OPTION1,
    O_PUZZLE_OPTION2,
    O_PUZZLE_OPTION3,
    O_PUZZLE_OPTION4,
    O_PUZZLE_HOLE1,
    O_PUZZLE_HOLE2,
    O_PUZZLE_HOLE3,
    O_PUZZLE_HOLE4,
    O_PUZZLE_DONE1,
    O_PUZZLE_DONE2,
    O_PUZZLE_DONE3,
    O_PUZZLE_DONE4,
    O_SECRET_ITEM1,
    O_SECRET_ITEM2,
    O_SECRET_ITEM3,
    O_KEY_ITEM1,
    O_KEY_ITEM2,
    O_KEY_ITEM3,
    O_KEY_ITEM4,
    O_KEY_OPTION1,
    O_KEY_OPTION2,
    O_KEY_OPTION3,
    O_KEY_OPTION4,
    O_KEY_HOLE1,
    O_KEY_HOLE2,
    O_KEY_HOLE3,
    O_KEY_HOLE4,
    O_PICKUP_ITEM1,
    O_PICKUP_ITEM2,
    O_PICKUP_OPTION1,
    O_PICKUP_OPTION2,
    O_ICON_PICKUP1_ITEM,
    O_ICON_PICKUP2_ITEM,
    O_ICON_PICKUP3_ITEM,
    O_ICON_PICKUP4_ITEM,
    O_ICON_PICKUP1_OPTION,
    O_ICON_PICKUP2_OPTION,
    O_ICON_PICKUP3_OPTION,
    O_ICON_PICKUP4_OPTION,
    O_PICKUPDISPLAY_PISTOLS,
    O_PICKUPDISPLAY_SHOTGUN,
    O_PICKUPDISPLAY_DESERTEAGLE,
    O_PICKUPDISPLAY_UZIS,
    O_PICKUPDISPLAY_HARPOON,
    O_PICKUPDISPLAY_HANDK,
    O_PICKUPDISPLAY_ROCKET_LAUNCHER,
    O_PICKUPDISPLAY_GRENADE_LAUNCHER,
    O_PICKUPDISPLAY_PISTOLS_AMMO,
    O_PICKUPDISPLAY_SHOTGUN_AMMO,
    O_PICKUPDISPLAY_DESERTEAGLE_AMMO,
    O_PICKUPDISPLAY_UZIS_AMMO,
    O_PICKUPDISPLAY_HARPOON_AMMO,
    O_PICKUPDISPLAY_HANDK_AMMO,
    O_PICKUPDISPLAY_ROCKET_LAUNCHER_AMMO,
    O_PICKUPDISPLAY_GRENADE_LAUNCHER_AMMO,
    O_PICKUPDISPLAY_SMALLMEDI,
    O_PICKUPDISPLAY_BIGMEDI,
    O_PICKUPDISPLAY_FLAREBOX,
    O_PICKUPDISPLAY_SGCRYSTAL,
    O_PICKUPDISPLAY_PUZZLE1,
    O_PICKUPDISPLAY_PUZZLE2,
    O_PICKUPDISPLAY_PUZZLE3,
    O_PICKUPDISPLAY_PUZZLE4,
    O_PICKUPDISPLAY_KEY1,
    O_PICKUPDISPLAY_KEY2,
    O_PICKUPDISPLAY_KEY3,
    O_PICKUPDISPLAY_KEY4,
    O_PICKUPDISPLAY_ICON1,
    O_PICKUPDISPLAY_ICON2,
    O_PICKUPDISPLAY_ICON3,
    O_PICKUPDISPLAY_ICON4,
    O_PICKUPDISPLAY_PICKUP1,
    O_PICKUPDISPLAY_PICKUP2,
    O_FIREHEAD,
    O_TONYFIREBALL,
    O_SPHERE_OF_DOOM3,
    O_ALARM_SOUND,
    O_WATER_DRIP,
    O_TREX,
    O_RAPTOR,
    O_BIRD_TWEETER,
    O_CLOCK_CHIMES,
    O_AREA51_LASER,
    O_LIGHTNING_EMITTER2,
    O_HOT_LIQUID,
    O_SHADOW,
    O_DETONATOR,
    O_EXPLOSION1,
    O_BUBBLES1,
    O_BUBBLES2,
    O_GLOW,
    O_GUN_FLASH,
    O_M16_FLASH,
    O_DESERT_EAGLE_FLASH,
    O_BODY_PART,
    O_CAMERA_TARGET,
    O_WATERFALL,
    O_DIVER_HARPOON,
    O_DRAGON_FIRE,
    O_KNIFE,
    O_ROCKET,
    O_HARPOON_BOLT,
    O_GRENADE,
    O_SPECIAL_FX1,
    O_SPECIAL_FX2,
    O_SPECIAL_FX3,
    O_LARA_SKIN,
    O_LAVA,
    O_LAVA_EMITTER,
    O_STROBE_LIGHT,
    O_ELECTRICAL_LIGHT,
    O_ON_OFF_LIGHT,
    O_PULSE_LIGHT,
    O_EXTRA_LIGHT1,
    O_EXTRA_LIGHT2,
    O_RED_LIGHT,
    O_GREEN_LIGHT,
    O_BLUE_LIGHT,
    O_AMBER_LIGHT,
    O_WHITE_LIGHT,
    O_FLAME,
    O_FLAME_EMITTER,
    O_FLAME_EMITTER2,
    O_FLAME_EMITTER3,
    O_SIDE_FLAME_EMITTER,
    O_SMOKE_EMITTER_WHITE,
    O_SMOKE_EMITTER_BLACK,
    O_STEAM_EMITTER,
    O_GHOST_GAS_EMITTER,
    O_PIRAHNAS,
    O_TROPICAL_FISH,
    O_PIRAHNA_GFX,
    O_TROPICAL_FISH_GFX,
    O_BAT_GFX,
    O_TRIBEBOSS_GFX,
    O_SPIDER_GFX,
    O_TUMBLEWEED,
    O_LEAVES,
    O_BAT_EMITTER,
    O_BIRD_EMITTER,
    O_ANIMATING1,
    O_ANIMATING2,
    O_ANIMATING3,
    O_ANIMATING4,
    O_ANIMATING5,
    O_ANIMATING6,
    O_HORIZON,
    O_ALPHABET,
    O_DING_DONG,
    O_LARA_ALARM,
    O_MINI_COPTER,
    O_WINSTON,
    O_ARMY_WINSTON,
    O_ASSAULT_NUMBERS,
    O_FINAL_LEVEL,
    O_CUT_SHOTGUN,
    O_EARTHQUAKE,
    O_GUNSHELL,
    O_SHOTGUNSHELL,
    O_EXTRAFX1,
    O_EXTRAFX2,
    O_EXTRAFX3,
    O_EXTRAFX4,
    O_EXTRAFX5,
    O_EXTRAFX6,
    O_EXTRAFX7,
    O_EXTRAFX8,
    O_NUMBER_OF,
};

struct TEXTSTRING {
    uint32_t flags;
    uint16_t text_flags;
    uint16_t bgnd_flags;
    uint16_t outl_flags;
    int16_t xpos;
    int16_t ypos;
    int16_t zpos;
    int16_t letter_spacing;
    int16_t word_spacing;
    int16_t flash_rate;
    int16_t flash_count;
    int16_t bgnd_colour;
    SG_COL *bgnd_gour;
    int16_t outl_colour;
    SG_COL *outl_gour;
    int16_t bgnd_size_x;
    int16_t bgnd_size_y;
    int16_t bgnd_off_x;
    int16_t bgnd_off_y;
    int16_t bgnd_off_z;
    int32_t scale_h;
    int32_t scale_v;
    int16_t colour;
    char *string;
};

struct REQUEST_INFO {
    uint16_t noselector : 1;
    uint16_t items;
    uint16_t selected;
    uint16_t vis_lines;
    uint16_t line_offset;
    uint16_t line_oldoffset;
    uint16_t pix_width;
    uint16_t line_height;
    int16_t xpos;
    int16_t ypos;
    int16_t zpos;
    int16_t item_text_len;
    char *item_texts1;
    char *item_texts2;
    uint32_t *item_texts1_flags;
    uint32_t *item_texts2_flags;
    uint32_t heading1_flags;
    uint32_t heading2_flags;
    uint32_t background_flags;
    uint32_t moreup_flags;
    uint32_t moredown_flags;
    uint32_t texts1_flags[MAX_REQLINES];
    uint32_t texts2_flags[MAX_REQLINES];
    TEXTSTRING *heading1_text;
    TEXTSTRING *heading2_text;
    TEXTSTRING *background_text;
    TEXTSTRING *moreup_text;
    TEXTSTRING *moredown_text;
    TEXTSTRING *texts1[MAX_REQLINES];
    TEXTSTRING *texts2[MAX_REQLINES];
    char heading1_str[32];
    char heading2_str[32];
    int32_t original_render_width;
    int32_t original_render_height;
};

struct INVENTORY_SPRITE {
    int16_t shape;
    int16_t x;
    int16_t y;
    int16_t z;
    int32_t param1;
    int32_t param2;
    SG_COL *grdptr;
    int16_t sprnum;
};

struct IMOTION_INFO {
    int16_t count;
    int16_t status;
    int16_t status_target;
    int16_t radius_target;
    int16_t radius_rate;
    int16_t camera_ytarget;
    int16_t camera_yrate;
    int16_t camera_pitch_target;
    int16_t camera_pitch_rate;
    int16_t rotate_target;
    int16_t rotate_rate;
    PHD_ANGLE item_ptxrot_target;
    PHD_ANGLE item_ptxrot_rate;
    PHD_ANGLE item_xrot_target;
    PHD_ANGLE item_xrot_rate;
    int32_t item_ytrans_target;
    int32_t item_ytrans_rate;
    int32_t item_ztrans_target;
    int32_t item_ztrans_rate;
    int32_t misc;
};

struct INVENTORY_ITEM {
    char *item_text;
    int16_t object_num;
    int16_t frames_total;
    int16_t current_frame;
    int16_t goal_frame;
    int16_t open_frame;
    int16_t anim_direction;
    int16_t anim_speed;
    int16_t anim_count;
    PHD_ANGLE pt_xrot_sel;
    PHD_ANGLE pt_xrot;
    PHD_ANGLE x_rot_sel;
    PHD_ANGLE x_rot_nosel;
    PHD_ANGLE x_rot;
    PHD_ANGLE y_rot_sel;
    PHD_ANGLE y_rot;
    int32_t ytrans_sel;
    int32_t ytrans;
    int32_t ztrans_sel;
    int32_t ztrans;
    uint32_t which_meshes;
    uint32_t drawn_meshes;
    int16_t inv_pos;
    INVENTORY_SPRITE **sprlist;
    int32_t misc_data[4];
};

struct RING_INFO {
    INVENTORY_ITEM **list;
    int16_t type;
    int16_t radius;
    int16_t camera_pitch;
    int16_t rotating;
    int16_t rot_count;
    int16_t current_object;
    int16_t target_object;
    int16_t number_of_objects;
    int16_t angle_adder;
    int16_t rot_adder;
    int16_t rot_adder_l;
    int16_t rot_adder_r;
    PHD_3DPOS ringpos;
    PHD_3DPOS camera;
    PHD_VECTOR light;
    IMOTION_INFO *imo;
};

struct ITEM_LIGHT {
    PHD_VECTOR sun;
    PHD_VECTOR bulb;
    PHD_VECTOR dynamic;
    unsigned char sunr;
    unsigned char sung;
    unsigned char sunb;
    char init;
    unsigned char bulbr;
    unsigned char bulbg;
    unsigned char bulbb;
    unsigned char ambient;
    unsigned char dynamicr;
    unsigned char dynamicg;
    unsigned char dynamicb;
    unsigned char pad2;
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
    int16_t fallspeed;
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
    PHD_3DPOS pos;
    ITEM_LIGHT il;
    uint16_t active:         1;
    uint16_t status:         2;
    uint16_t gravity_status: 1;
    uint16_t hit_status:     1;
    uint16_t collidable:     1;
    uint16_t looked_at:      1;
    uint16_t dynamic_light:  1;
    uint16_t clear_body:     1;
    uint16_t ai_bits:        5;
    uint16_t really_active:  1;
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
    int32_t radius;
    int32_t bad_pos;
    int32_t bad_neg;
    int32_t bad_ceiling;
    PHD_VECTOR shift;
    PHD_VECTOR old;
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
    uint16_t slopes_are_walls:   2;
    uint16_t slopes_are_pits:    1;
    uint16_t lava_is_pit:        1;
    uint16_t enable_baddie_push: 1;
    uint16_t enable_spaz:        1;
};

struct SPLASH_SETUP
{
    int32_t x;
    int32_t y;
    int32_t z;
    int16_t inner_xz_off;
    int16_t inner_xz_size;
    int16_t inner_y_size;
    int16_t inner_xz_vel;
    int16_t inner_y_vel;
    int16_t inner_gravity;
    int16_t inner_friction;
    int16_t middle_xz_off;
    int16_t middle_xz_size;
    int16_t middle_y_size;
    int16_t middle_xz_vel;
    int16_t middle_y_vel;
    int16_t middle_gravity;
    int16_t middle_friction;
    int16_t outer_xz_off;
    int16_t outer_xz_size;
    int16_t outer_xz_vel;
    int16_t outer_friction;
};

struct FLOOR_INFO {
    uint16_t index;
    uint16_t fx:      4;
    uint16_t box:     11;
    uint16_t stopper: 1;
    unsigned char pit_room;
    signed char floor;
    unsigned char sky_room;
    signed char ceiling;
};

struct SUNLIGHT {
    int16_t nx;
    int16_t ny;
    int16_t nz;
    int16_t pad;
};

struct SPOTLIGHT {
    int32_t intensity;
    int32_t falloff;
};

struct LIGHT_INFO {
    int32_t x;
    int32_t y;
    int32_t z;
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t type;
    union {
        SUNLIGHT sun;
        SPOTLIGHT spot;
    } l;
};

struct MESH_INFO {
    int32_t x;
    int32_t y;
    int32_t z;
    PHD_ANGLE y_rot;
    int16_t shade;
    int16_t shade_b;
    int16_t static_number;
};

struct ROOM_INFO {
    int16_t *data;
    int16_t *door;
    FLOOR_INFO *floor;
    LIGHT_INFO *light;
    MESH_INFO *mesh;
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
    int16_t item_number;
    int16_t fx_number;
    int16_t flipped_room;
    uint16_t flags;
};

struct FX_INFO {
    PHD_3DPOS pos;
    int16_t room_num;
    int16_t object_num;
    int16_t next_fx;
    int16_t next_active;
    int16_t speed;
    int16_t fallspeed;
    int16_t frame_num;
    int16_t counter;
    int16_t shade;
    int16_t flag1;
    int16_t flag2;
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

struct WEAPON_INFO {
    PHD_ANGLE lock_angles[4];
    PHD_ANGLE left_angles[4];
    PHD_ANGLE right_angles[4];
    PHD_ANGLE aim_speed;
    PHD_ANGLE shot_accuracy;
    int16_t gun_height;
    int16_t target_dist;
    char damage;
    char recoil_frame;
    char flash_time;
    char draw_frame;
    int16_t sample_num;
};

struct AMMO_INFO {
    int32_t ammo;
};

struct BOX_INFO {
    uint8_t left;
    uint8_t right;
    uint8_t top;
    uint8_t bottom;
    int16_t height;
    int16_t overlap_index;
};

struct BOX_NODE {
    int16_t exit_box;
    uint16_t search_num;
    int16_t next_expansion;
    int16_t box_num;
};

enum TARGET_TYPE {
    NO_TARGET,
    PRIME_TARGET,
    SECONDARY_TARGET
};

enum MOOD_TYPE {
    BORED_MOOD,
    ATTACK_MOOD,
    ESCAPE_MOOD,
    STALK_MOOD
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
    BOX_NODE *node;
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
    PHD_VECTOR target;
};

struct CREATURE_INFO {
    int16_t head_rotation;
    int16_t neck_rotation;
    int16_t maximum_turn;
    int16_t flags;
    int16_t item_num;
    MOOD_TYPE mood;
    LOT_INFO LOT;
    PHD_VECTOR target;
    ITEM_INFO *enemy;
};

struct LARA_INFO {
    int16_t item_num;
    int16_t gun_status;
    int16_t gun_type;
    int16_t request_gun_type;
    int16_t last_gun_type;
    int16_t calc_fallspeed;
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
    uint32_t flare_control_left:  1;
    uint32_t flare_control_right: 1;
    uint32_t extra_anim:          1;
    uint32_t look:                1;
    uint32_t burn:                1;
    uint32_t keep_ducked:         1;
    uint32_t can_monkey_swing:    1;
    uint32_t mine_l:              1;
    uint32_t mine_r:              1;
    uint32_t burn_green:          1;
    uint32_t is_ducked:           1;
    uint32_t has_fired:           1;
    int32_t water_surface_dist;
    PHD_VECTOR last_pos;
    FX_INFO *spaz_effect;
    int32_t mesh_effects;
    int16_t *mesh_ptrs[15];
    ITEM_INFO *target;
    PHD_ANGLE target_angles[2];
    PHD_ANGLE turn_rate;
    PHD_ANGLE move_angle;
    PHD_ANGLE head_y_rot;
    PHD_ANGLE head_x_rot;
    PHD_ANGLE head_z_rot;
    PHD_ANGLE torso_y_rot;
    PHD_ANGLE torso_x_rot;
    PHD_ANGLE torso_z_rot;
    LARA_ARM left_arm;
    LARA_ARM right_arm;
    AMMO_INFO pistols;
    AMMO_INFO magnums;
    AMMO_INFO uzis;
    AMMO_INFO shotgun;
    AMMO_INFO harpoon;
    AMMO_INFO rocket;
    AMMO_INFO grenade;
    AMMO_INFO m16;
    CREATURE_INFO *creature;
};

struct GAME_VECTOR {
    int32_t x;
    int32_t y;
    int32_t z;
    int16_t room_num;
    int16_t box_num;
};

struct OBJECT_VECTOR {
    int32_t x;
    int32_t y;
    int32_t z;
    int16_t data;
    int16_t flags;
};

struct ANIM_STRUCT {
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

struct CHANGE_STRUCT {
    int16_t goal_anim_state;
    int16_t number_ranges;
    int16_t range_index;
};

struct RANGE_STRUCT {
    int16_t start_frame;
    int16_t end_frame;
    int16_t link_anim_num;
    int16_t link_frame_num;
};

struct RIPPLE_STRUCT {
    int32_t x;
    int32_t y;
    int32_t z;
    char flags;
    unsigned char life;
    unsigned char size;
    unsigned char init;
};


struct KAYAK_INFO {
    int32_t vel;
    int32_t rot;
    int32_t fall_speed_f;
    int32_t fall_speed_l;
    int32_t fall_speed_r;
    int32_t water;
    PHD_3DPOS old_pos;
    char turn;
    char forward;
    char true_water;
    char flags;
};

#pragma pack(pop)
