#ifndef BSP_LED_H_
#define BSP_LED_H_

/*전처리로 포트 네이밍처리*/
#define GPIO_PORT_LED1  GPIOI
#define GPIO_PIN_LED1	GPIO_PIN_10

#define GPIO_PORT_LED2  GPIOF
#define GPIO_PIN_LED2	GPIO_PIN_7

#define GPIO_PORT_LED3  GPIOF
#define GPIO_PIN_LED3	GPIO_PIN_8

#define GPIO_PORT_LED4  GPIOC
#define GPIO_PIN_LED4	GPIO_PIN_2

void bsp_InitLed(void);
void bsp_LedOn(uint8_t _no);
void bsp_LedOff(uint8_t _no);

#endif