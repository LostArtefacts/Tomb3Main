#pragma once

// clang-format off
#define DEG_FULL              0x10000
#define DEG_1                 (DEG_FULL / 360) // = 182
#define DEG_45                (DEG_FULL / 8) // = 8192 = 0x2000
#define DEG_90                (DEG_FULL / 4) // = 16384 = 0x4000
#define DEG_180               (DEG_FULL / 2) // = 32768 = 0x8000
#define DEG_135               (DEG_45 * 3) // = 24576 = 0x6000
#define DEG_360               (DEG_FULL) // = 65536 = 0x10000

#define WALL_L                1024 // = 0x1000
#define WALL_SHIFT            10
#define STEP_L                (WALL_L / 4)

#define FAST_FALL_SPEED       128

#define LARA_TURN_UNDO        (DEG_1 * 2) // = 364
#define LARA_TURN_RATE        ((DEG_1 / 4) + LARA_TURN_UNDO) // = 409
#define LARA_SLOW_TURN        ((DEG_1 * 2) + LARA_TURN_UNDO) // = 728
#define LARA_MED_TURN         ((DEG_1 * 4) + LARA_TURN_UNDO) // = 1092
#define LARA_FAST_TURN        ((DEG_1 * 6) + LARA_TURN_UNDO) // = 1456

#define LARA_LEAN_UNDO        (DEG_1) // = 182
#define LARA_LEAN_RATE        ((DEG_1 / 2) + LARA_LEAN_UNDO) // = 273
#define LARA_LEAN_MAX_RATE    ((DEG_1 * 10) + LARA_LEAN_UNDO) // = 2002

#define LARA_JUMP_TURN        (DEG_1 + LARA_TURN_UNDO) // = 546
#define LARA_FAST_FALL_SPEED  (FAST_FALL_SPEED + 3) // = 131
#define LARA_DASH_TIME        (30 * 4) // 4 seconds
#define LARA_STEP_UP_HEIGHT   ((STEP_L * 3) / 2) // = 384

#define CAMERA_HANG_ANGLE     0
#define CAMERA_HANG_ELEVATION (DEG_1 * -60) // = -10920
#define CAMERA_REACH_ANGLE    (85 * DEG_1) // = 15470
// clang-format on
