#include <iostream>
#include <string.h>

using namespace std;

template <class T>
class Stack //堆
{ 
public:
	T a[100];
	int Top;

	Stack() { Top = 0; }
	T top()
	{
		return a[Top];
	}

	void pop() { Top--; }

	bool isempty()
	{
		if (Top == 0)
			return true;
		else
			return false;
	}

	void push(T b)
	{
		Top++;
		a[Top] = b;
	}
};


void transform(char inorder[], char post[], int &m) //将中缀表达式转换为后缀表达式
{
	int n = strlen(inorder); 
	Stack<char> operatorStack;		 //存放操作符的堆
	for (int i = 0; i < n; i++)
	{
		if (inorder[i] >= '0' && inorder[i] <= '9') 
		{
			post[m] = inorder[i];
			m++;
		}
		if (inorder[i] == '(')
			operatorStack.push(inorder[i]); //若为‘（’直接压入堆栈
		if (inorder[i] == '+')	  //若为‘+’与栈顶比较优先级，较低则将栈顶操作符加到数组中，在将‘+’压栈
		{
			if (!operatorStack.isempty() && (operatorStack.top() == '*' || operatorStack.top() == '/' || operatorStack.top() == '-'))
			{
				post[m++] = operatorStack.top();
				operatorStack.pop();
				operatorStack.push(inorder[i]);
			}
			else
			{
				operatorStack.push(inorder[i]);
			}
		}
		if (inorder[i] == '-') //若为‘-’与栈顶比较优先级，较低则将栈顶操作符加到数组中，将‘-’压栈
		{
			if (!operatorStack.isempty() && (operatorStack.top() == '*' || operatorStack.top() == '/'))
			{
				post[m++] = operatorStack.top();
				operatorStack.pop();
				operatorStack.push(inorder[i]);
			}
			else
			{
				operatorStack.push(inorder[i]);
			}
		}
		if (inorder[i] == '*' || inorder[i] == '/')
			operatorStack.push(inorder[i]); //若为‘*’或‘/’直接压栈
		if (inorder[i] == ')')	  //若遇到‘）’将栈中的操作符依次弹出直到遇到‘（’结束
		{
			while (operatorStack.top() != '(')
			{
				post[m++] = operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.pop(); //弹出‘（’
		}
	}
	while (!operatorStack.isempty()) 
	{
		post[m++] = operatorStack.top();
		operatorStack.pop();
	}
}

int comput(char post[], int n) //通过转换后的表达式求结果
{
	Stack<int> resultStack; //存放运算结果的堆
	int a, b, c, result;
	for (int i = 0; i < n; i++)
	{
		if (post[i] >= '0' && post[i] <= '9')
		{
			resultStack.push((post[i] - '0')); //char转int
		}
		
		//对四则运算符进行不同的操作
		if (post[i] == '-')
		{
			b = resultStack.top();
			resultStack.pop();
			a = resultStack.top();
			resultStack.pop();
			c = a - b;
			resultStack.push(c);
		}
		if (post[i] == '+')
		{
			b = resultStack.top();
			resultStack.pop();
			a = resultStack.top();
			resultStack.pop();
			c = a + b;
			resultStack.push(c);
		}
		if (post[i] == '*')
		{
			b = resultStack.top();
			resultStack.pop();
			a = resultStack.top();
			resultStack.pop();
			c = a * b;
			resultStack.push(c);
		}
		if (post[i] == '/')
		{
			b = resultStack.top();
			resultStack.pop();
			a = resultStack.top();
			resultStack.pop();
			c = a / b;
			resultStack.push(c);
		}
	}
	result = resultStack.top(); 
	resultStack.pop();			//清空
	return result;
}

int main(void)
{

	char in[100];
	char aftertran[100];
	int n = 0;
	char a;
	int i = 0;
	cout << "请输入需要运算的式子（以=结束): ";
	while (cin >> a) //循环获取输入直到遇到‘=’结束
	{
		if (a == '=')
			break;
		//输入检测
		else if((a < '0' || a > '9' ) && a != '+' && a != '-' && a != '*' && a != '/' && a != ' '){
			cout << "输入表达式中有非法字符";
			exit(0);
		}
		in[i++] = a;
	}
	transform(in, aftertran, n);
	cout << "运算结果为: " << comput(aftertran, n) << endl;
	return 0;
}