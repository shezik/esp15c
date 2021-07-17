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

/* 2线接口的位操作,与单片机有关 */
#define		CH450_SCL_SET		{CH450_SCL=1;}
#define		CH450_SCL_CLR		{CH450_SCL=0;}
#define		CH450_SCL_D_OUT		{}				// 设置SCL为输出方向,对于双向I/O需切换为输出
#define		CH450_SDA_SET		{CH450_SDA=1;}
#define		CH450_SDA_CLR		{CH450_SDA=0;}
#define		CH450_SDA_D_OUT		{}				// 设置SDA为输出方向,对于双向I/O需切换为输出

/* ********************************************************************************************* */
/* 常量定义 */

/* CH450的常用命令码，如果考虑与I2C兼容，那么高8位应该右移1位 */
#define CH450_SYSOFF    0x0400					// 关闭显示
#define CH450_SYSON1    0x0401					// 开启显示
#define CH450_DIG2      0x1200		            // 数码管位2显示,需另加8位数据
#define CH450_DIG3      0x1300		            // 数码管位3显示,需另加8位数据
#define CH450_DIG4      0x1400		            // 数码管位4显示,需另加8位数据
#define CH450_DIG5      0x1500					// 数码管位5显示,需另加8位数据
#define CH450_DIG6      0x1600					// 数码管位6显示,需另加8位数据
#define CH450_DIG7      0x1700		            // 数码管位7显示,需另加8位数据

// CH450接口定义
#define		CH450_I2C_ADDR1		0x40			// CH450的地址
#define		CH450_I2C_MASK		0x3E			// CH450的高字节命令掩码

// 对外子程序
extern  void CH450_Write(unsigned short cmd);	// 向CH450发出操作命令
