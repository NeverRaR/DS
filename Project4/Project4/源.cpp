#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;
#define max(x,y)  x>y?x:y

class BigInteger
{
public:
	explicit BigInteger();
	BigInteger(const int i);
	BigInteger(const string& strValues);
	BigInteger(const BigInteger& bigInt);
	~BigInteger() {};
	void setValue(const string& strValues);
	bool inline isPositive() { return flag; }
	bool inline isZero() { return values == "0"; }
	int compareBigint(const BigInteger& rhs)const;
	const BigInteger absolute()const;
	BigInteger& operator = (const BigInteger& rhs);

	friend ostream& operator <<(ostream& ou, const BigInteger& bigInt);
	friend istream& operator >>(istream& in, BigInteger& bigInt);
	friend const bool operator >(const BigInteger& lhs, const BigInteger& rhs);
	friend const bool operator ==(const BigInteger& lhs, const BigInteger& rhs);
	friend const BigInteger operator + (const BigInteger& lhs, const BigInteger& rhs);
	friend const BigInteger operator - (const BigInteger& lhs, const BigInteger& rhs);
	friend const BigInteger operator * (const BigInteger& lhs, const BigInteger& rhs);
	friend const BigInteger operator / (const BigInteger& lhs, const BigInteger& rhs);
	friend const BigInteger operator % (const BigInteger& lhs, const BigInteger& rhs);
	friend const BigInteger operator ^(const BigInteger& lhs, const BigInteger& rhs);


private:
	string values;
	bool flag;
};

ostream& operator <<(ostream& ou, const BigInteger& bigInt);
istream& operator >>(istream& in, BigInteger& bigInt);
const BigInteger operator + (const BigInteger& lhs, const BigInteger& rhs);
const BigInteger operator - (const BigInteger& lhs, const BigInteger& rhs);
const BigInteger operator * (const BigInteger& lhs, const BigInteger& rhs);
const BigInteger operator / (const BigInteger& lhs, const BigInteger& rhs);
const BigInteger operator % (const BigInteger& lhs, const BigInteger& rhs);

BigInteger::BigInteger() :values(""), flag(true)
{

}

BigInteger::BigInteger(const int i)
{
	values.clear();
	if (i >= 0)
	{
		flag = true;
	}
	else
		flag = false;
	int v = abs(i);
	while (v)
	{
		values.push_back(char('0' + (v % 10)));
		v /= 10;
	}
	reverse(values.begin(), values.end());
	if (values.empty())
	{
		values.push_back('0');
	}
}

BigInteger::BigInteger(const string& strValues)
{
	setValue(strValues);
}

BigInteger::BigInteger(const BigInteger& bigInt) :values(bigInt.values), flag(bigInt.flag)
{

}

void BigInteger::setValue(const string& strValues)
{
	values.clear();
	string tmpStr(strValues.begin() + strValues.find_first_not_of(' '), strValues.end());
	if (tmpStr.empty())
	{
		values.push_back('0');
		flag = true;
		return;
	}
	if (tmpStr[0] == '-')
	{
		flag = false;
	}
	else
		flag = true;
	int i = tmpStr.find_first_of("0123456789");
	int j = tmpStr.find_last_of("0123456789");
	values = tmpStr.substr(i, j - i + 1);
}

int BigInteger::compareBigint(const BigInteger& rhs)const
{
	if (flag && !rhs.flag)
	{
		return 1;
	}
	if (!flag && rhs.flag)
	{
		return -1;
	}

	int ret = 0;
	if (values.length() > rhs.values.length())
	{
		ret = 1;
	}
	else if (values.length() < rhs.values.length())
	{
		ret = -1;
	}
	else
		ret = values.compare(rhs.values);
	if (flag)
	{
		return ret;
	}
	else
		return -ret;

}

const BigInteger BigInteger::absolute()const
{
	BigInteger ret(*this);
	ret.flag = true;
	return ret;
}

BigInteger& BigInteger::operator= (const BigInteger& rhs)
{
	this->values = rhs.values;
	this->flag = rhs.flag;
	return *this;
}

ostream& operator << (ostream& ou, const BigInteger& bigInt)
{
	if (!bigInt.flag)
	{
		ou << '-';

	}
	ou << bigInt.values;
	return ou;
}

istream& operator>> (istream& in, BigInteger& bigInt)
{
	string str;
	in >> str;
	bigInt.setValue(str);
	return in;
}

const bool operator>(const BigInteger & lhs, const BigInteger & rhs)
{
	if (lhs.values.size()!= rhs.values.size()) return lhs.values.size() > rhs.values.size();
	for (int i = 0; i < lhs.values.size(); ++i)
	{
		if (lhs.values[i] != rhs.values[i])
			return lhs.values[i] > rhs.values[i];
	}
	return false;
}

const bool operator==(const BigInteger & lhs, const BigInteger & rhs)
{
	return lhs.values == rhs.values;
}

const BigInteger operator + (const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger ret;
	if (lhs.flag == rhs.flag)
	{
		string lvalues(lhs.values), rvalues(rhs.values);
		reverse(lvalues.begin(), lvalues.end());
		reverse(rvalues.begin(), rvalues.end());
		int i = 0;
		for (; i < lvalues.length() && i < rvalues.length(); i++)
		{
			ret.values.push_back(lvalues.at(i) + rvalues.at(i) - '0');
		}
		if (i < lvalues.length())
		{
			for (; i < lvalues.length(); i++)
			{
				ret.values.push_back(lvalues.at(i));
			}
		}
		else
			for (; i < rvalues.length(); i++)
			{
				ret.values.push_back(rvalues.at(i));
			}
		int carry = 0;
		for (int i = 0; i < ret.values.length(); i++)
		{
			int newValue = ret.values.at(i) - '0' + carry;
			carry = newValue / 10;
			ret.values.at(i) = newValue - carry * 10 + '0';
		}
		if (carry)
		{
			ret.values.push_back(carry + '0');
		}

		ret.flag = lhs.flag;
	}
	else
	{
		BigInteger absL = lhs.absolute();
		BigInteger absR = rhs.absolute();
		int compFlag = absL.compareBigint(absR);
		if (compFlag == 0)
		{
			ret.setValue("0");
			ret.flag = true;
			return ret;
		}
		else
		{
			if (compFlag == -1)
			{
				BigInteger tmp(absL);
				absL = absR;
				absR = tmp;
			}
			reverse(absL.values.begin(), absL.values.end());
			reverse(absR.values.begin(), absR.values.end());

			int i = 0;
			for (; i < absL.values.length() && i < absR.values.length(); ++i)
			{
				ret.values.push_back(absL.values.at(i) - absR.values.at(i) + '0');
			}
			if (i < absL.values.length())
			{
				for (; i < absL.values.length(); i++)
				{
					ret.values.push_back(absL.values.at(i));
				}
			}
			int carry = 0;
			for (i = 0; i < ret.values.length(); i++)
			{
				int newValue = ret.values.at(i) - carry - '0';
				if (newValue < 0)
				{
					carry = 1;
				}
				else
					carry = 0;
				ret.values.at(i) = newValue + carry * 10 + '0';
			}
			if (compFlag == 1)
			{
				ret.flag = lhs.flag;
			}
			else
				ret.flag = rhs.flag;
		}

	}
	reverse(ret.values.begin(), ret.values.end());
	int i = ret.values.find_first_not_of("0");
	if (i == string::npos)
	{
		ret.setValue("0");
		ret.flag = true;
		return ret;
	}
	ret.values = string(ret.values.begin() + i, ret.values.end());
	return ret;
}

const BigInteger operator - (const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger tmpRhs(rhs);
	tmpRhs.flag = !tmpRhs.flag;
	return(lhs + tmpRhs);
}

const BigInteger operator *(const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger ret;
	int flag1 = lhs.compareBigint(BigInteger(0));
	int flag2 = rhs.compareBigint(BigInteger(0));
	if (flag1 == 0 || flag2 == 0)
	{
		ret.setValue("0");
		ret.flag = 0;
		return ret;
	}
	if (lhs.flag == rhs.flag)
	{
		ret.flag = true;
	}
	else
		ret.flag = false;
	string lvalues(lhs.values), rvalues(rhs.values);
	reverse(lvalues.begin(), lvalues.end());
	reverse(rvalues.begin(), rvalues.end());
	ret.values.resize(lvalues.size() + rvalues.size(), '0');

	for (int i = 0; i < lvalues.size(); i++)
	{
		for (int j = 0; j < rvalues.size(); j++)
		{
			int newValue = ret.values.at(i + j) + (lvalues[i] - '0') * (rvalues[j] - '0') - '0';
			int carry = newValue / 10;
			ret.values.at(i + j) = newValue % 10 + '0';
			for (int k = i + j + 1; carry != 0 && k < ret.values.size(); k++)
			{
				newValue = ret.values.at(k) + carry - '0';
				carry = newValue / 10;
				ret.values.at(k) = newValue % 10 + '0';
			}
		}
	}

	reverse(ret.values.begin(), ret.values.end());
	ret.values = string(ret.values.begin() + ret.values.find_first_not_of("0"), ret.values.end());
	return ret;
}

const BigInteger operator / (const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger ret;
	ret.setValue("0");
	BigInteger absL(lhs.absolute());
	BigInteger absR(rhs.absolute());

	int comflag = absL.compareBigint(absR);
	if (comflag < 0)
	{
		return ret;
	}
	if (comflag == 0)
	{
		ret.setValue("1");
		if (lhs.flag == rhs.flag)
		{
			ret.flag = true;
		}
		else
			ret.flag = false;
		return ret;
	}
	int movCount = absL.values.size() - absR.values.size();
	const BigInteger tenBigint(10);

	while (movCount >= 0)
	{
		BigInteger tmp(absR);
		for (int i = 0; i < movCount; i++)
		{
			tmp = tmp * tenBigint;
		}
		int addNum = 0;
		while (absL.compareBigint(tmp) >= 0)
		{
			absL = absL - tmp;
			addNum++;
		}
		ret = ret * tenBigint + BigInteger(addNum);
		movCount--;
	}

	if (lhs.flag == rhs.flag)
	{
		ret.flag = true;
	}
	else
		ret.flag = false;

	return ret;
}

const BigInteger operator %(const BigInteger& lhs, const BigInteger& rhs)
{
	BigInteger divTmp = lhs / rhs;
	return (lhs - divTmp * rhs);
}

const BigInteger operator^(const BigInteger & lhs, const BigInteger & rhs)
{
	BigInteger ans("1");
	BigInteger a = lhs;
	BigInteger b = rhs;
	BigInteger Zero("0");
	while (b > Zero)
	{
		int BackValue = b.values.back() - '0';
		if (BackValue & 1)
		{
			ans = ans * a;
		}
		a = a * a;
		b = b / 2;
	}
	return ans;
}



template<typename ElementType> class Vector
{
public:
	~Vector<ElementType>();
	Vector<ElementType>() = default;
	Vector<ElementType>(const Vector<ElementType> & v);
	Vector<ElementType>& operator = (const Vector<ElementType>&v);
	void PushBack(const ElementType& t);
	void PopBack();
	void Clear();
	int GetSize() const;
	void ReSize(int NewSize);
	ElementType& operator[](int Index) const;
	bool Empty()const;
	const ElementType& Back() const;
private:
	void Extend();
	int Size = 0;
	int Capacity = 0;
	ElementType* Array = nullptr;
};

template<typename ElementType>
inline Vector<ElementType>::~Vector()
{
	delete[] Array;
}

template<typename ElementType>
inline Vector<ElementType>::Vector(const Vector<ElementType>& v) :Size(v.Size), Capacity(v.Capacity)
{
	Array = new ElementType[v.Capacity];
	for (int i = 0; i < v.Size; ++i)
	{
		Array[i] = v.Array[i];
	}
}

template<typename ElementType>
Vector<ElementType>& Vector<ElementType>::operator=(const Vector<ElementType>& v)
{
	ElementType* Temp = new ElementType[v.Capacity];
	for (int i = 0; i < v.Size; ++i)
	{
		Temp[i] = v.Array[i];
	}
	delete[] Array;
	Size = v.Size;
	Capacity = v.Capacity;
	Array = Temp;
	return *this;
}

template<typename ElementType>
inline void Vector<ElementType>::PushBack(const ElementType & t)
{
	if (Size == Capacity) Extend();
	Array[Size++] = t;
}

template<typename ElementType>
inline void Vector<ElementType>::PopBack()
{
	if (Size == 0) return;
	--Size;
}

template<typename ElementType>
inline void Vector<ElementType>::Clear()
{
	delete[] Array;
	Array = nullptr;
	Size = Capacity = 0;
}

template<typename ElementType>
inline int Vector<ElementType>::GetSize() const
{
	return Size;
}

template<typename ElementType>
inline void Vector<ElementType>::Extend()
{
	ElementType* Temp = new ElementType[Capacity * 2 + 1];
	for (int i = 0; i < Size; ++i)
	{
		Temp[i] = Array[i];
	}
	delete[] Array;
	Array = Temp;
	Capacity = 2 * Capacity + 1;
}
template<typename ElementType>
inline void Vector<ElementType>::ReSize(int NewSize)
{
	int RealSize = Size > NewSize ? NewSize : Size;
	ElementType* Temp = new ElementType[NewSize + 1];
	for (int i = 0; i < RealSize; ++i)
	{
		Temp[i] = Array[i];
	}
	delete[] Array;
	Array = Temp;
	Capacity = NewSize + 1;
	Size = NewSize;
}

template<typename ElementType>
inline  ElementType & Vector<ElementType>::operator[](int Index) const
{
	return Array[Index];
}

template<typename ElementType>
bool Vector<ElementType>::Empty() const
{
	return Size == 0;
}

template<typename ElementType>
const ElementType & Vector<ElementType>::Back() const
{
	return Array[Size - 1];
}
template <typename ElementType> class Stack
{
public:
	void Push(ElementType E)
	{
		L.PushBack(E);
	}
	void Pop()
	{
		L.PopBack();
	}
	ElementType Top()
	{
		return L.Back();
	}
	bool Empty()
	{
		return L.GetSize() == 0;
	}
	int Size()
	{
		return L.GetSize();
	}
private:
	Vector<ElementType> L;
};
struct ExpressionElement
{
	bool IsNum=false;
	BigInteger Num;
	int Symbol = 0;
};
char PriorityTable[10][10]= { //运算符优先等级 [栈顶][当前]
	//               |-------------------- 当前运算符-------------------|
 	//                   (	      )     +   	-      *	    /      %      #      $     ^    
	/* -- （  */     '<' , '=',   '<' , '<',  '<',   '<',   '<'  ,  '<',   '<' ,  '<',
	/* |     )  */      ' ',    ' ',    ' ',    ' ',   ' ',     ' ',    ' ',      ' ',     ' ',    ' ',
	/* 栈  +  */     '<',   '>',   '>',  '>',  '<',  '<',  '<',     '<',   '<',  '<',
	/* 顶   -  */     '<',   '>',   '>',  '>',  '<',  '<',  '<',     '<',   '<',  '<',
	/* 运   *  */     '<',   '>',   '>',  '>',  '>',  '>',  '>',		'<',    '<',  '<',
	/* 算   /  */     '<',   '>',   '>',  '>',  '>',  '>',  '>',		'<',    '<',  '<',
	/* 符   % */    '<',   '>',   '>',  '>',  '>',  '>',  '>',		'<',    '<',  '<',
	/* 号   #  */    '<',   '>',   '>',  '>',  '>',  '>',  '>',		'<',    '<',  '<',
	/* |     $  */     '<',   '>',   '>',  '>',  '>',  '>',  '>',		'<',    '<',  '<',
	/* --   ^  */    '<',   '>',   '>',  '>',  '>',  '>',  '>',		'>',    '>',  '<',
};
class Expression
{
public:
	void MakeStringToExpression(const string& s)
	{
		IsCorrect = true;
		Infix.Clear();
		int i;
		for (i = 0; i < s.size();)
		{
			ExpressionElement CurElement;
			if (s[i]<'0' || s[i]>'9')
			{
				switch (s[i])
				{
				case '(':
					CurElement.Symbol = 0;
					break;
				case ')':
					CurElement.Symbol = 1;
					break;
				case '+':
					CurElement.Symbol = 2;
					break;
				case '-':
					CurElement.Symbol = 3;
					break;
				case '*':
					CurElement.Symbol = 4;
					break;
				case '/':
					CurElement.Symbol = 5;
					break;
				case '%':
					CurElement.Symbol = 6;
					break;
				case '#': //这里表示一元+运算符
					CurElement.Symbol = 7;
					break;
				case '$': //这里表示一元-运算符
					CurElement.Symbol = 8;
					break;
				case '^'://这里表示乘方运算
					CurElement.Symbol = 9;
					break;
				default:
					cout << "出现非法运算符！" ;
					goto ERROR;
				}
				++i;
			}
			else
			{
				string t;
				while (i < s.size()&& s[i]>='0' && s[i]<='9')
				{
					t += s[i++];
				}
				CurElement.IsNum = true;
				CurElement.Num = t;
			}
			Infix.PushBack(CurElement);
		}
		return;
	ERROR:
		IsCorrect = false;
	}
	void CalculatePost()
	{
		if (!IsCorrect) return ;
		Postfix.Clear();
		Stack<ExpressionElement> s;
		int i;
		for (i = 0; i < Infix.GetSize(); ++i)
		{
			if (Infix[i].IsNum) Postfix.PushBack(Infix[i]);
			else
			{
				if (s.Empty()) s.Push(Infix[i]);
				else
				{
					switch (PriorityTable[s.Top().Symbol][Infix[i].Symbol])
					{
					case '<':
						s.Push(Infix[i]);
						break;
					case '>':
						while (!s.Empty() && PriorityTable[s.Top().Symbol][Infix[i].Symbol] == '>')
						{
							Postfix.PushBack(s.Top());
							s.Pop();
						}
						if (Infix[i].Symbol == 1)//当前为右括号
						{
							if (s.Empty() || s.Top().Symbol != 0)//未找到对应的左括号
							{
								cout << "括号不匹配！";
								goto ERROR;
							}
							else s.Pop();//找到左括号，弹出
						}
						else s.Push(Infix[i]);
						break;
					case '=':
						cout << "出现空的括号表达式！" ;
						goto ERROR;
						break;
					default:
						cout << "未知错误！" ;
						goto ERROR;
					}
				}
			}
		}
		while (!s.Empty())
		{
			if (s.Top().Symbol == 0)
			{
				cout << "括号不匹配！";
				goto ERROR;
			}
			Postfix.PushBack(s.Top());
			s.Pop();
		}
		return;
	ERROR:
		IsCorrect = false;
	}
	void CalculateExpression()
	{
		CalculatePost();
		if (!IsCorrect) return ;
		Stack<BigInteger> ans;
		for (int i = 0; i < Postfix.GetSize(); ++i)
		{
			if (Postfix[i].IsNum) ans.Push(Postfix[i].Num);
			else
			{
				BigInteger t1,t2;
				switch (Postfix[i].Symbol)
				{
				case 2:
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t1 = ans.Top(); ans.Pop();
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！";
						goto ERROR;
					}
					t2 = ans.Top(); ans.Pop();
					ans.Push(t2 + t1);
					break;
				case 3:
					if (ans.Empty()) 
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t1 = ans.Top(); ans.Pop();
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t2 = ans.Top(); ans.Pop();
					ans.Push(t2 - t1);
					break;
				case 4:
					if (ans.Empty()) 
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t1 = ans.Top(); ans.Pop();
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t2 = ans.Top(); ans.Pop();
					ans.Push(t2 * t1);
					break;
				case 5:
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t1 = ans.Top(); ans.Pop();
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t2 = ans.Top(); ans.Pop();
					if (t1.isZero())
					{
						cout << "发生除零操作！";
						goto ERROR;
					}
					ans.Push(t2 /  t1);
					break;
				case 6:
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！";
						goto ERROR;
					}
					t1 = ans.Top(); ans.Pop();
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t2 = ans.Top(); ans.Pop();
					if (t1.isZero())
					{
						cout << "发生除零操作！";
						goto ERROR;
					}
					ans.Push(t2 %t1);
					break;
				case 7:
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t1 = ans.Top(); ans.Pop();
					t2.setValue("1");
					ans.Push(t2*t1);
					break;
				case 8:
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t1 = ans.Top(); ans.Pop();
					t2.setValue("-1");
					ans.Push(t2*t1);
					break;
				case 9:
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t1 = ans.Top(); ans.Pop();
					if (ans.Empty())
					{
						cout << "操作符数与数字数量不匹配！" ;
						goto ERROR;
					}
					t2 = ans.Top(); ans.Pop();
					ans.Push(t2^t1);
					break;
				}
			}
		}
		Result = ans.Top();
		return;
	ERROR:
		IsCorrect = false;
	}
	BigInteger GetResult()
	{
		return Result;
	}
	bool IsCorrect = true;
private:
	
	Vector<ExpressionElement>  Infix, Postfix;
	BigInteger Result;
};
string Pretreat(const string& s)
{
	string t(s);
	int i;
	if (t.back() == '=')t.pop_back();
	for (i = 0; i < t.size(); ++i)
	{
		if (i == 0)
		{
			if (s[i] == '+')t[i] = '#';
			if (s[i] == '-')t[i] = '$';
		}
		else
		{
			if (s[i - 1] == ')' || (s[i - 1] >= '0'&&s[i - 1] <= '9')) continue;
			else
			{
				if (s[i] == '+')t[i] = '#';
				if (s[i] == '-')t[i] = '$';
			}
		}
	}
	return t;
}
int main(void)
{
	bool IsLooping = true;
	Expression E;
	string ExpressionString;
	cout << "欢迎使用表达式计算器，本计算器支持 + ,- ,* ,/ ,% ,^ 运算符！" << endl;
	while (IsLooping)
	{
		cout << "请输入您要计算的表达式：" << endl;
		cin >> ExpressionString;
		E.MakeStringToExpression(Pretreat(ExpressionString));
		E.CalculateExpression();
		if (E.IsCorrect)
		{

			cout << ExpressionString << "=" ;
			cout << E.GetResult() << endl;
			cout << "计算完毕！请问是否计算下一个表达式(输入y计算下一个表达式，否则退出程序) ？" << endl;
			string Next;
			cin >> Next;
			if (Next != "y") IsLooping = false;
		}
		else cout << "请重新输入！" << endl;
	}
	return 0;
}