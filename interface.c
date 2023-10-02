#include "exynos_4412.h"

void Delay (unsigned int time){
	while (time --);

}

int main()
{
	/*设置一级分频*/
	WDT.WTCON = WDT.WTCON | (0xFF << 8);
	/*设置二级分频*/
	WDT.WTCON = WDT.WTCON | (0x3 << 3);
	/*WTCNT递减频率 = PLCK （10000000） / (0xFF + 1)/ 128
	 * = 3052
	 * */
	/*禁止wdt产生中断信号*/
	WDT.WTCON = WDT.WTCON & (~ (1 << 2));
	/*使能WDT产生复位信号*/
	WDT.WTCON = WDT.WTCON | 1;

	/*设置计数器的值*/
	WDT.WTCNT = (3052 * 5) ;

	/*
	 * 使能WDT，计数器开始递减
	 * */
	WDT.WTCON= WDT.WTCON | (1<< 5);

	while (1)
	{

		printf (" WDT.WTCNT = %d\n ", WDT.WTCNT);
		WDT.WTCNT =3652;

		Delay(100000);

	}

	
	return 0;
}
