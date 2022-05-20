#pragma once

// Main non-public control routines.

#include "global/types.h"

void Lara_HandleAboveWater(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_HandleUnderwater(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_HandleSurface(struct ITEM_INFO *item, struct COLL_INFO *coll);
void Lara_CheatGetStuff(void);
