#ifndef STACK_H
#define STACK_H

#define MaxSize 100 

// �ַ�ջ,��������,���� translate ����
typedef struct { char  data[MaxSize]; int top; } charStack; 

// ����ջ,���˫���ȸ�����,���� calculate ����
typedef struct { double data[MaxSize]; int top; } doubleStack;

int currentOprPro(char );	//��ǰɨ��Ԫ�����ȼ� 
int topOprPro(char );		//ջ��Ԫ�����ȼ� 

//�ַ�ջ��ʼ��,��ջ,��ȡջ��Ԫ��,��ջ
void initChar(charStack* );		
int pushChar(charStack*, char );			
char getTopChar(charStack* );			 
char popChar(charStack* );				

//����ջ��ʼ��,��ջ,��ջ
void initDouble(doubleStack* );				
int pushDouble(doubleStack*, double );			
double popDouble(doubleStack* );				

void translate(char*, char* );	// ����׺���ʽת��Ϊ��׺���ʽ
double calculate(char* );		// �����׺���ʽ

#endif
