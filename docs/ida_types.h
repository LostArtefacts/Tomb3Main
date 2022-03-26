#define MAX_REQLINES 40
#define MAX_LEVELS 24
#pragma pack(push, 1)

typedef int16_t PHD_ANGLE;
typedef uint16_t SG_COL;

enum SORT_TYPE {
    MID_SORT,
    FAR_SORT,
    BACK_SORT,
};

enum SOUND_EFFECT_ID {
    SFX_LARA_FALL = 30,
};

enum OBJECT_ID {
    O_INVALID = -1,
    O_LARA = 0,
    O_PISTOLS = 1,
    O_HAIR = 2,
    O_SHOTGUN = 3,
    O_MAGNUM = 4,
    O_UZI = 5,
    O_M16 = 6,
    O_ROCKET_GUN = 7,
    O_GRENADE_GUN = 8,
    O_HARPOON_GUN = 9,
    O_FLARE = 10,
    O_VEHICLE_ANIM = 11,
    O_VEHICLE_EXTRA = 12,
    O_LARA_EXTRA = 13,
    O_KAYAK = 14,
    O_BOAT = 15,
    O_QUADBIKE = 16,
    O_MINECART = 17,
    O_BIGGUN = 18,
    O_UPV = 19,
    O_TRIBEAXE = 20,
    O_BLOWPIPE = 21,
    O_DOG = 22,
    O_SMALL_RAT = 23,
    O_KILL_ALL_TRIGGERS = 24,
    O_WHALE = 25,
    O_DIVER = 26,
    O_CROW = 27,
    O_TIGER = 28,
    O_VULTURE = 29,
    O_TARGETS = 30,
    O_BOO_MUTANT = 31,
    O_CROCODILE = 32,
    O_BUTTERFLY = 33,
    O_COMPY = 34,
    O_LIZARD_MAN = 35,
    O_TRIBEBOSS = 36,
    O_STHPAC_MERCENARY = 37,
    O_CARCASS = 38,
    O_OILRED = 39,
    O_WHITE_SOLDIER = 40,
    O_HUSKIE = 41,
    O_BURNT_MUTANT = 42,
    O_WILLARD = 43,
    O_MUTANT1 = 44,
    O_MUTANT2 = 45,
    O_MUTANT3 = 46,
    O_FLYING_MUTANT_EMITTER = 47,
    O_RAPTOR_EMITTER = 48,
    O_WILLARD_BOSS = 49,
    O_FLAMETHROWER_BLOKE = 50,
    O_LON_MERCENARY1 = 51,
    O_LON_MERCENARY2 = 52,
    O_PUNK1 = 53,
    O_PUNK2 = 54,
    O_WATER_BLOKE = 55,
    O_SECURITY_GUARD = 56,
    O_LON_BOSS = 57,
    O_ELECTRIC_CLEANER = 58,
    O_FLOATING_CORPSE = 59,
    O_MP1 = 60,
    O_MP2 = 61,
    O_BOB = 62,
    O_SWAT_GUN = 63,
    O_ROBOT_SENTRY_GUN = 64,
    O_CIVVIE = 65,
    O_SECURITY_LASER_ALARM = 66,
    O_SECURITY_LASER_DEADLY = 67,
    O_SECURITY_LASER_KILLER = 68,
    O_COBRA = 69,
    O_SHIVA = 70,
    O_MONKEY = 71,
    O_BEAR_TRAP = 72,
    O_TONY = 73,
    O_AI_GUARD = 74,
    O_AI_AMBUSH = 75,
    O_AI_PATROL1 = 76,
    O_AI_MODIFY = 77,
    O_AI_FOLLOW = 78,
    O_AI_PATROL2 = 79,
    O_AI_X1 = 80,
    O_AI_X2 = 81,
    O_AI_X3 = 82,
    O_FALLING_BLOCK = 83,
    O_FALLING_BLOCK2 = 84,
    O_FALLING_PLANK = 85,
    O_PENDULUM = 86,
    O_SPIKES = 87,
    O_ROLLING_BALL = 88,
    O_BIG_ROLLING_BALL = 89,
    O_DARTS = 90,
    O_DART_EMITTER = 91,
    O_HOMING_DART_EMITTER = 92,
    O_DRAW_BRIDGE = 93,
    O_TEETH_TRAP = 94,
    O_LIFT = 95,
    O_MOVING_BAR = 96,
    O_MOVABLE_BLOCK = 97,
    O_MOVABLE_BLOCK2 = 98,
    O_MOVABLE_BLOCK3 = 99,
    O_MOVABLE_BLOCK4 = 100,
    O_SMASH_WINDOW = 101,
    O_SMASH_OBJECT1 = 102,
    O_SMASH_OBJECT2 = 103,
    O_SMASH_OBJECT3 = 104,
    O_SAW = 105,
    O_HOOK = 106,
    O_FALLING_CEILING1 = 107,
    O_SPINNING_BLADE = 108,
    O_CIRCULAR_BLADE = 109,
    O_TRAIN = 110,
    O_BLADE = 111,
    O_AVALANCHE = 112,
    O_ICICLES = 113,
    O_SPIKE_WALL = 114,
    O_SPRING_BOARD = 115,
    O_CEILING_SPIKES = 116,
    O_AIRLOCK_SWITCH = 117,
    O_SMALL_SWITCH = 118,
    O_FAN = 119,
    O_SMALL_FAN = 120,
    O_SWING_BOX = 121,
    O_MESHSWAP1 = 122,
    O_MESHSWAP2 = 123,
    O_MESHSWAP3 = 124,
    O_BORDERS = 125,
    O_OILDRUMS = 126,
    O_DEATH_SLIDE = 127,
    O_PUSH_SWITCH = 128,
    O_SWITCH_TYPE1 = 129,
    O_SWITCH_TYPE2 = 130,
    O_DOOR_TYPE1 = 131,
    O_DOOR_TYPE2 = 132,
    O_DOOR_TYPE3 = 133,
    O_DOOR_TYPE4 = 134,
    O_DOOR_TYPE5 = 135,
    O_DOOR_TYPE6 = 136,
    O_DOOR_TYPE7 = 137,
    O_DOOR_TYPE8 = 138,
    O_TRAPDOOR = 139,
    O_TRAPDOOR2 = 140,
    O_BIGTRAPDOOR = 141,
    O_BRIDGE_FLAT = 142,
    O_BRIDGE_TILT1 = 143,
    O_BRIDGE_TILT2 = 144,
    O_PASSPORT_OPTION = 145,
    O_MAP_OPTION = 146,
    O_PHOTO_OPTION = 147,
    O_PLAYER_1 = 148,
    O_PLAYER_2 = 149,
    O_PLAYER_3 = 150,
    O_PLAYER4 = 151,
    O_PLAYER_5 = 152,
    O_PLAYER_6 = 153,
    O_PLAYER_7 = 154,
    O_PLAYER_8 = 155,
    O_PLAYER_9 = 156,
    O_PLAYER_10 = 157,
    O_PASSPORT_CLOSED = 158,
    O_MAP_CLOSED = 159,
    O_GUN_ITEM = 160,
    O_SHOTGUN_ITEM = 161,
    O_MAGNUM_ITEM = 162,
    O_UZI_ITEM = 163,
    O_HARPOON_ITEM = 164,
    O_M16_ITEM = 165,
    O_ROCKET_GUN_ITEM = 166,
    O_GRENADE_GUN_ITEM = 167,
    O_GUN_AMMO_ITEM = 168,
    O_SG_AMMO_ITEM = 169,
    O_MAG_AMMO_ITEM = 170,
    O_UZI_AMMO_ITEM = 171,
    O_HARPOON_AMMO_ITEM = 172,
    O_M16_AMMO_ITEM = 173,
    O_ROCKET_AMMO_ITEM = 174,
    O_GRENADE_AMMO_ITEM = 175,
    O_MEDI_ITEM = 176,
    O_BIGMEDI_ITEM = 177,
    O_FLAREBOX_ITEM = 178,
    O_FLARE_ITEM = 179,
    O_SAVEGAME_CRYSTAL_ITEM = 180,
    O_DETAIL_OPTION = 181,
    O_SOUND_OPTION = 182,
    O_CONTROL_OPTION = 183,
    O_GAMMA_OPTION = 184,
    O_GUN_OPTION = 185,
    O_SHOTGUN_OPTION = 186,
    O_MAGNUM_OPTION = 187,
    O_UZI_OPTION = 188,
    O_HARPOON_OPTION = 189,
    O_M16_OPTION = 190,
    O_ROCKET_OPTION = 191,
    O_GRENADE_OPTION = 192,
    O_GUN_AMMO_OPTION = 193,
    O_SG_AMMO_OPTION = 194,
    O_MAG_AMMO_OPTION = 195,
    O_UZI_AMMO_OPTION = 196,
    O_HARPOON_AMMO_OPTION = 197,
    O_M16_AMMO_OPTION = 198,
    O_ROCKET_AMMO_OPTION = 199,
    O_GRENADE_AMMO_OPTION = 200,
    O_MEDI_OPTION = 201,
    O_BIGMEDI_OPTION = 202,
    O_FLAREBOX_OPTION = 203,
    O_SAVEGAME_CRYSTAL_OPTION = 204,
    O_PUZZLE_ITEM1 = 205,
    O_PUZZLE_ITEM2 = 206,
    O_PUZZLE_ITEM3 = 207,
    O_PUZZLE_ITEM4 = 208,
    O_PUZZLE_OPTION1 = 209,
    O_PUZZLE_OPTION2 = 210,
    O_PUZZLE_OPTION3 = 211,
    O_PUZZLE_OPTION4 = 212,
    O_PUZZLE_HOLE1 = 213,
    O_PUZZLE_HOLE2 = 214,
    O_PUZZLE_HOLE3 = 215,
    O_PUZZLE_HOLE4 = 216,
    O_PUZZLE_DONE1 = 217,
    O_PUZZLE_DONE2 = 218,
    O_PUZZLE_DONE3 = 219,
    O_PUZZLE_DONE4 = 220,
    O_SECRET_ITEM1 = 221,
    O_SECRET_ITEM2 = 222,
    O_SECRET_ITEM3 = 223,
    O_KEY_ITEM1 = 224,
    O_KEY_ITEM2 = 225,
    O_KEY_ITEM3 = 226,
    O_KEY_ITEM4 = 227,
    O_KEY_OPTION1 = 228,
    O_KEY_OPTION2 = 229,
    O_KEY_OPTION3 = 230,
    O_KEY_OPTION4 = 231,
    O_KEY_HOLE1 = 232,
    O_KEY_HOLE2 = 233,
    O_KEY_HOLE3 = 234,
    O_KEY_HOLE4 = 235,
    O_PICKUP_ITEM1 = 236,
    O_PICKUP_ITEM2 = 237,
    O_PICKUP_OPTION1 = 238,
    O_PICKUP_OPTION2 = 239,
    O_ICON_PICKUP1_ITEM = 240,
    O_ICON_PICKUP2_ITEM = 241,
    O_ICON_PICKUP3_ITEM = 242,
    O_ICON_PICKUP4_ITEM = 243,
    O_ICON_PICKUP1_OPTION = 244,
    O_ICON_PICKUP2_OPTION = 245,
    O_ICON_PICKUP3_OPTION = 246,
    O_ICON_PICKUP4_OPTION = 247,
    O_PICKUPDISPLAY_PISTOLS = 248,
    O_PICKUPDISPLAY_SHOTGUN = 249,
    O_PICKUPDISPLAY_DESERTEAGLE = 250,
    O_PICKUPDISPLAY_UZIS = 251,
    O_PICKUPDISPLAY_HARPOON = 252,
    O_PICKUPDISPLAY_HANDK = 253,
    O_PICKUPDISPLAY_ROCKET_LAUNCHER = 254,
    O_PICKUPDISPLAY_GRENADE_LAUNCHER = 255,
    O_PICKUPDISPLAY_PISTOLS_AMMO = 256,
    O_PICKUPDISPLAY_SHOTGUN_AMMO = 257,
    O_PICKUPDISPLAY_DESERTEAGLE_AMMO = 258,
    O_PICKUPDISPLAY_UZIS_AMMO = 259,
    O_PICKUPDISPLAY_HARPOON_AMMO = 260,
    O_PICKUPDISPLAY_HANDK_AMMO = 261,
    O_PICKUPDISPLAY_ROCKET_LAUNCHER_AMMO = 262,
    O_PICKUPDISPLAY_GRENADE_LAUNCHER_AMMO = 263,
    O_PICKUPDISPLAY_SMALLMEDI = 264,
    O_PICKUPDISPLAY_BIGMEDI = 265,
    O_PICKUPDISPLAY_FLAREBOX = 266,
    O_PICKUPDISPLAY_SGCRYSTAL = 267,
    O_PICKUPDISPLAY_PUZZLE1 = 268,
    O_PICKUPDISPLAY_PUZZLE2 = 269,
    O_PICKUPDISPLAY_PUZZLE3 = 270,
    O_PICKUPDISPLAY_PUZZLE4 = 271,
    O_PICKUPDISPLAY_KEY1 = 272,
    O_PICKUPDISPLAY_KEY2 = 273,
    O_PICKUPDISPLAY_KEY3 = 274,
    O_PICKUPDISPLAY_KEY4 = 275,
    O_PICKUPDISPLAY_ICON1 = 276,
    O_PICKUPDISPLAY_ICON2 = 277,
    O_PICKUPDISPLAY_ICON3 = 278,
    O_PICKUPDISPLAY_ICON4 = 279,
    O_PICKUPDISPLAY_PICKUP1 = 280,
    O_PICKUPDISPLAY_PICKUP2 = 281,
    O_FIREHEAD = 282,
    O_TONYFIREBALL = 283,
    O_SPHERE_OF_DOOM3 = 284,
    O_ALARM_SOUND = 285,
    O_WATER_DRIP = 286,
    O_TREX = 287,
    O_RAPTOR = 288,
    O_BIRD_TWEETER = 289,
    O_CLOCK_CHIMES = 290,
    O_AREA51_LASER = 291,
    O_LIGHTNING_EMITTER2 = 292,
    O_HOT_LIQUID = 293,
    O_SHADOW = 294,
    O_DETONATOR = 295,
    O_EXPLOSION1 = 296,
    O_BUBBLES1 = 297,
    O_BUBBLES2 = 298,
    O_GLOW = 299,
    O_GUN_FLASH = 300,
    O_M16_FLASH = 301,
    O_DESERT_EAGLE_FLASH = 302,
    O_BODY_PART = 303,
    O_CAMERA_TARGET = 304,
    O_WATERFALL = 305,
    O_DIVER_HARPOON = 306,
    O_DRAGON_FIRE = 307,
    O_KNIFE = 308,
    O_ROCKET = 309,
    O_HARPOON_BOLT = 310,
    O_GRENADE = 311,
    O_SPECIAL_FX1 = 312,
    O_SPECIAL_FX2 = 313,
    O_SPECIAL_FX3 = 314,
    O_LARA_SKIN = 315,
    O_LAVA = 316,
    O_LAVA_EMITTER = 317,
    O_STROBE_LIGHT = 318,
    O_ELECTRICAL_LIGHT = 319,
    O_ON_OFF_LIGHT = 320,
    O_PULSE_LIGHT = 321,
    O_EXTRA_LIGHT1 = 322,
    O_EXTRA_LIGHT2 = 323,
    O_RED_LIGHT = 324,
    O_GREEN_LIGHT = 325,
    O_BLUE_LIGHT = 326,
    O_AMBER_LIGHT = 327,
    O_WHITE_LIGHT = 328,
    O_FLAME = 329,
    O_FLAME_EMITTER = 330,
    O_FLAME_EMITTER2 = 331,
    O_FLAME_EMITTER3 = 332,
    O_SIDE_FLAME_EMITTER = 333,
    O_SMOKE_EMITTER_WHITE = 334,
    O_SMOKE_EMITTER_BLACK = 335,
    O_STEAM_EMITTER = 336,
    O_GHOST_GAS_EMITTER = 337,
    O_PIRAHNAS = 338,
    O_TROPICAL_FISH = 339,
    O_PIRAHNA_GFX = 340,
    O_TROPICAL_FISH_GFX = 341,
    O_BAT_GFX = 342,
    O_TRIBEBOSS_GFX = 343,
    O_SPIDER_GFX = 344,
    O_TUMBLEWEED = 345,
    O_LEAVES = 346,
    O_BAT_EMITTER = 347,
    O_BIRD_EMITTER = 348,
    O_ANIMATING1 = 349,
    O_ANIMATING2 = 350,
    O_ANIMATING3 = 351,
    O_ANIMATING4 = 352,
    O_ANIMATING5 = 353,
    O_ANIMATING6 = 354,
    O_HORIZON = 355,
    O_ALPHABET = 356,
    O_DING_DONG = 357,
    O_LARA_ALARM = 358,
    O_MINI_COPTER = 359,
    O_WINSTON = 360,
    O_ARMY_WINSTON = 361,
    O_ASSAULT_NUMBERS = 362,
    O_FINAL_LEVEL = 363,
    O_CUT_SHOTGUN = 364,
    O_EARTHQUAKE = 365,
    O_GUNSHELL = 366,
    O_SHOTGUNSHELL = 367,
    O_EXTRAFX1 = 368,
    O_EXTRAFX2 = 369,
    O_EXTRAFX3 = 370,
    O_EXTRAFX4 = 371,
    O_EXTRAFX5 = 372,
    O_EXTRAFX6 = 373,
    O_EXTRAFX7 = 374,
    O_EXTRAFX8 = 375,
    O_NUMBER_OF = 376,
};

enum TARGET_TYPE {
    TARGET_NONE = 0,
    TARGET_PRIMARY = 1,
    TARGET_SECONDARY = 2,
};

enum MOOD_TYPE {
    MOOD_BORED = 0,
    MOOD_ATTACK = 1,
    MOOD_ESCAPE = 2,
    MOOD_STALK = 3,
};

enum CAMERA_TYPE {
    CT_CHASE = 0,
    CT_FIXED = 1,
    CT_LOOK = 2,
    CT_COMBAT = 3,
    CT_CINEMATIC = 4,
    CT_HEAVY = 5,
};

enum INPUT_STATE {
    IN_FORWARD = 1,
    IN_BACK = (1 << 1),
    IN_LEFT = (1 << 2),
    IN_RIGHT = (1 << 3),
    IN_JUMP = (1 << 4),
    IN_DRAW = (1 << 5),
    IN_ACTION = (1 << 6),
    IN_SLOW = (1 << 7),
    IN_OPTION = (1 << 8),
    IN_LOOK = (1 << 9),
    IN_STEPL = (1 << 10),
    IN_STEPR = (1 << 11),
    IN_ROLL = (1 << 12),
    IN_PAUSE = (1 << 13),
    IN_DEBUG_A = (1 << 14),
    IN_DEBUG_B = (1 << 15),
    IN_DEBUG_C = (1 << 16),
    IN_DEBUG_D = (1 << 17),
    IN_DEBUG_E = (1 << 18),
    IN_DEBUG_F = (1 << 19),
    IN_SELECT = (1 << 20),
    IN_DESELECT = (1 << 21),
    IN_SAVE = (1 << 22),
    IN_LOAD = (1 << 23),
    IN_STEPSHIFT = (1 << 24),
    IN_LOOKLEFT = (1 << 25),
    IN_LOOKRIGHT = (1 << 26),
    IN_LOOKFORWARD = (1 << 27),
    IN_LOOKBACK = (1 << 28),
    IN_DUCK = (1 << 29),
    IN_DASH = (1 << 30),
};

enum LARA_WATER_STATE {
    LWS_ABOVE_WATER = 0,
    LWS_UNDERWATER = 1,
    LWS_SURFACE = 2,
    LWS_CHEAT = 3,
    LWS_WADE = 4,
};

enum LARA_GUN_STATE {
    LG_ARMLESS = 0,
    LG_HANDSBUSY = 1,
    LG_DRAW = 2,
    LG_UNDRAW = 3,
    LG_READY = 4,
    LG_SPECIAL = 5,
};

enum LARA_ANIM {
    LA_RUN = 0,
    LA_WALK = 1,
    LA_STOP_L = 2,
    LA_STOP_R = 3,
    LA_START_RUN = 6,
    LA_STOP = 11,
    LA_FAST_FALL = 23,
    LA_LAND_FAR = 24,
    LA_STOP_HANG = 28,
    LA_LAND = 31,
    LA_FAST_SPLAT = 32,
    LA_FALL_DOWN = 34,
    LA_VAULT_34 = 42,
    LA_VAULT_12 = 50,
    LA_HIT_WALL_L = 53,
    LA_HIT_WALL_R = 54,
    LA_RUN_STEP_UP_R = 55,
    LA_RUN_STEP_UP_L = 56,
    LA_WALK_STEP_UP_L = 57,
    LA_WALK_STEP_UP_R = 58,
    LA_WALK_STEP_DOWN_R = 59,
    LA_WALK_STEP_DOWN_L = 60,
    LA_BACK_STEP_DOWN_L = 61,
    LA_BACK_STEP_DOWN_R = 62,
    LA_SLIDE = 70,
    LA_COMPRESS = 73,
    LA_SWIM_GLIDE = 87,
    LA_FALL_BACK = 93,
    LA_GRAB_LEDGE = 96,
    LA_HANG = 96,
    LA_START_HANG = 96,
    LA_BREATH = 103,
    LA_SLIDE_BACK = 104,
    LA_TREAD = 108,
    LA_SURF_CLIMB = 111,
    LA_JUMP_IN = 112,
    LA_SURF_TREAD = 114,
    LA_SURF_SWIM = 116,
    LA_SURF_DIVE = 119,
    LA_SPAZ_FORWARD = 125,
    LA_SPAZ_BACK = 126,
    LA_SPAZ_R = 127,
    LA_SPAZ_L = 128,
    LA_ROLLING_BALL_DEATH = 139,
    LA_SURF_TREAD_BACK = 140,
    LA_SURF_BACK = 141,
    LA_SURF_L = 143,
    LA_SURF_R = 144,
    LA_ROLL = 146,
    LA_SPIKE_DEATH = 149,
    LA_GRAB_LEDGE_IN = 150,
    LA_CLIMBING = 161,
    LA_CLIMB_UP_R = 162,
    LA_CLIMB_UP_L = 163,
    LA_CLIMB_STILL = 164,
    LA_CLIMB_DOWN_R = 166,
    LA_CLIMB_DOWN_L = 167,
    LA_CLIMB_DOWN = 168,
    LA_CLIMB_R = 170,
    LA_CLIMB_L = 171,
    LA_SURF_TO_WADE2 = 176,
    LA_UW_TO_WADE = 176,
    LA_WADE = 177,
    LA_HANG_UP = 187,
    LA_HANG_DOWN = 188,
    LA_THROW_FLARE = 189,
    LA_SURF_TO_WADE = 190,
    LA_SURF_TO_STAND = 191,
    LA_SWIM_TO_QSTAND = 192,
    LA_SURF_TO_QSTAND = 193,
    LA_CLIMB_TO_HANG = 194,
    LA_GRAB_R = 201,
    LA_GRAB_L = 202,
    LA_WATER_ROLL = 203,
    LA_PICKUP_FLARE_UW = 206,
    LA_STAND_TO_DUCK = 218,
    LA_DUCK_ROLL = 219,
    LA_DUCK_BREATHE = 223,
    LA_DASH = 224,
    LA_DASH_DIVE = 231,
    LA_MONKEY_HANG = 235,
    LA_MONKEY_SWING = 237,
};

enum LARA_STATE {
    LS_WALK = 0,
    LS_RUN = 1,
    LS_STOP = 2,
    LS_FORWARD_JUMP = 3,
    LS_POSE = 4,
    LS_FAST_BACK = 5,
    LS_TURN_R = 6,
    LS_TURN_L = 7,
    LS_DEATH = 8,
    LS_FAST_FALL = 9,
    LS_HANG = 10,
    LS_REACH = 11,
    LS_SPLAT = 12,
    LS_TREAD = 13,
    LS_LAND = 14,
    LS_COMPRESS = 15,
    LS_BACK = 16,
    LS_SWIM = 17,
    LS_GLIDE = 18,
    LS_NULL = 19,
    LS_FAST_TURN = 20,
    LS_STEP_RIGHT = 21,
    LS_STEP_LEFT = 22,
    LS_HIT = 23,
    LS_SLIDE = 24,
    LS_BACK_JUMP = 25,
    LS_RIGHT_JUMP = 26,
    LS_LEFT_JUMP = 27,
    LS_UP_JUMP = 28,
    LS_FALL_BACK = 29,
    LS_HANG_LEFT = 30,
    LS_HANG_RIGHT = 31,
    LS_SLIDE_BACK = 32,
    LS_SURF_TREAD = 33,
    LS_SURF_SWIM = 34,
    LS_DIVE = 35,
    LS_PUSH_BLOCK = 36,
    LS_PULL_BLOCK = 37,
    LS_PUSH_PULL_READY = 38,
    LS_PICKUP = 39,
    LS_SWITCH_ON = 40,
    LS_SWITCH_OFF = 41,
    LS_USE_KEY = 42,
    LS_USE_PUZZLE = 43,
    LS_UW_DEATH = 44,
    LS_ROLL = 45,
    LS_SPECIAL = 46,
    LS_SURF_BACK = 47,
    LS_SURF_LEFT = 48,
    LS_SURF_RIGHT = 49,
    LS_USE_MIDAS = 50,
    LS_DIE_MIDAS = 51,
    LS_SWAN_DIVE = 52,
    LS_FAST_DIVE = 53,
    LS_GYMNAST = 54,
    LS_WATER_OUT = 55,
    LS_CLIMB_STNC = 56,
    LS_CLIMBING = 57,
    LS_CLIMB_LEFT = 58,
    LS_CLIMB_END = 59,
    LS_CLIMB_RIGHT = 60,
    LS_CLIMB_DOWN = 61,
    LS_LARA_TEST1 = 62,
    LS_LARA_TEST2 = 63,
    LS_LARA_TEST3 = 64,
    LS_WADE = 65,
    LS_WATER_ROLL = 66,
    LS_FLARE_PICKUP = 67,
    LS_TWIST = 68,
    LS_KICK = 69,
    LS_DEATHS_LIDE = 70,
    LS_DUCK = 71,
    LS_DUCK_ROLL = 72,
    LS_DASH = 73,
    LS_DASH_DIVE = 74,
    LS_MONKEY_SWING = 75,
    LS_MONKEYF = 76,
    LS_LAST = 77,
};

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
    struct TEXTSTRING *heading1_text;
    struct TEXTSTRING *heading2_text;
    struct TEXTSTRING *background_text;
    struct TEXTSTRING *moreup_text;
    struct TEXTSTRING *moredown_text;
    struct TEXTSTRING *texts1[MAX_REQLINES];
    struct TEXTSTRING *texts2[MAX_REQLINES];
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
    struct INVENTORY_SPRITE **sprlist;
    int32_t misc_data[4];
};

struct RING_INFO {
    struct INVENTORY_ITEM **list;
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
    struct PHD_3DPOS ringpos;
    struct PHD_3DPOS camera;
    struct PHD_VECTOR light;
    struct IMOTION_INFO *imo;
};

struct ITEM_LIGHT {
    struct PHD_VECTOR sun;
    struct PHD_VECTOR bulb;
    struct PHD_VECTOR dynamic;
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

struct SPLASH_SETUP {
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
    uint16_t fx : 4;
    uint16_t box : 11;
    uint16_t stopper : 1;
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
    int16_t static_num;
};

struct DOORPOS_DATA {
    struct FLOOR_INFO *floor;
    struct FLOOR_INFO data;
    int16_t block;
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

struct FX_INFO {
    struct PHD_3DPOS pos;
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

struct CAMERA_INFO {
    GAME_VECTOR pos;
    GAME_VECTOR target;
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
    ITEM_INFO *item;
    ITEM_INFO *last_item;
    OBJECT_VECTOR *fixed;
    int32_t mike_at_lara;
    PHD_VECTOR mike_pos;
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
    struct PHD_3DPOS old_pos;
    char turn;
    char forward;
    char true_water;
    char flags;
};

struct SUB_INFO {
    int32_t vel;
    int32_t rot;
    int32_t rot_x;
    int16_t fan_rot;
    char flags;
    char weapon_timer;
};

struct CART_INFO {
    int32_t speed;
    int32_t mid_pos;
    int32_t front_pos;
    int32_t turn_x;
    int32_t turn_z;
    int16_t turn_len;
    int16_t turn_rot;
    int16_t y_vel;
    int16_t gradient;
    char flags;
    char stop_delay;
};

struct BITE_INFO {
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t mesh_num;
};

struct OBJECT_INFO {
    int16_t nmeshes;
    int16_t mesh_index;
    int32_t bone_index;
    int16_t *frame_base;
    void (*initialise)(int16_t item_num);
    void (*control)(int16_t item_num);
    void (*floor)(
        struct ITEM_INFO *item, int32_t x, int32_t y, int32_t z,
        int32_t *height);
    void (*ceiling)(
        struct ITEM_INFO *item, int32_t x, int32_t y, int32_t z,
        int32_t *height);
    void (*draw_routine)(ITEM_INFO *item);
    void (*collision)(
        int16_t item_num, struct ITEM_INFO *lara_item, struct COLL_INFO *coll);
    int16_t anim_index;
    int16_t hit_points;
    int16_t pivot_length;
    int16_t radius;
    int16_t shadow_size;
    uint16_t bite_offset;
    uint16_t loaded : 1;
    uint16_t intelligent : 1;
    uint16_t non_lot : 1;
    uint16_t save_position : 1;
    uint16_t save_hitpoints : 1;
    uint16_t save_flags : 1;
    uint16_t save_anim : 1;
    uint16_t semi_transparent : 1;
    uint16_t water_creature : 1;
};

struct EXPLOSION_VERTS {
    int16_t x;
    int16_t z;
    int32_t rgb;
};

struct EXPLOSION_RING {
    int16_t on;
    int16_t life;
    int16_t speed;
    int16_t radius;
    int16_t xrot;
    int16_t zrot;
    int32_t x;
    int32_t y;
    int32_t z;
    struct EXPLOSION_VERTS verts[16];
};

struct PHD_TEXTURE_STRUCT {
    uint16_t drawtype;
    uint16_t tpage;
    uint16_t u1;
    uint16_t v1;
    uint16_t u2;
    uint16_t v2;
    uint16_t u3;
    uint16_t v3;
    uint16_t u4;
    uint16_t v4;
};

struct PHD_SPRITE_STRUCT {
    uint16_t tpage;
    uint16_t offset;
    uint16_t width;
    uint16_t height;
    int16_t x1;
    int16_t y1;
    int16_t x2;
    int16_t y2;
};

struct PHD_VBUF {
    float xv;
    float yv;
    float zv;
    float ooz;
    float xs;
    float ys;
    int32_t z;
    int8_t clip;
    uint8_t fog;
    int16_t g;
    uint16_t u;
    uint16_t v;
    int32_t dynamic;
};

struct VERTEX_INFO {
    float x;
    float y;
    float ooz;
    float u;
    float v;
    float g;
    int32_t vr;
    int32_t vg;
    int32_t vb;
};

#pragma pack(pop)
