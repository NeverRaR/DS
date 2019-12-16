#include<iostream>
#include<string>
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
using std::string;
template <typename Key, typename Value> class TreeNode
{
	static int  Max(int x, int y)
	{
		if (x > y) return x;
		return y;
	}
	typedef TreeNode<Key, Value>* PtrToNode;
public:
	static int GetHeight(PtrToNode P)
	{
		return P ? P->Height : -1;
	}
	static PtrToNode SingleRotateWithLeft(PtrToNode K2)
	{
		PtrToNode K1;
		K1 = K2->Left;
		K2->Left = K1->Right;
		K1->Right = K2;
		K2->Height = Max(GetHeight(K2->Left), GetHeight(K2->Right)) + 1;
		K1->Height = Max(GetHeight(K1->Left), K2->Height) + 1;
		return K1;
	}
	static PtrToNode SingleRotateWithRight(PtrToNode K2)
	{
		PtrToNode K1;
		K1 = K2->Right;
		K2->Right = K1->Left;
		K1->Left = K2;
		K2->Height = Max(GetHeight(K2->Left), GetHeight(K2->Right)) + 1;
		K1->Height = Max(GetHeight(K1->Left), K2->Height) + 1;
		return K1;
	}
	static PtrToNode DoubleRotateWithLeft(PtrToNode K3)
	{
		K3->Left = SingleRotateWithRight(K3->Left);
		return SingleRotateWithLeft(K3);
	}
	static PtrToNode DoubleRotateWithRight(PtrToNode K3)
	{
		K3->Right = SingleRotateWithLeft(K3->Right);
		return SingleRotateWithRight(K3);
	}

	static PtrToNode Find(Key K, PtrToNode P)
	{
		if (P == nullptr) return nullptr;
		if (K < P->ElementKey)
			return Find(K, P->Left);
		else if (K > P->ElementKey) return Find(K, P->Right);
		else return P;
	}
	static PtrToNode FindMin(PtrToNode P)
	{
		if (P != nullptr)
			while (P->Left != nullptr)
				P = P->Left;
		return P;
	}
	static PtrToNode FindMax(PtrToNode P)
	{
		if (P != nullptr)
			while (P->Right != nullptr)
				P = P->Right;
		return P;
	}

	static PtrToNode Insert(Key K, Value V, PtrToNode P)
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
	static PtrToNode Delete(Key K, PtrToNode P)
	{
		PtrToNode TempCell;
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
	void MidVisit(ostream& os)
	{
		if (Left) Left->MidVisit(os);
		os << ElementValue << endl;
		if (Right) Right->MidVisit(os);
	}
	TreeNode<Key, Value>() = default;
	TreeNode<Key, Value>(Key K, Value V) : ElementKey(K), ElementValue(V) {}
	~TreeNode<Key, Value>()
	{
	}
	Key ElementKey;
	Value ElementValue;
	PtrToNode Left = nullptr, Right = nullptr;
	int Height = 0;
};
template <typename Key = int, typename Value = int> class AVLTree
{
	typedef TreeNode<Key, Value>* PtrToNode;
public:
	Value& operator [](const Key& K)
	{
		return Find(K)->ElementValue;
	}
	AVLTree<Key, Value>()
	{

	}
	AVLTree<Key, Value>(Key K, Value V)
	{
		Root = new TreeNode<Key, Value>(K, V);
	}
	~AVLTree<Key, Value>()
	{
		MakeEmpty();
	}
	PtrToNode Change(Key K, Value V)
	{
		PtrToNode TempCell = Root->Find(K, Root);
		if (TempCell)
		{
			TempCell->ElementValue = V;
			return TempCell;
		}
		else  return Root->UncheckInsert(K, Root);
	}

	PtrToNode Insert(Key K, Value V = Value())
	{
		if (Root == nullptr)
		{
			Size++;
			return Root = new TreeNode<Key, Value>(K, V);
		}
		PtrToNode TempCell = Root->Find(K, Root);
		if (TempCell) return UncheckChange(TempCell, V);
		else
		{
			Size++;
			Root = Root->Insert(K, V, Root);
			return Root;
		}
	}
	PtrToNode Find(Key K)
	{
		if (Root == nullptr) return nullptr;
		return Root->Find(K, Root);
	}
	PtrToNode Delete(Key K)
	{
		if (Root)
		{
			if (Root->Find(K, Root))
			{
				Size--;
				return Root = Root->Delete(K, Root);
			}
			return nullptr;
		}
		return nullptr;
	}
	PtrToNode MakeEmpty(PtrToNode P)
	{
		if (P == nullptr) return nullptr;
		if (P->Left) P->Left = MakeEmpty(P->Left);
		if (P->Right) P->Right = MakeEmpty(P->Right);
		delete P;
		return nullptr;
	}
	void MakeEmpty()
	{
		Size = 0;
		Root = MakeEmpty(Root);
	}
	void DisPlay(ostream& os)
	{
		Root->MidVisit(os);
	}
	int GetHeight()
	{
		return Root->GetHeight(Root);
	}
	PtrToNode UncheckChange(PtrToNode P, Value V)
	{
		P->ElementValue = V;
		return P;
	}
	PtrToNode UncheckInsert(Key K, Value V)
	{
		Size++;
		return Root = Root->Insert(K, V, Root);
	}
	int GetSize() { return Size; }
private:

	int Size = 0;
	PtrToNode Root = nullptr;


};
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
template <typename Key, typename Value> class TreeNode
{
	static int  Max(int x, int y)
	{
		if (x > y) return x;
		return y;
	}
	typedef TreeNode<Key, Value>* PtrToNode;
public:
	static int GetHeight(PtrToNode P)
	{
		return P ? P->Height : -1;
	}
	static PtrToNode SingleRotateWithLeft(PtrToNode K2)
	{
		PtrToNode K1;
		K1 = K2->Left;
		K2->Left = K1->Right;
		K1->Right = K2;
		K2->Height = Max(GetHeight(K2->Left), GetHeight(K2->Right)) + 1;
		K1->Height = Max(GetHeight(K1->Left), K2->Height) + 1;
		return K1;
	}
	static PtrToNode SingleRotateWithRight(PtrToNode K2)
	{
		PtrToNode K1;
		K1 = K2->Right;
		K2->Right = K1->Left;
		K1->Left = K2;
		K2->Height = Max(GetHeight(K2->Left), GetHeight(K2->Right)) + 1;
		K1->Height = Max(GetHeight(K1->Left), K2->Height) + 1;
		return K1;
	}
	static PtrToNode DoubleRotateWithLeft(PtrToNode K3)
	{
		K3->Left = SingleRotateWithRight(K3->Left);
		return SingleRotateWithLeft(K3);
	}
	static PtrToNode DoubleRotateWithRight(PtrToNode K3)
	{
		K3->Right = SingleRotateWithLeft(K3->Right);
		return SingleRotateWithRight(K3);
	}

	static PtrToNode Find(Key K, PtrToNode P)
	{
		if (P == nullptr) return nullptr;
		if (K < P->ElementKey)
			return Find(K, P->Left);
		else if (K > P->ElementKey) return Find(K, P->Right);
		else return P;
	}
	static PtrToNode FindMin(PtrToNode P)
	{
		if (P != nullptr)
			while (P->Left != nullptr)
				P = P->Left;
		return P;
	}
	static PtrToNode FindMax(PtrToNode P)
	{
		if (P != nullptr)
			while (P->Right != nullptr)
				P = P->Right;
		return P;
	}

	static PtrToNode Insert(Key K, Value V, PtrToNode P)
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
	static PtrToNode Delete(Key K, PtrToNode P)
	{
		PtrToNode TempCell;
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
	void MidVisit(ostream& os)
	{
		if (Left) Left->MidVisit(os);
		os << ElementValue << endl;
		if (Right) Right->MidVisit(os);
	}
	TreeNode<Key, Value>() = default;
	TreeNode<Key, Value>(Key K, Value V) : ElementKey(K), ElementValue(V) {}
	~TreeNode<Key, Value>()
	{
	}
	Key ElementKey;
	Value ElementValue;
	PtrToNode Left = nullptr, Right = nullptr;
	int Height = 0;
};
template <typename Key = int, typename Value = int> class AVLTree
{
	typedef TreeNode<Key, Value>* PtrToNode;
public:
	Value& operator [](const Key& K)
	{
		return Find(K)->ElementValue;
	}
	AVLTree<Key, Value>()
	{

	}
	AVLTree<Key, Value>(Key K, Value V)
	{
		Root = new TreeNode<Key, Value>(K, V);
	}
	~AVLTree<Key, Value>()
	{
		MakeEmpty();
	}
	PtrToNode Change(Key K, Value V)
	{
		PtrToNode TempCell = Root->Find(K, Root);
		if (TempCell)
		{
			TempCell->ElementValue = V;
			return TempCell;
		}
		else  return Root->UncheckInsert(K, Root);
	}

	PtrToNode Insert(Key K, Value V = Value())
	{
		if (Root == nullptr)
		{
			Size++;
			return Root = new TreeNode<Key, Value>(K, V);
		}
		PtrToNode TempCell = Root->Find(K, Root);
		if (TempCell) return UncheckChange(TempCell, V);
		else
		{
			Size++;
			Root = Root->Insert(K, V, Root);
			return Root;
		}
	}
	PtrToNode Find(Key K)
	{
		if (Root == nullptr) return nullptr;
		return Root->Find(K, Root);
	}
	PtrToNode Delete(Key K)
	{
		if (Root)
		{
			if (Root->Find(K, Root))
			{
				Size--;
				return Root = Root->Delete(K, Root);
			}
			return nullptr;
		}
		return nullptr;
	}
	PtrToNode MakeEmpty(PtrToNode P)
	{
		if (P == nullptr) return nullptr;
		if (P->Left) P->Left = MakeEmpty(P->Left);
		if (P->Right) P->Right = MakeEmpty(P->Right);
		delete P;
		return nullptr;
	}
	void MakeEmpty()
	{
		Size = 0;
		Root = MakeEmpty(Root);
	}
	void DisPlay(ostream& os)
	{
		Root->MidVisit(os);
	}
	int GetHeight()
	{
		return Root->GetHeight(Root);
	}
	PtrToNode UncheckChange(PtrToNode P, Value V)
	{
		P->ElementValue = V;
		return P;
	}
	PtrToNode UncheckInsert(Key K, Value V)
	{
		Size++;
		return Root = Root->Insert(K, V, Root);
	}
	int GetSize() { return Size; }
private:

	int Size = 0;
	PtrToNode Root = nullptr;
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
	Course& operator =(const Course& C)
	{
		Num = C.Num;
		Name = C.Name;
		ClassHours = C.ClassHours;
		OpenTerm =C.OpenTerm;
		IsArranged = C.IsArranged;
	}
	string Num, Name;
	int ClassHours;
	int OpenTerm;
	bool IsArranged;
};

class TimeTable
{
public:
	Vector<Vector<string>> Arrangement;
};
class AllTable
{
private:
	bool IsSorted = false;
	int CurTrem;
	Graph<string> CourseNet;
	Vector<int> CourseOrder;
	AVLTree<int, Course> CourseMap;
};
/*
	void TopologicalSort()
	{
		Vector<int> Indegrees;
		Queue<int> MaxVertexes;
		int i;
		for (i = 0; i < CourseNet.Vertexes.GetSize(); ++i)
		{
			Indegrees.PushBack(CourseNet.Vertexes[i]->InDegree);
		}
		for (i = 0; i < Indegrees.GetSize(); ++i)
		{
			if (Indegrees[i] == 0) MaxVertexes.EnQueue(i);
		}
		while (!MaxVertexes.Empty())
		{
			int Cur = MaxVertexes.Front();
			MaxVertexes.DeQueue();
			CourseOrder.PushBack(Cur);
			for (i = 0; i < CourseNet.Vertexes[i]->Next.GetSize(); ++i)
			{
				int NextVertexes = CourseNet.Vertexes[Cur]->Next[i]->Index;
				Indegrees[NextVertexes]--;
				if (Indegrees[NextVertexes] == 0)
				{
					MaxVertexes.EnQueue(NextVertexes);
				}
			}
		}
		if (CourseOrder.GetSize() < CourseMap.GetSize())
		{
			cout << "课程中存在循环依赖关系！" << endl;
			return;
		}
		IsSorted = true;
	};
	bool IsSorted = false;
	Graph<string> CourseNet;
	Vector<int> CourseOrder;
	AVLTree<int, Course> CourseMap;
*/