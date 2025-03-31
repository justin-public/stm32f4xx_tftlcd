#include "bsp.h"

void bsp_Init(void)
{
    bsp_InitLed();
    bsp_InitTimer();
}