#pragma once

#include <stdbool.h>
#include <stdint.h>

void InjectImpl(void (*from)(void), void (*to)(void), bool enable);

#define INJECT(from, to, enable)                                               \
    {                                                                          \
        InjectImpl((void (*)(void))from, (void (*)(void))to, enable);          \
    }

#define VAR(address, type) (*(type *)(address))
#define ARR(address, type, length) (*(type(*) length)(address))
