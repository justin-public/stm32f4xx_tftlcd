#include "bsp.h"

/*
*********************************************************************************************************
* 함수 이름: bsp_InitLed
* 기능 설명: LED 드라이브 초기화
* 형 매개: 없음
* 반환 값: 없음
*********************************************************************************************************
*/
void bsp_InitLed(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};   

    __HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

    bsp_LedOff(1);
    bsp_LedOff(2);
    bsp_LedOff(3);
    bsp_LedOff(4);

    GPIO_InitStructure.Pin = GPIO_PIN_LED1;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_LED2|GPIO_PIN_LED3;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_InitStructure.Pin = GPIO_PIN_LED4;
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);       
}

/*
*********************************************************************************************************
* 함수 이름: bsp_LedOn
* 기능 설명: LED ON 함수
* 형 매개: 없음
* 반환 값: 없음
*********************************************************************************************************
*/
void bsp_LedOn(uint8_t _no)
{
	_no--;

	if (_no == 0)
	{
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_LED1, GPIO_PIN_RESET);
	}
	else if (_no == 1)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_LED2, GPIO_PIN_RESET);
	}
	else if (_no == 2)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_LED3, GPIO_PIN_RESET);
	}
	else if (_no == 3)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_LED4, GPIO_PIN_RESET);
	}
}

/*
*********************************************************************************************************
* 함수 이름: bsp_LedOn
* 기능 설명: LED OFF 함수
* 형 매개: 없음
* 반환 값: 없음
*********************************************************************************************************
*/
void bsp_LedOff(uint8_t _no)
{
	_no--;

	if (_no == 0)
	{
		HAL_GPIO_WritePin(GPIOI, GPIO_PIN_LED1, GPIO_PIN_SET);
	}
	else if (_no == 1)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_LED2, GPIO_PIN_SET);
	}
	else if (_no == 2)
	{
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_LED3, GPIO_PIN_SET);
	}
	else if (_no == 3)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_LED4, GPIO_PIN_SET);
	}
}