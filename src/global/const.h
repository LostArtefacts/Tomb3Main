#pragma once

// clang-format off
#define ONE_DEGREE          182
#define FASTFALL_SPEED      128

#define LARA_TURN_UNDO      (2 * ONE_DEGREE) // = 364
#define LARA_TURN_RATE      ((ONE_DEGREE / 4) + LARA_TURN_UNDO) // = 409
#define LARA_JUMP_TURN      (ONE_DEGREE + LARA_TURN_UNDO)
#define LARA_FASTFALL_SPEED (FASTFALL_SPEED + 3) // = 131
#define LARA_SLOW_TURN      ((ONE_DEGREE * 2) + LARA_TURN_UNDO) // = 728
// clang-format on
