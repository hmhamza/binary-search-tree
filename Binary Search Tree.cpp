#include <iostream>
using namespace std;

struct Node_Tree{
	int data;
	Node_Tree *left;
	Node_Tree *right;
};

struct Node_Queue{
	Node_Tree *data_Node;
	Node_Queue *next;
};

class Queue{

	Node_Queue dummyHead;			//dummy head Node_Queue
	Node_Queue *tail;
	int no_of_elements;

public:
	Queue(){
		dummyHead.next = nullptr;
		tail = &dummyHead;
		no_of_elements = 0;
	}

	bool isEmpty(){
		return (dummyHead.next == nullptr);
	}

	bool enqueue(Node_Tree *obj){
		Node_Queue *temp = new Node_Queue;
		temp->data_Node = obj;
		temp->next = nullptr;
		tail->next = temp;
		tail = temp;
		no_of_elements++;
		return true;
	}

	bool dequeue(Node_Tree *&n){
		if (isEmpty())
			return false;
		else{
			Node_Queue *temp = dummyHead.next;
			if (temp == tail)
				tail = &dummyHead;
			n = temp->data_Node;
			dummyHead.next = temp->next;
			delete temp;
			return true;
		}
	}

	~Queue(){
		Node_Tree *n;
		while (!isEmpty())
			dequeue(n);
		tail = nullptr;
	}
};

class BinarySearchTree{
	Node_Tree *root;

public:

	BinarySearchTree(){
		root = nullptr;
	}

	BinarySearchTree(int x){
		Node_Tree *newNode = new Node_Tree;
		newNode->data = x;
		newNode->left = nullptr;
		newNode->right = nullptr;
		root = newNode;
	}

	BinarySearchTree(BinarySearchTree &obj){
		root = copyTree(obj.root);
	}

	Node_Tree* copyTree(Node_Tree *n){
		if (n == nullptr)
			return nullptr;
		Node_Tree *left = copyTree(n->left);
		Node_Tree *right = copyTree(n->right);
		Node_Tree *newNode = new Node_Tree;
		newNode->data = n->data;
		newNode->left = left;
		newNode->right = right;
		return newNode;
	}

	Node_Tree* search(int key){
		Node_Tree *curr = root;
		while (curr != nullptr){
			if (curr->data == key)
				return curr;
			else if (key<curr->data)
				curr = curr->left;
			else
				curr = curr->right;
		}
		return nullptr;
	}

	void insert(int n){
		Node_Tree *newNode = new Node_Tree;
		newNode->data = n;
		newNode->left = nullptr;
		newNode->right = nullptr;

		if (root == nullptr)
			root = newNode;
		else{
			Node_Tree *curr = root;
			while (1){
				if (n<curr->data)
				if (curr->left == nullptr)
					break;
				else
					curr = curr->left;
				else
				if (curr->right == nullptr)
					break;
				else
					curr = curr->right;
			}
			if (curr->left == nullptr)
				curr->left = newNode;
			else
				curr->right = newNode;
		}
	};

	bool deleteNode(int x){
		Node_Tree *del = search(x);
		if (del == nullptr)
			return false;
		Node_Tree *curr = del;
		if (curr->right->left != nullptr){
			curr = curr->right;
			while (curr->left->left != nullptr)
				curr = curr->left;
			del->data = curr->left->data;
			delete curr->left;
			curr->left = nullptr;
		}
		else{
			del->data = curr->right->data;
			delete curr->right;
			curr->right = nullptr;
		}
		return true;
	}

	void print_InOrder(){
		cout << "\t\t\tIn-Order Printing\n\n";
		recursion_printInOrder(root);
	}

	void recursion_printInOrder(Node_Tree *n){
		if (n == nullptr)
			return;
		recursion_printInOrder(n->left);
		cout << n->data << endl;
		recursion_printInOrder(n->right);
	}

	void print_PreOrder(){
		cout << "\t\t\tPre-Order Printing\n\n";
		recursion_printPreOrder(root);
	}

	void recursion_printPreOrder(Node_Tree *n){
		if (n == nullptr)
			return;
		cout << n->data << endl;
		recursion_printPreOrder(n->left);
		recursion_printPreOrder(n->right);
	}

	void print_PostOrder(){
		cout << "\t\t\tPost-Order Printing\n\n";
		recursion_printPostOrder(root);
	}

	void recursion_printPostOrder(Node_Tree *n){
		if (n == nullptr)
			return;
		recursion_printPostOrder(n->left);
		recursion_printPostOrder(n->right);
		cout << n->data << endl;
	}

	void print_LevelOrder(){
		cout << "\t\t\tLevel-Order Printing\n\n";
		Queue obj;
		obj.enqueue(root);
		Node_Tree *curr;
		while (!obj.isEmpty()){
			obj.dequeue(curr);
			cout << curr->data << endl;
			if (curr->left != nullptr)
				obj.enqueue(curr->left);
			if (curr->right != nullptr)
				obj.enqueue(curr->right);
		}
	}

	bool check_Equivalance(BinarySearchTree obj){
		cout << "\t\t\tCHECKING EQUIVALANCE\n\n";
		if (recursion_checkEquivalance(this->root, obj.root))
			return true;
		else
			return false;
	}

	bool recursion_checkEquivalance(Node_Tree *n1, Node_Tree *n2){
		if (n1->left == nullptr && n1->right == nullptr && n2->left == nullptr && n2->right == nullptr)
			return true;
		if ((n1->left == n1->right && n2->left != n2->right) || (n2->left == n2->right && n1->left != n1->right)) //here n1->left==n1->right means that both are nullptr
			return false;
		if (n1->data != n2->data)
			return false;
		if (!recursion_checkEquivalance(n1->left, n2->left))
			return false;
		if (!recursion_checkEquivalance(n1->right, n2->right))
			return false;
	}

	~BinarySearchTree(){
		recursion_Destructor(root);
	}

	void recursion_Destructor(Node_Tree *n){
		if (n->left == nullptr && n->right == nullptr){
			delete n;
			n = nullptr;
			return;
		}
		if (n->left != nullptr)
			recursion_Destructor(n->left);
		if (n->right != nullptr)
			recursion_Destructor(n->right);
		delete n;
		n = nullptr;
	}

};

