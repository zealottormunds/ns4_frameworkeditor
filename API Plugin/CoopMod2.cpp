#include "CoopMod2.h"
#include "ccPlayerMain.h"

bool CoopMod2::waitToEnable = false;
bool CoopMod2::isReady = false;
ccPlayerMain *  CoopMod2::p1 = 0;
ccPlayerMain *  CoopMod2::p1_prev = 0;
ccPlayerMain *  CoopMod2::p2 = 0;
ccPlayerMain *  CoopMod2::p2_prev = 0;
__int64 CoopMod2::ai = 0;