#include<iostream>
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
struct Point
{
	int x = 0;
	int y = 0;
	Point(int x=0, int y=0) :x(x), y(y) {};
	Point& operator =(const Point& p) 
	{
		x = p.x;
		y = p.y;
		return *this;
	}
};
class Maze
{
public:
	void ShowMap();
	void FindRoad();
	void ShowPath();
private:
	

	void InitVis();
	bool DFS(const Point& p);
	bool Vis[100][100] = { 0 };
	char MazeMap[100][100] =
	{
	{"##########################"},
	{"#O# ##  #    # #   ##  # #" },
	{"# #    #  ##     #   #   #"},
	{"#  # #  ##  ### # ##  # ##" },
	{"## #  #   #   # # #  #  ##" },
	{"#  ##  ##   # # #  # ##  #" },
	{"# #   # ## ##   ## #   # #" },
	{"#  # #    #  # # #  ## # #" },
	{"# #  # ##  #  ##   #   # #" },
	{"#   #    #   #   #  # #  #" },
	{"# ## ## #X# #  ## # #  # #" },
	{"##    #   #  # #  #  #   #"},
	{"#  ##  # #  ##   # #  ## #" },
	{"# #  #  #  #  # #    #   #" },
	{"# ##  #   #  #   ## #  ###" },
	{"#   #  ##  # # ##    # # #" },
	{"# #  #    #    ## ## #   #" },
	{"#  #  ####  ###    # ### #" },
	{"### # #    #    ###    # #" },
	{"#     # ### # ##    # #  #" },
	{"# #####   # #   # ##  # ##" },
	{"# #    ##    ##  ##  #   #" },
	{"#   ##  ## ##  #   # # # #" },
	{"# ### #       # ##  #   ##" },
	{"#      # ## #     #   #  #" },
	{"##########################" },
	};
	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	int MapSize = 26;
	Point Start = Point(1, 1);
	Vector<Point> PointPath;
};

int main(void)
{
	Maze MyMaze;
	MyMaze.ShowMap();
	MyMaze.FindRoad();
	MyMaze.ShowPath();
	cout << endl;
	cout << "请按任意键退出。" ;
	getchar();
	return 0;
}

inline void Maze::ShowMap()
{
	int i;
	cout << "迷宫地图（O为起点，X为终点，#为墙）：" << endl;
	for (i = 0; i < MapSize; ++i)
	{
		cout << MazeMap[i] << endl;
	}
}

inline void Maze::FindRoad()
{
	PointPath.Clear();
	InitVis();
	DFS(Start);
}

inline void Maze::ShowPath()
{
	cout << "路线展示（O为起点，X为终点,*为路径上经过的点）：" << endl;
	int i;
	for (i = PointPath.GetSize() - 2; i > 0; --i)
	{
		int x = PointPath[i].x, y = PointPath[i].y;
		MazeMap[x][y] = '*';
	}
	for (i = 0; i < MapSize; ++i)
	{
		cout << MazeMap[i] << endl;
	}
	for (i = PointPath.GetSize() - 2; i > 0; --i)
	{
		int x = PointPath[i].x, y = PointPath[i].y;
		MazeMap[x][y] = ' ';
	}
	int cnt = 0;
	for (i = PointPath.GetSize() - 1; i >= 0; --i)
	{
		int x = PointPath[i].x, y = PointPath[i].y;
		if (cnt % 10 == 0 && cnt != 0) cout << endl;
		if (cnt == 0)	cout << "迷宫路径：" << endl;
		cout << "(";
		if (x < 10) cout << " ";
		cout << x;
		cout << ",";
		if (y < 10) cout << " ";
		cout << y;
		cout << ")";
		if (i != 0)
		{
			cout << "→";
		}
		cnt++;
	}
}

inline void Maze::InitVis()
{
	int i, j;
	for (i = 0; i < MapSize; ++i)
	{
		for (j = 0; j < MapSize; ++j)
		{
			Vis[i][j] = false;
		}
	}
}

inline bool Maze::DFS(const Point & p)
{
	Vis[p.x][p.y] = true;
	if (MazeMap[p.x][p.y] == 'X')
	{
		PointPath.PushBack(p);
		return true;
	}
	int i;
	for (i = 0; i < 4; ++i)
	{
		int nx = p.x + dx[i];
		int ny = p.y + dy[i];
		if (Vis[nx][ny] == true || MazeMap[nx][ny] == '#')
			continue;
		if (DFS(Point(nx, ny)) == true)
		{
			PointPath.PushBack(p);
			return true;
		}
	}
	return false;
}
