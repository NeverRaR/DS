#include<iostream>
#include<string>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

template <typename Key, typename Value> class TreeNode
{
public:
	void MidVisit(ostream& os);
	TreeNode<Key, Value>() = default;
	TreeNode<Key, Value>(Key K, Value V);
	~TreeNode<Key, Value>();
	Key ElementKey;
	Value ElementValue;
	TreeNode<Key, Value>* Left = nullptr, *Right = nullptr;
	int Height = 0;
};
template <typename Key = int, typename Value = int> class AVLTree
{

public:
	AVLTree<Key, Value>();
	AVLTree<Key, Value>(Key K, Value V);
	~AVLTree<Key, Value>();
	TreeNode<Key, Value>* Change(Key K, Value V);
	TreeNode<Key, Value>* Insert(Key K, Value V = Value());
	TreeNode<Key, Value>* Find(Key K);
	TreeNode<Key, Value>* Delete(Key K);
	void MakeEmpty();
	void DisPlay(ostream& os);
	int GetHeight();
	TreeNode<Key, Value>* UncheckChange(TreeNode<Key, Value>* P, Value V);
	TreeNode<Key, Value>* UncheckInsert(Key K, Value V);
	int GetSize();
private:
	int  Max(int x, int y);
	int GetHeight(TreeNode<Key, Value>* P);
	TreeNode<Key, Value>* SingleRotateWithLeft(TreeNode<Key, Value>* K2);
	TreeNode<Key, Value>* SingleRotateWithRight(TreeNode<Key, Value>* K2);
	TreeNode<Key, Value>* DoubleRotateWithLeft(TreeNode<Key, Value>* K3);
	TreeNode<Key, Value>* DoubleRotateWithRight(TreeNode<Key, Value>* K3);
	TreeNode<Key, Value>* Find(Key K, TreeNode<Key, Value>* P);
	TreeNode<Key, Value>* FindMin(TreeNode<Key, Value>* P);
	TreeNode<Key, Value>* FindMax(TreeNode<Key, Value>* P);
	TreeNode<Key, Value>* Insert(Key K, Value V, TreeNode<Key, Value>* P);
	TreeNode<Key, Value>* Delete(Key K, TreeNode<Key, Value>* P);
	TreeNode<Key, Value>* MakeEmpty(TreeNode<Key, Value>* P);
	int Size = 0;
	TreeNode<Key, Value>* Root = nullptr;
};

template<typename Key, typename Value>
inline int AVLTree<Key, Value>::Max(int x, int y)
{
	if (x > y) return x;
	return y;
}

template<typename Key, typename Value>
inline int AVLTree<Key, Value>::GetHeight(TreeNode<Key, Value>* P)
{
	return P ? P->Height : -1;
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::SingleRotateWithLeft(TreeNode<Key, Value>* K2)
{
	TreeNode<Key, Value>* K1;
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	K2->Height = Max(GetHeight(K2->Left), GetHeight(K2->Right)) + 1;
	K1->Height = Max(GetHeight(K1->Left), K2->Height) + 1;
	return K1;
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::SingleRotateWithRight(TreeNode<Key, Value>* K2)
{
	TreeNode<Key, Value>* K1;
	K1 = K2->Right;
	K2->Right = K1->Left;
	K1->Left = K2;
	K2->Height = Max(GetHeight(K2->Left), GetHeight(K2->Right)) + 1;
	K1->Height = Max(GetHeight(K1->Left), K2->Height) + 1;
	return K1;
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::DoubleRotateWithLeft(TreeNode<Key, Value>* K3)
{
	K3->Left = SingleRotateWithRight(K3->Left);
	return SingleRotateWithLeft(K3);
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::DoubleRotateWithRight(TreeNode<Key, Value>* K3)
{
	K3->Right = SingleRotateWithLeft(K3->Right);
	return SingleRotateWithRight(K3);
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::Find(Key K, TreeNode<Key, Value>* P)
{
	if (P == nullptr) return nullptr;
	if (K < P->ElementKey)
		return Find(K, P->Left);
	else if (K > P->ElementKey) return Find(K, P->Right);
	else return P;
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::FindMin(TreeNode<Key, Value>* P)
{
	if (P != nullptr)
		while (P->Left != nullptr)
			P = P->Left;
	return P;
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::FindMax(TreeNode<Key, Value>* P)
{
	if (P != nullptr)
		while (P->Right != nullptr)
			P = P->Right;
	return P;
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::Insert(Key K, Value V, TreeNode<Key, Value>* P)
{
	if (P == nullptr)
	{
		P = new TreeNode<Key, Value>(K, V);
	}
	else if (K < P->ElementKey)
	{
		P->Left = Insert(K, V, P->Left);
		if (GetHeight(P->Left) - GetHeight(P->Right) == 2)
		{
			if (K < P->Left->ElementKey) P = SingleRotateWithLeft(P);
			else P = DoubleRotateWithLeft(P);
		}
	}
	else if (K > P->ElementKey)
	{
		P->Right = Insert(K, V, P->Right);
		if (GetHeight(P->Right) - GetHeight(P->Left) == 2)
		{
			if (K > P->Right->ElementKey) P = SingleRotateWithRight(P);
			else P = DoubleRotateWithRight(P);
		}
	}
	P->Height = Max(GetHeight(P->Left), GetHeight(P->Right)) + 1;
	return P;
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::Delete(Key K, TreeNode<Key, Value>* P)
{
	TreeNode<Key, Value>* TempCell;
	if (P == nullptr) return nullptr;
	else if (K < P->ElementKey)
	{
		P->Left = Delete(K, P->Left);
		if (GetHeight(P->Right) - GetHeight(P->Left) == 2)
		{
			TempCell = P->Right;
			if (GetHeight(TempCell->Left) < GetHeight(TempCell->Right)) P = SingleRotateWithRight(P);
			else P = DoubleRotateWithRight(P);
		}
	}
	else if (K > P->ElementKey)
	{
		P->Right = Delete(K, P->Right);
		if (GetHeight(P->Left) - GetHeight(P->Right) == 2)
		{
			TempCell = P->Left;
			if (GetHeight(TempCell->Left) > GetHeight(TempCell->Right))P = SingleRotateWithLeft(P);
			else P = DoubleRotateWithLeft(P);
		}
	}
	else
	{
		if (P->Left&&P->Right)
		{
			if (GetHeight(P->Left) > GetHeight(P->Right))
			{
				TempCell = FindMax(P->Left);
				P->ElementKey = TempCell->ElementKey;
				P->ElementValue = TempCell->ElementValue;
				P->Left = Delete(P->ElementKey, P->Left);
			}
			else
			{
				TempCell = FindMin(P->Right);
				P->ElementKey = TempCell->ElementKey;
				P->ElementValue = TempCell->ElementValue;
				P->Right = Delete(P->ElementKey, P->Right);
			}
		}
		else
		{
			TempCell = P;
			if (P->Left == nullptr) P = P->Right;
			else if (P->Right == nullptr)P = P->Left;
			delete TempCell;
			TempCell = nullptr;
		}
	}
	if (P) P->Height = Max(GetHeight(P->Left), GetHeight(P->Right)) + 1;
	return P;
}

template<typename Key, typename Value>
inline void TreeNode<Key, Value>::MidVisit(ostream & os)
{
	if (Left) Left->MidVisit(os);
	os << ElementValue << endl;
	if (Right) Right->MidVisit(os);
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>::TreeNode(Key K, Value V) : ElementKey(K), ElementValue(V) {}

template<typename Key, typename Value>
inline TreeNode<Key, Value>::~TreeNode()
{
}

template<typename Key, typename Value>
inline AVLTree<Key, Value>::AVLTree()
{

}

template<typename Key, typename Value>
inline AVLTree<Key, Value>::AVLTree(Key K, Value V)
{
	Root = new TreeNode<Key, Value>(K, V);
}

template<typename Key, typename Value>
inline AVLTree<Key, Value>::~AVLTree()
{
	MakeEmpty();
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::Change(Key K, Value V)
{
	TreeNode<Key, Value>* TempCell =Find(K, Root);
	if (TempCell)
	{
		TempCell->ElementValue = V;
		return TempCell;
	}
	else  return UncheckInsert(K, Root);
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::Insert(Key K, Value V)
{
	if (Root == nullptr)
	{
		Size++;
		return Root = new TreeNode<Key, Value>(K, V);
	}
	TreeNode<Key, Value>* TempCell = Find(K, Root);
	if (TempCell) return UncheckChange(TempCell, V);
	else
	{
		Size++;
		Root = Insert(K, V, Root);
		return Root;
	}
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::Find(Key K)
{
	if (Root == nullptr) return nullptr;
	return Find(K, Root);
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::Delete(Key K)
{
	if (Root)
	{
		if (Find(K, Root))
		{
			Size--;
			return Root = Delete(K, Root);
		}
		return nullptr;
	}
	return nullptr;
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::MakeEmpty(TreeNode<Key, Value>* P)
{
	if (P == nullptr) return nullptr;
	if (P->Left) P->Left = MakeEmpty(P->Left);
	if (P->Right) P->Right = MakeEmpty(P->Right);
	delete P;
	return nullptr;
}

template<typename Key, typename Value>
inline void AVLTree<Key, Value>::MakeEmpty()
{
	Size = 0;
	Root = MakeEmpty(Root);
}

template<typename Key, typename Value>
inline void AVLTree<Key, Value>::DisPlay(ostream & os)
{
	Root->MidVisit(os);
}

template<typename Key, typename Value>
inline int AVLTree<Key, Value>::GetHeight()
{
	return Root->GetHeight(Root);
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::UncheckChange(TreeNode<Key, Value>* P, Value V)
{
	P->ElementValue = V;
	return P;
}

template<typename Key, typename Value>
inline TreeNode<Key, Value>* AVLTree<Key, Value>::UncheckInsert(Key K, Value V)
{
	Size++;
	return Root=Insert(K, V, Root);
}

template<typename Key, typename Value>
inline int AVLTree<Key, Value>::GetSize() { return Size; }

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
class Student
{

public:
	static const int  LineLength = 12;
	static string  Display(const string & s, int Delta = 0);
	Student() = default;
	Student(string ID, string N, string S, string A, string T);
	Student& operator =(Student S)
	{
		Age = S.Age;
		ID = S.ID;
		Sex = S.Sex;
		Name = S.Name;
		TestCatagory = S.TestCatagory;
		return *this;
	}
	friend ostream & operator<<(ostream & os, const Student & s);
	friend istream& operator >>(istream& is, const  Student &S);
	BigInteger ID, Age;
	string Sex, Name, TestCatagory;

	
};


ostream & operator<<(ostream & os, const Student & s)
{
	return os << Student::Display(s.ID.Integer) << " "
		<< Student::Display(s.Name) << " "
		<< Student::Display(s.Sex,-7) << " "
		<< Student::Display(s.Age.Integer,-7) << " "
		<< s.TestCatagory;
}
istream& operator >>(istream& is,   Student &S)
{
	return is >> S.ID.Integer >> S.Name >> S.Sex >> S.Age.Integer >> S.TestCatagory;
}
class StudentInformationSystem
{
public:
	StudentInformationSystem(){}
	~StudentInformationSystem(){}
	void Init();
	void Insert();
	void Change();
	void Delete();
	void Find();
	void Display();
	int GetStudentNum();
private:
	Student HeadLine;
	AVLTree<BigInteger, Student> StudentTree;
};

inline void StudentInformationSystem::Init()
{
	int i;
	cout << "首先请建立考生信息系统!" << endl;
	cout << "请输入考生人数：";
	int StudentNum;
	cin >> StudentNum;
	while (StudentNum <= 0)
	{
		cout << "请输入一个正整数！" << endl;
		cout << "请输入考生人数：";
		cin >> StudentNum;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别：" << endl;
	HeadLine = Student(string("考号"), string("姓名"), string("性别"), string("年龄"), string("报考类别"));
	for (i = 0; i < StudentNum; ++i)
	{
		Student TempStudent;
		cin >> TempStudent;
		StudentTree.Insert(TempStudent.ID, TempStudent);
	}
	cout << HeadLine << endl;
	StudentTree.DisPlay(cout);
}

inline void StudentInformationSystem::Insert()
{
	cout << "请依次输入要插入考生的考号，姓名，性别，年龄及报考类别：" << endl;
	Student TempStudent;
	cin >> TempStudent;
	auto FoundPtr = StudentTree.Find(TempStudent.ID);
	if (FoundPtr)
	{
		cout << "该学号已被其他考生使用，请检查插入考生信息是否错误" << endl;
		return;
	}
	else
	{
		StudentTree.UncheckInsert(TempStudent.ID, TempStudent);
		cout << "插入完成!" << endl;
	}
}

inline void StudentInformationSystem::Change()
{
	cout << "请依次输入要修改考生的考号，和修改后的姓名，性别，年龄及报考类别：" << endl;
	Student TempStudent;
	cin >> TempStudent;
	auto FoundPtr = StudentTree.Find(TempStudent.ID);
	if (FoundPtr == nullptr)
	{
		cout << "该学号对应考生不存在，请检查输入考号是否错误" << endl;
		return;
	}
	else
	{
		StudentTree.UncheckChange(FoundPtr, TempStudent);
		cout << "修改完成!" << endl;
	}
}

inline void StudentInformationSystem::Delete()
{
	cout << "请输入要删除考生的考号：" << endl;
	BigInteger ID;
	cin >> ID;
	auto FoundPtr = StudentTree.Find(ID);
	if (FoundPtr == nullptr)
	{
		cout << "该学号对应考生不存在，请检查输入考号是否错误" << endl;
		return;
	}
	else
	{
		cout << "你删除的考生的信息为：" << endl;
		cout << HeadLine << endl;
		cout << FoundPtr->ElementValue << endl;
		StudentTree.Delete(ID);
		cout << "删除完成!" << endl;
	}
}

inline void StudentInformationSystem::Find()
{
	cout << "请输入要查询考生的考号：" << endl;
	BigInteger ID;
	cin >> ID;
	auto FoundPtr = StudentTree.Find(ID);
	if (FoundPtr == nullptr)
	{
		cout << "该学号对应考生不存在，请检查输入考号是否错误" << endl;
		return;
	}
	else
	{
		cout << HeadLine << endl;
		cout << FoundPtr->ElementValue << endl;
	}
}

inline void StudentInformationSystem::Display()
{
	cout << "学生数量：" << GetStudentNum() << endl;
	if (GetStudentNum() > 0)
	{
		cout << HeadLine << endl;
		StudentTree.DisPlay(cout);
	}
}

inline int StudentInformationSystem::GetStudentNum() { return StudentTree.GetSize(); }

inline string Student::Display(const string & s, int Delta)
{
	int Length = s.length();
	if (Length >= LineLength + Delta)
	{
		return s;
	}
	else
	{
		string DisposedS(s);
		for (int i = 0; i < LineLength - Length + Delta; ++i)
		{
			DisposedS.push_back(' ');
		}
		return DisposedS;
	}
}

inline Student::Student(string ID, string N, string S, string A, string T) :
	Age(A), ID(ID), Sex(S), Name(N), TestCatagory(T) { }
int main()
{
	StudentInformationSystem SIS;
	SIS.Init();
	while (true)
	{
		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为退出）:" << endl;
		int Command;
		cin >> Command;
		switch (Command)
		{
		case 1:
			SIS.Insert();
			break;
		case 2:
			SIS.Delete();
			break;
		case 3:
			SIS.Find();
			break;
		case 4:
			SIS.Change();
			break;
		case 5:
			SIS.Display();
			break;
		case 0:
			cout << "感谢您的使用！" << endl;
			return 0;
		default:
			cout << "请不要输入其他数字，请重新输入!" << endl;
			break;
		}
	}
	return 0;
}
