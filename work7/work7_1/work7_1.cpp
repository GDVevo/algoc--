#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
	int value;
	vector<Node*> children;
	Node(int value) : value(value) {}
};


// рекурсивная часть, сделано через string из-за проблем с цифрой 0
vector<string> rec_part(Node* node) {
	vector<string> nums;
	if (node->children.empty()) nums.push_back(to_string(node->value));
	else {
		for (int i = 0; i < node->children.size(); i++) {
			vector<string> result = rec_part(node->children[i]);
			for (int n = 0; n < result.size();n++) {
				nums.push_back(to_string(node->value) + result[n]);
			}
		}
	}
	return nums;
}

int function(Node* root) {
	int summ = 0;
	vector<string> numbers;
	numbers = rec_part(root);
	for (int i = 0; i < numbers.size(); i++) {
		summ += stoi(numbers[i]);
	}
	return summ;
}

// создание графа из числа (одного), для unit-теста
Node* create_node(string num, Node *parent = nullptr) {
	if (parent == nullptr) {
		reverse(num.begin(), num.end());
	}
	int val = num[num.size() - 1] - '0';
	Node* result = new Node(val);
	num = num.substr(0, num.size()-1);
	if (num.size() > 0) {
		result->children.push_back(create_node(num, result));
		return result;
	}
	else return result;	
}

int main() {
	Node root(1);
	Node l1(3);
	Node r1(5);
	root.children = { &l1, &r1 };
	cout << "example 1: " << function(&root) << endl;
	root.children.clear();
	l1.value = 2;
	r1.value = 3;
	Node l2(2);
	Node r2(1);
	root.children = { &l1, &r1 };
	r1.children = { &l2, &r2 };
	cout << "example 2: " << function(&root) << endl;
	return 0;
}