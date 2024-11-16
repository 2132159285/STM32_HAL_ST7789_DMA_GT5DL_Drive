#ifndef _GT5DL24A2W_H_
#define _GT5DL24A2W_H_


/* �ⲿ�������� ��Ҫ�û�����ʹ�õ�mcuʵ�֣��ο��ļ����о���Ĳο�����*/
extern unsigned long r_dat_bat(unsigned long address,unsigned long DataLen,unsigned char *pBuff);
extern unsigned char gt_read_data(unsigned char* sendbuf , unsigned char sendlen , unsigned char* receivebuf, unsigned int receivelen);

/* ----------------------------------------------------------- */
//�ֿ��ʼ��
int GT_Font_Init(void);
/* ----------------------------------------------------------- */


#define ASCII_5X7           1
#define ASCII_7X8           2
#define ASCII_6X12          3
#define ASCII_8X16					4
#define ASCII_12X24					5
#define ASCII_12X24_B				6
#define ASCII_12_N					7
#define ASCII_24_N					8


//���к궨������zz_zf����
//����, ����, б�干17������, �������0~16
#define F_FONT_24				20	//����
#define F_FONT_32				21
#define F_FONT_48				22

#define S_FONT_24				23	//����
#define S_FONT_32				24
#define S_FONT_48				25

#define I_FONT_24				26	//б��
#define I_FONT_32				27
#define I_FONT_48				28

//Բ��	���ȿ�		��14���ַ�, �������0~13
#define A_16X16_T				30
#define A_24X24_T				31
#define A_24X32_T				32
#define A_40X48_T				33
#define A_40X64_T				34

//����	���ȿ�
#define B_16X16_T				35
#define B_24X24_T				36
#define B_24X32_T				37
#define B_40X48_T				38
#define B_40X64_T				39

//��14���ַ�
#define T_FONT_24X24		40	//ʱ����, ���ȿ�
#define T_FONT_24X32		41
#define T_FONT_40X48		42
#define T_FONT_48X64		43

//��14���ַ�, ��Ӧ�������� 0~13
#define F_8X16_T				44	//������, ���ȿ�
#define F_16X24_T				45
#define F_16X32_T				46
#define F_24X48_T				47
#define F_32X64_T				48


unsigned char  ASCII_GetData(unsigned char asc,unsigned long ascii_kind,unsigned char *DZ_Data);
unsigned long  U2G(unsigned int  unicode);
unsigned long U2K(unsigned int Unicode);
unsigned long U2J(unsigned int Unicode);
unsigned long BIG5_GBK( unsigned char h,unsigned char l);
unsigned long Shift_JIS_TO_JIS0208(unsigned int Code16);
void gt_16_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long GBK_24_GetData(unsigned char MSB, unsigned char LSB,unsigned char *DZ_Data);
unsigned long KSC5601_F_16_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long KSC5601_F_24_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long JIS0208_16X16_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long JIS0208_24X24_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long LATIN_8X16_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long LATIN_16_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long LATIN_12X24_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long  CYRILLIC_8X16_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long CYRILLIC_16_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long  CYRILLIC_12X24_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long GREECE_8X16_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long GREECE_16_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long GREECE_12X24_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long HEBREW_8X16_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long HEBREW_12X24_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned long ALB_16_GetData(unsigned int unicode_alb,unsigned char *DZ_Data);
unsigned long ALB_24_GetData(unsigned int UNICODE_alb,unsigned char *DZ_Data);
unsigned long THAILAND_16X24_GetData(unsigned int FontCode,unsigned char *DZ_Data);
unsigned char zz_zf(unsigned char Sequence,unsigned char kind,unsigned char *DZ_Data);

//һά��
unsigned long *BAR_CODE_EAN13(unsigned char* BAR_NUM);
unsigned long BAR_CODE39(unsigned char ASCIICODE,unsigned char *DZ_Data);
unsigned long * BAR_CODE128(unsigned char  *BAR_NUM,unsigned char BAR_NUM_LEN, unsigned char  flag);


#endif

