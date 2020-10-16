//Mingyang Xu
//841104584
//CSE674 HW5
//HW5  AVL Tree
//Due: Friday (Nov. 8) at 11:59PM
//55 points
//This homework requires more efforts. You should get started as soon as possible.

#include <iostream> //to use cout
#include <algorithm> //to use max function such as  i = max(a, b);
#include <stack>

using namespace std;

//You need to use the following node class for each node of the AVL tree
class node {
public:
	int value;
	int height;//this is tree height. Leaf node is 1; empty node (i.e., NIL) is 0
	node* parent;
	node* l_child;
	node* r_child;
	node() {}
	node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr; }

};

class avl_tree {
public:
	node* root;
	avl_tree() {
		root = nullptr;
	}

	//************************************************************************************
	//Implement the following member functions
	void add_node(int i);
	//if case of a tie, add i to the last of existing nodes with value i in the in-order sequence

	void delete_node(int i);
	//Delete the node with value i.  in case of multiple nodes with value i, delete the first node with value i in the in-order traveral sequence


	void in_order_traversal(node* p); //such as 2 5 9 11 11 14 15 15 ...

	pair<node*, int> height_update(node* p);
	/*
	This function will be invoked by add_node and delete_node.
	p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
	All nodes whose heights need to be updated will be performed in this function.
	The function returns a pair.  If no imbalance is detected, the first of the pair will be nullptr; otherwise it will be the address of the action node.
	The second of the pair will be 0 if no imbalance is detected; otherwise its value is 1,2,3,4 for RR RL, LL, and LR pattern, respectively.
	*/

	void L_Rotate(node* p);
	//p points to the node at which the rotation will be performed.

	void R_Rotate(node* p);
	//p points to the node at which the rotation will be performed.
};

void avl_tree::add_node(int i)
{
	node* inode = new node(i);
	if (root == nullptr)
	{
		root = inode;
		return;
	}

	node* findparent = root;
	node* findp = root;

	while (findp != nullptr)
	{
		findparent = findp;

		if (inode->value >= findp->value)
		{

			findp = findp->r_child;
		}
		else
		{
			findp = findp->l_child;
		}

	}

	inode->parent = findparent;
	if (inode->value >= findparent->value)
	{

		findparent->r_child = inode;
	}
	else
	{
		findparent->l_child = inode;

	}
	height_update(findparent);
	node* check = height_update(findparent).first;
	if (height_update(findparent).second == 1)
	{

		L_Rotate(check); //RRpattern
	}
	else if (height_update(findparent).second == 2)
	{

		node* checkchild = check->r_child;
		R_Rotate(checkchild);
		L_Rotate(check);//RLpattern
	}
	else if (height_update(findparent).second == 3)
	{
		R_Rotate(check); //LLpattern
	}
	else if (height_update(findparent).second == 4)
	{
		node* checkchild = check->l_child;
		L_Rotate(checkchild);
		R_Rotate(check);//LRpattern

	}


}
void avl_tree::delete_node(int i)
{
	node* p = root;

	if (root == nullptr)
	{
		return;
	}
	if (root->l_child == nullptr && root->r_child == nullptr)
	{
		root = nullptr;
		return;
	}
	node* findp = root;

	while (findp != nullptr)
	{


		if (i > findp->value)
		{

			findp = findp->r_child;
		}
		else if (i < findp->value)
		{
			findp = findp->l_child;
		}
		else
		{
			break;
		}
	}

	if (findp == nullptr)
	{
		return;
	}
	if (findp->l_child == nullptr && findp->r_child == nullptr)
	{
		node* findparent = findp->parent;
		if (findp == findparent->l_child)
		{
			findparent->l_child = nullptr;
		}
		else
		{
			findparent->r_child = nullptr;
		}
		findp->parent = nullptr;
		height_update(findparent);
		while (height_update(findparent).first != nullptr)
		{
			node* check = height_update(findparent).first;
			if (height_update(findparent).second == 1)
			{

				L_Rotate(check); //RRpattern
			}
			else if (height_update(findparent).second == 2)
			{

				node* checkchild = check->r_child;
				R_Rotate(checkchild);
				L_Rotate(check);//RLpattern
			}
			else if (height_update(findparent).second == 3)
			{
				R_Rotate(check); //LLpattern
			}
			else if (height_update(findparent).second == 4)
			{
				node* checkchild = check->l_child;
				L_Rotate(checkchild);
				R_Rotate(check);//LRpattern

			}
			height_update(check);
		}
		return;
	}
	if (findp->height == 2 && (findp->l_child == nullptr || findp->r_child == nullptr))
	{
		node* findparent = findp->parent;
		node* child = root;
		if (findp->l_child == nullptr)
		{
			child = findp->r_child;
		}
		else
		{
			child = findp->l_child;
		}
		if (findparent->l_child == findp)
		{
			findparent->l_child = child;
		}
		else
		{
			findparent->r_child = child;
		}
		child->parent = findparent;
		findp->l_child = nullptr;
		findp->r_child = nullptr;
		findp->parent = nullptr;
		height_update(findparent);
		while (height_update(findparent).first != nullptr)
		{
			node* check = height_update(findparent).first;
			if (height_update(findparent).second == 1)
			{

				L_Rotate(check); //RRpattern
			}
			else if (height_update(findparent).second == 2)
			{

				node* checkchild = check->r_child;
				R_Rotate(checkchild);
				L_Rotate(check);//RLpattern
			}
			else if (height_update(findparent).second == 3)
			{
				R_Rotate(check); //LLpattern
			}
			else if (height_update(findparent).second == 4)
			{
				node* checkchild = check->l_child;
				L_Rotate(checkchild);
				R_Rotate(check);//LRpattern

			}
			height_update(check);
		}
		return;
	}
	node* predecessor = findp->l_child;
	if (predecessor != nullptr)
	{
		while (predecessor->r_child != nullptr)
		{
			predecessor = predecessor->r_child;
		}
	}
	node* sucessor = findp->r_child;
	if (sucessor != nullptr)
	{
		while (sucessor->l_child != nullptr)
		{
			sucessor = sucessor->l_child;
		}
	}
	node* preparent = predecessor->parent;
	node* prel = predecessor->l_child;
	node* prer = predecessor->r_child;
	node* sucprent = sucessor->parent;
	node* sucl = sucessor->l_child;
	node* sucr = sucessor->r_child;
	node* ANparent = findp->parent;
	node* ANl = findp->l_child;
	node* ANr = findp->r_child;
	if (predecessor != nullptr)
	{
		if (findp == root)
		{
			root = predecessor;
		}
		if (predecessor == ANl)
		{
			predecessor->r_child = ANr;
			predecessor->parent = ANparent;
			ANr->parent = predecessor;
			if (ANparent != nullptr)
			{
				ANparent->l_child = predecessor;
			}
			findp->l_child = nullptr;
			findp->r_child = nullptr;
			findp->parent = nullptr;

		}
		else
		{
			if (prel != nullptr)
			{
				prel->parent = preparent;
			}
			if (preparent == findp)
			{
				preparent->l_child = prel;
			}
			else
			{
				preparent->r_child = prel;
			}
			if (ANparent != nullptr)
			{
				if (findp == ANparent->l_child)
				{
					ANparent->l_child = predecessor;
				}
				else
				{
					ANparent->r_child = predecessor;

				}
			}
			predecessor->l_child = ANl;
			ANl->parent = predecessor;
			predecessor->r_child = ANr;
			ANr->parent = predecessor;
			predecessor->parent = ANparent;
			findp->l_child = nullptr;
			findp->r_child = nullptr;
			findp->parent = nullptr;
		}
	}
	else
	{
		if (findp == root)
		{
			root = sucessor;
		}
		if (sucessor == ANr)
		{
			sucessor->r_child = ANr;
			sucessor->parent = ANparent;
			ANl->parent = sucessor;
			if (ANparent != nullptr)
			{
				ANparent->r_child = sucessor;
			}
			findp->l_child = nullptr;
			findp->r_child = nullptr;
			findp->parent = nullptr;

		}
		else
		{
			if (sucr != nullptr)
			{
				sucr->parent = preparent;
			}
			if (preparent == findp)
			{
				preparent->l_child = sucr;
			}
			else
			{
				preparent->r_child = sucr;
			}
			if (ANparent != nullptr)
			{
				if (findp == ANparent->l_child)
				{
					ANparent->l_child = sucessor;
				}
				else
				{
					ANparent->r_child = sucr;

				}
			}
			sucessor->l_child = ANl;
			ANl->parent = sucessor;
			sucessor->r_child = ANr;
			ANr->parent = sucessor;
			sucessor->parent = ANparent;
			findp->l_child = nullptr;
			findp->r_child = nullptr;
			findp->parent = nullptr;
		}
	}
	node* findparent = root;
	if (predecessor != nullptr)
	{
		findparent = predecessor;
	}
	else
	{
		findparent = sucessor;
	}
	height_update(findparent);
	while (height_update(findparent).first != nullptr)
	{
		node* check = height_update(findparent).first;
		if (height_update(findparent).second == 1)
		{

			L_Rotate(check); //RRpattern
		}
		else if (height_update(findparent).second == 2)
		{

			node* checkchild = check->r_child;
			R_Rotate(checkchild);
			L_Rotate(check);//RLpattern
		}
		else if (height_update(findparent).second == 3)
		{
			R_Rotate(check); //LLpattern
		}
		else if (height_update(findparent).second == 4)
		{
			node* checkchild = check->l_child;
			L_Rotate(checkchild);
			R_Rotate(check);//LRpattern

		}
		height_update(check);
	}
	return;



}

void avl_tree::in_order_traversal(node* p)
{
	if (p == nullptr)
	{
		return;
	}


	in_order_traversal(p->l_child);
	cout << p->value << " ";
	in_order_traversal(p->r_child);
}


pair<node*, int>avl_tree::height_update(node* p)
{
	node* temp = p;
	node* pleft = p->l_child;
	node* pright = p->r_child;
	if (pleft != nullptr)
	{
		p = pleft;
		while (p != nullptr)
		{
			if (p->r_child == nullptr && p->l_child == nullptr)
			{
				p->height = 1;
			}
			else if (p->r_child == nullptr && p->l_child != nullptr)
			{
				p->height = 1 + p->l_child->height;
			}
			else if (p->l_child == nullptr && p->r_child != nullptr)
			{
				p->height = 1 + p->r_child->height;
			}
			else
			{
				p->height = max(p->r_child->height, p->l_child->height) + 1;
			}
			p = p->parent;
		}
	}
	else if (pright != nullptr)
	{
		p = pright;
		while (p != nullptr)
		{
			if (p->r_child == nullptr && p->l_child == nullptr)
			{
				p->height = 1;
			}
			else if (p->r_child == nullptr && p->l_child != nullptr)
			{
				p->height = 1 + p->l_child->height;
			}
			else if (p->l_child == nullptr && p->r_child != nullptr)
			{
				p->height = 1 + p->r_child->height;
			}
			else
			{
				p->height = max(p->r_child->height, p->l_child->height) + 1;
			}
			p = p->parent;
		}
	}



	node* check = temp;
	int dif = 0;
	int lhight = 0; int rhight = 0;
	while (check != nullptr)
	{
		if (check->l_child == nullptr)
		{
			lhight = 0;
		}
		else
		{
			lhight = check->l_child->height;
		}
		if (check->r_child == nullptr)
		{
			rhight = 0;
		}
		else
		{
			rhight = check->r_child->height;
		}
		dif = abs(lhight - rhight);
		if (dif > 1)
		{
			break;
		}
		else
		{
			check = check->parent;
		}
	}
	if (check == nullptr) return{ nullptr, 0 };
	int lchight = 0, rchight = 0;
	//if (lhight == rhight) return;
	if (lhight > rhight)
	{
		node* checkchild = check->l_child;

		if (checkchild->l_child == nullptr)
		{
			lchight = 0;
		}
		else
		{
			lchight = checkchild->l_child->height;
		}
		if (checkchild->r_child == nullptr)
		{
			rchight = 0;
		}
		else
		{
			rchight = checkchild->r_child->height;
		}
		if (lchight > rchight)
		{
			return { check, 3 };
			//R_Rotate(check); //LLpattern
		}
		else
		{
			return { check, 4 };
			//L_Rotate(checkchild);
			//R_Rotate(check);
			//LRpattern
		}
	}
	else
	{
		node* checkchild = check->r_child;
		if (checkchild->l_child == nullptr)
		{
			lchight = 0;
		}
		else
		{
			lchight = checkchild->l_child->height;
		}
		if (checkchild->r_child == nullptr)
		{
			rchight = 0;
		}
		else
		{
			rchight = checkchild->r_child->height;
		}
		if (rchight > lchight)
		{
			return { check, 1 };
			//L_Rotate(check);//RRpattern
		}
		else
		{
			return { check, 2 };
			//R_Rotate(checkchild);
			//L_Rotate(check);//RLpattern
		}
	}


}



void avl_tree::L_Rotate(node* p)
{
	node* higher = p->parent;
	node* R = p->r_child;

	node* q = R->l_child;
	if (p == root)
	{
		p->parent = R;
		R->l_child = p;
		if (q != nullptr)
		{
			p->r_child = q;
			q->parent = p;
		}
		else
		{
			p->r_child = nullptr;
		}
		R->parent = nullptr;
		root = R;

	}
	else
	{
		if (higher->l_child == p)
		{
			higher->l_child = R;
		}
		else
		{
			higher->r_child = R;
		}
		R->parent = higher;
		R->l_child = p;
		p->parent = R;
		//p->r_child = nullptr;

		if (q != nullptr)
		{
			p->r_child = q;
			q->parent = p;
		}
		else
		{
			p->r_child = nullptr;
		}

	}

	while (p != nullptr)
	{
		if (p->r_child == nullptr && p->l_child == nullptr)
		{
			p->height = 1;
		}
		else if (p->r_child == nullptr && p->l_child != nullptr)
		{
			p->height = 1 + p->l_child->height;
		}
		else if (p->l_child == nullptr && p->r_child != nullptr)
		{
			p->height = 1 + p->r_child->height;
		}
		else
		{
			p->height = max(p->r_child->height, p->l_child->height) + 1;
		}
		p = p->parent;
	}

}
void avl_tree::R_Rotate(node* p)
{
	node* higher = p->parent;
	node* L = p->l_child;

	node* q = L->r_child;
	if (p == root)
	{

		p->parent = L;
		L->r_child = p;
		if (q != nullptr)
		{
			p->l_child = q;
			q->parent = p;
		}
		else
		{
			p->l_child = nullptr;
		}
		L->parent = nullptr;
		root = L;


	}
	else
	{
		if (higher->l_child == p)
		{
			higher->l_child = L;
		}
		else
		{
			higher->r_child = L;
		}

		L->parent = higher;
		L->r_child = p;
		p->parent = L;
		//p->l_child = nullptr;

		if (q != nullptr)
		{
			p->l_child = q;
			q->parent = p;
		}
		else
		{
			p->l_child = nullptr;
		}
	}
	while (p != nullptr)
	{
		if (p->r_child == nullptr && p->l_child == nullptr)
		{
			p->height = 1;
		}
		else if (p->r_child == nullptr && p->l_child != nullptr)
		{
			p->height = 1 + p->l_child->height;
		}
		else if (p->l_child == nullptr && p->r_child != nullptr)
		{
			p->height = 1 + p->r_child->height;
		}
		else
		{
			p->height = max(p->r_child->height, p->l_child->height) + 1;
		}
		p = p->parent;
	}

}

int main() {
	//Different test cases will be used during grading.
	avl_tree t1;
	t1.add_node(45);
	t1.in_order_traversal(t1.root);
	t1.delete_node(45);
	t1.in_order_traversal(t1.root);
	t1.add_node(50);
	t1.add_node(46);
	t1.add_node(30);
	t1.add_node(34);
	t1.in_order_traversal(t1.root);
	t1.delete_node(48);
	t1.in_order_traversal(t1.root);
	getchar();
	getchar();
	return 0;
}

//The following is an example showing how to return a pair.
/*
#include <iostream>
using namespace std;

pair<int *, int> f1(){
	return { new int {10}, 10 };
}
int main() {
	cout << *f1().first << " " << f1().second << endl;
	getchar();
	getchar();
	return 0;
}
*/