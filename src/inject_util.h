#pragma once

#include <stdbool.h>
#include <stdint.h>

void InjectFunc(void (*from)(void), void (*to)(void));

#define INJECT(from, to, enable)                                               \
    {                                                                          \
        InjectImpl((void (*)(void))from, (void (*)(void))to, enable);          \
    }

#define VAR_U_(address, type) (*(type *)(address))
#define VAR_I_(address, type, value) (*(type *)(address))
#define ARRAY_(address, type, length) (*(type(*) length)(address))
