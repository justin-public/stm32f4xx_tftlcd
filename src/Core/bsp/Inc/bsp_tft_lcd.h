#ifndef BSP_TFTLCD_H_
#define BSP_TFTLCD_H_

/*포트 전처리*/
#define LCD_PWM_Pin GPIO_PIN_6
#define LCD_PWM_GPIO_Port GPIOF
#define TP_NCS_Pin GPIO_PIN_0
#define TP_NCS_GPIO_Port GPIOI
#define TP_INT_Pin GPIO_PIN_3
#define TP_INT_GPIO_Port GPIOI
#define LCD_BUSY_Pin GPIO_PIN_3
#define LCD_BUSY_GPIO_Port GPIOD

void LCD_InitHard(void);
void LCD_BackLight_on(void);

#endif