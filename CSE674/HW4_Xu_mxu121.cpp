//Mingyang Xu
//841104584
//CSE674 HW4
/*
CSE 674 HW4 Due : 11 : 59PM Friday(Oct. 11)
Objectives : Practice BFS and DFS, and apply them to solving mazes.
	You are required to implement as described in class.
	Generate one meaningful 20 by 20 maze, and include it in the end of your
	code.
	Your program will read in a maze from a file, maze.txt.
	Search the maze and find the path from start to finish using both depth first
	algorithm and breadth first algorithm.Note that both DFS and BFS are
	implemented as functions.At each C, if multiple neighbor Cs can be
	pushed to stack or queue, follow the sequence : S - E - N - W.You can use stack
	and queue from C++ STL.
	void DFS(vector<C>& maze, int n, int start, int end);//end is target C
void BFS(vector<C>& maze, int n, int start, int end);
Output should looks like the following :
Using DFS :
0 -> 1 -> 5 -> 7->бн or No solution.
Using BFS :
0 -> 4->бн or No solution.
Bonus : Print out the maze and its solution two - dimensionally.
*/
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;
class cell {
public:
	int id;
	int wall;
	bool visited;
	bool in_structure;
	int from;


	//design your constructor
};

void BFS(vector<cell>& maze, int n, int start, int end)
{
	if (start == end)
	{
		maze[start].from = start;
		cout << "Using BFS:" << endl;
		cout << maze[start].id << endl;
		return;
	}
	queue<cell> Q;
	int p = 0;
	int current = maze[start].id;
	int last;
	maze[current].visited = 1;
	int number = sqrt(n + 1);
	int dw, rw, lw, uw;
	int down = current + number, right = current + 1, left = current - 1, up = current - number;

	if (down >= 0 && down <= n)
	{
		dw = (maze[down].wall / 2 / 2) % 2;
	}
	if (right >= 0 && right <= n)
	{
		rw = (maze[right].wall / 2 / 2 / 2) % 2;
	}
	if (left >= 0 && left <= n)
	{
		lw = (maze[left].wall / 2) % 2;
	}
	if (up >= 0 && up <= n)
	{
		uw = maze[up].wall % 2;
	}

	while (current != end)
	{
		p = 0;
		if (down >= 0 && down <= n)
		{
			if (maze[current].wall % 2 == 0 && dw == 0 && maze[down].visited != 1 && maze[down].in_structure != 1)
			{
				maze[down].from = current;
				maze[down].in_structure = 1;
				Q.push(maze[down]);
				p++;
			}
		}
		if (right >= 0 && right <= n)
		{
			if ((maze[current].wall / 2) % 2 == 0 && rw == 0 && maze[right].visited != 1 && maze[right].in_structure != 1)
			{
				if ((current + 1) % number != 0)
				{
					maze[right].from = current;
					maze[right].in_structure = 1;
					Q.push(maze[right]);
					p++;
				}
			}
		}
		if (up >= 0 && up <= n)
		{
			if ((maze[current].wall / 2 / 2) % 2 == 0 && uw == 0 && maze[up].visited != 1 && maze[up].in_structure != 1)
			{
				maze[up].from = current;
				maze[up].in_structure = 1;
				Q.push(maze[up]);
				p++;
			}
		}
		if (left >= 0 && left <= n)
		{
			if ((maze[current].wall / 2 / 2 / 2) % 2 == 0 && lw == 0 && maze[left].visited != 1 && maze[left].in_structure != 1)
			{
				if (current % number != 0)
				{
					maze[left].from = current;
					maze[left].in_structure = 1;
					Q.push(maze[left]);
					p++;
				}
			}
		}

		if (Q.size() == 0 && current != end)
		{
			maze[current].visited = 1;
			cout << "Using DFS:" << endl;
			cout << "No Solution" << endl;
			return;
		}
		maze[current].visited = 1;
		current = Q.front().id;
		Q.pop();
		if (current == end)
		{
			maze[end].visited = 1;
		}
		down = current + number, right = current + 1, left = current - 1, up = current - number;
		if (down >= 0 && down < n)
		{
			dw = (maze[down].wall / 2 / 2) % 2;
		}
		if (right >= 0 && right < n)
		{
			rw = (maze[right].wall / 2 / 2 / 2) % 2;
		}
		if (left >= 0 && left < n)
		{
			lw = (maze[left].wall / 2) % 2;
		}
		if (up >= 0 && up < n)
		{
			uw = maze[up].wall % 2;
		}
	}
	vector<cell> solution;
	while (maze[current].id != start)
	{
		solution.push_back({ maze[current] });
		current = maze[current].from;

	}
	solution.push_back({ maze[current] });
	cout << "Using BFS:" << endl;
	for (int size = solution.size() - 1; size > 0; size--)
	{
		cout << solution[size].id << " -> ";
	}
	cout << solution[0].id << endl;
}

void DFS(vector<cell>& maze, int n, int start, int end)
{
	if (start == end)
	{
		maze[start].from = start;
		cout << "Using DFS:" << endl;
		cout << maze[start].id << endl;
		return;
	}
	stack<cell> S;
	int p = 0;
	int current = maze[start].id;
	int last;
	maze[current].visited = 1;
	int number = sqrt(n + 1);
	int dw, rw, lw, uw;
	int down = current + number, right = current + 1, left = current - 1, up = current - number;

	if (down >= 0 && down <= n)
	{
		dw = (maze[down].wall / 2 / 2) % 2;
	}
	if (right >= 0 && right <= n)
	{
		rw = (maze[right].wall / 2 / 2 / 2) % 2;
	}
	if (left >= 0 && left <= n)
	{
		lw = (maze[left].wall / 2) % 2;
	}
	if (up >= 0 && up <= n)
	{
		uw = maze[up].wall % 2;
	}

	while (current != end)
	{
		p = 0;
		if (down >= 0 && down <= n)
		{
			if (maze[current].wall % 2 == 0 && dw == 0 && maze[down].visited != 1 && maze[down].in_structure != 1)
			{
				maze[down].from = current;
				maze[down].in_structure = 1;
				S.push(maze[down]);
				p++;
			}
		}
		if (right >= 0 && right <= n)
		{
			if ((maze[current].wall / 2) % 2 == 0 && rw == 0 && maze[right].visited != 1 && maze[right].in_structure != 1)
			{
				if ((current + 1) % number != 0)
				{
					maze[right].from = current;
					maze[right].in_structure = 1;
					S.push(maze[right]);
					p++;
				}
			}
		}
		if (up >= 0 && up <= n)
		{
			if ((maze[current].wall / 2 / 2) % 2 == 0 && uw == 0 && maze[up].visited != 1 && maze[up].in_structure != 1)
			{
				maze[up].from = current;
				maze[up].in_structure = 1;
				S.push(maze[up]);
				p++;
			}
		}
		if (left >= 0 && left <= n)
		{
			if ((maze[current].wall / 2 / 2 / 2) % 2 == 0 && lw == 0 && maze[left].visited != 1 && maze[left].in_structure != 1)
			{
				if (current % number != 0)
				{
					maze[left].from = current;
					maze[left].in_structure = 1;
					S.push(maze[left]);
					p++;
				}
			}
		}


		if (S.size() == 0 && current != end)
		{
			maze[current].visited = 1;
			cout << "Using DFS:" << endl;
			cout << "No Solution" << endl;
			return;
		}
		maze[current].visited = 1;

		if (p == 0)
		{
			if (S.top().from == current)
			{
				current = S.top().id;
				S.pop();
			}

			else
			{
				current = maze[current].from;
			}
		}
		else
		{
			current = S.top().id;
			S.pop();
		}

		if (current == end)
		{
			maze[end].visited = 1;
		}

		down = current + number, right = current + 1, left = current - 1, up = current - number;
		if (down >= 0 && down < n)
		{
			dw = (maze[down].wall / 2 / 2) % 2;
		}
		if (right >= 0 && right < n)
		{
			rw = (maze[right].wall / 2 / 2 / 2) % 2;
		}
		if (left >= 0 && left < n)
		{
			lw = (maze[left].wall / 2) % 2;
		}
		if (up >= 0 && up < n)
		{
			uw = maze[up].wall % 2;
		}
		if (current == end)
		{
			maze[current].visited == 1;
		}
	}
	vector<cell> solution;
	while (maze[current].id != start)
	{
		solution.push_back({ maze[current] });
		current = maze[current].from;

	}
	solution.push_back({ maze[current] });
	cout << "Using DFS:" << endl;
	for (int size = solution.size() - 1; size > 0; size--)
	{
		cout << solution[size].id << " -> ";
	}
	cout << solution[0].id << endl;
}

void draw_maze(vector<cell> maze, int n, int start, int end)
{

	int number = sqrt(n + 1);
	int a = 0, b = 0;
	int current = 0;
	vector<char> line;
	vector<vector<char>> image;
	int dw, rw, lw, uw;
	int down = current + number, right = current + 1, left = current - 1, up = current - number;


	for (int i = 0; i < n; i++)
	{
		for (int i = 0; i < ((2 * number + 1)); i++)
		{
			line.push_back({ '#' });
			//line.push_back({ '.' });
		}
		for (int i = 0; i < ((2 * number + 1)); i++)
		{
			image.push_back({ line });
		}

		image[((current / number) * 2 + 1)][(current % number) * 2 + 1] = ' ';

		if (down >= 0 && down <= n)
		{
			dw = (maze[down].wall / 2 / 2) % 2;
		}
		if (right >= 0 && right <= n)
		{
			rw = (maze[right].wall / 2 / 2 / 2) % 2;
		}
		if (left >= 0 && left <= n)
		{
			lw = (maze[left].wall / 2) % 2;
		}
		if (up >= 0 && up <= n)
		{
			uw = maze[up].wall % 2;
		}



		if (down >= 0 && down <= n)
		{
			if (maze[current].wall % 2 == 0 && dw == 0)
			{
				//image[((current / number) * 2 + 2)][(current % number)*2+1] = '.';
				image[(current % number) * 2 + 1][((current / number) * 2 + 2)] = ' ';
			}
		}
		if (right >= 0 && right <= n)
		{
			if ((maze[current].wall / 2) % 2 == 0 && rw == 0)
			{
				if ((current + 1) % number != 0)
				{
					//image[((current / number) * 2 +1)][((current % number)*2 +2)] = '.';
					image[((current % number) * 2 + 2)][((current / number) * 2 + 1)] = ' ';
				}
			}
		}
		if (up >= 0 && up <= n)
		{
			if ((maze[current].wall / 2 / 2) % 2 == 0 && uw == 0)
			{
				//image[((current / number) * 2 )][(current % number)*2+1] = '.';
				image[(current % number) * 2 + 1][((current / number) * 2)] = ' ';
			}
		}
		if (left >= 0 && left <= n)
		{
			if ((maze[current].wall / 2 / 2 / 2) % 2 == 0 && lw == 0)
			{
				if (current % number != 0)
				{
					//image[((current / number) * 2 + 1)][(current % number)*2] = '.';
					image[(current % number) * 2][((current / number) * 2 + 1)] = ' ';
				}
			}
		}
		current++;
	}
	int edge = start;
	int times = 0;
	if (start != end)
	{
		if (maze[end].visited == 1)
		{
			while (times != 2)
			{
				if (edge >= 0 && edge <= number)
				{
					if ((maze[edge].wall / 2 / 2) % 2 == 0)
					{
						image[(edge % number) * 2 + 1][((edge / number) * 2)] = '@';
					}
				}
				if (edge >= n - number && edge <= n - 1)
				{
					if ((maze[edge].wall) % 2 == 0)
					{
						image[(edge % number) * 2 + 1][((edge / number) * 2 + 2)] = '@';
					}
				}
				int x = 0;
				while (x <= n)
				{
					if ((maze[edge].wall / 2 / 2 / 2) % 2 == 0)
					{
						image[(edge % number) * 2][((edge / number) * 2 + 1)] = '@';
					}
					x = x + number;
				}
				x = number;
				while (x <= n)
				{
					if ((maze[edge].wall / 2) % 2 == 0)
					{
						image[((edge % number) * 2 + 2)][((edge / number) * 2 + 1)] = '@';
					}
					x = x + number;
				}
				edge = end;
				times++;
			}
		}
		//BFS(maze, n, start, end);
		if (maze[end].visited == 1)
		{
			current = end;
			vector<cell> solution;
			while (maze[current].id != start)
			{
				solution.push_back({ maze[current] });
				current = maze[current].from;

			}
			solution.push_back({ maze[current] });
			int i = 0, j = 0;
			for (int size = solution.size() - 1; size >= 0; size--)
			{
				//j = image[(solution[size].id % number) * 2 + 1][((solution[size].id / number) * 2 + 1)];
					//image[((solution[size].id / number) * 2 + 1)][(solution[size].id % number) * 2 + 1] = '@';
				image[(solution[size].id % number) * 2 + 1][((solution[size].id / number) * 2 + 1)] = '@';
				//i = image[(solution[size].id % number) * 2 + 1][((solution[size].id / number) * 2 + 1)];
				if (size != 0)
				{
					if ((solution[size].id % number) * 2 + 1 == (solution[size - 1].id % number) * 2 + 1)
					{
						if (((solution[size].id / number) * 2 + 1) > ((solution[size - 1].id / number) * 2 + 1))
						{
							image[(solution[size].id % number) * 2 + 1][((solution[size].id / number) * 2)] = '@';
						}
						else
						{
							{
								image[(solution[size].id % number) * 2 + 1][((solution[size].id / number) * 2 + 2)] = '@';
							}
						}

					}
					else
					{
						if (((solution[size].id % number) * 2 + 1) > ((solution[size - 1].id % number) * 2 + 1))
						{
							image[(solution[size].id % number) * 2][((solution[size].id / number) * 2 + 1)] = '@';
						}
						else
						{
							{
								image[(solution[size].id % number) * 2 + 2][((solution[size].id / number) * 2 + 1)] = '@';
							}
						}
					}
				}
				//if()
			}
			//cout << solution[0].id << endl;
		}
	}

	for (b = 0; b < (2 * number + 1); b++)
	{
		for (a = 0; a < (2 * number + 1); a++)
		{
			cout << image[a][b];
		}
		cout << endl;
	}
}

int main()
{
	cell C;
	vector<cell> maze;
	C.id = 0;
	C.wall = 0;
	C.visited = 0;
	C.in_structure = 0;
	C.from = -1;
	int n, start, end, w;
	ifstream in("maze1.txt");
	in >> n >> start >> end;
	for (int i = 0; i < n; i++)
	{
		in >> w;
		C.wall = w;
		maze.push_back({ C.id,C.wall,C.visited,C.in_structure,C.from });
		C.id++;
	}
	in.close();
	BFS(maze, n, start, end);
	draw_maze(maze, n, start, end);
	for (int i = 0; i < n; i++)
	{
		maze[i].visited = 0;
		maze[i].in_structure = 0;
		maze[i].from = -1;
	}
	DFS(maze, n, start, end);
	draw_maze(maze, n, start, end);
	cin.get();
	return 0;
}
//Format for maze.txt:
//16 //number of Cs
//0//starting C
//15//target C
//8 4 5 6 10 9 6 10 8 6 11 10 11 9 7 10//C walls

//maze.txt:
//400
//0
//399
/*
8 4 5 5 4 5 7 4 5 7 12 5 4 6 12 5 6 12 5 6
10 10 13 5 3 12 5 2 12 6 10 12 2 10 9 6 10 10 13 3
11 9 6 12 7 10 14 9 3 9 3 10 10 9 6 10 10 9 5 6
12 5 3 8 5 2 10 12 6 12 4 2 10 12 3 11 10 12 7 10
9 5 4 3 14 9 3 10 9 3 11 10 10 9 5 5 3 9 4 2
8 6 9 7 8 6 12 3 14 12 5 3 9 6 12 5 5 5 3 10
11 9 6 12 3 9 1 5 3 9 6 12 6 11 9 6 13 5 5 3
8 5 3 9 4 5 5 5 5 6 9 2 10 12 6 9 5 6 12 6
10 12 6 14 10 14 12 5 5 3 12 3 9 3 9 6 13 1 3 10
10 10 10 8 2 10 10 12 5 5 3 13 5 4 5 0 6 13 6 10
10 10 9 3 9 3 9 3 12 5 5 5 4 3 13 3 9 6 8 2
10 9 6 12 5 5 5 5 3 14 12 6 9 6 12 5 7 9 3 10
9 4 3 10 12 6 12 6 9 1 3 9 6 10 9 6 12 6 14 10
8 3 14 8 2 9 3 10 12 6 12 6 10 9 6 9 3 8 0 2
9 4 3 10 9 5 6 9 3 8 3 10 8 7 9 5 7 10 10 11
12 3 12 3 12 6 9 6 13 1 7 9 1 6 12 6 12 3 9 6
10 14 10 12 3 9 7 9 4 6 12 7 12 3 10 8 3 13 6 10
11 8 3 9 5 5 5 6 10 9 9 5 3 12 3 9 5 6 9 3
12 3 12 5 5 5 6 10 10 12 5 5 6 10 12 5 5 3 12 6
9 5 3 13 5 5 3 9 3 9 5 7 9 3 9 5 5 5 3 10
*/
