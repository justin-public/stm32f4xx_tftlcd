#include "bsp.h"
#include "fonts.h"

static uint16_t s_WinX = 0;
static uint16_t s_WinY = 0;
static uint16_t s_WinHeight = 272;
static uint16_t s_WinWidth = 480;

uint16_t g_LcdHeight = 272;      // 272			
uint16_t g_LcdWidth = 480;		 // 480	


void RA8875_PLL_ini(void)
{
    // 480  x 272
    LCD_CmdWrite(0x88);      
    RA8875_Delaly1us();
    LCD_DataWrite(0x0a);
    RA8875_Delaly1ms();    
    LCD_CmdWrite(0x89);
    RA8875_Delaly1us();        
    LCD_DataWrite(0x02);  
}

void RA8875_Initial(void)
{
    RA8875_PLL_ini();
    RA8875_Delaly1ms();
    
    LCD_CmdWrite(0x10);  //SYSR   bit[4:3]=00 256 color  bit[2:1]=  00 8bit MPU interface
    //LCD_DataWrite(0x000c);   // if 8bit MCU interface   and 65k color display  						    
    LCD_DataWrite(0x0F); // if 16bit MCU interface   and 65k color display
    //RA8875_Delaly1us();
    
    // Pixel 480 x 272
    LCD_CmdWrite(0x04);    //set PCLK invers
    LCD_DataWrite(0x82); 
    RA8875_Delaly1ms();

    //Horizontal set
    LCD_CmdWrite(0x14); //HDWR//Horizontal Display Width Setting Bit[6:0]                   
    LCD_DataWrite(0x3B);//Horizontal display width(pixels) = (HDWR + 1)*8                   
    LCD_CmdWrite(0x15); //Horizontal Non-Display Period Fine Tuning Option Register (HNDFTR)
    LCD_DataWrite(0x00);//Horizontal Non-Display Period Fine Tuning(HNDFT) [3:0]            
    LCD_CmdWrite(0x16); //HNDR//Horizontal Non-Display Period Bit[4:0]                      
    LCD_DataWrite(0x01);//Horizontal Non-Display Period (pixels) = (HNDR + 1)*8             
    LCD_CmdWrite(0x17); //HSTR//HSYNC Start Position[4:0]                                   
    LCD_DataWrite(0x00);//HSYNC Start Position(PCLK) = (HSTR + 1)*8                         
    LCD_CmdWrite(0x18); //HPWR//HSYNC Polarity ,The period width of HSYNC.                  
    LCD_DataWrite(0x05);//HSYNC Width [4:0]   HSYNC Pulse width(PCLK) = (HPWR + 1)*8        
                                             
    //Vertical set                                            
    LCD_CmdWrite(0x19); //VDHR0 //Vertical Display Height Bit [7:0]                            
    LCD_DataWrite(0x0f); //Vertical pixels = VDHR + 1                                      
    LCD_CmdWrite(0x1a); //VDHR1 //Vertical Display Height Bit [8]                  
    LCD_DataWrite(0x01); //Vertical pixels = VDHR + 1                           
    LCD_CmdWrite(0x1b);  //VNDR0 //Vertical Non-Display Period Bit [7:0]                    
    LCD_DataWrite(0x02);  //VSYNC Start Position(PCLK) = (VSTR + 1)                          
    LCD_CmdWrite(0x1c);  //VNDR1 //Vertical Non-Display Period Bit [8]                             
    LCD_DataWrite(0x00); //Vertical Non-Display area = (VNDR + 1)                            
    LCD_CmdWrite(0x1d); //VSTR0 //VSYNC Start Position[7:0]                               
    LCD_DataWrite(0x07);//VSYNC Start Position(PCLK) = (VSTR + 1)                           
    LCD_CmdWrite(0x1e); //VSTR1 //VSYNC Start Position[8]                   
    LCD_DataWrite(0x00);//VSYNC Start Position(PCLK) = (VSTR + 1)                            
    LCD_CmdWrite(0x1f);    //VPWR //VSYNC Polarity ,VSYNC Pulse Width[6:0]
    LCD_DataWrite(0x09);   //VSYNC Pulse Width(PCLK) = (VPWR + 1) 

    // add
    //LCD_CmdWrite(0x40);
    //LCD_DataWrite(0x00);

    //LCD_CmdWrite(0x41);
    //LCD_DataWrite(0x00);
}


void RA8875_Delaly1us(void)
{
	uint8_t i;
	for (i = 0; i < 10; i++);
}

void RA8875_Delaly1ms(void)
{
    uint16_t i;
	for (i = 0; i < 5000; i++);
}

void RA8875_display_on(void)
{
    LCD_CmdWrite(0x01);   
    LCD_DataWrite(0x80); 
}

void RA8875_display_panel_on(void)
{
    LCD_CmdWrite(0xc7);
    LCD_DataWrite(0x01); 
}

void RA8875_display_setting(void)
{
    //setting active window X
    LCD_CmdWrite(0x30); //Horizontal Start Point 0 of Active Window (HSAW0)
    LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [7:0]
    LCD_CmdWrite(0x31); //Horizontal Start Point 1 of Active Window (HSAW1)	   
    LCD_DataWrite(0x00); //Horizontal Start Point of Active Window [9:8]               
    LCD_CmdWrite(0x34); //Horizontal End Point 0 of Active Window (HEAW0)
    LCD_DataWrite(0xDF); //Horizontal End Point of Active Window [7:0]                 
    LCD_CmdWrite(0x35); //Horizontal End Point 1 of Active Window (HEAW1)	   
    LCD_DataWrite(0x01); //Horizontal End Point of Active Window [9:8]                  

    //setting active window Y
    LCD_CmdWrite(0x32); //Vertical Start Point 0 of Active Window (VSAW0)
    LCD_DataWrite(0x00); //Vertical Start Point of Active Window [7:0]
    LCD_CmdWrite(0x33); //Vertical Start Point 1 of Active Window (VSAW1)	   
    LCD_DataWrite(0x00); //Vertical Start Point of Active Window [8]                    
    LCD_CmdWrite(0x36); //Vertical End Point of Active Window 0 (VEAW0)
    LCD_DataWrite(0x0F); //Vertical End Point of Active Window [7:0]                      
    LCD_CmdWrite(0x37); //Vertical End Point of Active Window 1 (VEAW1)	   
    LCD_DataWrite(0x01); //Vertical End Point of Active Window [8]                    
}

#if 1
void Touch_Panel_Interrupt_Enable(void)
{ 
    uint8_t temp;
    LCD_CmdWrite(0xF0);//INTC
    temp=LCD_DataRead(); 
    temp |= 0x04;
    LCD_DataWrite(temp);
}

void TP_auto_mode(void)
{	
    uint8_t temp;
  	LCD_CmdWrite(0x71);//TPCR1	
	temp = LCD_DataRead();
	temp &= cClrD6;
	LCD_DataWrite(temp);
}

void Enable_TP(void)
{   
    uint8_t temp;	  
	LCD_CmdWrite(0x70);//TPCR0	
	temp = LCD_DataRead();
	temp |= cSetD7;   
	LCD_DataWrite(temp);
}

void SROM_CLK_DIV(uint8_t CLK_DIV)
{
    LCD_CmdWrite(0x06);
    LCD_DataWrite(CLK_DIV);
}

void Serial_ROM_select1(void)
{   
    uint8_t temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp |=cSetD7;
	LCD_DataWrite(temp);
}

void Select_Serial_Waveform_mode3(void)
{	
    uint8_t temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp |=cSetD5;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_Read_Cycle_5bus(void)
{
    uint8_t temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=0xE7;
    temp |=cSetD3;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_DMA_mode(void)
{
    uint8_t temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp |=cSetD2;
	LCD_DataWrite(temp);
}

void SERIAL_ROM_Signal_mode(void)
{   
    uint8_t temp;
  	LCD_CmdWrite(0x05);//PWRR
	temp = LCD_DataRead();
	temp &=0xFC;
	LCD_DataWrite(temp);
}

void DMA_Block_mode(void)
{ 
    LCD_CmdWrite(0xBF);
    LCD_DataWrite(0x02);
}

void Clear_Active_Window(void)
{
	uint8_t temp;
	LCD_CmdWrite(0x8e);//MCLR
	temp = LCD_DataRead();
	temp |= cSetD6 ;
	LCD_DataWrite(temp);  
}
#endif

void PWM1_enable(void)
{
	uint8_t temp;
	LCD_CmdWrite(0x8a);//MCLR
	temp = LCD_DataRead();
	temp |= cSetD7 ;
	LCD_DataWrite(temp);  
}

void PWM1_fnuction_sel(void)
{
	uint8_t temp;
	LCD_CmdWrite(0x8a);//MCLR
	temp = LCD_DataRead();
	temp &= cClrD4 ;
	LCD_DataWrite(temp);  
}

void PWM1_clock_ratio(uint8_t setx)
{
    uint8_t temp,temp1;
	temp1= setx&0x0f;
	LCD_CmdWrite(0x8a);//MCLR
	temp = LCD_DataRead();
	temp &= 0xf0;
	temp |= temp1 ;
	LCD_DataWrite(temp);  
}

void PWM1_duty_cycle(uint8_t setx) //bit0~7
{
    LCD_CmdWrite(0x8b);//PTNO
	LCD_DataWrite(setx);
} 	

void LCD_Clear(uint16_t Color)
{
    uint32_t index = 0;
  
    LCD_SetCursor(0,0); 
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

    for(index = 0; index < 130560; index++)
    {
        LCD_DataWrite(Color);
    }
    // while(1);  
}

void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
    LCD_CmdWrite(0x46);
	LCD_DataWrite(Xpos);  
    LCD_CmdWrite(0x47);	   
	LCD_DataWrite(Xpos>>8);
    LCD_CmdWrite(0x48);
	LCD_DataWrite(Ypos);
    LCD_CmdWrite(0x49);	   
	LCD_DataWrite(Ypos>>8);
}	

void LCD_WriteRAM_Prepare(void)
{
    LCD_CmdWrite(0x02); //
}

void LCD_DisplayStringLine(uint16_t Line, char *ptr, uint16_t charColor, uint16_t bkColor)
{
  uint32_t i = 0;
  uint16_t refcolumn = 0;

  /* Send the string character by character on lCD */
  while ((*ptr != 0) & (i < 50))
  {
    LCD_PutChar(refcolumn, Line, *ptr, charColor, bkColor);
    /* Decrement the column position by 16 */
    refcolumn += 16;
    /* Point on the next character */
    ptr++;
    /* Increment the character counter */
    i++;
  }
}

void LCD_PutChar(uint16_t x,uint16_t y,uint8_t c,uint16_t charColor,uint16_t bkColor)
{
    uint16_t i=0;
    uint16_t j=0;
  
    uint16_t tmp_char=0;

    for (i=0;i<24;i++)
    {
        tmp_char=ASCII_Table[((c-0x20)*24)+i];	 //´î¥h32ªº°¾²¾¡A¬O¦]¬°¦r²Åªí±qªÅ®æ¶}©lªº¡A°Ñ¦Ò¦r²Åªí¨ºªºª`ÄÀ
        for (j=0;j<16;j++)
        {
            // if ( (tmp_char >> 15-j) & 0x01 == 0x01)	«ö·Ó¤W­±ªºÅã¥Ü¡A¦r²Å¬O­Ë¹L¨Óªº¡A¨ì³o¨½§ï¹L¨Ó´N¦æ¤F
	        if ( (tmp_char >> j) & 0x01 == 0x01)
            {
                LCD_SetPoint(x+j,y+i,charColor); //¦r²ÅÃC¦â
            }
            else
            {
                LCD_SetPoint(x+j,y+i,bkColor); // ¦r²ÅÃC¦â
            }
        }
    }
}

void LCD_SetPoint(uint16_t x,uint16_t y,uint16_t point)
{
  LCD_SetCursor(x,y);
  LCD_WriteRAM_Prepare();
  LCD_DataWrite(point);
}


