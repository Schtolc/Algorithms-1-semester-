#include <iostream>

using namespace std;

struct Node {
    int key;
    Node *left;
    Node *right;

    Node() : key(0), left(NULL), right(NULL) { }

    Node(int data) : key(data), left(NULL), right(NULL) { }

};


class BTree {
private:
    Node *root;

    void add(int data, Node *&root);

    void print(Node *root);

    void remove(Node *root);

public:
    BTree();

    ~BTree();

    void add(int data);

    void print();
};

BTree::BTree() : root(NULL) { }


BTree::~BTree() {
    remove(root);
}

void BTree::remove(Node *root) {
    if (root) {
        remove(root->left);
        remove(root->right);
        delete (root);
    }
}

void BTree::add(int data) {
    add(data, root);
}

void BTree::add(int data, Node *&root) {
    if (!root) {
        root = new Node(data);
        return;
    }
    if (root->key <= data) {
        add(data, root->right);
    } else if (root->key > data) {
        add(data, root->left);
    }
}

void BTree::print() {
    print(root);
}

void BTree::print(Node *root) {
    if (root) {
        cout << root->key << " ";
        print(root->left);
        print(root->right);
    }
}

int main() {
    int size = 0;
    cin >> size;
    BTree tree;
    for (int i = 0; i < size; i++) {
        int tmp = 0;
        cin >> tmp;
        tree.add(tmp);
    }
    tree.print();
}
