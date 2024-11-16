#ifndef LCD__H
#define LCD__H

#include "stdint.h"

//ON or OFF
#define ON  0x01
#define OFF 0x00
//SPI
#define LCD_SPI									hspi1
#define LCD_SPI_WAIT  					0xFFFF
//DMA 
#define LCD_DMA_ENABLE 	  			ON
#if 		LCD_DMA_ENABLE==ON
#define DMA_TMP_SIZE 						2500
#endif
//DIRECTION
#define DIRECTION  							2 
//BACKLIGHT
#define PWM_MODE 								ON
#if			PWM_MODE==ON
#define PWM_TIM 								htim5
#define PWM_CHN       					TIM_CHANNEL_4
#endif
//FORTROM
#define FORT_ROM								ON
//GPIO SETING
#define LCD_CS_GPIO_PORT				LCD_NSS_GPIO_Port
#define LCD_CS_GPIO_PIN					LCD_NSS_Pin
#define LCD_DC_GPIO_PORT				LCD_DC_GPIO_Port
#define LCD_DC_GPIO_PIN					LCD_DC_Pin
#define LCD_RES_GPIO_PORT				LCD_RES_GPIO_Port
#define LCD_RES_GPIO_PIN				LCD_RES_Pin
#if			PWM_MODE==OFF
#define LCD_BLK_GPIO_PORT 			LCD_BLK_GPIO_Port				
#define LCD_BLK_GPIO_PIN				LCD_BLK_Pin			
#endif
#if			FORT_ROM==ON
#define ROM_CS_GPIO_PORT 				ROM_NSS_GPIO_Port				
#define ROM_CS_GPIO_PIN					ROM_NSS_Pin	
#endif



//COLOR
#define WHITE         	0xFFFF
#define BLACK         	0x0000	  
#define BLUE           	0x001F  
#define BRED            0XF81F
#define GRED 			      0XFFE0
#define GBLUE			      0X07FF
#define RED           	0xF800
#define MAGENTA       	0xF81F
#define GREEN         	0x07E0
#define CYAN          	0x7FFF
#define YELLOW        	0xFFE0
#define BROWN 			    0XBC40 
#define BRRED 			    0XFC07 
#define GRAY  			    0X8430 
#define DARKBLUE      	0X01CF	
#define LIGHTBLUE      	0X7D7C	 
#define GRAYBLUE       	0X5458 
#define LIGHTGREEN     	0X841F 
#define LGRAY 			    0XC618 
#define LGRAYBLUE       0XA651 
#define LBBLUE          0X2B12 

//Function
void LcdInit(uint16_t color,uint8_t blk);
void LcdFill(uint16_t x,uint16_t y,uint16_t xlength,uint16_t ylength,uint16_t color);
void LcdSetBlk(uint8_t val);
void LcdShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t height,uint16_t bmp[]);
void LcdShouPoint(uint16_t x,uint16_t y,uint16_t color);


//Settings---DO NOT CHANGE  !!!!!!
#if DIRECTION==1 || DIRECTION==0
#define LCD_W 170	
#define LCD_H 320
#endif
#if DIRECTION==2 || DIRECTION==3
#define LCD_W 320
#define LCD_H 170
#endif
#define LCD_CS_Clr()  					HAL_GPIO_WritePin(LCD_CS_GPIO_PORT,LCD_CS_GPIO_PIN,GPIO_PIN_RESET)
#define LCD_CS_Set()  					HAL_GPIO_WritePin(LCD_CS_GPIO_PORT,LCD_CS_GPIO_PIN,GPIO_PIN_SET)
#define LCD_DC_Clr()  					HAL_GPIO_WritePin(LCD_DC_GPIO_PORT,LCD_DC_GPIO_PIN,GPIO_PIN_RESET)
#define LCD_DC_Set()  					HAL_GPIO_WritePin(LCD_DC_GPIO_PORT,LCD_DC_GPIO_PIN,GPIO_PIN_SET)
#define LCD_RES_Clr() 					HAL_GPIO_WritePin(LCD_RES_GPIO_PORT,LCD_RES_GPIO_PIN,GPIO_PIN_RESET)
#define LCD_RES_Set() 					HAL_GPIO_WritePin(LCD_RES_GPIO_PORT,LCD_RES_GPIO_PIN,GPIO_PIN_SET)
#if			PWM_MODE==OFF
#define LCD_BLK_ON() 						HAL_GPIO_WritePin(LCD_BLK_GPIO_PORT,LCD_BLK_GPIO_PIN,GPIO_PIN_SET)
#define LCD_BLK_OFF()						HAL_GPIO_WritePin(LCD_BLK_GPIO_PORT,LCD_BLK_GPIO_PIN,GPIO_PIN_RESET)
#endif
#if			FORT_ROM==ON
enum LCD_SIZE
{
	FORT_16 = 16,
	FORT_24 = 24
};
#define ROM_CS_Clr() 						HAL_GPIO_WritePin(ROM_CS_GPIO_PORT,ROM_CS_GPIO_PIN,GPIO_PIN_RESET)
#define ROM_CS_Set()						HAL_GPIO_WritePin(ROM_CS_GPIO_PORT,ROM_CS_GPIO_PIN,GPIO_PIN_SET)
uint8_t utf8_to_unicode(uint8_t *p_utf8, uint32_t *res);
void LcdShowUTF8String(uint16_t x,uint16_t y,enum LCD_SIZE size,uint16_t front,uint16_t back,uint8_t* str);
#endif

#endif