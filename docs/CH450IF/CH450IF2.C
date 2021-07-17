/* ***************************
 Website:  http://wch.cn
 Email:    tech@wch.cn
 Author:   W.ch 2006.4
 CH450 接口子程序
****************************
 CH450的2线接口，不含按键中断为2个I/O引脚，含按键中断为3个I/O，兼容I2C/IIC时序
 为了节约传输时间，可以适当减少SCL/SDA之间的延时
 如果希望SCL与其它电路共用，那么只要保持SDA不变化，SCL就可以用于任何用途
 如果希望SCL和SDA都与其它电路共用，那么关键是确保SDA只在SCL为低电平期间发生变化，所以SCL和SDA适合作为输出引脚使用
     1、对于SCL引脚，直接输出
     2、对于SDA引脚，输出时：
          如果SCL为低电平，那么直接输出，
          如果SCL为高电平，那么先将SCL输出低电平，再将SDA输出，最后将SCL恢复为高电平
*************************************************************************** */
#include	"CH450IF2.H"		// 修改该文件以适应硬件环境/单片机型号等

void CH450_I2c_Start(void)  // 操作起始
{
	DISABLE_KEY_INTERRUPT;  //禁止键盘中断,防止开始时被CH450中断而进入中断服务程序中的START
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
	CH450_SDA_D_OUT;   /* 设置SDA为输出方向 */
	DELAY_0_1US;
	CH450_SCL_SET;
	DELAY_0_1US;
	CH450_SDA_SET;  /*发送I2C总线结束信号*/
	DELAY_0_1US;
	CH450_SDA_D_IN;   /* 设置SDA为输入方向 */
	ENABLE_KEY_INTERRUPT;
}

void CH450_I2c_WrByte(unsigned char dat)	//写一个字节数据
{
	unsigned char i;
	CH450_SDA_D_OUT;   /* 设置SDA为输出方向 */
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
	CH450_SDA_D_IN;   /* 设置SDA为输入方向 */
	CH450_SDA_SET;
	DELAY_0_1US;
	CH450_SCL_SET;  // 接收应答
	DELAY_0_1US;
	CH450_SCL_CLR;
}

unsigned char  CH450_I2c_RdByte(void)		//读一个字节数据
{
	unsigned char dat,i;
	CH450_SDA_SET;
	CH450_SDA_D_IN;   /* 设置SDA为输入方向 */
	dat=0;
	for(i=0;i!=8;i++)  // 输入8位数据
	{
		DELAY_0_1US;  // 可选延时
		CH450_SCL_SET;
		DELAY_0_1US;  // 可选延时
		dat<<=1;
		if(CH450_SDA_IN) dat++;  // 输入1位
		CH450_SCL_CLR;
	}
	CH450_SDA_SET;
	DELAY_0_1US;
	CH450_SCL_SET;  // 发出无效应答
	DELAY_0_1US;
	CH450_SCL_CLR;
	return(dat);
}

void CH450_Write(unsigned short cmd)	//写命令
{
	CH450_I2c_Start();               /*启动总线*/
   	CH450_I2c_WrByte(((unsigned char)(cmd>>7)&CH450_I2C_MASK)|CH450_I2C_ADDR1);
   	CH450_I2c_WrByte((unsigned char)cmd);               /*发送数据*/
  	CH450_I2c_Stop();                 /*结束总线*/ 
}

unsigned char CH450_Read(void)		//读取按键
{
	unsigned char keycode;
   	CH450_I2c_Start();                /*启动总线*/
   	CH450_I2c_WrByte((unsigned char)(CH450_GET_KEY>>7)&CH450_I2C_MASK|0x01|CH450_I2C_ADDR1);
   	keycode=CH450_I2c_RdByte();      /*读取数据*/
	CH450_I2c_Stop();                /*结束总线*/ 
	return(keycode);
}
