
#include <iostream>
#include <limits>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Функция для проверки, является ли дерево BST
bool isBST(Node* node, int min = numeric_limits<int>::min(), int max = numeric_limits<int>::max()) {
    // Если узел пустой, он является BST
    if (node == nullptr) {
        return true;
    }

    // Проверяем, что значение текущего узла находится в пределах min и max
    if (node->data <= min || node->data >= max) {
        return false;
    }

    // Рекурсивно проверяем левое и правое поддеревья
    return isBST(node->left, min, node->data) && isBST(node->right, node->data, max);
}

int main() {
    setlocale(LC_ALL, "ru");
    // Пример создания дерева
    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(3);
    root->left->right = new Node(7);
    root->right->left = new Node(99);
    root->right->right = new Node(25);

    if (isBST(root)) {
        cout << "Дерево является BST." << endl;
    }
    else {
        cout << "Дерево не является BST." << endl;
    }

    return 0;
}
