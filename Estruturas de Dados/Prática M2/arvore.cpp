#include <iostream>

struct WorkerNode {
	std::string cargo;
	double salario;
	WorkerNode* left;
	WorkerNode* right;
	
	WorkerNode(std::string cargo, double salario) : cargo(cargo), salario(salario), left(nullptr), right(nullptr) {}
};

struct Update {
	std::string cargo;
	double salario;
	
	Update(std::string cargo, double salario) : cargo(cargo), salario(salario) {}
};

void updateTree(WorkerNode* node, Update updates[5]) {
	if (node == nullptr) return;

	for (int i = 0; i < 5; i++) {
		if (updates[i].cargo == node->cargo) {
			node->salario = updates[i].salario;
		}
	}
	
	updateTree(node->left, updates);
	updateTree(node->right, updates);
}

void printTree(WorkerNode* node) {
	if (node == nullptr) return;
	std::cout << node->cargo << ", " << node->salario << "\n";
	
	printTree(node->left);
	printTree(node->right);
}

int main() {
	WorkerNode* a = new WorkerNode("testador", 0);
	WorkerNode* b = new WorkerNode("programador", 10);
	WorkerNode* raiz = new WorkerNode("cientista", 20);
	WorkerNode* c = new WorkerNode("pesquisador", 15);
	WorkerNode* d = new WorkerNode("designer", -5);
	
	raiz->left = a;
	raiz->right = b;
	
	b->left = c;
	b->right = d;
	
	Update updates[] = {Update("testador", 20), Update("cientista", 1000), Update("pesquisador", 900), Update("designer", -99), Update("programador", 400)};
	updateTree(raiz, updates);
	printTree(raiz);
}