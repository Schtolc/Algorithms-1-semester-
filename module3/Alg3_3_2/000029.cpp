#include <iostream>

using namespace std;

template<class T>
int getWidth(T *root, int level){

    if (root == NULL)
        return 0;
    if (level == 1)
        return 1;
    else if (level > 1)
        return getWidth(root->left, level - 1) + getWidth(root->right, level - 1);
}

template<class T>
int getHeight(T *node){
    if (node == NULL)
        return 0;
    else {
        int L = getHeight(node->left);
        int R = getHeight(node->right);
        return (L > R) ? (L + 1) : (R + 1);
    }
}

template<class T>
int maxWidth(T *root){
    int maxWidth = 0;
    int width;
    int h = getHeight(root);

    for (int i = 1; i <= h; i++) {
        width = getWidth(root, i);
        if (width > maxWidth)
            maxWidth = width;
    }

    return maxWidth;
}

template<class T>
void removeNode(T *root) {
    if (root) {
        removeNode(root->left);
        removeNode(root->right);
        delete (root);
    }
}

struct BNode {
    int key;
    BNode *left;
    BNode *right;

    BNode() : key(0), left(NULL), right(NULL) { }
    BNode(int data) : key(data), left(NULL), right(NULL) { }
};

struct TNode {
    int key;
    int priority;
    TNode *left;
    TNode *right;

    TNode() : key(0), priority(0), left(NULL), right(NULL) { }
    TNode(int x, int y, TNode *l, TNode *r) : key(x), priority(y), left(l), right(r) { }
};

class Treap {
private:
    TNode *root;

    void split(TNode *root, int key, TNode *&left, TNode *&right);
    void add(TNode *&root, int key, int priority);

public:
    Treap();
    ~Treap();
    void add(int key, int priority);
    int width() const;
    int height() const;
};

Treap::Treap() : root(NULL) { }

Treap::~Treap() {
    removeNode(root);
}

void Treap::split(TNode *root, int key, TNode *&left, TNode *&right) {
    if (root == 0) {
        left = 0;
        right = 0;
    } else if (root->key <= key) {
        split(root->right, key, root->right, right);
        left = root;
    } else {
        split(root->left, key, left, root->left);
        right = root;
    }
}

void Treap::add(int key, int priority) {
    add(root, key, priority);
}

void Treap::add(TNode *&root, int key, int priority) {
    if (!root) {
        root = new TNode(key, priority, NULL, NULL);
        return;
    }
    if (root->key <= key && root->priority >= priority) {
        add(root->right, key, priority);
    } else if (root->key > key && root->priority >= priority) {
        add(root->left, key, priority);
    } else if (root->priority < priority) {
        TNode *T1 = NULL;
        TNode *T2 = NULL;
        split(root, key, T1, T2);
        TNode *newNode = new TNode(key, priority, T1, T2);
        root = newNode;
    }
}

int Treap::width() const{
    return maxWidth(root);
}

class BTree {
private:
    BNode *root;

    void add(int data, BNode *&root);

public:
    BTree();
    ~BTree();
    void add(int data);
    int width() const;
    int height() const;

};

BTree::BTree() : root(NULL) { }

BTree::~BTree() {
    removeNode(root);
}

void BTree::add(int data) {
    add(data, root);
}

void BTree::add(int data, BNode *&root) {
    if (!root) {
        root = new BNode(data);
        return;
    }
    if (root->key <= data) {
        add(data, root->right);
    } else if (root->key > data) {
        add(data, root->left);
    }
}

int BTree::width() const{
    return maxWidth(root);
}

int main() {
    int size = 0;
    cin >> size;

    BTree tree;
    Treap treap;

    for (int i = 0; i < size; i++) {
        int tmp = 0;
        int tmp2 = 0;
        cin >> tmp >> tmp2;
        tree.add(tmp);
        treap.add(tmp, tmp2);
    }

    cout << tree.height() -treap.height() << endl;
}


int BTree::height() const {
    return getHeight(root);
}

int Treap::height() const {
    return getHeight(root);
}
