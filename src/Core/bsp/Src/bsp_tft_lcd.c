#include "bsp.h"

static void LCD_CtrlLinesConfig(void);
static void LCD_FSMCConfig(void);
/*
*********************************************************************************************************
*	함수명: LCD_InitHard
*	기능설명: LCD 초기화
*	매개변수: 없음
*	반환값: 없음
*********************************************************************************************************
*/
void LCD_InitHard(void)
{
    uint16_t id;

    LCD_CtrlLinesConfig();
    
    LCD_FSMCConfig();

    bsp_DelayMS(20);

    
}


/*
*********************************************************************************************************
*	함수명: LCD_CtrlLinesConfig
*	기능설명: LCD 
*	매개변수: 없음
*	반환값: 없음
*********************************************************************************************************
*/
static void LCD_CtrlLinesConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(TP_INT_GPIO_Port, TP_INT_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_BUSY_GPIO_Port, LCD_BUSY_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : LCD_PWM_Pin */
    GPIO_InitStruct.Pin = LCD_PWM_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(LCD_PWM_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO(PORTE) pins : PE7 PE8 PE9 PE10
                           PE11 PE12 PE13 PE14
                           PE15 */
    GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10
                        |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                        |GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_FSMC;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /*Configure GPIO pin : TP_NCS_Pin */
    GPIO_InitStruct.Pin = TP_NCS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(TP_NCS_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : TP_INT_Pin */
    GPIO_InitStruct.Pin = TP_INT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(TP_INT_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : LCD_BUSY_Pin */
    GPIO_InitStruct.Pin = LCD_BUSY_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LCD_BUSY_GPIO_Port, &GPIO_InitStruct);
}

/*
*********************************************************************************************************
*	함수명: LCD_CtrlLinesConfig
*	기능설명: LCD 
*	매개변수: 없음
*	반환값: 없음
*********************************************************************************************************
*/
static void LCD_FSMCConfig(void)
{
    SRAM_HandleTypeDef hsram4;
    FSMC_NORSRAM_TimingTypeDef Timing = {0};

    hsram4.Instance = FSMC_NORSRAM_DEVICE;
    hsram4.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
    /* hsram4.Init */
    hsram4.Init.NSBank = FSMC_NORSRAM_BANK4;
    hsram4.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
    hsram4.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
    hsram4.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
    hsram4.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
    hsram4.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
    hsram4.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
    hsram4.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
    hsram4.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
    hsram4.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
    hsram4.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
    hsram4.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
    hsram4.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
    hsram4.Init.PageSize = FSMC_PAGE_SIZE_NONE;
  
    Timing.AddressSetupTime = 1;
    Timing.AddressHoldTime = 0;
    Timing.DataSetupTime = 4;
    Timing.BusTurnAroundDuration = 1;
    Timing.CLKDivision = 0;
    Timing.DataLatency = 0;
    Timing.AccessMode = FSMC_ACCESS_MODE_A;
    /* ExtTiming */

    if (HAL_SRAM_Init(&hsram4, &Timing, NULL) != HAL_OK)
    {
        Error_Handler( );
    }
}

