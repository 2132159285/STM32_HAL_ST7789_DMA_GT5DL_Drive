#include "lcd.h"
#include "stdint.h"
#include "spi.h"
#include "lcd.h"
#include "math.h"
#include "string.h"
#include "stdio.h"
#include "tim.h"
#include "dma.h"
#include "main.h"

#if FORT_ROM == ON
#include "GT5DL24A2W.h"
#endif

#if LCD_DMA_ENABLE == ON
uint16_t DMA_TMP1[DMA_TMP_SIZE+5];
uint16_t DMA_TMP2[DMA_TMP_SIZE+5];
uint32_t DMA_NUM1=0;
uint32_t DMA_NUM2=0;
#endif

#if FORT_ROM == ON
uint8_t  FORT_DATA[1024];
#endif


//背光控制
void LcdSetBlk(uint8_t val)
{
	#if PWM_MODE == 1 
	__HAL_TIM_SetCompare(&PWM_TIM,PWM_CHN,val);
	#else
	if(sta==ON) LCD_BLK_OFF();
	else 			  LCD_BLK_ON();
	#endif
}


//LCD数据发送
void SpiData08(uint8_t  data)
{
	LCD_CS_Clr();
	HAL_SPI_Transmit(&LCD_SPI,&data,1,LCD_SPI_WAIT);
	LCD_CS_Set();
}
void SpiData16(uint16_t data)
{
	LCD_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
	HAL_SPI_Init(&LCD_SPI);
	LCD_CS_Clr();
	HAL_SPI_Transmit(&LCD_SPI,(uint8_t*)&data,1,LCD_SPI_WAIT);
	LCD_CS_Set();
	LCD_SPI.Init.DataSize = SPI_DATASIZE_8BIT;
	HAL_SPI_Init(&LCD_SPI);
}
void LcdReg(uint8_t data)
{
	LCD_DC_Clr();
	SpiData08(data);
	LCD_DC_Set();
}

//LCD设置绘图区
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
	#if DIRECTION==0
	LcdReg(0x2a);//列地址设置
	SpiData16(x1+35);
	SpiData16(x2+35);
	LcdReg(0x2b);//行地址设置
	SpiData16(y1);
	SpiData16(y2);
	LcdReg(0x2c);//储存器写
	#endif
	
	#if DIRECTION==1
	LcdReg(0x2a);//列地址设置
	SpiData16(x1+35);
	SpiData16(x2+35);
	LcdReg(0x2b);//行地址设置
	SpiData16(y1);
	SpiData16(y2);
	LcdReg(0x2c);//储存器写
	#endif
	
	#if DIRECTION==2
	LcdReg(0x2a);//列地址设置
	SpiData16(x1);
	SpiData16(x2);
	LcdReg(0x2b);//行地址设置
	SpiData16(y1+35);
	SpiData16(y2+35);
	LcdReg(0x2c);//储存器写
	#endif
	
	#if DIRECTION==3
	LcdReg(0x2a);//列地址设置
	SpiData16(x1);
	SpiData16(x2);
	LcdReg(0x2b);//行地址设置
	SpiData16(y1+35);
	SpiData16(y2+35);
	LcdReg(0x2c);//储存器写
	#endif
}

	
//LCD初始化
void LcdInit(uint16_t color,uint8_t blk)
{
	LCD_RES_Clr();
	HAL_Delay(20);
	LCD_RES_Set();
	HAL_Delay(20);
	LcdReg(0x11); 
	LcdReg(0x36); 
	if(DIRECTION==0)	SpiData08(0x00);
	if(DIRECTION==1)	SpiData08(0xC0);
	if(DIRECTION==2)	SpiData08(0x70);
	if(DIRECTION==3) 	SpiData08(0xA0);
	LcdReg(0x3A);
	SpiData08(0x05);
	LcdReg(0xB2);
	SpiData08(0x0C);
	SpiData08(0x0C);
	SpiData08(0x00);
	SpiData08(0x33);
	SpiData08(0x33); 
	LcdReg(0xB7); 
	SpiData08(0x35);  
	LcdReg(0xBB);
	SpiData08(0x1A);
	LcdReg(0xC0);
	SpiData08(0x2C);
	LcdReg(0xC2);
	SpiData08(0x01);
	LcdReg(0xC3);
	SpiData08(0x0B);   
	LcdReg(0xC4);
	SpiData08(0x20);  
	LcdReg(0xC6); 
	SpiData08(0x0F);    
	LcdReg(0xD0); 
	SpiData08(0xA4);
	SpiData08(0xA1);
	LcdReg(0x21); 
	LcdReg(0xE0);
	SpiData08(0xF0);
	SpiData08(0x00);
	SpiData08(0x04);
	SpiData08(0x04);
	SpiData08(0x04);
	SpiData08(0x05);
	SpiData08(0x29);
	SpiData08(0x33);
	SpiData08(0x3E);
	SpiData08(0x38);
	SpiData08(0x12);
	SpiData08(0x12);
	SpiData08(0x28);
	SpiData08(0x30);
	LcdReg(0xE1);
	SpiData08(0xF0);
	SpiData08(0x07);
	SpiData08(0x0A);
	SpiData08(0x0D);
	SpiData08(0x0B);
	SpiData08(0x07);
	SpiData08(0x28);
	SpiData08(0x33);
	SpiData08(0x3E);
	SpiData08(0x36);
	SpiData08(0x14);
	SpiData08(0x14);
	SpiData08(0x29);
	SpiData08(0x32);
  LcdReg(0x11);
  HAL_Delay(120);	
	LcdReg(0x29);
	LcdFill(0,0,LCD_W,LCD_H,color);
	
	#if FORT_ROM==ON
	//LCD_SPI.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_4;
	//HAL_SPI_Init(&LCD_SPI);
	//ROM_CS_Clr();
	GT_Font_Init();
	//ROM_CS_Set();
	//LCD_SPI.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_2;
	//HAL_SPI_Init(&LCD_SPI);
	#endif
	
	#if PWM_MODE == 1
	HAL_TIM_PWM_Start(&PWM_TIM,PWM_CHN);
	LcdSetBlk(blk);
	#else
	LcdConBLK(ON);
	#endif
}

//LCD画点
void LcdShouPoint(uint16_t x,uint16_t y,uint16_t color)
{
	LCD_Address_Set(x,y,x,y);
	SpiData16(color);
}

//LCD填充
#if LCD_DMA_ENABLE == ON
void LcdFill(uint16_t x,uint16_t y,uint16_t xlength,uint16_t ylength,uint16_t color)
{
	uint16_t Len=(DMA_TMP_SIZE>=2500?2500:DMA_TMP_SIZE);
	DMA_NUM1=xlength*ylength;
	
	if(DMA_NUM1<=Len) {for(uint16_t i=1;i<=DMA_NUM1;i++) DMA_TMP1[i-1]=color;}
	else 					 	  {for(uint16_t i=1;i<=Len;i++)      DMA_TMP1[i-1]=color;}
	
	LCD_Address_Set(x,y,x+xlength-1,y+ylength-1);
	
	LCD_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
	HAL_SPI_Init(&LCD_SPI);
	LCD_CS_Clr();
	
	while(DMA_NUM1)
	{
		if(DMA_NUM1>Len)
		{
			HAL_SPI_Transmit_DMA(&LCD_SPI,(uint8_t*)DMA_TMP1,Len);
			DMA_NUM1-=Len;
			while(LCD_SPI.State!=HAL_SPI_STATE_READY);
		}
		else
		{
			HAL_SPI_Transmit_DMA(&LCD_SPI,(uint8_t*)DMA_TMP1,DMA_NUM1);
			DMA_NUM1=0;
			while(LCD_SPI.State!=HAL_SPI_STATE_READY);
		}
	}
	
	LCD_CS_Set();	
	LCD_SPI.Init.DataSize = SPI_DATASIZE_8BIT;
	HAL_SPI_Init(&LCD_SPI);
}
#else
void LcdFill(uint16_t x,uint16_t y,uint16_t xlength,uint16_t ylength,uint16_t color)
{ 
	LCD_Address_Set(x,y,x+xlength-1,y+ylength-1);
	LCD_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
	HAL_SPI_Init(&LCD_SPI);
	LCD_CS_Clr();

	for(uint32_t LEN=xlength*ylength;LEN>0;LEN--)
	{													   	 	
		HAL_SPI_Transmit(&LCD_SPI,(uint8_t*)&color,1,LCD_SPI_WAIT);
	}

	LCD_CS_Set();	
	LCD_SPI.Init.DataSize = SPI_DATASIZE_8BIT;
	HAL_SPI_Init(&LCD_SPI);
}
#endif

//LCD显示图片
#if LCD_DMA_ENABLE == ON
void LcdShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t height,uint16_t bmp[])
{
	uint32_t LEN=length*height,Pos=0;
	LCD_Address_Set(x,y,x+length-1,y+height-1);
	LCD_SPI.Init.DataSize = SPI_DATASIZE_16BIT;
	HAL_SPI_Init(&LCD_SPI);
	LCD_CS_Clr();
	while(LEN)
	{
		if(LEN>25560)
		{
			HAL_SPI_Transmit_DMA(&LCD_SPI,(uint8_t*)&bmp[Pos],25560);
			LEN-=25560; Pos+=25560;
			while(LCD_SPI.State!=HAL_SPI_STATE_READY);
		}
		else
		{
			HAL_SPI_Transmit_DMA(&LCD_SPI,(uint8_t*)&bmp[Pos],LEN);
			LEN=0;
			while(LCD_SPI.State!=HAL_SPI_STATE_READY);
		}
	}
	LCD_CS_Set();	
	LCD_SPI.Init.DataSize = SPI_DATASIZE_8BIT;
	HAL_SPI_Init(&LCD_SPI);
}
#else
void LcdShowPicture(uint16_t x,uint16_t y,uint16_t length,uint16_t height,uint8_t bmp[])
{
	HAL_DMA_GetState(&hdma_spi1_tx);
	LCD_Address_Set(x,y,x+length-1,y+height-1);
	LCD_CS_Clr();
	for(uint32_t i=0;i<length*height*2;i++)
	{
		HAL_SPI_Transmit(&hspi1,&bmp[i],1,LCD_SPI_WAIT);
	}
	LCD_CS_Set();	
}
#endif







//字库相关函数
#if FORT_ROM == ON

unsigned long r_dat_bat(unsigned long address,unsigned long DataLen,unsigned char *pBuff)
{
	uint8_t Address[4]={0x30,address>>16,address>>8,(uint8_t)address};
	
	LCD_SPI.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_4;
	HAL_SPI_Init(&LCD_SPI);
	ROM_CS_Clr();
	
	HAL_SPI_Transmit(&LCD_SPI,Address,4,LCD_SPI_WAIT);
	HAL_SPI_Receive (&LCD_SPI,pBuff,DataLen,LCD_SPI_WAIT);
	
	ROM_CS_Set();
	LCD_SPI.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_2;
	HAL_SPI_Init(&LCD_SPI);
	
	return DataLen;
	
}

unsigned char gt_read_data(unsigned char* sendbuf , unsigned char sendlen , unsigned char* receivebuf, unsigned int receivelen)
{
	LCD_SPI.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_4;
	HAL_SPI_Init(&LCD_SPI);
	ROM_CS_Clr();
	
	HAL_SPI_Transmit(&LCD_SPI,sendbuf,sendlen,LCD_SPI_WAIT);
	HAL_SPI_Receive(&LCD_SPI,receivebuf,receivelen,LCD_SPI_WAIT);
	
	ROM_CS_Set();
	LCD_SPI.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_2;
	HAL_SPI_Init(&LCD_SPI);
	
	return 1;
}

uint8_t utf8_to_unicode(uint8_t *p_utf8, uint32_t *res)
{
	if (p_utf8[0] < 0x80) 
	{
		*res = p_utf8[0];
		return 1;
	} 
	else if (p_utf8[0] < 0xE0) 
	{
		*res = ((p_utf8[0] & 0x1F) << 6) | (p_utf8[1] & 0x3F);
		return 2;
	} 
	else if (p_utf8[0] < 0xF0) 
	{
		*res = ((p_utf8[0] & 0x0F) << 12) | ((p_utf8[1] & 0x3F) << 6) | (p_utf8[2] & 0x3F);
		return 3;
	} 
	else if (0xF0 == (p_utf8[0] & 0xF0)) 
	{
		*res = ((p_utf8[0] & 0x07) << 18) | ((p_utf8[1] & 0x3F) << 12) | ((p_utf8[2] & 0x3F) << 6) | (p_utf8[3] & 0x3F);
		return 4;
	}
	return 0;
}

//从字符缓冲显示一个字符
void LcdShowRam(uint16_t x,uint16_t y,uint16_t Disx,uint16_t Disy,uint16_t front,uint16_t back)
{
	uint16_t cnt = 0,disp_x, disp_y = 0;
  uint8_t temp=0,multiple = ((Disx + 7) >> 3);
	
  for (uint16_t i = 0; i < Disy; i++)
  {
		for (uint16_t j = 0; j < multiple; j++)
		{
			temp = FORT_DATA[cnt++];
			for (uint16_t k = 0; k < 8; k++)
			{
				disp_x = (x + k + (j * 8));
				disp_y = (y + i);
				if ( ((temp << k) & 0x80) == 0 ) LcdShouPoint(disp_x, disp_y, back);
				else 														 LcdShouPoint(disp_x, disp_y, front);
			}
		}
	}
	
}

//显示多国语言混合字符串
void LcdShowUTF8String(uint16_t x,uint16_t y,enum LCD_SIZE size,uint16_t front,uint16_t back,uint8_t* str)
{
	uint32_t unicode=0;
	uint16_t i=0,w=0,index=0;
	
	while(str[i]!='\0')
	{
		index=utf8_to_unicode(&str[i],&unicode);
		if(index==0) {i++; continue;}
		if(unicode <0x7F)
		{
			if(size == FORT_16)
			{
				ASCII_GetData(unicode,ASCII_8X16, FORT_DATA);
				LcdShowRam(x,y,8,16,front,back);
				x+=((FORT_DATA[0]<<8)|(FORT_DATA[1]));
			}
			else 
			{
				ASCII_GetData(unicode,ASCII_12X24,FORT_DATA);
				LcdShowRam(x,y,12,24,front,back);
				x+=((FORT_DATA[0]<<8)|(FORT_DATA[1]));
			}
		}
		index++;
	}
}

#endif


