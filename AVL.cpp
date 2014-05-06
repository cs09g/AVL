// ��� ���Զ����� inorder��� ���
// Ʈ�����̵� ���� ���, ȸ���� �ʿ��� ��쿡�� ȸ���� ����(LL LR RR RL)�� ǥ��.
#include <iostream>
#include <string>
#define KEYTYPE string
using namespace std;
class Node{
public:
	KEYTYPE k; 
	Node *left, *right;
};
typedef Node Node;
enum R_type{ LL, LR, RR, RL };
KEYTYPE in[] = { "k", "o", "m", "i", "n", "u", "v", "e", "r", "s", "t", "y", "c", "d", "a", "b" };

Node *getTreeNode(); // ��� ���� �Լ�
Node *insertAVL(Node *, KEYTYPE n_key); // AVL Ʈ�� �����Լ�
Node *rotateLL(Node *);
Node *rotateLR(Node *);
Node *rotateRR(Node *);
Node *rotateRL(Node *);
Node *balanceFactor(Node *); // 
Node *findRoot(Node *); // �ֻ��� ��带 ã�� �Լ�
void Inorder(Node *); // inorder ��� ����Լ�
int countDepth(Node *B); // ���� ���ϴ� �Լ�

int R; // ȸ�� ������ ��Ÿ�������� ���
void main()
{
	Node *Tree=NULL;
	for (int i = 0; i < sizeof(in) / sizeof(in[0]); i++){
		R = 4; 
		Tree = insertAVL(Tree, in[i]);
		cout << "in " << in[i] <<" : "; Inorder(Tree);
		cout << "/ depth : " << countDepth(Tree);
		switch (R){ 
		case LL: cout << " / rotation " << "LL"; break;
		case LR: cout << " / rotation " << "LR"; break;
		case RR: cout << " / rotation " << "RR"; break;
		case RL: cout << " / rotation " << "RL"; break;
		default: break;
		}
		cout << endl;
	}
}
Node *getTreeNode()
{
	Node *newNode = new Node[sizeof(Node)];
	return newNode;
}
Node *insertAVL(Node *B, KEYTYPE n_key)
{
	// Ʈ���� ��������� ���� ����
	if (B == NULL){
		B = getTreeNode();
		B->k = n_key;
		B->left = NULL;
		B->right = NULL;
	}
	// �� Ű���� ����� Ű ������ ũ�� �����ʿ� ����
	else if (n_key > B->k){
		B->right = insertAVL(B->right, n_key);
		// bf�� ���ؼ� ȸ���� ����
		B = balanceFactor(B);
	}
	else{
		B->left = insertAVL(B->left, n_key);
		B = balanceFactor(B);
	}
	return B;
}
Node *rotateLL(Node *parent)
{
	Node *child = parent->left;
	parent->left = child->right;
	child->right = parent;
	return child;
}
Node *rotateLR(Node *parent)
{
	Node *child = parent->left;
	parent->left = rotateRR(child);
	return rotateLL(parent);
}
Node *rotateRR(Node *parent)
{
	Node *child = parent->right;
	parent->right = child->left;
	child->left = parent;
	return child;
}
Node *rotateRL(Node *parent)
{
	Node *child = parent->right;
	parent->right = rotateLL(child);
	return rotateRR(parent);
}
Node *balanceFactor(Node *B)
{
	// �¿� �ڽ� ����� ���̸� ���� bf�� ���Ѵ�.
	int bf = countDepth(B->left) - countDepth(B->right);
	int c_bf;
	// bf�� 1���� ũ�� ���� Ʈ���� ���̰� �����Ƿ�, 
	// ���� �ڽ��� bf�� ���Ѵ�.
	if (bf > 1){
		c_bf = countDepth(B->left->left) - countDepth(B->left->right);
		// ���� �ڽ��� bf�� �� ���⿡ ���� LL, LR ȸ���� �Ѵ�.
		if (c_bf > 0){
			R = LL; B = rotateLL(B);
		}
		else{
			R = LR; B = rotateLR(B);
		}
	}
	// bf�� -1���� ������ ������ Ʈ���� ���̰� �����Ƿ�,
	// ������ �ڽ��� bf�� ���Ѵ�.
	else if (bf < -1){
		c_bf = countDepth(B->right->left) - countDepth(B->right->right);
		if (c_bf > 0){ 
			R = RL; B = rotateRL(B);
		}
		else{
			R = RR; B = rotateRR(B); 
		}
	}
	return B;
}
void Inorder(Node *B)
{
	if (B == NULL) return;
	Inorder(B->left);
	cout << B->k << ' ';
	Inorder(B->right);
}
int countDepth(Node *B)
{
	int depth = 0;
	if (B != NULL){
		if (countDepth(B->left) > countDepth(B->right)) 
			depth = 1 + countDepth(B->left);
		else 
			depth = 1 + countDepth(B->right);
	}
	return depth;
}