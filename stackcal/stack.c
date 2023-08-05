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
 	if(charLink->top < MaxSize )
 	{
 		charLink->data[++charLink->top] = opr; // -> 的优先级高于 ++
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

int currentOprPro(char opr)	//当前扫描运算符优先级
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



// ---------- 将中缀表达式翻译为逆波兰式 ----------

void translate(char *infix, char *rvsPolish)  
{	

	int NUM = 0;
	int OPR = 1;	
	int last_out = -1;	 // last_out 为 0表示上次输出为数字，1表示上次输出为运算符
	int last_scan = -1;  // last_scan 为 0表示上次扫描为数字, 1表示运算符
	// last_out,last_scan这两个变量用于逆波兰式中在相邻数字之间加空格,起到分隔效果
	
	charStack char_stack;  
	initChar(&char_stack);  //暂放运算符
	
	int i = 0;
	int j = 0;	
	
	while(infix[i]!='\0')	//此循环用于处理可能的负数 
	{
		if(infix[0]=='-')	//第一位数字为负数时 
		{          
			j = strlen (infix);
			
			while(j>0) 
			{ infix[j+5] = infix[j]; j--; }  // 右移五位
			
			infix[0] = '('; 
			infix[1] = '0'; 
			infix[2] = '-'; 
			infix[3] = '1'; 
			infix[4] = ')'; 
			infix[5] = '*'; 
			// 实现将开头的 - 转换为 (0-1)*
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
			// 实现将 - 转换为 (0-1)*
		}
		i++;
	}  // 处理负数部分结束
	
	i = 0;
	j = 0;
	
	while( infix[i] != '\0' )
	{	
		//若上次输出数字，上次循环扫描为字符，则表示该数字串结束，则在数字后加空格区分
		
		if(last_out == NUM && last_scan == OPR)  // last_scan 和 last_out 仅在这里有用
		 { rvsPolish[j++] = ' '; last_out = OPR; }
		
		if( (infix[i] >= '0' && infix[i] <= '9' ) || infix[i] == '.' )
		{
			rvsPolish[j++] = infix[i];
			last_scan = NUM;
			last_out = NUM;
		}
		
		else if( infix[i] == '+'||infix[i] == '-'||infix[i] == '*'
								||infix[i] == '/'||infix[i] == '(' )
		{
			last_scan = OPR;
			
			if(char_stack.top < 0 || 
			   currentOprPro(infix[i]) > topOprPro(getTopChar(&char_stack)))
			{ pushChar( &char_stack, infix[i] ); }   //直接入栈的情形
			
			else
			{	
			    //当前扫描字符优先级不断与栈顶字符优先级比较
				//当前字符小于栈顶字符时退栈并输出 
			    while(char_stack.top >= 0 &&
					  currentOprPro(infix[i]) < topOprPro(getTopChar(&char_stack)))		
			    { rvsPolish[j++] = popChar(&char_stack); last_out = OPR; }
				
			    //当前字符优先级大于栈顶优先级或栈空时当前字符压入字符栈内
			    if(char_stack.top < 0 || 
				   currentOprPro(infix[i]) > topOprPro( getTopChar(&char_stack)) )			 
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
			
			popChar(&char_stack);	//将 ( 出栈 
		}
		
		i++;
	}
	
	while(char_stack.top >= 0)	//将栈内剩余的运算符依次退栈输出 
	{
		rvsPolish[j++] = popChar(&char_stack);
	}
	
	rvsPolish[j]='\0';
}
 


// ------------ 计算逆波兰式,返回运算结果 ------------

double calculate(char *f )  
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
				if(f[i] == '.') { kind = DECIMAL; i++; continue; } // 有小数点则转化
				
				if(kind == INTEGER) { sum = sum*10 + (double)(f[i]-'0'); }
				
				else { divider=divider*10; sum = sum + ((double)(f[i]-'0')) / divider;}
				
				i++;
			}
			
			//转化成功一个数据，若下个字符为运算符，则 i--，回到当前运算的数据位置 
			if(f[i] == '+'||f[i] == '-'||f[i] == '*'||f[i] == '/') i--;	
			
			pushDouble(&double_stack, sum);
		}
		
		i++;  //准备下一个字符的转换 
	}
	
	return popDouble(&double_stack);
}
