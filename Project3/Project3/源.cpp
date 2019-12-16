#include"Vector.h"
#include"iostream"
using std::cout;
using std::endl;
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
	void ShowMap()
	{
		int i;
		cout << "迷宫地图（O为起点，X为终点，#为墙）：" << endl;
		for (i = 0; i < MapSize; ++i)
		{
			cout << MazeMap[i] << endl;
		}
	}
	void FindRoad()
	{
		PointPath.Clear();
		InitVis();
		DFS(Start);
	}
	void ShowPath()
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
			if (cnt % 10 == 0&&cnt!=0) cout << endl;
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
private:
	

	void InitVis()
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
	bool DFS(const Point& p)
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
			if (Vis[nx][ny]==true || MazeMap[nx][ny] == '#')
				continue;
			if (DFS(Point(nx, ny)) == true)
			{
				PointPath.PushBack(p);
				return true;
			}
		}
		return false;
	}
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