#include<iostream>
#include<string>
using std::ostream;
using std::cin;
using std::cout;
using std::endl;
using std::string;


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
	TreeNode<Key, Value>* TempCell = Root->Find(K, Root);
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
template<typename ElementType> class Greater
{
public:
	bool operator ()(const ElementType& E1, const ElementType& E2)
	{
		return  E2 < E1;
	}
};
template<typename ElementType> class Less
{
public:
	bool operator ()(const ElementType& E1, const ElementType& E2)
	{
		return E1 < E2;
	}
};
template<typename ElementType, typename Comparator = Greater<ElementType>> class Heap
{
public:
	~Heap<ElementType, Comparator>() = default;
	Heap<ElementType, Comparator>();
	Heap<ElementType, Comparator>(int Size);
	int GetSize() { return Elements.GetSize() - 1; };
	bool Empty() { return Elements.GetSize() <= 1; };
	void Push(const ElementType& E);
	void Build(int Size);
	void Pop();
	void Clear();
	ElementType Top();
private:
	Vector<ElementType> Elements;
};

template<typename ElementType, typename Comparator>
Heap<ElementType, Comparator>::Heap()
{
	Elements.ReSize(1);
}

template<typename ElementType, typename Comparator>
Heap<ElementType, Comparator>::Heap(int Size)
{
	Elements.ReSize(Size + 1);
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::Push(const ElementType & E)
{
	int i;
	Elements.PushBack(E);
	Comparator Cmp;
	for (i = Elements.GetSize() - 1; i > 1; i /= 2)
	{
		if (Cmp(Elements[i / 2], E)) Elements[i] = Elements[i / 2];
		else break;
	}
	Elements[i] = E;
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::Build(int Size)
{
	Elements.ReSize(Size + 1);
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::Pop()
{
	if (Empty()) return;
	int i, Child, CurSize = Elements.GetSize();
	Comparator Cmp;
	ElementType  LastElement;
	LastElement = Elements.Back();
	for (i = 1; i * 2 < CurSize; i = Child)
	{
		Child = i * 2;
		if (Child != CurSize - 1 && Cmp(Elements[Child], Elements[Child + 1]))
			++Child;
		if (Cmp(LastElement, Elements[Child])) Elements[i] = Elements[Child];
		else break;
	}
	Elements[i] = LastElement;
	Elements.PopBack();
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::Clear()
{
	Elements.Clear();
	Elements.ReSize(1);
}

template<typename ElementType, typename Comparator>
ElementType Heap<ElementType, Comparator>::Top()
{
	if (Empty()) return Elements[0];
	return Elements[1];
}
template<typename Tag>
class Vertex
{
public:
	Vertex<Tag>() = default;
	Vertex<Tag>(const Tag& T) : VertexTag(T) {};
	int Index;
	Tag VertexTag;
	Vector<Vertex*> Adjacency;
	Vector<int> Weight;
};

template<typename Tag> class Graph
{
public:
	Graph<Tag>() = default;
	~Graph<Tag>() ;
	void Clear();
	Vertex<Tag>* AddVertex(const Tag& T);
	void Link(const Tag&T1, const Tag&T2, int Weight);
	void Link(Vertex<Tag>*V1, Vertex<Tag>*V2, int Weight);
	void SingleLink(Vertex<Tag>*V1, Vertex<Tag>*V2, int Weight);
	Vector<Vertex<Tag>*> Vertexes;
	AVLTree<Tag, int> VertexTree;
};

template<typename Tag>
void Graph<Tag>::Clear()
{
	VertexTree.MakeEmpty();
	for (int i = 0; i <Vertexes.GetSize(); i++)
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
void Graph<Tag>::Link(const Tag & T1, const Tag & T2, int Weight)
{
	TreeNode<Tag,int>* N1, *N2;
	Vertex<Tag>* V1, *V2;
	N1 = VertexTree.Find(T1);
	if (N1 == nullptr) return;
	V1 =  Vertexes[N1->ElementValue];
	N2 = VertexTree.Find(T2);
	if (N2 == nullptr||N1==N2) return;
	V2 = Vertexes[N2->ElementValue];
	Link(V1, V2, Weight);
}

template<typename Tag>
void Graph<Tag>::Link(Vertex<Tag>* V1, Vertex<Tag>* V2, int Weight)
{
	V1->Adjacency.PushBack(V2);
	V1->Weight.PushBack(Weight);
	V2->Adjacency.PushBack(V1);
	V2->Weight.PushBack(Weight);
}

template<typename Tag>
void Graph<Tag>::SingleLink(Vertex<Tag>* V1, Vertex<Tag>* V2, int Weight)
{
	V1->Adjacency.PushBack(V2);
	V1->Weight.PushBack(Weight);
}

template<typename Tag>
Graph<Tag>::~Graph()
{
	Clear();
}
class STP
{
public:
	void Display()
	{
		if (G.Vertexes.GetSize() == 1)
		{
			cout << Root->VertexTag << endl;
		}
		else
		{
			int Cnt = 0;
			DFS(Root, Cnt);
			cout << endl;
		}
	}
	void DFS(Vertex<string> *Cur, int&Cnt)
	{
		if (Cur == nullptr) return;
		int i;
		for (i = 0; i < Cur->Adjacency.GetSize(); ++i)
		{
			if (Cnt % 8 == 0&&Cnt!=0) cout << endl;
			cout << Cur->VertexTag << "-<" << Cur->Weight[i] << ">-" << Cur->Adjacency[i]->VertexTag << "   ";
			Cnt++;
			DFS(Cur->Adjacency[i], Cnt);
		}
	}
	Vertex<string>* Root = nullptr;
	Graph<string> G;
};
class PowerGrid
{
public:
	void Menu();
	void CreatNetVertex();
	void AddEdge();
	void BuildSTP();
	void DisplaySTP();
	void Destory();
private:
	bool STPIsReady = false;
	bool CheckName(const Vector<string>& AllName);
	Graph<string> Net;
	STP NetSTP;

};

void PowerGrid::Menu()
{
	cout << "**\t\t电网造价模拟系统\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t请选择要执行的操作：\t\t**" << endl;
	cout << "**\t\tA---创建电网顶点\t\t**" << endl;
	cout << "**\t\tB---添加电网的边\t\t**" << endl;
	cout << "**\t\tC---构造最小生成树\t\t**" << endl;
	cout << "**\t\tD---显示最小生成树\t\t**" << endl;
	cout << "**\t\tE---清空电网系统\t\t**" << endl;
	cout << "**\t\tF---退出程序\t\t\t**" << endl;
	for (int i = 0; i < 50; i++)
	{
		cout << '=';
	}
	cout << endl;
}

void PowerGrid::CreatNetVertex()
{
	STPIsReady = false;
	int n;
	cout << "请输入顶点的个数：";
	cin >> n;
	while (n <= 0)
	{
		cout << "顶点个数为负数或0！请重新输入一个正整数：";
		cin >> n;
	}
	Vector<string> AllName;
	AllName.ReSize(n);
	cout << "请依次输入各顶点的名称：" << endl;
	int i;
	for (i = 0; i < n; ++i)
	{
		cin >> AllName[i];
	}
	while (CheckName(AllName) == false)
	{
		cout << "请重新输入顶点名称序列：" << endl;
		for (i = 0; i < n; ++i)
		{
			cin >> AllName[i];
		}
	}
	for (i = 0; i < n; ++i)
	{
		Net.AddVertex(AllName[i]);
	}
}

void PowerGrid::AddEdge()
{
	STPIsReady = false;
	int n, i;
	cout << "请输入要添加的边的个数：";
	cin >> n;
	while (n <= 0)
	{
		cout << "顶点个数为负数或0！请重新输入一个正整数：" ;
		cin >> n;
	}
	string S1, S2;
	int Weight;
	for (i = 0; i < n; ++i)
	{
		cout << "请输入两个顶点及边的权值：" ;
		cin >> S1 >> S2 >> Weight;
		Net.Link(S1, S2, Weight);
	}
}

void PowerGrid::BuildSTP()
{

	struct VertexInfo
	{
		bool IsJoined = false;
		int Weight= 0x7fffffff;
		int PreV;
		VertexInfo(int W, int s,bool b=false) :Weight(W), PreV(s),IsJoined(b) {};
		const VertexInfo& operator =(const VertexInfo& VI)
		{
			Weight = VI.Weight;
			IsJoined = VI.IsJoined;
			PreV = VI.PreV;
			return *this;
		}
		VertexInfo() = default;
	};
	struct Edge
	{
		Edge(int T1, int T2, int W) : VT1(T1), VT2(T2), Weight(W) {};
		Edge() = default;
		bool operator <(const Edge& E) const { return Weight < E.Weight; };
		int VT1, VT2;
		int Weight;
	};
	if (Net.Vertexes.Empty())
	{
		cout << "网络中不存在顶点，请至少创建一个顶点！" << endl;
		return;
	}
	string Name;
	int VertexNum = Net.Vertexes.GetSize();
	cout << "请输入起始顶点：";
	cin >> Name;
	TreeNode<string, int>* Start;
	while ((Start=Net.VertexTree.Find(Name)) == nullptr)
	{
		cout << "该顶点不存在！请重新输入：";
		cin >> Name;
	}
	if (STPIsReady == true&&NetSTP.Root->VertexTag==Name) return;
	NetSTP.G.Clear();
	NetSTP.Root = nullptr;
	int i;
	int StartIndex = Start->ElementValue;
	NetSTP.Root=NetSTP.G.AddVertex(Name);
	Vector<VertexInfo> Info;
	Info.ReSize(VertexNum);
	Info[StartIndex].IsJoined = true;
	Info[StartIndex].Weight = 0;
	Heap<Edge> MinEdgeH;
	for (i = 0; i < Net.Vertexes[StartIndex]->Adjacency.GetSize(); i++)
	{
		Vertex<string> *t= Net.Vertexes[StartIndex]->Adjacency[i];
		int NextVertex = Net.Vertexes[StartIndex]->Adjacency[i]->Index;
		int NextWeight= Net.Vertexes[StartIndex]->Weight[i];
		MinEdgeH.Push(Edge(StartIndex,NextVertex,NextWeight));
		Info[NextVertex].PreV = 0;
		Info[NextVertex].Weight = NextWeight;
	}
	while (!MinEdgeH.Empty())
	{
		int Cur = MinEdgeH.Top().VT2; MinEdgeH.Pop();
		if (Info[Cur].IsJoined == true) continue;
		string CurName = Net.Vertexes[Cur]->VertexTag;
		auto NewNode=NetSTP.G.AddVertex(CurName);
		NetSTP.G.SingleLink(NetSTP.G.Vertexes[Info[Cur].PreV], NewNode, Info[Cur].Weight);
		Info[Cur].IsJoined = true;
		for (i = 0; i < Net.Vertexes[Cur]->Adjacency.GetSize(); i++)
		{
			int NextVertex = Net.Vertexes[Cur]->Adjacency[i]->Index;
			int NextWeight = Net.Vertexes[Cur]->Weight[i];
			if (Info[NextVertex].IsJoined == true) continue;
			if (Info[NextVertex].Weight > NextWeight)
			{
				Info[NextVertex].PreV = NetSTP.G.Vertexes.GetSize() - 1;
				Info[NextVertex].Weight = NextWeight;
				MinEdgeH.Push(Edge(Cur, NextVertex, NextWeight));
			}
		}
	}
	if (NetSTP.G.Vertexes.GetSize() < Net.Vertexes.GetSize())
	{
		cout << "原网络不连通！请重建网络或者添加上其他边!" << endl;
		return;
	}
	cout << "生成Prim最小生成树！" << endl;
	STPIsReady = true;
}

void PowerGrid::DisplaySTP()
{
	if (STPIsReady == false)
	{
		cout << "最小生成树不存在，请先生成最小生成树！" << endl;
		return;
	}
	cout << "最小生成树的顶点及边为：" << endl;
	NetSTP.Display();
}

void PowerGrid::Destory()
{
	STPIsReady = false;
	Net.Clear();
	cout << "网络销毁完成！" << endl;
}

bool PowerGrid::CheckName(const Vector<string>& AllName)
{
	AVLTree<string> NameSet;
	int i;
	for (i = 0; i < AllName.GetSize(); ++i)
	{
		if (NameSet.Find(AllName[i]) != nullptr)
		{
			cout << "新增顶点名称序列中存在重复项！" << endl;
			return false;
		}
		NameSet.Insert(AllName[i]);
	}
	for (i = 0; i < AllName.GetSize(); ++i)
	{
		if (Net.VertexTree.Find(AllName[i]) != nullptr)
		{
			cout << "新增顶点名称序列中存在与原有顶点名称重复的项！" << endl;
			return false;
		}
	}
	return true;
}
int main(void)
{
	PowerGrid MyPowerGrid;
	MyPowerGrid.Menu();
	string Cmd;
	bool IsLooping = true;
	while (IsLooping)
	{
		cout << "请选择操作：";
		cin >> Cmd;
		switch (Cmd[0])
		{
		case 'A':
			MyPowerGrid.CreatNetVertex();
			break;
		case 'B':
			MyPowerGrid.AddEdge();
			break;
		case 'C':
			MyPowerGrid.BuildSTP();
			break;
		case 'D':
			MyPowerGrid.DisplaySTP();
			break;
		case 'E':
			MyPowerGrid.Destory();
			break;
		case 'F':
			IsLooping = false;
			break;
		default:
			cout << "未知命令！" << endl;
			break;
		}
	}
	return 0;
}
