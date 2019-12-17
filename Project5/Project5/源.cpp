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


template<typename ElementType>class Queue;
template<typename ElementType> class Node
{
private:
	friend class Queue<ElementType>;
	Node<ElementType>() : Pre(nullptr), Next(nullptr) {};
	Node<ElementType>(const ElementType& e) :Element(e) {};
	Node<ElementType>* Next=nullptr, *Pre=nullptr;
	ElementType Element;
};
template<typename ElementType> class Queue
{
public:
	Queue<ElementType>();
	~Queue<ElementType>();
	int GetSize();
	bool Empty();
	void EnQueue(ElementType E);
	void DeQueue();
	ElementType Front();
	void Clear();
private:
	int Size=0;
	Node<ElementType>* Head, *Tail;
};
void CustomerSeparation(Queue<int>& A, Queue<int>& B, int &CustomerNum)
{
	cout << "����һ��������˿͵�������ÿλ�˿͵ı��:" << endl;
	cin >> CustomerNum;
	while (CustomerNum <= 0)
	{
		cout << "������һ����������" << endl;
		cin >> CustomerNum;
	}
	int i;
	for (i = 0; i < CustomerNum; ++i)
	{
		int CurNum;
		cin >> CurNum;
		if (CurNum % 2 == 0)
			B.EnQueue(CurNum);
		else
			A.EnQueue(CurNum);
	}
}
void ProcessBusiness(Queue<int>& A, Queue<int>& B, Vector<int> &OutSequence)
{
	int B_BusyTime = 1; //����B����ǰҵ��ʣ��ʱ��
	while (!A.Empty() && !B.Empty())//���������ж���Ϊ��ʱ
	{
		OutSequence.PushBack(A.Front());//A���Ƚ����������
		A.DeQueue();
		if (B_BusyTime == 0)//���B�Ѿ������굱ǰҵ��
		{
			OutSequence.PushBack(B.Front());//���׽����������
			B.DeQueue();
			B_BusyTime = 1;//ҵ��ʣ��ʱ������Ϊ1
		}
		else --B_BusyTime;//���δ�����꣬��ʣ��ʱ��-1
	}
	while (!A.Empty())//���A��Ϊ�գ����Aʣ��Ԫ��ȫ�����������
	{
		OutSequence.PushBack(A.Front());
		A.DeQueue();
	}
	while (!B.Empty())//���B��Ϊ�գ����Bʣ��Ԫ��ȫ�����������
	{
		OutSequence.PushBack(B.Front());
		B.DeQueue();
	}
}
int main(void)
{
	int i;
	int CustomerNum = 0;
	Vector<int> OutSequence;
	Queue<int> A, B;
	CustomerSeparation(A, B,CustomerNum);
	ProcessBusiness(A, B, OutSequence);
	cout << "��������Ϊ��" << endl;
	for (i = 0; i < CustomerNum-1; ++i)
	{
		cout << OutSequence[i] << " ";
	}
	cout << OutSequence[i];
	while (getchar() != '\n') continue;//�����ĩ���з�
	cout << endl << "��������˳���" << endl;
	getchar();

	return 0;
}

template<typename ElementType>
inline int Queue<ElementType>::GetSize() { return Size; }

template<typename ElementType>
inline bool Queue<ElementType>::Empty() { return Size == 0; }

template<typename ElementType>
inline void Queue<ElementType>::EnQueue(ElementType E)
{
	Node<ElementType>* Temp = new Node<ElementType>(E);
	Temp->Pre = Tail->Pre;
	Temp->Next = Tail;
	Tail->Pre = Temp;
	Temp->Pre->Next = Temp;
	Size++;
}

template<typename ElementType>
inline void Queue<ElementType>::DeQueue()
{
	if (Empty()) return;
	Node<ElementType>* Temp = Head->Next;
	Head->Next = Temp->Next;
	Head->Next->Pre = Head;
	delete Temp;
	Size--;
}

template<typename ElementType>
inline ElementType Queue<ElementType>::Front()
{
	return Head->Next->Element;
}

template<typename ElementType>
inline void Queue<ElementType>::Clear()
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

template<typename ElementType>
inline Queue<ElementType>::Queue()
{
	Head = new Node<ElementType>();
	Tail = new Node<ElementType>();
	Head->Next = Tail;
	Tail->Pre = Head;
}

template<typename ElementType>
inline Queue<ElementType>::~Queue()
{
	Clear();
	delete Head;
	delete Tail;
}
