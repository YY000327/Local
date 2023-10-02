/*
 *一、汇编语言访问存储器
 * 1. 读存储器
 * 		LDR R1, [R2]
 * 2. 写寄存器
 * 		STR R1, [R2]
 *
 * 二、c语言访问存储器
 * 1. 读存储器
 * 		data= *ADDR
 * 2. 写存储器
 * 		*ADDR = data
 *
 *
 *
 *
 * */

void Delay (unsigned int Time){

		while (Time --);

}	

# if 0
int main()
{
	/* 通过设置GPX2CON寄存器来将GPX2DAT引脚设置成输出功能*/
	*(unsigned int *)0x11000c40=0x10000000;
	

	while(1)
	{
		/*点亮*/
		*(unsigned int*) 0x11000c44=0x00000080;
		Delay(100000);
		/* 熄灭 */
		*(unsigned int*) 0x11000c44=0x00000000;
		Delay(100000);

	}
	return 0;
}
#endif

#if 0
#define GPX2CON (*(unsigned int *) 0x11000c40)
#define GPX2DAT (*(unsigned int *) 0x11000c44)

int main()
{
	
	while(1)
	{
		/*点亮*/
		GPX2CON=0x00000080;
		/*延时*/
		Delay(100000);
		/* 熄灭 */
		GPX2DAT=0x00000000;
		Delay(100000);

	}
	return 0;
}
# endif

#if 0
typedef struct{
	
	unsigned int CON;
	unsigned int DAT;
	unsigned int PUD;
	unsigned int DRV;


}gpx2;

#define GPX2 (*(gpx2 *) 0x11000c40)


int main()
{
	while(1)
	{
		/*点亮*/
		GPX2.CON=0x00000080;
		/*延时*/
		Delay(100000);
		/* 熄灭 */
		GPX2.DAT=0x00000000;
		/*延时*/
		Delay(100000);

	return 0;
}

# endif

#include "exynos_4412.h"

int main()
{
	GPX2.CON=GPX2.CON & (~ (0xF<<28)) | (0x1 << 28);
	
	while(1)
	{
		/*点亮*/
		GPX2.DAT=GPX2.DAT | (1 << 7);
		/*延时*/
		Delay(100000);
		/* 熄灭 */
		GPX2.DAT=GPX2.DAT & (~ (1 << 7 ));
		/*延时*/
		Delay(100000);
	}
	return 0;
}
/*
 * 1. unsigned int a; 将a的第三位是1，其他位置保持不变
 * 	
 * 	00000000 00000000 00000000 000010000
 * 	a= a | ( 1 << 3);
 *
 * 2. unsigned int a; 将a的第三位是0，其他位置保持不变
 *
 * 	a= a $ 0xFFFFFF7;
 * 	或者
 * 	a= a & (~(1 << 3));
 *
 * 3. unsigned int a; 将a的第7:4位为0101，其他位置保持不变
 * ********* ******** ******** ********
 * ********* ******** ******** 0101****
 *  
 *
 *  	1), 先清零
 *  	11111111 11111111 11111111 00001111
 * 		00000000 00000000 00000000 11110000
 * 		00000000 00000000 00000000 00001111
 *
 * 		a= a & ( ~ (0xF << 4 ))
 *
 * 		2).再置位
 *
 * 		a= a | (0x5 << 4);
 * 			
 * 		=> a= a & ( ~ (0xF << 4 ))| (0x5 << 4)
 *
 * */
