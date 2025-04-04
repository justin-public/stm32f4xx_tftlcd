#ifndef BSP_RA8875_H_
#define BSP_RA8875_H_

#define RA8875_BASE		((uint32_t)(0x6C000000 | 0x00000000))
//#define LCD_CMD		    *(__IO uint16_t *)(RA8875_BASE +  (1 << (18 + 1)))	
#define LCD_CMD         (*((volatile unsigned short *) (0x6C000000 | 0x01 << 19)))
#define LCD_DATA		(*((volatile unsigned short *) 0x6C000000))                 /* RS = 0 */

#if 1
#define LCD_CmdWrite(cmd)     LCD_CMD = cmd
#define LCD_DataWrite(data)   LCD_DATA = data

#define LCD_StatusRead()     *(__IO uint16_t *)(RA8875_BASE + (1 << (18 + 1)))
#define LCD_DataRead()       *(__IO uint16_t *)(RA8875_BASE)
#endif

#define Line0          0
#define Line1          24
#define Line2          48
#define Line3          72

#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define	cSetD2		     0x04
#define	cSetD3		     0x08
#define	cSetD5		     0x20
#define	cSetD6		     0x40
#define	cSetD7		     0x80

#define	cClrD4		     0xef
#define	cClrD6		     0xbf
#define	cClrD7		     0x7f

void RA8875_PLL_ini(void);
void RA8875_Initial(void);

void RA8875_Delaly1us(void);
void RA8875_Delaly1ms(void);

void RA8875_display_on(void);
void RA8875_display_panel_on(void);
void RA8875_display_setting(void);






void Touch_Panel_Interrupt_Enable(void);
void TP_auto_mode(void);
void Enable_TP(void);
void SROM_CLK_DIV(uint8_t CLK_DIV);
void Serial_ROM_select1(void);
void Select_Serial_Waveform_mode3(void);
void SERIAL_ROM_Read_Cycle_5bus(void);
void SERIAL_ROM_DMA_mode(void);
void SERIAL_ROM_Signal_mode(void);
void DMA_Block_mode(void);

void Clear_Active_Window(void);
void PWM1_enable(void);
void PWM1_fnuction_sel(void);
void PWM1_clock_ratio(uint8_t setx);
void PWM1_duty_cycle(uint8_t setx);

void LCD_Clear(uint16_t Color);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_WriteRAM_Prepare(void);

void LCD_DisplayStringLine(uint16_t Line, char *ptr, uint16_t charColor, uint16_t bkColor);
void LCD_PutChar(uint16_t x,uint16_t y,uint8_t c,uint16_t charColor,uint16_t bkColor);
void LCD_SetPoint(uint16_t x,uint16_t y,uint16_t point);

void lcd_rst(void);

#endif