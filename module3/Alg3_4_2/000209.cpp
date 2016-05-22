#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct AVLNode {
    int key;
    int height;
    int size;
    AVLNode *left;
    AVLNode *right;

    AVLNode() : key(0), height(1), size(1), left(NULL), right(NULL) { }

    AVLNode(int key) : key(key), height(1), size(1), left(NULL), right(NULL) { }
};

class AVLTree {
private:
    AVLNode *root;

    int getHeight(AVLNode *root) const;

    int getSize(AVLNode *root) const;

    int getBalanceFactor(AVLNode *root) const;

    void rotateLeft(AVLNode *&a);

    void rotateRight(AVLNode *&a);

    void balanceTree(AVLNode *&root);

    void print(AVLNode *root) const;

    void add(int key, AVLNode *&root);

    void removeNode(AVLNode *root);

    AVLNode *minNode(AVLNode *root) const;

    void remove(int key, AVLNode *&root);

    int findOrderStat(int k, AVLNode *root) const;

public:
    AVLTree() : root(NULL) { }

    ~AVLTree() {
        removeNode(root);
    }

    void Print() const {
        print(root);
        cout << endl;
    }

    void Add(int key) {
        add(key, root);
    }

    void Remove(int key) {
        remove(key, root);
    }

    int findOrderStat(int k) const {
        return findOrderStat(k + 1, root);
    }
};

int AVLTree::findOrderStat(int k, AVLNode *root) const {
    if (k == getSize(root->left) + 1) {
        return root->key;
    } else if (k < getSize(root->left) + 1) {
        findOrderStat(k, root->left);
    } else {
        findOrderStat(k - getSize(root->left) - 1, root->right);
    }
}

int AVLTree::getHeight(AVLNode *root) const {
    if (root == NULL)
        return 0;
    return root->height;
}

int AVLTree::getSize(AVLNode *root) const {
    if (root == NULL)
        return 0;
    return root->size;
}

//Разность между высотой левого и правого дерева
int AVLTree::getBalanceFactor(AVLNode *root) const {
    if (root == NULL)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

/*              a                      b
               / \                    / \
              L  b     ------>       a  R
                / \                 / \
               C  R                L  C
 */
void AVLTree::rotateLeft(AVLNode *&a) {
    AVLNode *b = a->right;
    AVLNode *C = b->left;

    b->left = a;
    a->right = C;

    a->height = std::max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = std::max(getHeight(b->left), getHeight(b->right)) + 1;

    a->size = getSize(a->left) + getSize(a->right) + 1;
    b->size = getSize(b->left) + getSize(b->right) + 1;

    a = b;

}

/*              a                      b
               / \                    / \
              b  R     ------>       L  a
             / \                       / \
            L  C                      C  R
 */
void AVLTree::rotateRight(AVLNode *&a) {
    AVLNode *b = a->left;
    AVLNode *C = b->right;

    b->right = a;
    a->left = C;

    a->height = std::max(getHeight(a->left), getHeight(a->right)) + 1;
    b->height = std::max(getHeight(b->left), getHeight(b->right)) + 1;

    a->size = getSize(a->left) + getSize(a->right) + 1;
    b->size = getSize(b->left) + getSize(b->right) + 1;

    a = b;
}


void AVLTree::balanceTree(AVLNode *&root) {
    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1) {
        if (getHeight(root->left->left) >= getHeight(root->left->right)) {
            //Правое малое вращение
            /*
             *         a                        b
             *        / \                     /  \
             *       b  R                   c    a
             *      / \     -------->      / \  / \
             *     c  C                  LL LR C  R
             *    / \
             *   LL LR
             */
            rotateRight(root);
        } else {
            //Правое большое вращение
            /*
             *         a                   a                    b
             *        / \                 / \                 /  \
             *       c  R                b  R               c    a
             *      / \     -------->   / \    ----------> / \  / \
             *     LL b                c  C              LL LR C  R
             *       / \              / \
             *      LR  C            LL LR
             */
            rotateLeft(root->left);
            rotateRight(root);
        }
    } else if (balanceFactor < -1) {
        if (getHeight(root->right->right) > getHeight(root->right->left)) {
            //Аналогичное левое малое вращение
            rotateLeft(root);
        } else {
            //Аналогичное левое большое вращение
            rotateRight(root->right);
            rotateLeft(root);
        }
    }
}

void AVLTree::print(AVLNode *root) const {
    if (root != NULL) {
        cout << root->key << " " << root->height << " " << root->size << endl;
        print(root->left);
        print(root->right);
    }
}

void AVLTree::add(int key, AVLNode *&root) {
    if (root == NULL) {
        root = new AVLNode(key);
        return;
    }

    if (key < root->key)
        add(key, root->left);
    else {
        add(key, root->right);
    }
    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
    root->size = getSize(root->left) + getSize(root->right) + 1;

    balanceTree(root);
}

void AVLTree::removeNode(AVLNode *root) {
    if (root) {
        removeNode(root->left);
        removeNode(root->right);
        delete (root);
    }
}

AVLNode *AVLTree::minNode(AVLNode *root) const {
    AVLNode *iter = root;
    while (iter->left) {
        iter = iter->left;
    }
    return iter;
}

void AVLTree::remove(int key, AVLNode *&root) {
    if (root == NULL)
        return;

    if (key < root->key) {
        remove(key, root->left);
    } else if (key > root->key) {
        remove(key, root->right);
    }

    else {
        // Один или ни одного сына
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode *tmp = root->left ? root->left : root->right;
            //Ни одного сына
            if (tmp == NULL) {
                tmp = root;
                root = NULL;
            }
                //Один сын
            else {
                *root = *tmp;
            }
            delete (tmp);
        }
            //Два сына
        else {
            AVLNode *tmp = minNode(root->right);
            root->key = tmp->key;
            remove(tmp->key, root->right);
        }
    }

    // Удалили дерево
    if (root == NULL)
        return;

    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;
    root->size = getSize(root->left) + getSize(root->right) + 1;

    balanceTree(root);
}

int main() {
    AVLTree tree;

    int size = 0;
    cin >> size;
    for (int i = 0; i < size; i++) {
        int temp1 = 0, temp2 = 0;
        cin >> temp1 >> temp2;
        if (temp1 >= 0) {
            tree.Add(temp1);
        } else {
            tree.Remove(-temp1);
        }
        cout << tree.findOrderStat(temp2) << endl;
    }
}

