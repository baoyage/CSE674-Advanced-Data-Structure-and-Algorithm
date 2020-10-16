//Mingyang Xu
//841104584
//CSE674 HW6  Due: 11:59PM, Nov. 25 (Monday)
#include <iostream>
using namespace std;

class node {
public:
	int value;
	bool color;
	node* p_parent;
	node* p_Lchild;
	node* p_Rchild;

	//true: red, false: black
	node() { p_parent = p_Lchild = p_Rchild = nullptr; }
	node(int i) { value = i; p_parent = p_Lchild = p_Rchild = nullptr; }
};

class tree {
public:
	node* root;
	tree() { root = nullptr; }

	//For insert, the new node should be the last of nodes with the same value in the order of 
	//inorder traversal.  (The same as HW5.)
	void insert_node(int i);
	void insert_R_rotate(node* p);//For insert_node, R-rotate at node pointed by p
	void insert_L_rotate(node* p);//for insert_node, L-rotate at node pointed by p
	//All other siutions of insert_node should be directly implemented inside add_node


	//For delete, the deleted node shoud be the first of nodes with the same value in the order of
	//inorder traversal. (The same as HW5).
	//For replacement, always recursively replace it with predecessor, unless there is no predecessor. (In this
	//case, replace it with sucessor.)


	void delete_node(int i);
	void delete_1(node* p); //case 1 of delete_node; p points to the parent of double black node
	void delete_1_R_rotate(node* p);//R_totate used in case 1 of delete_node; p points to the parent of double black node
	void delete_1_L_rotate(node* p);//L_totate used in case 1 of delete_node; p points to the parent of double black node
	void delete_2A(node* p); //case 2A of delete_node; p points to the parent of double black node
	void delete_2B(node* p);//case 2B of delete_node; p points to the parent of double black node
	void delete_3(node* p);//case 3 of delete_node; p points to the parent of double black node
	//All other cases of delete_node should be directly implemented inside the delete_node.

	//For the following, during traveral, print (value, color) of each node.
	void InorderPrint(node*);
	void PostorderPrint(node*);
	void PreorderPrint(node*);
	//void tr(node* p);
};

void tree::delete_3(node* p)
{
	if (p == root)
	{
		return;
	}
	node* parent = p->p_parent;
	node* sibling = nullptr;
	if (p == parent->p_Lchild)
	{
		sibling = parent->p_Rchild;
	}
	else
	{
		sibling = parent->p_Lchild;
	}
	node* pL = p->p_Lchild;
	node* pR = p->p_Rchild;
	node* sL = sibling->p_Lchild;
	node* sR = sibling->p_Rchild;
	sibling->color = false;
	parent->color = true;
	if (sibling == parent->p_Rchild)
	{
		delete_1_L_rotate(parent);
	}
	else
	{
		delete_1_R_rotate(parent);
	}

	parent = p->p_parent;
	sibling = nullptr;
	if (p == parent->p_Lchild)
	{
		sibling = parent->p_Rchild;
	}
	else
	{
		sibling = parent->p_Lchild;
	}
	pL = p->p_Lchild;
	pR = p->p_Rchild;
	sL = sibling->p_Lchild;
	sR = sibling->p_Rchild;
	bool sLcolor, sRcolor, scolor;
	if (sL != nullptr)
	{
		sLcolor = sL->color;
	}
	else
	{
		sLcolor = false;
	}
	if (sR != nullptr)
	{
		sRcolor = sR->color;
	}
	else
	{
		sRcolor = false;
	}
	if (sibling != nullptr)
	{
		scolor = sibling->color;
	}
	else
	{
		scolor = false;
	}

	if (scolor == false)
	{
		if (sLcolor == true || sRcolor == true)
		{
			delete_1(p);
			return;
		}
		if (sLcolor == false && sRcolor == false)
		{
			if (parent->color == false)
			{
				delete_2A(p);
				return;
			}
			else
			{
				delete_2B(p);
				return;
			}
		}
	}
	else
	{
		delete_3(p);
		return;
	}
}

void tree::delete_2B(node* p)
{
	if (p == root)
	{
		return;
	}
	node* parent = p->p_parent;
	node* sibling = nullptr;
	if (p == parent->p_Lchild)
	{
		sibling = parent->p_Rchild;
	}
	else
	{
		sibling = parent->p_Lchild;
	}
	node* pL = p->p_Lchild;
	node* pR = p->p_Rchild;
	node* sL = sibling->p_Lchild;
	node* sR = sibling->p_Rchild;
	bool pLcolor, pRcolor, pcolor;
	if (pL != nullptr)
	{
		pLcolor = pL->color;
	}
	else
	{
		pLcolor = false;
	}
	if (pR != nullptr)
	{
		pRcolor = pR->color;
	}
	else
	{
		pRcolor = false;
	}
	if (p != nullptr)
	{
		pcolor = p->color;
	}
	else
	{
		pcolor = false;
	}
	if (pRcolor != true && pLcolor != true)
	{
		if (p == parent->p_Lchild)
		{
			parent->p_Lchild = nullptr;
			if (pL != nullptr)
			{
				pL->p_parent = parent;
				parent->p_Lchild = pL;
			}
			if (pR != nullptr)
			{
				pR->p_parent = parent;
				parent->p_Lchild = pR;
			}
		}
		else
		{
			parent->p_Rchild = nullptr;
			if (pL != nullptr)
			{
				pL->p_parent = parent;
				parent->p_Rchild = pL;
			}
			if (pR != nullptr)
			{
				pR->p_parent = parent;
				parent->p_Rchild = pR;
			}
		}
		p->p_Lchild = nullptr;
		p->p_Rchild = nullptr;
		p->p_parent = nullptr;
	}
	sibling->color = true;
	parent->color = false;
}
void tree::delete_2A(node* p)
{
	if (p == root)
	{
		return;
	}
	node* parent = p->p_parent;
	node* sibling = nullptr;
	if (p == parent->p_Lchild)
	{
		sibling = parent->p_Rchild;
	}
	else
	{
		sibling = parent->p_Lchild;
	}
	node* pL = p->p_Lchild;
	node* pR = p->p_Rchild;
	node* sL = sibling->p_Lchild;
	node* sR = sibling->p_Rchild;
	bool pLcolor, pRcolor, pcolor;
	if (pL != nullptr)
	{
		pLcolor = pL->color;
	}
	else
	{
		pLcolor = false;
	}
	if (pR != nullptr)
	{
		pRcolor = pR->color;
	}
	else
	{
		pRcolor = false;
	}
	if (p != nullptr)
	{
		pcolor = p->color;
	}
	else
	{
		pcolor = false;
	}
	if (pRcolor != true && pLcolor != true)
	{
		if (p == parent->p_Lchild)
		{
			parent->p_Lchild = nullptr;
			if (pL != nullptr)
			{
				pL->p_parent = parent;
				parent->p_Lchild = pL;
			}
			if (pR != nullptr)
			{
				pR->p_parent = parent;
				parent->p_Lchild = pR;
			}
		}
		else
		{
			parent->p_Rchild = nullptr;
			if (pL != nullptr)
			{
				pL->p_parent = parent;
				parent->p_Rchild = pL;
			}
			if (pR != nullptr)
			{
				pR->p_parent = parent;
				parent->p_Rchild = pR;
			}
		}
		p->p_Lchild = nullptr;
		p->p_Rchild = nullptr;
		p->p_parent = nullptr;
	}
	sibling->color = true;
	parent->color = false;
	p = parent;
	if (p == root)
	{
		return;
	}
	parent = p->p_parent;
	sibling = nullptr;
	if (p == parent->p_Lchild)
	{
		sibling = parent->p_Rchild;
	}
	else
	{
		sibling = parent->p_Lchild;
	}
	pL = p->p_Lchild;
	pR = p->p_Rchild;
	sL = sibling->p_Lchild;
	sR = sibling->p_Rchild;
	bool sLcolor, sRcolor, scolor;
	if (sL != nullptr)
	{
		sLcolor = sL->color;
	}
	else
	{
		sLcolor = false;
	}
	if (sR != nullptr)
	{
		sRcolor = sR->color;
	}
	else
	{
		sRcolor = false;
	}
	if (sibling != nullptr)
	{
		scolor = sibling->color;
	}
	else
	{
		scolor = false;
	}

	if (scolor == false)
	{
		if (sLcolor == true || sRcolor == true)
		{
			delete_1(p);
			return;
		}
		if (sLcolor == false && sRcolor == false)
		{
			if (parent->color == false)
			{
				delete_2A(p);
				return;
			}
			else
			{
				delete_2B(p);
				return;
			}
		}
	}
	else
	{
		delete_3(p);
		return;
	}

}

void tree::delete_1_R_rotate(node* p)
{
	node* higher = p->p_parent;
	node* L = p->p_Lchild;

	node* q = L->p_Rchild;
	if (p == root)
	{

		p->p_parent = L;
		L->p_Rchild = p;
		if (q != nullptr)
		{
			p->p_Lchild = q;
			q->p_parent = p;
		}
		else
		{
			p->p_Lchild = nullptr;
		}
		L->p_parent = nullptr;
		root = L;


	}
	else
	{
		if (higher->p_Lchild == p)
		{
			higher->p_Lchild = L;
		}
		else
		{
			higher->p_Rchild = L;
		}

		L->p_parent = higher;
		L->p_Rchild = p;
		p->p_parent = L;
		//p->p_Lchild = nullptr;

		if (q != nullptr)
		{
			p->p_Lchild = q;
			q->p_parent = p;
		}
		else
		{
			p->p_Lchild = nullptr;
		}
	}
}
void tree::delete_1_L_rotate(node* p)
{
	node* higher = p->p_parent;
	node* R = p->p_Rchild;

	node* q = R->p_Lchild;
	if (p == root)
	{
		p->p_parent = R;
		R->p_Lchild = p;
		if (q != nullptr)
		{
			p->p_Rchild = q;
			q->p_parent = p;
		}
		else
		{
			p->p_Rchild = nullptr;
		}
		R->p_parent = nullptr;
		root = R;

	}
	else
	{
		if (higher->p_Lchild == p)
		{
			higher->p_Lchild = R;
		}
		else
		{
			higher->p_Rchild = R;
		}
		R->p_parent = higher;
		R->p_Lchild = p;
		p->p_parent = R;
		//p->p_Rchild = nullptr;

		if (q != nullptr)
		{
			p->p_Rchild = q;
			q->p_parent = p;
		}
		else
		{
			p->p_Rchild = nullptr;
		}

	}
}

void tree::delete_1(node* p)
{
	if (p == root)
	{
		return;
	}
	node* parent = p->p_parent;
	node* sibling = nullptr;
	if (p == parent->p_Lchild)
	{
		sibling = parent->p_Rchild;
	}
	else
	{
		sibling = parent->p_Lchild;
	}
	node* pL = p->p_Lchild;
	node* pR = p->p_Rchild;
	node* sL = sibling->p_Lchild;
	node* sR = sibling->p_Rchild;
	bool pLcolor, pRcolor, pcolor;
	if (pL != nullptr)
	{
		pLcolor = pL->color;
	}
	else
	{
		pLcolor = false;
	}
	if (pR != nullptr)
	{
		pRcolor = pR->color;
	}
	else
	{
		pRcolor = false;
	}
	if (p != nullptr)
	{
		pcolor = p->color;
	}
	else
	{
		pcolor = false;
	}
	if (pRcolor != true && pLcolor != true)
	{
		if (p == parent->p_Lchild)
		{
			parent->p_Lchild = nullptr;
			if (pL != nullptr)
			{
				pL->p_parent = parent;
				parent->p_Lchild = pL;
			}
			if (pR != nullptr)
			{
				pR->p_parent = parent;
				parent->p_Lchild = pR;
			}
		}
		else
		{
			parent->p_Rchild = nullptr;
			if (pL != nullptr)
			{
				pL->p_parent = parent;
				parent->p_Rchild = pL;
			}
			if (pR != nullptr)
			{
				pR->p_parent = parent;
				parent->p_Rchild = pR;
			}
		}
		p->p_Lchild = nullptr;
		p->p_Rchild = nullptr;
		p->p_parent = nullptr;
	}


	if (sR != nullptr && sR->color == true)
	{
		if (sibling == parent->p_Rchild)
		{
			sR->color = false;
			sibling->color = parent->color;
			parent->color = false;
			delete_1_L_rotate(parent);
			//rr pattern
		}
		else
		{
			sR->color = false;
			sibling->color = parent->color;
			parent->color = false;
			delete_1_L_rotate(sibling);
			delete_1_R_rotate(parent);
			//lr pattern
		}
	}
	else
	{
		if (sibling == parent->p_Lchild)
		{
			sL->color = false;
			sibling->color = parent->color;
			parent->color = false;
			delete_1_R_rotate(parent);//ll pattern
		}
		else
		{
			sL->color = false;
			sibling->color = parent->color;
			parent->color = false;
			delete_1_R_rotate(sibling);
			delete_1_L_rotate(parent);
			//rl pattern
		}
	}
}


void tree::delete_node(int i)
{
	node* p = root;

	if (root == nullptr)
	{
		return;
	}
	if (root->p_Lchild == nullptr && root->p_Rchild == nullptr)
	{
		if (root->value == i)
		{
			root = nullptr;
		}
		return;
	}
	node* findp = root;

	while (findp != nullptr)
	{


		if (i > findp->value)
		{

			findp = findp->p_Rchild;
		}
		else if (i < findp->value)
		{
			findp = findp->p_Lchild;
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

	node* parent = findp->p_parent;

	node* L = findp->p_Lchild;
	node* R = findp->p_Rchild;
	node* child = nullptr;
	if (R != nullptr && L != nullptr)
	{
		node* predecessor = findp->p_Lchild;
		if (predecessor != nullptr)
		{
			while (predecessor->p_Rchild != nullptr)
			{
				predecessor = predecessor->p_Rchild;
			}
		}
		node* sucessor = findp->p_Rchild;
		if (sucessor != nullptr)
		{
			while (sucessor->p_Lchild != nullptr)
			{
				sucessor = sucessor->p_Lchild;
			}
		}
		node* preparent = predecessor->p_parent;
		node* prel = predecessor->p_Lchild;
		node* prer = predecessor->p_Rchild;
		node* sucprent = sucessor->p_parent;
		node* sucl = sucessor->p_Lchild;
		node* sucr = sucessor->p_Rchild;
		node* ANparent = findp->p_parent;
		node* ANl = findp->p_Lchild;
		node* ANr = findp->p_Rchild;
		if (predecessor != nullptr)
		{
			findp->value = predecessor->value;
			findp = predecessor;
		}
		else
		{
			findp->value = sucessor->value;
			findp = sucessor;
		}


	}
	parent = findp->p_parent;
	L = findp->p_Lchild;
	R = findp->p_Rchild;
	child = nullptr;

	if (L == nullptr && R != nullptr)
	{
		child = R;
	}
	else if (R == nullptr && L != nullptr)
	{
		child = L;
	}


	if (findp->p_Lchild == nullptr && findp->p_Rchild == nullptr && findp->color == true)
	{
		node* findparent = findp->p_parent;
		if (findp == findparent->p_Lchild)
		{
			findparent->p_Lchild = nullptr;
		}
		else
		{
			findparent->p_Rchild = nullptr;
		}
		findp->p_parent = nullptr;
		return;
	}



	if (child != nullptr && child->p_Lchild == nullptr && child->p_Rchild == nullptr)
	{
		if (findp->color != child->color)
		{
			findp->p_parent = nullptr;
			findp->p_Lchild = nullptr;
			findp->p_Rchild = nullptr;
			if (findp == root)
			{
				child->p_parent = nullptr;
				root = child;
			}
			else
			{

				child->p_parent = parent;
				if (findp == parent->p_Lchild)
				{
					parent->p_Lchild = child;
				}
				else if (findp == parent->p_Rchild)
				{
					parent->p_Rchild = child;
				}
			}
			child->color = false;
			return;
		}
	}

	node* sibling = nullptr;
	if (findp == parent->p_Lchild)
	{
		sibling = parent->p_Rchild;
	}
	else
	{
		sibling = parent->p_Lchild;
	}
	node* sL = sibling->p_Lchild;
	node* sR = sibling->p_Rchild;
	bool sLcolor, sRcolor, scolor;
	if (sL != nullptr)
	{
		sLcolor = sL->color;
	}
	else
	{
		sLcolor = false;
	}
	if (sR != nullptr)
	{
		sRcolor = sR->color;
	}
	else
	{
		sRcolor = false;
	}
	if (sibling != nullptr)
	{
		scolor = sibling->color;
	}
	else
	{
		scolor = false;
	}



	if (scolor == false)
	{
		if (sLcolor == true || sRcolor == true)
		{
			delete_1(findp);
			return;
		}
		if (sLcolor == false && sRcolor == false)
		{
			if (parent->color == false)
			{
				delete_2A(findp);
				return;
			}
			else
			{
				delete_2B(findp);
				return;
			}
		}
	}
	else
	{
		delete_3(findp);
		return;
	}

}



void tree::insert_node(int i)
{
	node* inode = new node(i);
	inode->color = true;
	if (root == nullptr)
	{
		root = inode;
		root->color = false;
		return;
	}

	node* parent = root;
	node* findp = root;

	while (findp != nullptr)
	{
		parent = findp;

		if (inode->value >= findp->value)
		{

			findp = findp->p_Rchild;
		}
		else
		{
			findp = findp->p_Lchild;
		}

	}

	inode->p_parent = parent;
	if (inode->value >= parent->value)
	{

		parent->p_Rchild = inode;
	}
	else
	{
		parent->p_Lchild = inode;

	}
	node* uncle = nullptr;
	node* grand = nullptr;
	while (inode != root)
	{
		if (inode == nullptr)
		{
			return;
		}
		parent = inode->p_parent;
		grand = parent->p_parent;
		if (parent->color == true)
		{
			if (grand->p_Rchild == parent)
			{
				uncle = grand->p_Lchild;
			}
			else
			{
				uncle = grand->p_Rchild;
			}
			if (uncle == nullptr || uncle->color == false)
			{
				if (inode == parent->p_Rchild && parent == grand->p_Lchild)
				{
					insert_L_rotate(parent);
					inode = inode->p_Lchild;
				}
				else if (inode == parent->p_Lchild && parent == grand->p_Rchild)
				{
					insert_R_rotate(parent);
					inode = inode->p_Rchild;
				}
				parent = inode->p_parent;
				grand = parent->p_parent;
				if (inode == parent->p_Lchild)
				{
					insert_R_rotate(grand);
				}
				else
				{
					insert_L_rotate(grand);
				}
				parent->color = false;
				grand->color = true;

				root->color = false;

			}
			else if (uncle->color == true)
			{
				uncle->color = false;
				parent->color = false;
				grand->color = true;
			}

		}
		parent = inode->p_parent;

		grand = parent->p_parent;
		inode = grand;



		root->color = false;
	}
}
void tree::InorderPrint(node* p)
{

	if (p == nullptr)
	{
		return;
	}

	InorderPrint(p->p_Lchild);
	cout << "(" << p->value << "," << p->color << ") ";
	InorderPrint(p->p_Rchild);
}
void tree::PostorderPrint(node* p)
{
	if (p == nullptr)
	{
		return;
	}
	PostorderPrint(p->p_Lchild);
	PostorderPrint(p->p_Rchild);
	cout << "(" << p->value << "," << p->color << ") ";
}
void tree::PreorderPrint(node* p)
{
	if (p == nullptr)
	{
		return;
	}
	cout << "(" << p->value << "," << p->color << ") ";
	PostorderPrint(p->p_Lchild);
	PostorderPrint(p->p_Rchild);
}

void tree::insert_R_rotate(node* p)
{
	node* higher = p->p_parent;
	node* L = p->p_Lchild;

	node* q = L->p_Rchild;
	if (p == root)
	{

		p->p_parent = L;
		L->p_Rchild = p;
		if (q != nullptr)
		{
			p->p_Lchild = q;
			q->p_parent = p;
		}
		else
		{
			p->p_Lchild = nullptr;
		}
		L->p_parent = nullptr;
		root = L;


	}
	else
	{
		if (higher->p_Lchild == p)
		{
			higher->p_Lchild = L;
		}
		else
		{
			higher->p_Rchild = L;
		}

		L->p_parent = higher;
		L->p_Rchild = p;
		p->p_parent = L;
		//p->p_Lchild = nullptr;

		if (q != nullptr)
		{
			p->p_Lchild = q;
			q->p_parent = p;
		}
		else
		{
			p->p_Lchild = nullptr;
		}
	}
}
void tree::insert_L_rotate(node* p)
{
	node* higher = p->p_parent;
	node* R = p->p_Rchild;

	node* q = R->p_Lchild;
	if (p == root)
	{
		p->p_parent = R;
		R->p_Lchild = p;
		if (q != nullptr)
		{
			p->p_Rchild = q;
			q->p_parent = p;
		}
		else
		{
			p->p_Rchild = nullptr;
		}
		R->p_parent = nullptr;
		root = R;

	}
	else
	{
		if (higher->p_Lchild == p)
		{
			higher->p_Lchild = R;
		}
		else
		{
			higher->p_Rchild = R;
		}
		R->p_parent = higher;
		R->p_Lchild = p;
		p->p_parent = R;
		//p->p_Rchild = nullptr;

		if (q != nullptr)
		{
			p->p_Rchild = q;
			q->p_parent = p;
		}
		else
		{
			p->p_Rchild = nullptr;
		}

	}
}
/*
void tree::tr(node* p)
{
	if (p == nullptr)
	{
		return;
	}

	tr(p->p_Lchild);
	if (p->value == 50|| p->value == 20)
	{
		p->color = true;
	}

	else
	{
		p->color = false;
	}
	tr(p->p_Rchild);
}
*/

int main()
{
	tree T;

	T.insert_node(100);

	T.insert_node(50);
	T.insert_node(200);
	T.insert_node(30);
	T.insert_node(70);
	T.insert_node(150);
	T.insert_node(300);
	T.insert_node(20);
	T.insert_node(40);
	T.insert_node(60);
	T.insert_node(80);
	T.insert_node(120);
	T.insert_node(180);
	T.insert_node(250);
	T.insert_node(400);
	T.insert_node(10);
	T.insert_node(25);
	T.insert_node(35);
	T.insert_node(45);
	T.insert_node(55);
	T.insert_node(65);
	T.insert_node(75);
	T.insert_node(90);
	T.insert_node(5);
	T.insert_node(12);
	T.insert_node(23);
	T.insert_node(28);


	//T.tr(T.root);
	T.InorderPrint(T.root);
	//T.delete_node(400);
	//T.delete_node(50);
	cout << endl;
	T.delete_node(200);
	T.InorderPrint(T.root);
	cout << endl;
	T.PostorderPrint(T.root);
	cout << endl;
	T.PreorderPrint(T.root);
	getchar();
	getchar();
	return 0;
}
/* example 2&3
T.insert_node(100);

T.insert_node(50);
T.insert_node(200);
T.insert_node(30);
T.insert_node(80);
T.insert_node(150);
T.insert_node(300);
T.insert_node(20);
T.insert_node(40);
T.insert_node(60);
T.insert_node(90);
T.insert_node(120);
T.insert_node(180);
T.insert_node(10);
T.insert_node(25);

T.tr(T.root);
T.InorderPrint(T.root);
//T.delete_node(400);
//T.delete_node(50);
cout << endl;
T.delete_node(100);
T.InorderPrint(T.root);*/