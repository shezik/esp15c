/* ***************************
 Website:  http://wch.cn
 Email:    tech@wch.cn
 Author:   W.ch 2006.4
 CH450 接口子程序
****************************
 CH450的2线接口，只需要2个I/O引脚，兼容I2C/IIC时序
 为了节约传输时间，可以适当减少SCL/SDA之间的延时
 如果希望SCL与其它电路共用，那么只要保持SDA不变化，SCL就可以用于任何用途
 如果希望SCL和SDA都与其它电路共用，那么关键是确保SDA只在SCL为低电平期间发生变化，所以SCL和SDA适合作为输出引脚使用
     1、对于SCL引脚，直接输出
     2、对于SDA引脚，输出时：
          如果SCL为低电平，那么直接输出，
          如果SCL为高电平，那么先将SCL输出低电平，再将SDA输出，最后将SCL恢复为高电平
*************************************************************************** */
#include	"CH450IF.H"		// 修改该文件以适应硬件环境/单片机型号等

void CH450_I2c_Start(void)  // 操作起始
{
	CH450_SDA_SET;   /*发送起始条件的数据信号*/
	CH450_SDA_D_OUT;   /* 设置SDA为输出方向 */
	CH450_SCL_SET;
	CH450_SCL_D_OUT;   /* 设置SCL为输出方向 */
	DELAY_0_1US;
	CH450_SDA_CLR;   /*发送起始信号*/
	DELAY_0_1US;      
	CH450_SCL_CLR;   /*钳住I2C总线，准备发送或接收数据 */
}

void CH450_I2c_Stop(void)  // 操作结束
{
	CH450_SDA_CLR;
	DELAY_0_1US;
	CH450_SCL_SET;
	DELAY_0_1US;
	CH450_SDA_SET;  /*发送I2C总线结束信号*/
	DELAY_0_1US;
}

void CH450_I2c_WrByte(unsigned char dat)	//写一个字节数据
{
	unsigned char i;
	for(i=0;i!=8;i++)  // 输出8位数据
	{
		if(dat&0x80) {CH450_SDA_SET;}
		else {CH450_SDA_CLR;}
		DELAY_0_1US;
		CH450_SCL_SET;
		dat<<=1;
		DELAY_0_1US;  // 可选延时
		CH450_SCL_CLR;
	}
	CH450_SDA_SET;
	DELAY_0_1US;
	CH450_SCL_SET;  // 接收应答
	DELAY_0_1US;
	CH450_SCL_CLR;
}

void CH450_Write(unsigned short cmd)	//写命令
{
	CH450_I2c_Start();               /*启动总线*/
   	CH450_I2c_WrByte(((unsigned char)(cmd>>7)&CH450_I2C_MASK)|CH450_I2C_ADDR1);
   	CH450_I2c_WrByte((unsigned char)cmd);               /*发送数据*/
  	CH450_I2c_Stop();                 /*结束总线*/ 
}
