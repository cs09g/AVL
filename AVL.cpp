// 노드 삽입때마다 inorder결과 출력
// 트리깊이도 같이 출력, 회전이 필요한 경우에는 회전의 유형(LL LR RR RL)을 표시.
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

Node *getTreeNode(); // 노드 생성 함수
Node *insertAVL(Node *, KEYTYPE n_key); // AVL 트리 삽입함수
Node *rotateLL(Node *);
Node *rotateLR(Node *);
Node *rotateRR(Node *);
Node *rotateRL(Node *);
Node *balanceFactor(Node *); // 
Node *findRoot(Node *); // 최상위 노드를 찾는 함수
void Inorder(Node *); // inorder 결과 출력함수
int countDepth(Node *B); // 깊이 구하는 함수

int R; // 회전 유형을 나타내기위한 상수
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
	// 트리가 비어있으면 새로 생성
	if (B == NULL){
		B = getTreeNode();
		B->k = n_key;
		B->left = NULL;
		B->right = NULL;
	}
	// 새 키값이 노드의 키 값보다 크면 오른쪽에 삽입
	else if (n_key > B->k){
		B->right = insertAVL(B->right, n_key);
		// bf를 비교해서 회전을 결정
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
	// 좌우 자식 노드의 차이를 통해 bf를 구한다.
	int bf = countDepth(B->left) - countDepth(B->right);
	int c_bf;
	// bf가 1보다 크면 왼쪽 트리의 깊이가 깊으므로, 
	// 왼쪽 자식의 bf를 구한다.
	if (bf > 1){
		c_bf = countDepth(B->left->left) - countDepth(B->left->right);
		// 왼쪽 자식의 bf가 쏠린 방향에 따라 LL, LR 회전을 한다.
		if (c_bf > 0){
			R = LL; B = rotateLL(B);
		}
		else{
			R = LR; B = rotateLR(B);
		}
	}
	// bf가 -1보다 작으면 오른쪽 트리의 깊이가 깊으므로,
	// 오른쪽 자식의 bf를 구한다.
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