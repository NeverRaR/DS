#include<iostream>
#include<string>
#include<time.h>

using std::string;
using std::cin;
using std::cout;
using std::endl;
int RandomArray[100000050];
int ArrayToBeSorted[100000050];
class MT19937
{
public:
	int  Extract()
	{
		int y;
		int  i = index;
		if (index >= N)
		{
			Twist();
			i = index;
		}
		y = mt[i];
		index = i + 1;
		y ^= (y >> U);
		y ^= (y << S) & B;
		y ^= (y << T) & C;
		y ^= (y >> L);
		if (y <= 0) y *= -1;
		else if (y == 0) y = 1;
		return y ;
	}
	void Initialize(const int  seed)
	{
		int  i;
		mt[0] = seed;
		for (i = 1; i < N; i++)
		{
			mt[i] = (F * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i);
		}
		index = N;
	}
private:
	enum
	{
		W = 32,
		N = 624,
		M = 397,
		R = 31,
		A = 0x9908B0DF,

		F = 1812433253,

		U = 11,
		D = 0xFFFFFFFF,

		S = 7,
		B = 0x9D2C5680,

		T = 15,
		C = 0xEFC60000,

		L = 18,

		MASK_LOWER = (1ull << R) - 1,
		MASK_UPPER = (1ull << R)
	};
	void Twist()
	{
		int i, x, xA;
		for (i = 0; i < N; i++)
		{
			x = (mt[i] & MASK_UPPER) + (mt[(i + 1) % N] & MASK_LOWER);
			xA = x >> 1;
			if (x & 0x1)
			{
				xA ^= A;
			}
			mt[i] = mt[(i + M) % N] ^ xA;
		}

		index = 0;
	}
	int  mt[N];
	int  index;
};
long long MoveTime = 0;
long long CmpTime = 0;
void Swap(int&x, int&y)
{
	MoveTime += 3;
	int Tmp = x;
	x = y;
	y = Tmp;
}
void BubbleSort(int V[], int Len)
{
	int i, j;
	bool IsSwap = false;
	for (i = 0; i < Len - 1; ++i)
	{
		IsSwap = false;
		for (j = 0; j < Len - i - 1; j++)
		{
			++CmpTime;
			if (V[j + 1] < V[j])
			{
				Swap(V[j + 1], V[j]);
				IsSwap = true;
			}
		}
		if (IsSwap == false) break;
	}
}
void SelectionSort(int V[], int Len)
{
	int i, j;
	int MinIndex;
	for (i = 0; i < Len - 1; ++i)
	{
		MinIndex = i;
		for (j = i+1; j < Len ; j++)
		{
			++CmpTime;
			if (V[MinIndex] > V[j])
			{
				MinIndex = j;
			}
		}
		if (MinIndex != i)
		{
			Swap(V[MinIndex], V[i]);
		}
	}
}
void InsertionSort(int V[], int Len)
{
	int i, j;
	int Tmp;
	for (i = 1; i < Len; ++i)
	{
		Tmp = V[i];
		for (j = i; j > 0 && V[j - 1] > Tmp; j--)
		{
			++CmpTime;
			++MoveTime;
			V[j] = V[j - 1];
		}
		V[j] = Tmp;
		MoveTime++;
	}
}

void ShellSort(int V[], int Len)
{
	int Sedgewick[30] =
	{ 0, 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289,
	  64769, 146305, 260609, 587521, 1045505, 2354689, 4188161, 9427969, 16764929,
	  37730305, 67084289, 150958081, 268386305, 603906049, 1073643521 };
	int i, j;
	int Tmp;
	int Gap;
	int GapIndex = 0;
	while (Sedgewick[GapIndex] < Len/2) GapIndex++;
	Gap = Sedgewick[GapIndex];
	while (Gap > 0)
	{
		for (i = Gap; i < Len; ++i)
		{
			Tmp = V[i];
			for (j = i; j >= Gap; j -= Gap)
			{
			
				if (Tmp < V[j - Gap])
				{
					++CmpTime;
					++MoveTime;
					V[j] = V[j - Gap];
				}
				else
					break;
			}
			V[j] = Tmp;
			++MoveTime;
		}
		Gap = Sedgewick[--GapIndex];
	}
}
void PercDown(int V[], int i, int N)
{
	int Child;
	int Tmp;
	for (Tmp = V[i]; 2 * i + 1 < N; i = Child)
	{
		Child = 2 * i + 1;
		MoveTime++;
		CmpTime += 3;
		if (Child != N - 1 && V[Child + 1] > V[Child]) ++Child;
		if (Tmp < V[Child]) V[i] = V[Child];
		else break;
	}
	V[i] = Tmp;
	MoveTime++;
}
void HeapSort(int V[], int Len)
{
	int i;
	for (i = Len / 2; i >= 0; --i)
	{
		PercDown(V, i, Len);
	}
	for (i = Len - 1; i > 0; --i)
	{
		Swap(V[0], V[i]);
		PercDown(V, 0, i);
	}
}
void Merge(int V[], int TmpArray[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, NumElements, TmpPos;
	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;

	while (Lpos <= LeftEnd && Rpos <= RightEnd)
	{
		++MoveTime;
		++CmpTime;
		if (V[Lpos] <= V[Rpos])
			TmpArray[TmpPos++] = V[Lpos++];
		else
			TmpArray[TmpPos++] = V[Rpos++];
	}
	while (Lpos <= LeftEnd)
	{
		TmpArray[TmpPos++] = V[Lpos++];
		++MoveTime;
	}
	while (Rpos <= RightEnd)
	{
		TmpArray[TmpPos++] = V[Rpos++];
		++MoveTime;
	}
	for (i = 0; i < NumElements; ++i)
	{
		V[RightEnd] = TmpArray[RightEnd];
		++MoveTime;
		--RightEnd;
	}
}
void Msort(int V[], int TmpArray[], int Left, int Right)
{
	int Center;
	if (Left < Right)
	{
		Center = (Left + Right) / 2;
		Msort(V, TmpArray, Left, Center);
		Msort(V, TmpArray, Center + 1, Right);
		Merge(V, TmpArray, Left, Center + 1, Right);
	}
}
void MergeSort(int V[], int Len)
{
	int *TmpArray = new int[Len];
	Msort(V, TmpArray, 0, Len - 1);
	delete TmpArray;
}
void RadixSort(int V[], int Len)
{
	int Max = V[0];
	int i, j, k;
	for (i = 0; i < Len; ++i) if (Max < V[i])Max = V[i];
	int **Buckets;
	Buckets = new int*[2];
	Buckets[0] = new int[Len];
	Buckets[1] = new int[Len];
	int BucketsSize[2] = { 0,0 };
	int  TotalCnt = 0;
	while (Max > 0)
	{
		TotalCnt++;
		Max >>= 1;
	}
	int CurBit, CurNum, CurIndex;
	for (CurBit = 0; CurBit <= TotalCnt; ++CurBit)
	{
		for (i = 0; i < Len; ++i)
		{
			CurNum = V[i];
			CurIndex = (CurNum >> CurBit) & 1;
			Buckets[CurIndex][BucketsSize[CurIndex]++] = CurNum;
			++MoveTime;
		}
		k = 0;
		for (i = 0; i < 2; ++i)
		{
			for (j = 0; j < BucketsSize[i]; ++j)
			{
				V[k++] = Buckets[i][j];
				++MoveTime;
			}
			BucketsSize[i] = 0;
		}
	}
	delete Buckets[0];
	delete Buckets[1];
	delete Buckets;
}
void Qsort(int V[], int Left, int Right)
{
	int i, j;
	int Pivot;
	int Center = (Left + Right) / 2;
	CmpTime += 3;
	if (V[Center] < V[Left]) Swap(V[Left], V[Center]);
	if (V[Right] < V[Left]) Swap(V[Left], V[Right]);
	if (V[Right] < V[Center]) Swap(V[Center], V[Right]);
	if (Left + 3 <= Right)
	{
	
		Swap(V[Center], V[Right - 1]);
		Pivot = V[Right - 1];
		i = Left; j = Right - 1;
		while (true)
		{
			while (V[++i] < Pivot)++CmpTime;
			while (V[--j] > Pivot)++CmpTime;
			if (i < j) Swap(V[i], V[j]);
			else break;
		}
		Swap(V[i], V[Right - 1]);
		Qsort(V, Left, i - 1);
		Qsort(V, i + 1, Right);
	}
}
void QuickSort(int V[], int Len)
{
    Qsort(V, 0, Len - 1);
}
void Menu()
{
	cout << "**\t\t排序算法比较\t\t**" << endl;
	for (int i = 0; i < 42; i++)
	{
		cout << '=';
	}
	cout << endl;
	cout << "**\t\t1---冒泡排序\t\t**" << endl;
	cout << "**\t\t2---选择排序\t\t**" << endl;
	cout << "**\t\t3---插入排序\t\t**" << endl;
	cout << "**\t\t4---希尔排序\t\t**" << endl;
	cout << "**\t\t5---快速排序\t\t**" << endl;
	cout << "**\t\t6---堆排序\t\t**" << endl;
	cout << "**\t\t7---归并排序\t\t**" << endl;
	cout << "**\t\t8---基数排序\t\t**" << endl;
	cout << "**\t\t9---退出程序\t\t**" << endl;
	for (int i = 0; i < 42; i++)
	{
		cout << '=';
	}
	cout << endl;
}
void CreatRandomNum(int n)
{
	MT19937 M;
	M.Initialize(clock());
	int i;
	for (i = 0; i < n; ++i)
	{
		RandomArray[i] = M.Extract();
	}
}
void Check(int v[], int Len)
{
	int i;
	for (i = 0; i < Len - 1; ++i)
	{
		if (v[i] > v[i + 1])
		{
			cout << "排序出错！" << endl;
			return;
		}
	}
	cout << "排序完成！" << endl;
}
int main(void)
{
	Menu();
	int n, i;
	cout << "请输入要产生的随机数个数：";
	cin >> n;
	cout << endl;
	CreatRandomNum(n);
	bool IsLooping = true;
	int Start, End;
	int Cmd;
	while (IsLooping)
	{
		for (i = 0; i < n; ++i) ArrayToBeSorted[i] = RandomArray[i];
		MoveTime = 0;
		CmpTime = 0;
		cout << "请选择排序算法：" << "\t";
		cin >> Cmd;
		string Name;
		Start = clock();
		switch (Cmd)
		{
		case 1:
			BubbleSort(ArrayToBeSorted, n);
			Name = "冒泡排序";
			break;
		case 2:
			SelectionSort(ArrayToBeSorted, n);
			Name = "选择排序";
			break;
		case 3:
			InsertionSort(ArrayToBeSorted, n);
			Name = "插入排序";
			break;
		case 4:
			ShellSort(ArrayToBeSorted, n);
			Name = "希尔排序";
			break;
		case 5:
			QuickSort(ArrayToBeSorted, n);
			Name = "快速排序";
			break;
		case 6:
			HeapSort(ArrayToBeSorted, n);
			Name = "堆排序";
			break;
		case 7:
			MergeSort(ArrayToBeSorted, n);
			Name = "归并排序";
			break;
		case 8:
			RadixSort(ArrayToBeSorted, n);
			Name = "基数排序";
			break;
		default:
			IsLooping = false;
			break;
		}
		End = clock();
		Check(ArrayToBeSorted, n);
		cout << Name << "所用时间是：" << "\t" << End - Start << "毫秒" << endl;
		cout << Name << "移动次数是：" << "\t" << MoveTime << "次" << endl ;
		cout << Name << "比较次数是：" << "\t" << CmpTime << "次" << endl << endl;
	}
}