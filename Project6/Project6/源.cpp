#pragma once
#include<iostream>
#include<string>
using std::string;
using std::ostream;
using std::endl;
using std::cin;
using std::cout;
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
public:
	AVLTree<Key, Value>();
	AVLTree<Key, Value>(Key K, Value V);
	~AVLTree<Key, Value>();
	TreeNode<Key, Value>* Change(Key K, Value V);
	TreeNode<Key, Value>* Insert(Key K, Value V = Value());
	TreeNode<Key, Value>* Find(Key K);
	TreeNode<Key, Value>* Delete(Key K);
	TreeNode<Key, Value>* MakeEmpty(TreeNode<Key, Value>* P);
	void MakeEmpty();
	void DisPlay(ostream& os);
	int GetHeight();
	TreeNode<Key, Value>* UncheckChange(TreeNode<Key, Value>* P, Value V);
	TreeNode<Key, Value>* UncheckInsert(Key K, Value V);
	int GetSize();
private:
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
	TreeNode<Key, Value>* TempCell = Find(K, Root);
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

template<typename ElementType> class MultiTree;
template<typename ElementType> class MultiNode
{
	friend class MultiTree<ElementType>;
public:
	~MultiNode<ElementType>() {};
	MultiNode<ElementType>() = default;
	MultiNode<ElementType>(const ElementType& E) : Element(E) {};
	bool IsRoot() { return Father == nullptr; }
	bool IsFirstSon() { return Father != nullptr&& Father->FirstSon == this; }
	MultiNode<ElementType>* GetLastSon();
	MultiNode<ElementType>* FirstSon = nullptr, *NextBro = nullptr, *Father = nullptr;
	ElementType Element;
};

template<typename ElementType>
MultiNode<ElementType>* MultiNode<ElementType>::GetLastSon()
{
	if (FirstSon == nullptr) return nullptr;
	MultiNode<ElementType>* Cur = FirstSon;
	while (Cur->NextBro != nullptr) Cur = Cur->NextBro;
	return Cur;
}

template<typename ElementType> class MultiTree
{
public:
	MultiTree<ElementType>() = default;
	~MultiTree<ElementType>();

	void DisplayAllChild(ostream& os,MultiNode<ElementType>* N);
	void Destory(MultiNode<ElementType>* N);
	void Clear();
	MultiNode<ElementType>* Root = nullptr;
};

template<typename ElementType>
void MultiTree<ElementType>::DisplayAllChild(ostream & os, MultiNode<ElementType>* N)
{
	MultiNode<ElementType>* CurNode = N->FirstSon;
	while (CurNode != nullptr)
	{
		os << CurNode->Element << " ";
		CurNode = CurNode->NextBro;
	}
}

template<typename ElementType>
void MultiTree<ElementType>::Destory(MultiNode<ElementType>* N)
{
	if (N == nullptr) return;
	Destory(N->FirstSon);
	Destory(N->NextBro);
	delete N;
}

template<typename ElementType>
void MultiTree<ElementType>::Clear()
{
	Destory(Root);
}

template<typename ElementType>
MultiTree<ElementType>::~MultiTree()
{
	Destory(Root);
}

class Genealogy
{
public:

	Genealogy() = default;
	~Genealogy() = default;
	void Menu();
	void Init();
	void Build();
	void Add();
	void Dissolve();
	void Query();
	void Change();
private:
	MultiNode<string> *AddNewSon(MultiNode<string>* N, const string& E);
	MultiNode<string> *AddNewSon(MultiNode<string>* N, const Vector<string>& V);
	void Display(MultiNode<string>* N);
	bool CheckNewChild(const Vector<string>& AllChild);
	bool CheckNewChild(const string& Child);
	MultiTree<string> FamilyTree;
	AVLTree<string, MultiNode<string>*> FamilyMap;
};

void Genealogy::Menu()
{
	cout << "**\t\t家谱管理系统\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\tA---完善家谱\t\t\t**" << endl;
	cout << "**\t\tB---添加家庭成员\t\t**" << endl;
	cout << "**\t\tC---解散局部家庭\t\t**" << endl;
	cout << "**\t\tD---更改家庭成员姓名\t\t**" << endl;
	cout << "**\t\tE---查询家庭成员的第一代子孙\t**" << endl;
	cout << "**\t\tF---退出程序\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
}

void Genealogy::Init()
{
	FamilyTree.Clear();
	cout << "首先建立一个家谱！" << endl;
	cout << "请输入祖先的姓名：";
	string s;
	cin >> s;
	FamilyTree.Root=new  MultiNode<string>(s);
	FamilyMap.Insert(s, FamilyTree.Root);
	cout << "此家谱的祖先是：" << s << endl;
}

void Genealogy::Build()
{
	string s;
	TreeNode<string, MultiNode<string>*>* Ancestor;
	cout << "请输入要建立家庭的人的姓名：" ;
	cin >> s;
	while((Ancestor=FamilyMap.Find(s)) == nullptr)
	{
		cout << "此人不存在！" << endl;
		cout << "请重新输入：";
		cin >> s;
	}
	MultiNode<string>* AncestorNode = Ancestor->ElementValue;
	int Num = 0;
	cout << "请输入" << s << "的儿女的人数：";
	cin >>  Num;
	while (Num <= 0)
	{
		cout << "请输入一个大于0的整数！" << endl;
		cout << "请重新输入：";
		cin >> Num;
	}
	Vector<string> AllChild;
	AllChild.ReSize(Num);
	int i;
	cout << "请依次输入" << s << "的儿女的姓名：";
	for (i = 0; i < Num; ++i)
	{
		cin >> AllChild[i];
	}
	while (CheckNewChild(AllChild) == false)
	{
		cout << "请重新依次输入整个儿女姓名序列：";
		for (i = 0; i < Num; ++i)
		{
			cin >> AllChild[i];
		}
	}
    AddNewSon(AncestorNode, AllChild);
	Display(AncestorNode);
}

void Genealogy::Add()
{
	string s;
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	cin >> s;
	TreeNode<string, MultiNode<string>*>* Ancestor;
	while ((Ancestor = FamilyMap.Find(s)) == nullptr)
	{
		cout << "此人不存在！" << endl;
		cout << "请重新输入：";
		cin >> s;
	}
	MultiNode<string>* AncestorNode = Ancestor->ElementValue;

	string Child;
	cout << "请输入"<<s<<"新添加儿子（或女儿）的姓名：";
	cin >> Child;
	while (CheckNewChild(Child) == false)
	{
		cout << "请重新输入：";
		cin >> Child;
	}
	AddNewSon(AncestorNode, Child);
	Display(AncestorNode);

}

void Genealogy::Dissolve()
{
	string s;
	TreeNode<string, MultiNode<string>*>* Ancestor;
	cout << "请输入要解散家庭的人的姓名：";
	cin >> s;
	while ((Ancestor = FamilyMap.Find(s)) == nullptr)
	{
		cout << "此人不存在！" << endl;
		cout << "请重新输入：";
		cin >> s;
	}
	MultiNode<string>* AncestorNode = Ancestor->ElementValue;
	if (AncestorNode == FamilyTree.Root)
	{
		cout << "不允许解散第一代祖先的家庭！" << endl;
		return;
	}
	Display(AncestorNode);
	if (AncestorNode->Father != nullptr)
	{
		if (AncestorNode->IsFirstSon() == false)
			AncestorNode->Father->NextBro = AncestorNode->NextBro;
		else AncestorNode->Father->FirstSon = nullptr;
	}
	FamilyTree.Destory(AncestorNode->FirstSon);
	delete AncestorNode;
	FamilyMap.Delete(s);
}

void Genealogy::Query()
{
	string s;
	TreeNode<string, MultiNode<string>*>* Ancestor;
	cout << "请输入要查询第一代子孙的人的姓名：";
	cin >> s;
	while ((Ancestor = FamilyMap.Find(s)) == nullptr)
	{
		cout << "此人不存在！" << endl;
		cout << "请重新输入：";
		cin >> s;
	}
	MultiNode<string>* AncestorNode = Ancestor->ElementValue;
	Display(AncestorNode);
}

void Genealogy::Change()
{
	string OldName,NewName;
	TreeNode<string, MultiNode<string>*>* Ancestor;
	cout << "请输入要更改姓名的人的目前姓名：";
	cin >> OldName;
	while ((Ancestor = FamilyMap.Find(OldName)) == nullptr)
	{
		cout << "此人不存在！" << endl;
		cout << "请重新输入：";
		cin >> OldName;
	}
	MultiNode<string>* AncestorNode = Ancestor->ElementValue;
	FamilyMap.Delete(OldName);
	cout << "请输入更改后的姓名：";
	cin >> NewName;
	while ( FamilyMap.Find(NewName) != nullptr)
	{
		cout << "此姓名已存在于家谱中！" << endl;
		cout << "请重新输入：";
		cin >> NewName;
	}
	FamilyMap.Insert(NewName, AncestorNode);
	AncestorNode->Element = NewName;
	cout << OldName << "已更名为" << NewName << endl;
}

MultiNode<string>* Genealogy::AddNewSon(MultiNode<string>* N, const string & E)
{
	if (N == nullptr) return nullptr;
	MultiNode<string>* NewNode = new MultiNode<string>(E);
	FamilyMap.Insert(E, NewNode);
	MultiNode<string>* Last = N->GetLastSon();
	if (Last == nullptr) N->FirstSon = NewNode;
	else Last->NextBro = NewNode;
	NewNode->Father = N;	
	return NewNode;
}

MultiNode<string>* Genealogy::AddNewSon(MultiNode<string>* N, const Vector<string>& V)
{
	if (N == nullptr || V.Empty()) return nullptr;
	MultiNode<string>* NewNode = new MultiNode<string>(V[0]);
	FamilyMap.Insert(V[0], NewNode);
	MultiNode<string>* Last = N->GetLastSon();
	if (Last == nullptr) N->FirstSon = NewNode;
	else Last->NextBro = NewNode;
	Last = NewNode;
	Last->Father = N;
	int i;
	for (i = 1; i < V.GetSize(); ++i)
	{
		string t = V[i];
	
		Last->NextBro =new MultiNode<string>(V[i]);
		Last->NextBro->Father = Last;
		Last = Last->NextBro;
		FamilyMap.Insert(V[i], Last);
	}
	return Last;;
}

void Genealogy::Display(MultiNode<string>* N)
{
	if (N->FirstSon == nullptr) cout << N->Element << "没有任何子孙！" << endl;
	else
	{
		cout << N->Element << "的第一代子孙是：";
		FamilyTree.DisplayAllChild(cout, N);
		cout << endl;
	}
}

bool Genealogy::CheckNewChild(const Vector<string>& AllChild)
{
	int i;
	AVLTree<string> NameSet;
	for (i = 0; i < AllChild.GetSize(); ++i)
	{
		if (NameSet.Find(AllChild[i]) != nullptr)
		{
			cout << "儿女中存在姓名相同的人！" << endl;
			return false;
		}
		NameSet.Insert(AllChild[i]);
	}
	bool Flag = true;
	for (i = 0; i < AllChild.GetSize(); ++i)
	{
		if (FamilyMap.Find(AllChild[i]) != nullptr)
		{
			if (Flag == true)
			{
				cout << "有的儿女姓名与家谱已存在人姓名重复！" << endl;
				cout << "重复的姓名有：";
				Flag = false;
			}
			cout << AllChild[i] << " ";
		}
	}
   if(Flag==false) cout << endl;
	return Flag;
}
bool Genealogy::CheckNewChild(const string & Child)
{
	if (FamilyMap.Find(Child) != nullptr)
	{
		cout << "新的儿女姓名已在家谱中存在！" << endl;
		return false;
	}
	return true;
}
int main(void)
{
	Genealogy MyGenealogy;
	MyGenealogy.Menu();
	MyGenealogy.Init();
	string s;
	bool IsLooping = true;
	while (IsLooping)
	{
		cout << endl << "请输入要执行的操作：";
		cin >> s;
		switch (s[0])
		{
		case 'A':
			MyGenealogy.Build();
			break;
		case 'B':
			MyGenealogy.Add();
			break;
		case 'C':
			MyGenealogy.Dissolve();
			break;
		case 'D':
			MyGenealogy.Change();
			break;
		case 'E':
			MyGenealogy.Query();
			break;
		case 'F':
			IsLooping = false;
			break;
		default:
			cout << "未知标识符！请重新输入!" << endl;

		}
	}
}