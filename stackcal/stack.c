#include "stack.h"
#include <string.h>

#define OK    1
#define ERROR 0

typedef int Status;

// ------------- �ַ�ջ����ʵ�� --------------------

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



// ------------- ����ջ����ʵ�� ------------------

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



// ----------------- �������ȼ�����ʵ�� -----------

int crntOprPro(char opr)	//��ǰɨ����������ȼ�
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

int topOprPro(char opr)		//ջ����������ȼ�
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
	int last_out = -1;	 // last_outΪ 0��ʾ�ϴ����Ϊ���֣�1��ʾ�ϴ����Ϊ�����
	int last_scan = -1;  // last_scanΪ 0��ʾ�ϴ�ɨ��Ϊ����, 1��ʾ�ϴ�ɨ��Ϊ��������������ֺ�ӿո�
	int NUM = 0;
	int OPR = 1;
	
	charStack char_stack;  
	initChar(&char_stack);  //�ݷ������
	
	while(infix[i]!='\0')	//������ 
	{
		if(infix[0]=='-')	//��һλ����Ϊ����ʱ 
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
		
		if(infix[i] =='(' && infix[i+1] == '-')	// �ǵ�һλ����ʱ 
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
	}  // ���������ֽ���
	
	i=0;
	j=0;
	
	while( infix[i] != '\0' )
	{	
		//���ϴ�������֣��ϴ�ѭ��ɨ��Ϊ�ַ������ʾ�����ִ��������������ֺ�ӿո�����
		
		if(last_out == NUM && last_scan == OPR)  // �˺������ last_scan �� last_out ֻ������������
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
			    //��ǰɨ���ַ����ȼ�������ջ���ַ����ȼ��Ƚϣ���ǰ�ַ�С��ջ���ַ�ʱ��ջ����� 
			    while(char_stack.top >= 0 && crntOprPro(infix[i]) < topOprPro(getTopChar(&char_stack)))		
			    { rvsPolish[j++] = popChar(&char_stack); last_out = OPR; }
				
			    //��ǰ�ַ����ȼ�����ջ�����ȼ���ջ��ʱ��ǰ�ַ�ѹ���ַ�ջ��
			    if(char_stack.top < 0 || crntOprPro(infix[i]) > topOprPro( getTopChar(&char_stack)) )			 
			    { pushChar( &char_stack, infix[i] ); }
			}
		}
		
		else if( infix[i]==')' )				 
		{
			last_scan = OPR;
			
			//�����Ž�����������û����������
			if( getTopChar(&char_stack) != '(' ) 
			{ last_out = OPR; }
			
			while( getTopChar(&char_stack) != '(' ) 
			{ rvsPolish[j++] = popChar(&char_stack); }
			
			popChar(&char_stack);	//��'('��ջ 
		}
		
		i++;
	}
	
	while(char_stack.top >= 0)	//��ջ��ʣ��������������ջ��� 
	{
		rvsPolish[j++] = popChar(&char_stack);
	}
	
	rvsPolish[j]='\0';
}
 







double calculate(char *f )  // �����沨��ʽ f
{
	int i = 0;
	int kind;		   // char����ת��Ϊ double �������ݱ�� 
	int INTEGER = 0;  
	int DECIMAL = 1;   // ��ֵΪ 0Ϊ�������ֱ�ǣ�1ΪС�����ֱ��
	
	double data1,data2;
	double sum;
	doubleStack double_stack;
	initDouble(&double_stack);
	
	while(f[i] != '\0')
	{	
		// ��Ϊ�����, ��ȡջ������Ԫ�ؽ��м��� 
		    
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
		
		else   // Ϊ���ݻ�С����ʱת��Ϊ double����ѹջ 
		{
			kind = INTEGER;	 
			sum = 0.0000000;
			double divider = 1.0000000;
			
			while( (f[i] >= '0' && f[i] <= '9' ) || f[i] == '.' )
			{
				if(f[i] == '.') { kind = DECIMAL; i++; continue; } // ��С���㣬����ת��
				
				if(kind == INTEGER) { sum = sum*10 + (double)(f[i]-'0'); }
				
				else { divider=divider*10; sum = sum + ((double)(f[i]-'0')) / divider; }
				
				i++;
			}
			
			//ת���ɹ�һ�����ݣ����¸��ַ�Ϊ��������� i--���ص���ǰ���������λ�� 
			if(f[i] == '+'||f[i] == '-'||f[i] == '*'||f[i] == '/') i--;	
			
			pushDouble(&double_stack, sum);
		}
		
		i++;		// i++, ׼����һ���ַ���ת�� 
	}
	
	return popDouble(&double_stack);
}
