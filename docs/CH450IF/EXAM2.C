// *************************************
//Website:  http://wch.cn
//Email:    tech@wch.cn
//Author:   W.ch 2006.4
// *************************************

#include <reg52.h>
#include <intrins.h>

#include "CH450IF2.H"	// 修改该文件以适应硬件环境/单片机型号等

const unsigned char BCD_decode_tab[0x10] = { 0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F, 0X77, 0X7C, 0X58, 0X5E, 0X79, 0X71 };

void	mDelaymS( unsigned char ms )     // 延时毫秒
{
	unsigned short i;
	while ( ms -- ) {
		for(i=0;i!=1000;i++);
	}
}

void	mDelayS( unsigned char s )      // 延时秒
{
	while ( s -- ) 
	{	mDelaymS( 250 );
		mDelaymS( 250 );
		mDelaymS( 250 );
		mDelaymS( 250 );
	}
}

void init_CH450( void ) // 设置CH450按键中断
{
	IE1=0;
	EX1=1;
	EA=1;
}

// INT1中断服务程序
void int1(void) interrupt 2 //using 1
{
	unsigned char keycode;
	keycode=CH450_Read();
	CH450_Write( CH450_DIG2 | BCD_decode_tab[keycode&0x0f] );	// 显示键值
	CH450_Write( CH450_DIG3 | BCD_decode_tab[keycode>>4] );
}

main()
{
	unsigned char i;
	mDelaymS( 50 );
	init_CH450();
	for ( i = 0; i != 6; i ++ ) CH450_Write( CH450_DIG2 + ( (unsigned short)i << 8 ) );  // 因为CH450复位时不清空显示内容，所以刚开电后必须人为清空，再开显示
	CH450_Write(CH450_SYSON2);	// 开启显示及键盘
// 如果需要定期刷新显示内容，那么只要执行7个命令，包括6个数据加载命令，以及1个开启显示命令
	CH450_Write(CH450_DIG7 | BCD_decode_tab[1]);	// 显示BCD码1
	CH450_Write(CH450_DIG6 | BCD_decode_tab[2]);
	CH450_Write(CH450_DIG5 | BCD_decode_tab[3]);
	CH450_Write(CH450_DIG4 | BCD_decode_tab[4]);
	CH450_Write(CH450_DIG3 | BCD_decode_tab[5]);
	CH450_Write(CH450_DIG2 | BCD_decode_tab[6]);
	mDelayS(1);
	while ( 1 ) {	// 在中断中处理
	}
}
