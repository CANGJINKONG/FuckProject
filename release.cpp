#include <iostream>
#include <algorithm>
#include <stack>
//#include <sstream> 辣鸡库，毁青春
#include <ctype.h>
using namespace std;
double calc_line(int start,int last);
string s;
int suitable(int i)//寻找匹配的括号
{
	//cout<<"call suitable at "<<i;
	int t=0;
    do
	{
		if (s[i]=='(')
		t++;
		if (s[i]==')')
		t--;
		i++;
	} while (t!=0);
	//cout<<" and result is "<<i-1<<endl;
	return i-1;
}

//WARNING 这个函数会改变p的值
double inputnum(int &p) //哼，万恶sstream不支持从中间输入，我就自己写一个:( 应该把C艹标准委员会的人拖出去Happy Corner掉
{
//	cout<<"call inputnum at "<<p<<endl;
	double result;
	if (s[p]=='(')
	{
		double temp=p;
		p=suitable(p)+1;
		return calc_line(temp+1,p-1);
	}
	char temp[20];
	int i=0;
	while(isdigit(s[p]) or s[p]=='.' )
	{
		//cout<<s[p];
		temp[i]=s[p];
		p++;
		i++;
	}
	temp[i]='\0';
	//cout<<"temp is "<<temp<<endl;
	result=atof(temp);
	return result;
}
double calc_two(double a,double b,char op)//计算两个数字，op为符号
{
	//cout<<"calling calc_two at "<<a<<" "<<b<<" "<<op<<endl;//debug
	if (op=='+')
	return a+b;
	if (op=='-')
	return a-b;
	if (op=='*')
	return a*b;
	else return a/b;
}
double calc_line(int start,int last)
{
	//cout<<"call calc_line at"<<start<<endl;
	stack <double> nums;
	stack <char> ops;
	nums.push(0);
	ops.push('+');
	while (start<=last)
	{
			if (ops.top()=='*'||ops.top()=='/')
			{
				double temp=(calc_two(nums.top(),inputnum(start),ops.top()));
				nums.pop();
				nums.push(temp);
				ops.pop();
			}
			else nums.push(inputnum(start));
			if (s[start]!=0&&s[start]!=')')
			{
				
				//cout<<"push op at "<<start<<" which is"<<int(s[start])<<endl;
				ops.push(s[start]);
			}
			start++;
	}
	double result=0;
	while (!ops.empty())
	{
		result+=calc_two(0,nums.top(),ops.top());
		nums.pop();
		ops.pop();
	}
	//cout<<"result is "<<result<<endl;
	return result;
}
int main()
{	cout<<"欢迎使用TOM的计算器"<<endl;
	cout<<"输入 + - × / () 和数字进行基本的运算"<<endl;
	cout<<"Ege: 4+5\n ((((3*2)+(4*8))+7)*9)\n";
	cout<<"Warning 未做出任何错误处理，错误的表达式可能会造成稀奇古怪的问题甚至系统崩溃"<<endl;
	cout<<"请输入表达式:";
	while(cin>>s)
	{
		cout<<calc_line(0,s.length()-1)<<endl;;
		cout<<"请输入表达式:";
	}
}

