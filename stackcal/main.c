#include <stdio.h>
#include <string.h>
#include "stack.h"

int main()
{
	char infix[MaxSize];		
	char rvsPolish[MaxSize];	 
	printf( "��������ʽ: " );
	scanf( "%[^\n]", infix );
	translate( infix, rvsPolish );
	printf( "������Ϊ: %lf", calculate(rvsPolish) );
	return 0;
}

/* 
	����ջʵ�ֵļ��׼�����,���� + - * / () ���������   
	����һ����׺���ʽ,�ȷ���Ϊ�沨��ʽ,�ټ���������
	���־���Ϊ double �� ,���Ĭ�ϱ���С��Ϊ 6 λ,
	��׷����߾���,���� 12 �� %lf ���޸�
	
	                                Dale Chu  Mar.4th,2023
*/
