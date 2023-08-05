#ifndef STACK_H
#define STACK_H

#define MaxSize 100 

// 字符栈,存放运算符,用于 translate 函数
typedef struct { char  data[MaxSize]; int top; } charStack; 

// 数字栈,存放双精度浮点数,用于 calculate 函数
typedef struct { double data[MaxSize]; int top; } doubleStack;

int currentOprPro(char );	//当前扫描元素优先级 
int topOprPro(char );		//栈顶元素优先级 

//字符栈初始化,入栈,获取栈顶元素,出栈
void initChar(charStack* );		
int pushChar(charStack*, char );			
char getTopChar(charStack* );			 
char popChar(charStack* );				

//数字栈初始化,入栈,出栈
void initDouble(doubleStack* );				
int pushDouble(doubleStack*, double );			
double popDouble(doubleStack* );				

void translate(char*, char* );	// 将中缀表达式转换为后缀表达式
double calculate(char* );		// 计算后缀表达式

#endif
