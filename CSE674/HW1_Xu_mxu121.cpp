//Mingyang Xu
//841104584
//CSE674 HW1
//Due: 11:59PM, Thursday (9/12)

#include <iostream>

using namespace std;


class Node {
public:
	int value;
	Node* next;
	Node(int i) { value = i; next = nullptr; }
	Node() { next = nullptr; }
};

class LinkedList {
public:
	int numNodes;
	Node* head;
	LinkedList() { numNodes = 0; head = nullptr; }
	void makeRandomList(int m, int n);
	void printList();



	//Recursively merge sort i numbers starting at node pointed by p
	void mergeSort(Node*& p, int i);//in-place recursive merge sort


	//Merge i1 numbers starting at node pointed by p1 with i2 numbers
	//starting at node pointed by p2
	void merge(Node*& p1, int i1, Node* p2, int i2);
};

void LinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		Node* p1 = new Node(rand() % n);
		p1->next = head;
		head = p1;
		numNodes++;
	}
}

void LinkedList::printList() {
	cout << endl;
	Node* p1 = head;
	while (p1 != nullptr) {
		cout << p1->value << " ";
		p1 = p1->next;
	}
}
void LinkedList::merge(Node*& p1, int i1, Node* p2, int i2) {
	while (i1 != 0 && i2 != 0) {
		if (p1->value >= p2->value) {
			int temp = p1->value;
			p1->value = p2->value;
			p2->value = temp;

			if (p1->next == p2) {

				i1++;
				i2--;
				p2 = p2->next;

			}
			else {
				Node* p3 = p1->next;
				Node* p4 = p2->next;
				Node* temp2 = nullptr;
				Node* temp3 = nullptr;
				temp2 = head;
				temp3 = head;
				while (temp3 != p2)
				{
					temp2 = temp3;
					temp3 = temp3->next;
				}


				p1->next = p2;
				p2->next = p3;
				temp2->next = p4;


				i1++;
				i2--;
				p2 = p4;
			}
		}
		else {
			p1 = p1->next;
			i1--;
		}
	}

}

void LinkedList::mergeSort(Node*& p, int i) {
	Node* p1 = p;
	Node* p2 = p1->next;
	int temp1 = 0;
	int t = i / 2;
	Node* mid = p1;
	int n = 0;
	while (n < t)
	{
		n++;
		mid = mid->next;
	}
	if (i <= 1)
		return;
	mergeSort(p1, t);
	mergeSort(mid, i - t);
	merge(p1, t, mid, i - t);
}

int main() {

	LinkedList d1;


	d1.makeRandomList(40, 20);
	d1.printList();

	d1.mergeSort(d1.head, d1.numNodes);
	d1.printList();

	getchar();
	getchar();
	return 0;

}