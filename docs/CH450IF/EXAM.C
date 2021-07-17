// *************************************
//Website:  http://wch.cn
//Email:    tech@wch.cn
//Author:   W.ch 2006.4
// *************************************

#include <reg52.h>
#include <intrins.h>

#include "CH450IF.H"	// 修改该文件以适应硬件环境/单片机型号等

unsigned char CH450_buf[6];                 //定义6个数码管的数据映象缓存区
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

void	CH450_buf_write( unsigned short cmd )  // 向CH450输出数据或者操作命令,自动建立数据映象
{
	if ( cmd & 0x1000 ) {   // 加载数据的命令,需要备份数据到映象缓冲区
		CH450_buf[ (unsigned char)( ( cmd >> 8 ) - 2 ) & 0x07 ] = (unsigned char)( cmd & 0xFF );	// 备份数据到相应的映象单元
	}
	CH450_Write( cmd );	// 发出
}

void	CH450_buf_index( unsigned char index, unsigned char dat )  // 向CH450指定的数码管输出数据,自动建立数据映象
// index 为数码管序号,有效值为0到5,分别对应DIG2到DIG7
{
	unsigned short cmd;
	CH450_buf[ index ] = dat;	// 备份数据到相应的映象单元
	cmd = ( CH450_DIG2 + ( (unsigned short)index << 8 ) ) | dat ;	// 生成操作命令
	CH450_Write( cmd );	// 发出
}

void CH450_set_bit(unsigned char bit_addr)     //段位点亮
{
	unsigned char byte_addr;
	byte_addr=(bit_addr&0x38)>>3;
	if ( byte_addr < 6 ) CH450_buf_index( byte_addr, CH450_buf[byte_addr] | (1<<(bit_addr&0x07)) );
}

void CH450_clr_bit(unsigned char bit_addr)     //段位熄灭
{
	unsigned char byte_addr;
	byte_addr=(bit_addr&0x38)>>3;
	if ( byte_addr < 6 ) CH450_buf_index( byte_addr, CH450_buf[byte_addr] & ~(1<<(bit_addr&0x07)) );
}

main()
{
	unsigned char i, j;
	mDelaymS( 50 );
	for ( i = 0; i < 6; i ++ ) CH450_buf_index( i, 0 );  // 因为CH450复位时不清空显示内容，所以刚开电后必须人为清空，再开显示
	CH450_buf_write(CH450_SYSON1);	// 开启显示
// 如果需要定期刷新显示内容，那么只要执行7个命令，包括6个数据加载命令，以及1个开启显示命令
	CH450_buf_write(CH450_DIG7 | BCD_decode_tab[1]);	// 显示BCD码1
	CH450_buf_write(CH450_DIG6 | BCD_decode_tab[2]);
	CH450_buf_write(CH450_DIG5 | BCD_decode_tab[3]);
	CH450_buf_write(CH450_DIG4 | BCD_decode_tab[4]);
	CH450_buf_write(CH450_DIG3 | BCD_decode_tab[5]);
	CH450_buf_write(CH450_DIG2 | BCD_decode_tab[6]);
	while ( 1 ) {  // 演示
		for( i=0; i<6; i++ ) CH450_buf_index( i, 0xFF );  // 全亮
		mDelayS(1);
		for( i=0; i<6; i++ ) CH450_buf_index( i, 0x00 );  // 全灭
		mDelayS(1);
		for ( j = 0; j != 8; j ++ ) {  // 依次扫描每段，演示
			for ( i = 0; i != 6; i ++ ) CH450_buf_index( i, 1<<j );
			mDelaymS( 250 );
			mDelaymS( 250 );
		}
		for( i=0; i<6; i++ ) CH450_buf_index( i, 0xFF );  // 全亮
		mDelayS(1);
		for( i=0; i<6; i++ ) CH450_buf_index( i, BCD_decode_tab[i] );  // 依次显示BCD译码0、1、2、3、4、5
		mDelayS(1);
		for( i=0; i<6; i++ ) CH450_buf_index( i, BCD_decode_tab[i+6] );  // 依次显示BCD译码6、7、8、9、a、b
		mDelayS(1);
		for( i=0; i<6; i++ ) CH450_buf_index( i, 0x00 );  // 全灭
		mDelayS(1);
		for(i=0;i!=6*8;i++) {  // 依次置段位
			CH450_set_bit(i);
			mDelaymS(200);
		}
		mDelayS(1);
		for(i=0;i!=6*8;i++) {  // 依次清段位
			CH450_clr_bit(i);
			mDelaymS(200);
		}
		mDelayS(1);
	}
}
