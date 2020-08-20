#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include<ctype.h>

using namespace std;


int priority(char c)
{
	if (c == '+' || c == '-')
		return 0;
	if (c == '*' || c == '/')
		return 1;
	if (c == '(' || c == ')')
		return -1;
	return -1;
}

bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')
		return true;
	else 
		return false;
}

int main()
{
	cout << "请输入要计算的表达式: ";
	string str;
	cin >> str;
	
	
	//进行输入检测
	int len = str.length();
	char temp1[len];
	strncpy(temp1,str.c_str(),len);
	for(int i = 0; i < len; i++){
		if((temp1[i] < '0' || temp1[i] > '9' ) && temp1[i] != '+' && temp1[i] != '-' && temp1[i] != '*' && temp1[i] != '/' && temp1[i] != '.'){
			cout << "输入表达式中有非法字符";
			exit(0);
		}
		
	}
	
	
	
	vector<string> out; //存放转化后用于输出的字符
	stack<char> opStact;	//存放操作符
	
	
	//首先由中缀表达式转化为后缀表达式
	for (size_t i = 0; i < str.length();)
	{
		if (!isOperator(str[i]))
		{				   
			char temp[20]; 
			int flag = 0;
			for (; !isOperator(str[i]) && i < str.length(); i++)
			{
				temp[flag++] = str[i];
			}
			temp[flag++] = 0;
			string tempstr(temp, strlen(temp));
			out.push_back(tempstr);
		}
		else
		{
			if ('(' == str[i])
				opStact.push(str[i]);
			else if (')' == str[i])
			{
				while (!opStact.empty() && (opStact.top() != '('))
				{
					char c = opStact.top();
					char cc[2];
					cc[0] = c;
					cc[1] = 0;
					string tempstr(cc, 1);
					out.push_back(tempstr);
					opStact.pop();
				}
				opStact.pop();
			}
			else
			{ //其它操作符
				if (!opStact.empty())
				{										  
					if (priority(str[i]) > priority(opStact.top())) ///比较优先级，较低则将栈顶操作符加到数组中，压栈
						opStact.push(str[i]);
					else
					{ 
						while ((!opStact.empty()) && (priority(str[i]) <= priority(opStact.top())))
						{ //一直到比栈顶高
							char c = opStact.top();
							char cc[2];
							cc[0] = c;
							cc[1] = 0;
							string tempstr(cc, 1);
							out.push_back(tempstr);
							opStact.pop();
						}
						opStact.push(str[i]);
					}
				}
				else
				{ 
					opStact.push(str[i]);
				}
			}
			i++;
		}
	}
	while (!opStact.empty())
	{
		char c = opStact.top();
		char cc[2];
		cc[0] = c;
		cc[1] = 0;
		string tempstr(cc, 1);
		out.push_back(tempstr);
		opStact.pop();
	}

	
	for (size_t i = 1; i < out.size(); i++)
	{
		string str1 = out[i];
		string str = out[i - 1];
		
	}
	

	//根据后缀表达式求值
	stack<double> calcuStack;
	for (size_t i = 0; i < out.size(); i++)
	{
		string str = out[i];
		if (!isOperator(str[0]))
		{
			const char *p = str.c_str();
			double ff = atof(p);
			calcuStack.push(ff);
		}
		else
		{
			double a = calcuStack.top();
			calcuStack.pop();
			double b = calcuStack.top();
			calcuStack.pop();
			char c = str[0];
			switch (c)
			{
			case '+':
				calcuStack.push(b + a);
				break;
			case '-':
				calcuStack.push(b - a);
				break;
			case '*':
				calcuStack.push(b * a);
				break;
			case '/':
				calcuStack.push(b / a);
				break;
			case '%':
				calcuStack.push((int)b % (int)a);
				break;
			}
		}
	}
	cout << "运算结果为： " << calcuStack.top() << endl
		 << endl;
}
