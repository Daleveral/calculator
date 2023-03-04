#include <stdio.h>
#include <string.h>
#include "stack.h"

int main()
{
	char infix[MaxSize];		
	char rvsPolish[MaxSize];	 
	printf( "请输入算式: " );
	scanf( "%[^\n]", infix );
	translate( infix, rvsPolish );
	printf( "计算结果为: %lf", calculate(rvsPolish) );
	return 0;
}

/* 
	利用栈实现的简易计算器,进行 + - * / () 的四则计算   
	接收一个中缀表达式,先翻译为逆波兰式,再计算给出结果
	数字精度为 double 型 ,结果默认保留小数为 6 位,
	若追求更高精度,则在 12 行 %lf 处修改
	
	                                Dale Chu  Mar.4th,2023
*/
