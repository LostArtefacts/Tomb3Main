#pragma once

// clang-format off
#define ONE_DEGREE            182
#define FAST_FALL_SPEED       128

#define LARA_TURN_UNDO        (2 * ONE_DEGREE) // = 364
#define LARA_TURN_RATE        ((ONE_DEGREE / 4) + LARA_TURN_UNDO) // = 409
#define LARA_SLOW_TURN        ((ONE_DEGREE * 2) + LARA_TURN_UNDO) // = 728
#define LARA_MED_TURN         ((ONE_DEGREE * 4) + LARA_TURN_UNDO) // = 1092
#define LARA_FAST_TURN        ((ONE_DEGREE * 6) + LARA_TURN_UNDO) // = 1456

#define LARA_LEAN_UNDO        (ONE_DEGREE) // = 182
#define LARA_LEAN_RATE        ((ONE_DEGREE / 2) + LARA_LEAN_UNDO) // = 273
#define LARA_LEAN_MAX_RATE    ((ONE_DEGREE * 10) + LARA_LEAN_UNDO) // = 2002

#define LARA_JUMP_TURN        (ONE_DEGREE + LARA_TURN_UNDO) // = 546
#define LARA_FAST_FALL_SPEED  (FAST_FALL_SPEED + 3) // = 131
#define LARA_DASH_TIME        (30 * 4) // 4 seconds

#define CAMERA_HANG_ANGLE     0
#define CAMERA_HANG_ELEVATION (ONE_DEGREE * -60) // = -10920
// clang-format on
