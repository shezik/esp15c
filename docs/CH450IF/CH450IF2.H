// 硬件相关定义, 请根据实际硬件修改本文件

#include <reg52.h>
#include <intrins.h>
#pragma NOAREGS		// 如果MCS51在中断服务程序中调用CH450子程序或者使用键盘中断功能，那么建议加入此编译选项

/* 延时0.1uS子程序,与单片机速度有关,对于双向I/O可以不需要延时,对于带上拉的准双向I/O建议加上延时 */
//#define		DELAY_0_1US		{}				// MCS51<=10MHz
#define		DELAY_0_1US		{_nop_();}		// MCS51>10MHz

/* 2线接口的连接,与实际电路有关 */
sbit	CH450_SCL=P1^7;
sbit	CH450_SDA=P1^6;
sbit	CH450_INT=P3^3;   // 标准的2线接口使用该引脚输出中断

/* 2线接口的位操作,与单片机有关 */
#define		CH450_SCL_SET		{CH450_SCL=1;}
#define		CH450_SCL_CLR		{CH450_SCL=0;}
#define		CH450_SCL_D_OUT		{}				// 设置SCL为输出方向,对于双向I/O需切换为输出
#define		CH450_SDA_SET		{CH450_SDA=1;}
#define		CH450_SDA_CLR		{CH450_SDA=0;}
#define		CH450_SDA_IN		(CH450_SDA)
#define		CH450_SDA_D_OUT		{}				// 设置SDA为输出方向,对于双向I/O需切换为输出
#define		CH450_SDA_D_IN		{CH450_SDA=1;}	// 设置SDA为输入方向,对于双向I/O需切换为输入

/* 与单片机有关,与中断连接方式有关 */
//#define		USE_CH450_KEY		1			// 使用了CH450的按键中断
#ifdef USE_CH450_KEY
#define		DISABLE_KEY_INTERRUPT	{EX1=0;}
#define		ENABLE_KEY_INTERRUPT	{EX1=1;}
#define		CLEAR_KEY_INTER_FLAG	{IE1=0;}
#else
#define		DISABLE_KEY_INTERRUPT	{}
#define		ENABLE_KEY_INTERRUPT	{}
#define		CLEAR_KEY_INTER_FLAG	{}
#endif

/* ********************************************************************************************* */
/* 常量定义 */

/* CH450的常用命令码，如果考虑与I2C兼容，那么高8位应该右移1位 */
#define CH450_SYSOFF    0x0400					// 关闭显示、关闭键盘
#define CH450_SYSON1    0x0401					// 开启显示
#define CH450_SYSON2    0x0403					// 开启显示、键盘
#define CH450_GET_KEY	0x0700					// 获取按键,返回按键代码
#define CH450_DIG2      0x1200		            // 数码管位2显示,需另加8位数据
#define CH450_DIG3      0x1300		            // 数码管位3显示,需另加8位数据
#define CH450_DIG4      0x1400		            // 数码管位4显示,需另加8位数据
#define CH450_DIG5      0x1500					// 数码管位5显示,需另加8位数据
#define CH450_DIG6      0x1600					// 数码管位6显示,需另加8位数据
#define CH450_DIG7      0x1700		            // 数码管位7显示,需另加8位数据

// 有效按键代码
#define		CH450_KEY_MIN		0x42
#define		CH450_KEY_MAX		0x7F

// CH450接口定义
#define		CH450_I2C_ADDR1		0x40			// CH450的地址
#define		CH450_I2C_MASK		0x3E			// CH450的高字节命令掩码

// 对外子程序
extern	unsigned char CH450_Read(void);				// 从CH450读取按键代码
extern  void CH450_Write(unsigned short cmd);	// 向CH450发出操作命令
