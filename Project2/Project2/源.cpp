#include<iostream>
#include<string>
using std::istream;
using std::stringstream;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
bool Error1 = false, Error2 = false;
using std::ostream;
template <typename ElementType> class Node
{
public:
	Node<ElementType>();
	Node<ElementType>(ElementType E);;
	~Node<ElementType>();
	Node<ElementType>* Insert(Node<ElementType>* P, ElementType E);
	Node<ElementType>* Delete(Node<ElementType>* P);
	void DeleteList();
	ElementType GetElement();

	Node<ElementType>* GetNext();
private:
	ElementType Element;
	Node<ElementType>* Next = nullptr;
};
template <typename ElementType> class List
{
public:
	List<ElementType>();
	~List<ElementType>();
	void Clear();
	ElementType GetCurElement();
	Node<ElementType>* CurToNext();
	Node<ElementType>* ResetCur();
	Node<ElementType>* GetCur();
	Node<ElementType>* GetHead();
	Node<ElementType>* GetLast();
	int GetLength();
	Node<ElementType>* PushBack(ElementType E);
	Node<ElementType>* PushFront(ElementType E);
	const List< ElementType>& operator =(const List< ElementType>&L)
	{
		Head = L.Head;
		Last = L.Last;
		Cur = L.Cur;
		return *this;
	}
	void Display(ostream& os);
private:
	Node<ElementType>* Head = nullptr, *Last = nullptr, *Cur = nullptr;
	int Length = 0;
};

template<typename ElementType>
inline Node<ElementType>::Node()
{

}

template<typename ElementType>
inline Node<ElementType>::Node(ElementType E) : Element(E) {}

template<typename ElementType>
inline Node<ElementType>::~Node()
{
}

template<typename ElementType>
inline  Node<ElementType>* Node<ElementType>::Insert(Node<ElementType>* P, ElementType E)
{
	if (P != nullptr)
	{
		if (P->Next == nullptr)
		{
			P->Next = new Node<ElementType>(E);
			return P->Next;
		}
		else
		{
			Node<ElementType>* TempCell_1 = P->Next;
			Node<ElementType>* TempCell_2 = new Node<ElementType>(E);
			P->Next = TempCell_2;
			TempCell_2->Next = TempCell_1;
			return TempCell_1;
		}
	}
	else return nullptr;
}

template<typename ElementType>
inline  Node<ElementType>* Node<ElementType>::Delete(Node<ElementType>* P)
{
	if (P != nullptr)
	{

		if (P->Next == nullptr) return nullptr;
		else
		{
			Node<ElementType>* TempCell = P->Next;
			P->Next = P->Next->Next;
			delete TempCell;
			return P->Next;
		}
	}
}

template<typename ElementType>
inline void Node<ElementType>::DeleteList()
{
	Node<ElementType>* P,* T;
	P = Next;
	Next = nullptr;
	while (P != nullptr)
	{
		T = P->Next;
		delete P;
		P = T;
	}
}

template<typename ElementType>
inline ElementType Node<ElementType>::GetElement() { return Element; }

template<typename ElementType>
inline  Node<ElementType>* Node<ElementType>::GetNext() { return Next; }

template<typename ElementType>
inline void List<ElementType>::Clear() { Head->DeleteList(); }

template<typename ElementType>
inline ElementType List<ElementType>::GetCurElement() { return Cur->GetElement(); }

template<typename ElementType>
inline Node<ElementType>* List<ElementType>::CurToNext() { return Cur = Cur->GetNext(); }

template<typename ElementType>
inline Node<ElementType>* List<ElementType>::ResetCur() { return Cur = Head; }

template<typename ElementType>
inline Node<ElementType>* List<ElementType>::GetCur() { return Cur; }

template<typename ElementType>
inline Node<ElementType>* List<ElementType>::GetHead() { return Head; }

template<typename ElementType>
inline Node<ElementType>* List<ElementType>::GetLast() { return Last; }

template<typename ElementType>
inline int List<ElementType>::GetLength() { return Length; }

template<typename ElementType>
inline  Node<ElementType>* List<ElementType>::PushBack(ElementType E)
{
	Length++;
	return Last = Last->Insert(Last, E);
}

template<typename ElementType>
inline  Node<ElementType>* List<ElementType>::PushFront(ElementType E)
{
	Length++;
	return Head->Insert(Head, E);
}

template<typename ElementType>
inline void List<ElementType>::Display(ostream & os)
{
	Node<ElementType>* DisplayPtr = Head->GetNext();
	if (Length == 0)
	{
		os << "NULL";
		return;
	}
	while (DisplayPtr != nullptr)
	{
		os << DisplayPtr->GetElement() << " ";
		DisplayPtr = DisplayPtr->GetNext();
	}
}

template<typename ElementType>
inline List<ElementType>::List()
{
	Head = new  Node<ElementType>();
	Cur = Last = Head;
}

template<typename ElementType>
inline List<ElementType>::~List()
{
	Head->DeleteList();
	Cur = Last = nullptr;
}

class BigInteger
{
public:
	BigInteger(string Integer = {}) :Integer(Integer) {};
	string Integer = {};
	bool operator > (const BigInteger B) const
	{
		if (Integer.length() < B.Integer.length()) return false;
		if (Integer.length() > B.Integer.length()) return true;
		for (int i = 0; i < Integer.length(); ++i)
		{
			if (Integer[i] > B.Integer[i]) return true;
			if (Integer[i] < B.Integer[i]) return false;
		}
		return false;
	}
	bool operator < (const BigInteger B) const
	{
		if (Integer.length() < B.Integer.length()) return true;
		if (Integer.length() > B.Integer.length()) return false;
		for (int i = 0; i < Integer.length(); ++i)
		{
			if (Integer[i] < B.Integer[i]) return true;
			if (Integer[i] > B.Integer[i]) return false;
		}
		return false;
	}
	bool operator ==(const BigInteger B) const
	{
		if (Integer.length() != B.Integer.length()) return false;
		for (int i = 0; i < Integer.length(); ++i)
		{
			if (Integer[i] != B.Integer[i]) return false;

		}
		return true;
	}
	BigInteger& operator =(string s)
	{
		Integer = s;
		return *this;
	}
	friend ostream &operator <<(ostream &os, const BigInteger &B);
	friend istream& operator >>(istream& is, BigInteger &B);
};
ostream & operator<<(ostream & os, const BigInteger & B)
{
	return os << B.Integer;
}
istream& operator >>(istream& is, BigInteger &B)
{
	return is >> B.Integer;
}
string CheckString(string& S)
{
	int i = 0, j = 0;
	if (S == "-1") return S;
	while (j<S.length()&& S[j] == '0')//去除前置0
	{
		++j;
	}
	for (i = j; i < S.length(); ++i)
	{
		if (S[i]<'0' || S[i]>'9')
		{
			if (!Error1)
			{
				cout << "输入含有非-1负数或非数字字符,已忽略不符合要求的输入。 " << endl;
			}
			Error1 = true;
			return string();
		}
	}
	return string(S.begin() + j, S.end());
}
List<BigInteger>* Read()
{
	Error1 = Error2 = false;
	List<BigInteger>* TempList = new List<BigInteger>();
	string S;
	BigInteger DisposedB, PreB;
	while (cin >> S)
	{
		DisposedB = CheckString(S);
		if (DisposedB == BigInteger("-1")) return TempList;
		if (DisposedB.Integer.empty()) continue;
		if (PreB > DisposedB)
		{
			if (!Error2)
			{
				cout << "存在数字小于上一个数，不满足非降序，已忽略不符合要求的整数" << endl;
			}
			Error2 = true;
			continue;
		}
		TempList->PushBack(DisposedB);
		PreB = DisposedB;
	}
	return TempList;
}
List<BigInteger> * GetIntersection(List<BigInteger> *List_1, List<BigInteger>*List_2)
{
	List<BigInteger> *Intersection = new List<BigInteger>();
	List_1->ResetCur(); List_2->ResetCur();
	List_1->CurToNext(); List_2->CurToNext();
	while (List_1->GetCur() != nullptr&&List_2->GetCur()!= nullptr)
	{
		if (List_1->GetCurElement() > List_2->GetCurElement()) List_2->CurToNext();
		else if(List_2->GetCurElement() > List_1->GetCurElement()) List_1->CurToNext();
		else
		{
			Intersection->PushBack(BigInteger(List_1->GetCurElement()));
			List_1->CurToNext(); List_2->CurToNext();
		}
	}
	return Intersection;
}
int main(void)
{
	cout << "本程序用于求解两个链表的交集序列。" << endl;
	cout << "请输入两个非降序正整数序列（每个序列以-1表示结束，每个数字用空格隔开）" << endl;
	cout << "是否进行求解？是请输入Y运行程序，否则请输入N退出。" << endl;
	string s;
	while (cin>>s)
	{
		if (s == "N"||s=="n") break;
		if (s != "Y"&&s!="y")
		{
			cout << "请输入Y或者N，不要输入其他字符串。" << endl;
			continue;
		}
		List<BigInteger> *List_1, *List_2;
		cout << "请输入第一个序列:" << endl;
		List_1 = Read();
		cout << "请输入第二个序列:" << endl;
		List_2 = Read();
		List<BigInteger> *Intersection = GetIntersection(List_1, List_2);
		cout << "两个序列的交集为:" << endl;
		Intersection->Display(cout);
		cout << endl;
		cout << "是否求解下一组？是请输入Y，否则请输入N退出。" << endl;
		List_1->Clear(); List_2->Clear(); Intersection->Clear();
	}
	return 0;
}