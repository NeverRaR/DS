#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::stringstream;
using std::fstream;
using std::ios_base;
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
	return Root = Insert(K, V, Root);
}

template<typename Key, typename Value>
inline int AVLTree<Key, Value>::GetSize() { return Size; }

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
template<typename Tag>
class Vertex
{
public:
	Vertex<Tag>() = default;
	Vertex<Tag>(const Tag& T) : VertexTag(T) {};
	int Index;
	int InDegree;
	Tag VertexTag;
	Vector<Vertex*> Next;
};

template<typename Tag> class Graph
{
public:
	Graph<Tag>() = default;
	~Graph<Tag>();
	void Clear();
	Vertex<Tag>* AddVertex(const Tag& T);
	void Link(const Tag&T1, const Tag&T2);
	void Link(Vertex<Tag>*V1, Vertex<Tag>*V2);
	Vector<Vertex<Tag>*> Vertexes;
	AVLTree<Tag, int> VertexTree;
};

template<typename Tag>
void Graph<Tag>::Clear()
{
	VertexTree.MakeEmpty();
	for (int i = 0; i < Vertexes.GetSize(); i++)
	{
		delete Vertexes[i];
	}
	Vertexes.Clear();
}

template<typename Tag>
Vertex<Tag>* Graph<Tag>::AddVertex(const Tag & T)
{
	if (VertexTree.Find(T) != nullptr) return nullptr;
	Vertex<Tag>* NewVertex = new Vertex<Tag>(T);
	VertexTree.Insert(T, Vertexes.GetSize());
	NewVertex->Index = Vertexes.GetSize();
	Vertexes.PushBack(NewVertex);
	return NewVertex;
}

template<typename Tag>
void Graph<Tag>::Link(const Tag & T1, const Tag & T2)
{
	TreeNode<Tag, int>* N1, *N2;
	Vertex<Tag>* V1, *V2;
	N1 = VertexTree.Find(T1);
	if (N1 == nullptr) return;
	V1 = Vertexes[N1->ElementValue];
	N2 = VertexTree.Find(T2);
	if (N2 == nullptr || N1 == N2) return;
	V2 = Vertexes[N2->ElementValue];
	Link(V1, V2);
}

template<typename Tag>
void Graph<Tag>::Link(Vertex<Tag>* V1, Vertex<Tag>* V2)
{
	V1->Next.PushBack(V2);
	V2->InDegree++;
}
template<typename ElementType>class Queue;
template<typename ElementType> class Node
{
	friend class Queue<ElementType>;
	Node<ElementType>() : Pre(nullptr), Next(nullptr) {};
	Node<ElementType>(const ElementType& e) : Element(e) {};
	Node<ElementType>* Next = nullptr, *Pre = nullptr;
	ElementType Element;
};
template<typename ElementType> class Queue
{
public:
	Queue<ElementType>()
	{
		Head = new Node<ElementType>();
		Tail = new Node<ElementType>();
		Head->Next = Tail;
		Tail->Pre = Head;
	}
	~Queue<ElementType>()
	{
		Clear();
		delete Head;
		delete Tail;
	}
	int GetSize() { return Size; }
	bool Empty() { return Size == 0; }
	void EnQueue(ElementType E)
	{
		Node<ElementType>* Temp = new Node<ElementType>(E);
		Temp->Pre = Tail->Pre;
		Temp->Next = Tail;
		Tail->Pre = Temp;
		Temp->Pre->Next = Temp;
		Size++;
	}
	void DeQueue()
	{
		if (Empty()) return;
		Node<ElementType>* Temp = Head->Next;
		Head->Next = Temp->Next;
		Head->Next->Pre = Head;
		delete Temp;
		Size--;
	}
	ElementType Front()
	{
		return Head->Next->Element;
	}
	void Clear()
	{
		int i;
		Node<ElementType>* Cur = Head->Next;
		Node<ElementType>* Temp;
		for (i = 0; i < Size; ++i)
		{
			Temp = Cur->Next;
			delete Cur;
			Cur = Temp;
		}
		Size = 0;
	}
private:
	int Size = 0;
	Node<ElementType>* Head, *Tail;
};

template<typename Tag>
Graph<Tag>::~Graph()
{
	Clear();
}
class Course
{
public:
	Course() = default;
	string Num, Name;
	int ClassHours;
	int OpenTerm;
	int EarliestOpenTerm = 0;
	Vector<string> PreCourse;
};
class CourseTable
{
public:
	const int  Gap = 8;
	const int ExtraGap = 4;
	int MaxCourseNum;
	int CourseCnt;
	string Table[5][10];
	void DisPlay(ostream& os)
	{
		int ColHeight[10] = { 1,1, 1, 1, 1, 1, 1, 1, 1, 1 };
		int i, j;
		for (j = 0; j < 10; ++j)
		{
			for (i = 0; i < 5; ++i)
			{
				int CurHeight = Table[i][j].size() / Gap + 1;
				if (ColHeight[j] < CurHeight) ColHeight[j] = CurHeight;
			}
		}
		Vector<string> DisplayTable;
		int SumHeight[11] = { 0 };
		for (j = 1; j < 11; ++j) SumHeight[j] = ColHeight[j - 1]+SumHeight[j-1];
		DisplayTable.ReSize(SumHeight[10]);
		for (i = 0; i < 5; ++i)
		{
			for (j = 0; j < 10; ++j)
			{
				int k;
				int BeginLine = 0;
				if (Table[i][j].empty())
				{
					for (k = 0; k < ColHeight[j]; ++k)
					{
						DisplayTable[SumHeight[j] + k] += "||";
						DisplayTable[SumHeight[j] + k] += string(ExtraGap * 2 + Gap, ' ');
					}
					continue;
				}
				int CurHeight = Table[i][j].size() / Gap + 1;
				if (CurHeight < ColHeight[j]) BeginLine = (ColHeight[j] - CurHeight) / 2;
				for (k = 0; k < BeginLine; ++k) DisplayTable[SumHeight[j] + k] += string(ExtraGap*2+Gap, ' ');
				int Cur = 0;
				while (Table[i][j].size() - Cur >= Gap)
				{
					int d;
					DisplayTable[SumHeight[j] + k] += "||";
					DisplayTable[SumHeight[j] + k]+= string(ExtraGap , ' ');
					for (d = 0; d < Gap; ++d)
					{
						DisplayTable[SumHeight[j] + k] += Table[i][j][Cur + d];
					}
					DisplayTable[SumHeight[j] + k] += string(ExtraGap, ' ');
					Cur += d;
					++k;
				}
				if (Table[i][j].size() > Cur)
				{
					int Head = (Gap - (Table[i][j].size() - Cur)) / 2;
					int Tail = Gap - (Table[i][j].size() - Cur) - Head;
					DisplayTable[SumHeight[j] + k] += "||";
					DisplayTable[SumHeight[j] + k] += string(ExtraGap, ' ');
					DisplayTable[SumHeight[j] + k] += string(Head, ' ');
					for (; Cur < Table[i][j].size(); ++Cur) DisplayTable[SumHeight[j] + k] += Table[i][j][Cur];
					DisplayTable[SumHeight[j] + k] += string(Tail, ' ');
					DisplayTable[SumHeight[j] + k] += string(ExtraGap, ' ');
					++k;
				}
				for(;k<ColHeight[j];++k)
				{
					DisplayTable[SumHeight[j] + k] += "||";
					DisplayTable[SumHeight[j] + k] += string(ExtraGap * 2 + Gap, ' ');
				}
			}
		}
		int LineLength = DisplayTable[0].size() + 2;
		for (i = 0; i < 10; ++i)
		{
			os << string(LineLength, '-') << endl;
			for (j = 0; j < ColHeight[i]; ++j)
			{
				os << DisplayTable[SumHeight[i]+j] << "||" << endl;
			}
		}
		os << string(LineLength, '-') << endl;
	}
};
	fstream in, out;
class SchedulingSystem
{
public:
	CourseTable TermTable[8];
	Graph<string> CourseNet;
	AVLTree<int, Course> CourseMap;
	void PutCourse(Course& CurCourse, int& CurTerm)
	{
		int Temp = CurTerm;
		if (CurCourse.EarliestOpenTerm > CurTerm) CurTerm++;//如果先修课在这学期不被满足，则排下一个学期
		if (CurTerm >= 8)
		{
			cout << "课程设计存在问题！排课失败！" << endl;
			cout << "按任意键退出！" << endl;
			getchar();
			exit(-1);//八个学期已经排完;
		}
		if (TermTable[CurTerm].CourseCnt == TermTable[CurTerm].MaxCourseNum) CurTerm++;//这学期课已经排满，则排下一个学期
		bool Recover = false;

		int i, j;
		int ResCourse = 0;
		bool IsPut[5] = { false,false,false,false,false };
		for (i = 0; i < 5; ++i)
		{
			for (j = 0; j < 10; ++j)
			{
				if (TermTable[CurTerm].Table[i][j].empty()) ResCourse++;
			}
		}

		if (CurCourse.OpenTerm != 0)
		{
			CurTerm = CurCourse.OpenTerm-1;
			Recover = true;
		}
		if (CurTerm >= 8)
		{
			cout << "课程设计存在问题！排课失败！" << endl;
			cout << "按任意键退出！" << endl;
			getchar();
			exit(-1);//八个学期已经排完
		}
		if (ResCourse < CurCourse.ClassHours) CurTerm++;//如果排不下，则排下一学期
		int ResHour = CurCourse.ClassHours;
		TermTable[CurTerm].CourseCnt++;//该学期排课数量加一
		if (ResHour >= 3)//尝试隔天连续三节排课
		{
			for (i = 0; i < 5; ++i)
			{
				if (ResHour < 3)break;
				if (IsPut[i] == true) continue;
				if (i > 0 && IsPut[i - 1] == true)continue;
				if (i < 4 && IsPut[i + 1] == true) continue;
				for (j = 0; j < 8; ++j)
				{
					if (ResHour < 3)break;
					if (j == 3)
					{
						++j;
						continue;
					}
					if (TermTable[CurTerm].Table[i][j].empty() && TermTable[CurTerm].Table[i][j + 1].empty() && TermTable[CurTerm].Table[i][j + 2].empty())//如果接下来三节都空闲,则排上
					{
						TermTable[CurTerm].Table[i][j] = CurCourse.Name;
						TermTable[CurTerm].Table[i][j + 1] = CurCourse.Name;
						TermTable[CurTerm].Table[i][j + 2] = CurCourse.Name;
						ResHour -= 3;
						IsPut[i] = true;
						break;
					}
				}
			}
		}
		if (ResHour >= 2)//尝试隔天连续两节排课
		{
			for (i = 0; i < 5; ++i)
			{
				if (ResHour < 2)break;
				if (IsPut[i] == true) continue;
				if (i > 0 && IsPut[i - 1] == true)continue;
				if (i < 4 && IsPut[i + 1] == true) continue;
				for (j = 0; j < 9; ++j)
				{
					if (ResHour < 2) break;
					if (j == 4) continue;
					if (TermTable[CurTerm].Table[i][j].empty() && TermTable[CurTerm].Table[i][j + 1].empty())//如果接下来两节都空闲,则排上
					{
						TermTable[CurTerm].Table[i][j] = CurCourse.Name;
						TermTable[CurTerm].Table[i][j + 1] = CurCourse.Name;
						ResHour -= 2;
						IsPut[i] = true;
						break;
					}
				}
			}
		}
		if (ResHour >= 1)//尝试隔天排课
			{
				for (i = 0; i < 5; ++i)
				{
					if (ResHour < 1)break;
					if (IsPut[i] == true)continue;
					if (i > 0 && IsPut[i - 1] == true)continue;
					if (i < 4 && IsPut[i + 1] == true) continue;
					for (j = 0; j < 10; ++j)
					{
						if (TermTable[CurTerm].Table[i][j].empty() && TermTable[CurTerm].Table[i][j + 1].empty())//如果这节空闲,则排上
						{
							TermTable[CurTerm].Table[i][j] = CurCourse.Name;
							ResHour -= 1;
							IsPut[i] = true;
							break;
						}
					}
				}
			}
		if (ResHour >= 3)//尝试不隔天连续三节排课
		{
			for (i = 0; i < 5; ++i)
			{
				if (ResHour < 3)break;
				for (j = 0; j < 8; ++j)
				{
					if (ResHour < 3)break;
					if (j == 3)
					{
						++j;
						continue;
					}
					if (TermTable[CurTerm].Table[i][j].empty() && TermTable[CurTerm].Table[i][j + 1].empty() && TermTable[CurTerm].Table[i][j + 2].empty())//如果接下来三节都空闲,则排上
					{
						TermTable[CurTerm].Table[i][j] = CurCourse.Name;
						TermTable[CurTerm].Table[i][j + 1] = CurCourse.Name;
						TermTable[CurTerm].Table[i][j + 2] = CurCourse.Name;
						ResHour -= 3;
						IsPut[i] = true;
					}
				}
			}
		}
		if (ResHour >= 2)//尝试不隔天连续两节排课
		{
			for (i = 0; i < 5; ++i)
			{
				if (ResHour < 2)break;
				for (j = 0; j < 9; ++j)
				{
					if (ResHour < 2) break;
					if (j == 4) continue;
					if (TermTable[CurTerm].Table[i][j].empty() && TermTable[CurTerm].Table[i][j + 1].empty())//如果接下来两节都空闲,则排上
					{
						TermTable[CurTerm].Table[i][j] = CurCourse.Name;
						TermTable[CurTerm].Table[i][j + 1] = CurCourse.Name;
						ResHour -= 2;
						IsPut[i] = true;
					}
				}
			}
		}
		if (ResHour >= 1)//仍然未排完
		{
			for (i = 0; i < 5; ++i)
			{
				if (ResHour < 1)break;
				for (j = 0; j < 10; ++j)
				{
					if (TermTable[CurTerm].Table[i][j].empty() && TermTable[CurTerm].Table[i][j + 1].empty())//如果这节空闲,则排上
					{
						TermTable[CurTerm].Table[i][j] = CurCourse.Name;
						ResHour -= 1;
					}
				}
			}
		}	
		if (Recover) 
			CurTerm = Temp;
	}
	void Arrange()
	{
		int CurTerm = 0;
		int CourseCnt = 0;
		Vector<int> Indegrees;
		Queue<int> MaxVertexes;
		int i;
		for (i = 0; i < CourseNet.Vertexes.GetSize(); ++i)
		{
			Indegrees.PushBack(CourseNet.Vertexes[i]->InDegree);
		}
		for (i = 0; i < Indegrees.GetSize(); ++i)
		{
			if (CourseMap.Find(i)->ElementValue.OpenTerm != 0) MaxVertexes.EnQueue(i);
		}
		for (i = 0; i < Indegrees.GetSize(); ++i)
		{
			if (Indegrees[i]==0&&CourseMap.Find(i)->ElementValue.OpenTerm == 0) MaxVertexes.EnQueue(i);
		}
		while (!MaxVertexes.Empty())
		{

			int Cur = MaxVertexes.Front();
			MaxVertexes.DeQueue();
			auto CurPtr = CourseMap.Find(Cur);
			auto CurCourse = CurPtr->ElementValue;
			int k = 0;
			k++;
			PutCourse(CurCourse, CurTerm);
			CourseCnt++;
			for (i = 0; i < CourseNet.Vertexes[Cur]->Next.GetSize(); ++i)
			{
				int NextVertexes = CourseNet.Vertexes[Cur]->Next[i]->Index;
				Indegrees[NextVertexes]--;
				if (Indegrees[NextVertexes] == 0)
				{
					MaxVertexes.EnQueue(NextVertexes);
					CourseMap.Find(NextVertexes)->ElementValue.EarliestOpenTerm = (CurTerm + 1);
				}
			}

		}
		if (CourseCnt < CourseMap.GetSize())
		{
			cout << "课程出现循环依赖关系！" << endl;
			cout << "按任意键退出！" << endl;
			getchar();
			exit(-1);
		}
	}
};
void Check(string& s)
{
	int i;
	int Cnt = 0;
	string Temp;
	for (i = 0; i < s.size(); ++i)
	{
		if (s[i] < 0)
		{
			if (Cnt % 2 == 1)
			{
				Temp.push_back(' ');
			}
			Cnt = 0;
		}
		else Cnt++;
		Temp.push_back(s[i]);
	}
	s = Temp;
}

int main(void)
{
	
	SchedulingSystem MySchedulingSystem;
	Vector<Course> AllCourse;

	in.open("in.txt", ios_base::in | ios_base::binary);
	out.open("out.txt", ios_base::out | ios_base::binary);
	if (in.is_open() == false || out.is_open() == false)
	{
		cout << "文件打开失败，请检查文件是否正确命名！" << endl;
		cout << "按任意键退出 ！" << endl;
		getchar();
		exit(-1);
	}
	int n, i, j;
	in >> n;

	int SumCourseNum = 0;
	for (i = 0; i < 8; ++i)
	{
		in >> MySchedulingSystem.TermTable[i].MaxCourseNum;
		SumCourseNum+=MySchedulingSystem.TermTable[i].MaxCourseNum;
	}
	while (in.get() != '\n') continue;
	if (SumCourseNum != n)
	{
		cout << "开课数量和每学期开课数总和不同！请检查课程设计是否出错！" << endl;
		cout << "按任意键退出 ！" << endl;
		getchar();
		exit(-1);
	}
	AllCourse.ReSize(n);
	for (i = 0; i < n; ++i)
	{
		string s;
		getline(in, s);
		stringstream ss(s);
		ss >> AllCourse[i].Num;
		ss >> AllCourse[i].Name;
		Check(AllCourse[i].Name);
		ss >> AllCourse[i].ClassHours;
		ss >> AllCourse[i].OpenTerm;
		while (ss >> s)
		{
			AllCourse[i].PreCourse.PushBack(s);
		}
		MySchedulingSystem.CourseMap.Insert(i, AllCourse[i]);
	}
	in.close();
	for (i = 0; i < n; ++i)
	{
		MySchedulingSystem.CourseNet.AddVertex(AllCourse[i].Num);
	}
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < AllCourse[i].PreCourse.GetSize(); ++j)
		{
			MySchedulingSystem.CourseNet.Link(AllCourse[i].PreCourse[j], AllCourse[i].Num);
		}
	}
	MySchedulingSystem.Arrange();
	for (i = 0; i < 8; ++i)
	{
		//将结果打印至屏幕
		cout << "第" << i +1<< "学期课表为:" << endl;
		MySchedulingSystem.TermTable[i].DisPlay(cout);
		cout << endl << endl;
		//将结果写入文件
		out << "第" << i +1<< "学期课表为:" << endl;
		MySchedulingSystem.TermTable[i].DisPlay(out);
		out << endl << endl;
	}
	cout << "课表安排完成！" << endl;
	cout << "请按任意键退出" << endl;
	getchar();
	out.close();
	return 0;
}