#include "stack.h"
#include <string.h>

#define OK    1
#define ERROR 0

typedef int Status;

// ------------- 字符栈函数实现 --------------------

void initChar(charStack *c)
{
	c->top = -1;
}

Status pushChar(charStack *charLink,char opr)
{
 	if(charLink->top< MaxSize )
 	{
 		charLink->data[++charLink->top] = opr;
 		return OK;
	}
	else return ERROR;
}

char getTopChar(charStack *charLink)
{
	return charLink->data[charLink->top];
}

char popChar(charStack *charLink)
{
	return charLink->data[charLink->top--];
}



// ------------- 数字栈函数实现 ------------------

void initDouble(doubleStack *doubleLink)
{
	doubleLink->top=-1;
}

Status pushDouble(doubleStack *doubleLink,double data)
{
	if(doubleLink->top < MaxSize)
	{
		doubleLink->data[++doubleLink->top]=data;
		return OK;
	}
	else return ERROR;
}

double popDouble(doubleStack *doubleLink)
{
	return doubleLink->data[doubleLink->top--];
}



// ----------------- 运算优先级函数实现 -----------

int crntOprPro(char opr)	//当前扫描运算符优先级
{	
	int k;
	switch(opr)
	{
		case '(': k = 6; break;
		case '+': case '-': k = 2; break;
		case '*': case '/': k = 4; break;
	}
	return k;
}

int topOprPro(char opr)		//栈顶运算符优先级
{	
	int k;
	switch(opr)
	{
		case '(': k = 1; break;
		case '+': case '-': k = 3; break;
		case '*': case '/': k = 5; break;
	}
	return k;
}



void translate(char *infix, char *rvsPolish)
{	
	int i=0;
	int j=0;
	int last_out = -1;	 // last_out为 0表示上次输出为数字，1表示上次输出为运算符
	int last_scan = -1;  // last_scan为 0表示上次扫描为数字, 1表示上次扫描为运算符，区分数字后加空格
	int NUM = 0;
	int OPR = 1;
	
	charStack char_stack;  
	initChar(&char_stack);  //暂放运算符
	
	while(infix[i]!='\0')	//处理负数 
	{
		if(infix[0]=='-')	//第一位数字为负数时 
		{          
			j = strlen (infix);
			
			while(j>0) 
			{ infix[j+5] = infix[j]; j--; }
			
			infix[j++] = '('; // 0
			infix[j++] = '0'; // 1
			infix[j++] = '-'; // 2
			infix[j++] = '1'; // 3
			infix[j++] = ')'; // 4
			infix[j]   = '*'; // 5
		}
		
		if(infix[i] =='(' && infix[i+1] == '-')	// 非第一位负数时 
		{
			j = strlen(infix);
			
			while(j > i+1) 
			{ infix[j+5] = infix[j]; j--; }
			
			infix[j++] = '(';
			infix[j++] = '0';
			infix[j++] = '-';
			infix[j++] = '1';
			infix[j++] = ')';
			infix[j]   = '*';
			i = i + 5 ;
		}
		i++;
	}  // 处理负数部分结束
	
	i=0;
	j=0;
	
	while( infix[i] != '\0' )
	{	
		//若上次输出数字，上次循环扫描为字符，则表示该数字串结束，则在数字后加空格区分
		
		if(last_out == NUM && last_scan == OPR)  // 此函数里的 last_scan 和 last_out 只有在这里有用
		 { rvsPolish[j++] = ' '; last_out = OPR; }
		
		if( (infix[i] >= '0' && infix[i] <= '9' ) || infix[i] == '.' )
		{
			rvsPolish[j++] = infix[i];
			last_scan = NUM;
			last_out = NUM;
		}
		
		else if( infix[i] == '+'||infix[i] == '-'||infix[i] == '*'||infix[i] == '/'||infix[i] == '(' )
		{
			last_scan = OPR;
			
			if(char_stack.top < 0 || crntOprPro(infix[i]) > topOprPro( getTopChar(&char_stack)) )
			{ pushChar( &char_stack, infix[i] ); }
			
			else
			{	
			    //当前扫描字符优先级不断与栈顶字符优先级比较，当前字符小于栈顶字符时退栈并输出 
			    while(char_stack.top >= 0 && crntOprPro(infix[i]) < topOprPro(getTopChar(&char_stack)))		
			    { rvsPolish[j++] = popChar(&char_stack); last_out = OPR; }
				
			    //当前字符优先级大于栈顶优先级或栈空时当前字符压入字符栈内
			    if(char_stack.top < 0 || crntOprPro(infix[i]) > topOprPro( getTopChar(&char_stack)) )			 
			    { pushChar( &char_stack, infix[i] ); }
			}
		}
		
		else if( infix[i]==')' )				 
		{
			last_scan = OPR;
			
			//若括号仅包含数字则没有输出运算符
			if( getTopChar(&char_stack) != '(' ) 
			{ last_out = OPR; }
			
			while( getTopChar(&char_stack) != '(' ) 
			{ rvsPolish[j++] = popChar(&char_stack); }
			
			popChar(&char_stack);	//将'('出栈 
		}
		
		i++;
	}
	
	while(char_stack.top >= 0)	//将栈内剩余的运算符依次退栈输出 
	{
		rvsPolish[j++] = popChar(&char_stack);
	}
	
	rvsPolish[j]='\0';
}
 







double calculate(char *f )  // 计算逆波兰式 f
{
	int i = 0;
	int kind;		   // char类型转换为 double 类型数据标记 
	int INTEGER = 0;  
	int DECIMAL = 1;   // 赋值为 0为整数部分标记，1为小数部分标记
	
	double data1,data2;
	double sum;
	doubleStack double_stack;
	initDouble(&double_stack);
	
	while(f[i] != '\0')
	{	
		// 若为运算符, 获取栈顶两个元素进行计算 
		    
		if(f[i]=='+'||f[i]=='-'||f[i]=='*'||f[i]=='/')			
		{
			data1 = popDouble(&double_stack);
			data2 = popDouble(&double_stack);

			switch( f[i] )
			{
				case '+': pushDouble(&double_stack, data2 + data1); break;
				case '-': pushDouble(&double_stack, data2 - data1); break;
				case '*': pushDouble(&double_stack, data2 * data1); break;
				case '/': pushDouble(&double_stack, data2 / data1); break;
			}
		}
		
		else   // 为数据或小数点时转化为 double类型压栈 
		{
			kind = INTEGER;	 
			sum = 0.0000000;
			double divider = 1.0000000;
			
			while( (f[i] >= '0' && f[i] <= '9' ) || f[i] == '.' )
			{
				if(f[i] == '.') { kind = DECIMAL; i++; continue; } // 有小数点，进行转化
				
				if(kind == INTEGER) { sum = sum*10 + (double)(f[i]-'0'); }
				
				else { divider=divider*10; sum = sum + ((double)(f[i]-'0')) / divider; }
				
				i++;
			}
			
			//转化成功一个数据，若下个字符为运算符，则 i--，回到当前运算的数据位置 
			if(f[i] == '+'||f[i] == '-'||f[i] == '*'||f[i] == '/') i--;	
			
			pushDouble(&double_stack, sum);
		}
		
		i++;		// i++, 准备下一个字符的转换 
	}
	
	return popDouble(&double_stack);
}
