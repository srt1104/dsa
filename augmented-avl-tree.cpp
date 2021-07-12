#include <iostream>
#include <algorithm>

using namespace std;

class AVL {
private:
    struct Node {
        int key;
        int height;
        int size;
        Node *left, *right;

        Node(int _key): key{_key}, height{0}, size{1}, left{nullptr}, right{nullptr} {}
    };

    int getHeight(Node *node) {
        return node == nullptr ? -1 : node->height;
    }

    int getSize(Node *node) {
        return node == nullptr ? 0 : node->size;
    }

    void update(Node *node) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        node->size = getSize(node->left) + getSize(node->right) + 1;
    }

    Node* rotateRight(Node *x, Node *y) {
        y->left = x->right;
        x->right = y;

        update(y);
        update(x);

        return x;
    }

    Node* rotateLeft(Node *x, Node *y) {
        x->right = y->left;
        y->left = x;

        update(x);
        update(y);

        return y;
    }

    Node* insert(Node *root, int key) {
        if (root == nullptr)
            return new Node(key);

        if (key <= root->key)
            root->left = insert(root->left, key);
        else
            root->right = insert(root->right, key);

        update(root);

        int diff = getHeight(root->left) - getHeight(root->right);

        if (-1 <= diff && diff <= 1)
            return root;

        if (diff > 1) {
            Node *leftChild = root->left;
            int diffChild = getHeight(leftChild->left) - getHeight(leftChild->right);

            if (diffChild == 1)
                return rotateRight(leftChild, root);
            else {
                Node *temp = rotateLeft(leftChild, leftChild->right);
                return rotateRight(temp, root);
            }
        } else {
            Node *rightChild = root->right;
            int diffChild = getHeight(rightChild->left) - getHeight(rightChild->right);

            if (diffChild == -1)
                return rotateLeft(root, rightChild);
            else {
                Node *temp = rotateRight(rightChild->left, rightChild);
                return rotateLeft(root, temp);
            }
        }
    }

    void print(Node *root) {
        if (root == nullptr)
            return;

        cout << '(' << root->key << ',' << root->height << ',' << root->size << ") ";
        print(root->left);
        print(root->right);
    }

    Node* getByRank(Node *root, int rank) {
        int rootRank = getSize(root->left) + 1;

        if (rank == rootRank)
            return root;

        if (rank < rootRank)
            return getByRank(root->left, rank);
        else
            return getByRank(root->right, rank-rootRank);
    }

public:
    AVL(): root{nullptr} {}

    void insert(int key) {
        root = insert(root, key);
    }

    void print() {
        print(root);
    }

    Node* getByRank(int rank) {
        if (rank < 0 || rank > root->size)
            return nullptr;

        return getByRank(root, rank);
    }

private:
    Node *root;
};
