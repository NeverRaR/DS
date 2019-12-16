#include<iostream>
using std::cin;
using std::cout;
using std::endl;
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
template<typename ElementType, typename Comparator=Greater<ElementType>> class Heap
{
public:
	~Heap<ElementType, Comparator>() = default;
	Heap<ElementType, Comparator>() ;
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
	Elements.ReSize(Size+1);
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::Push(const ElementType & E)
{
	int i;
	Elements.PushBack(E);
	Comparator Cmp;
	for (i=Elements.GetSize()-1; i > 1; i /= 2)
	{
		if(Cmp(Elements[i/2],E)) Elements[i]=Elements[i/2];
		else break;
	}
	Elements[i]=E;
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::Build(int Size)
{
	Elements.ReSize(Size + 1);
}

template<typename ElementType, typename Comparator>
void Heap<ElementType, Comparator>::Pop()
{
	if(Empty()) return;
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
int main(void)
{
	Heap<int> H;
	int i, Num;
	cin >> Num;
	int Temp, Ans=0;
	for (i = 0; i < Num; ++i)
	{
		cin >> Temp;
		H.Push(Temp);
	}
	while (H.GetSize() > 1)
	{
		int First = H.Top(); H.Pop();
		int Second = H.Top(); H.Pop();
		int NewCost = First + Second;
		Ans += NewCost;
		H.Push(NewCost);
	}
	cout << Ans;
	return 0;
}