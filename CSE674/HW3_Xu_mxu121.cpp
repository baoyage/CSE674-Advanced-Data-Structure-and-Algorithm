//Mingyang Xu
//841104584
//CSE674 HW3
//Use the following names for the structures.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <cmath>
using namespace std;
class n_node { //stand for neighbor_node
public:
	int id;  //neighbor id
	int weight;
	//Do your own constructor(s)
};

class rt_node {
public:
	bool is_visited; //true if visited; else false
	int cost; //path cost
	int from; //from node
	int h_pos;//the positon of this node in heap
//Do your own constructor(s)
};

class h_node {
public:
	int id;//node id
	int cost; //cost to this node from source
	int from;		  //Do your own constructor(s)
};

std::ostream& operator<<(std::ostream& str, const n_node& n_node) {
	{
		str << n_node.id << " " << n_node.weight;
	}
	return str;
}
std::ostream& operator<<(std::ostream& str, const rt_node& rt_node) {
	{
		str << rt_node.is_visited << " " << rt_node.cost << " " << rt_node.from << " " << rt_node.h_pos;
	}
	return str;
}

void heaplify(int N, vector <h_node>& Heap)
{
	int M;
	M = N;
	int times;
	times = log(N + 1) / log(2);
	while (times > 0)
	{
		times--;
		N = M;
		while (N - 1 >= 0)
		{
			if (N % 2 != 0)
			{
				if (Heap[(N - 1) / 2].cost > Heap[N].cost)
				{
					swap(Heap[N], Heap[(N - 1) / 2]);
				}
				N = N - 1;
				if (N == 0)
				{
					return;
				}
			}
			if (Heap[(N - 1) / 2].cost > Heap[N].cost)
			{
				if (Heap[(N - 1) / 2].cost > Heap[N - 1].cost)
				{
					if (Heap[N].cost > Heap[N - 1].cost)
					{
						swap(Heap[N - 1], Heap[(N - 1) / 2]);
					}
					else
					{
						swap(Heap[N], Heap[(N - 1) / 2]);
					}
				}
				else
				{
					swap(Heap[N], Heap[(N - 1) / 2]);
				}
			}
			else
			{
				if (Heap[(N - 1) / 2].cost > Heap[N - 1].cost)
				{
					swap(Heap[N - 1], Heap[(N - 1) / 2]);
				}
			}
			N = N - 2;
		}
	}
}

void remove(vector <h_node>& Heap, vector <rt_node>& Routing_Table)
{
	int c = 0, d = 0;
	while (c <= Heap.size() + 1 && d <= Heap.size() + 1)
	{
		d++; c = 0;
		while (c < Heap.size() && d < Heap.size())
		{
			if (c <= Heap.size() && Heap[c].id == Heap[d].id)
			{
				if (c != d)
				{
					if (Heap[c].cost > Heap[d].cost)
					{
						swap(Heap[c], Heap[Heap.size() - 1]);
					}
					else
					{
						swap(Heap[d], Heap[Heap.size() - 1]);
					}
					Heap.pop_back();
				}
			}
			c++;
		}
	}
}

void remove_visited(vector <h_node>& Heap, vector <rt_node>& Routing_Table)
{
	for (int s = 0; s < Routing_Table.size(); s++)
	{
		if (Routing_Table[s].is_visited == 1)
		{
			int a = 0;
			while (Heap[a].id == s)
			{
				a++;
				if (a > Heap.size() - 1)
				{
					a--;
					break;
				}
			}
			swap(Heap[a], Heap[Heap.size() - 1]);
			for (int i = 0; i < Heap.size(); i++)
			{
				if (Heap[i].id == s)
				{
					swap(Heap[i], Heap[Heap.size() - 1]);
					Heap.pop_back();
					if (Heap.size() != 0)
					{
						swap(Heap[Heap.size() - 1], Heap[0]);
					}
				}

			}
		}
	}
}
int main() {
	ifstream in("graph.txt");
	int i, j, k, x, y, z;
	float f;
	in >> i >> j >> k;
	n_node n;
	vector<n_node> V;
	vector<vector<n_node>> Graph1(j);
	for (int p = 0; p < 2 * k; p++) {
		in >> x >> y >> z;
		n.id = y;
		n.weight = z;

		V.push_back({ n.id, n.weight });

		Graph1[x].push_back(V[p]);
		p++;
		n.id = x;
		V.push_back({ n.id, n.weight });
		Graph1[y].push_back(V[p]);
	}
	in.close();
	vector<vector<n_node>* > Graph;
	for (int p = 0; p < j; p++) {


		Graph.push_back(&Graph1[p]);
	}


	rt_node rt;
	vector <rt_node> Routing_Table;
	h_node H;
	vector <h_node> Heap;
	rt.is_visited = 0; rt.cost = 9999; rt.from = -1; rt.h_pos = -1;
	for (int p = 0; p < j; p++) {

		Routing_Table.push_back({ rt.is_visited, rt.cost,rt.from,rt.h_pos });
	}
	Routing_Table[i].cost = 0;
	Routing_Table[i].from = i;
	Routing_Table[i].h_pos = 0;
	H.id = i;
	H.cost = 0;
	H.from = 0;
	Heap.push_back({ H.id ,H.cost,H.from });
	int a, b;
	a = Heap[0].id;
	b = Heap[0].cost;
	int s;
	int u = j;

	while (u >= 0)
	{
		u--;
		heaplify(Heap.size() - 1, Heap);
		if (Heap.size() == 0)
		{
			break;
		}
		a = Heap[0].id;
		b = Heap[0].cost;

		Routing_Table[a].h_pos = Heap[0].id;
		Routing_Table[a].is_visited = 1;
		for (int s = 0; s <= Heap.size() - 1; s++)
		{
			if (Routing_Table[Heap[s].id].cost > Heap[s].cost)
			{
				Routing_Table[Heap[s].id].cost = Heap[s].cost;
				Routing_Table[Heap[s].id].from = Heap[s].from;
			}
		}
		if (u == -1)
		{
			break;
		}
		for (s = 0; s < (*Graph[a]).size(); s++)
		{
			Heap.push_back({ (*Graph[a])[s].id,(*Graph[a])[s].weight,a });
		}
		remove_visited(Heap, Routing_Table);
	}
	int sum = 0;
	for (s = 0; s < Routing_Table.size(); s++)
	{
		cout << s << " " << Routing_Table[s].from << " " << Routing_Table[s].cost << endl;
		sum = sum + Routing_Table[s].cost;
	}
	cout << "The overall cost of the minimum spanning tree is " << sum << endl;
	getchar();
	getchar();
	return 0;

}

