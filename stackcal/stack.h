#ifndef STACK_H
#define STACK_H

#define MaxSize 100 

typedef struct { char  data[MaxSize]; int top; } charStack; 
typedef struct { double data[MaxSize]; int top; } doubleStack;

int crntOprPro(char );	//当前扫描元素优先级 
int topOprPro(char );	//栈顶元素优先级 

void initChar(charStack* );		
int pushChar(charStack*, char );			
char getTopChar(charStack* );			 
char popChar(charStack* );				

void initDouble(doubleStack* );				
int pushDouble(doubleStack*, double );			
double popDouble(doubleStack* );				

void translate(char*, char* );	
double calculate(char* );		

#endif
