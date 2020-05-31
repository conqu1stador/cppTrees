#include "stdafx.h"
#include <iostream>

template <typename T>
struct TNode {
    TNode(T k) {
        data = k;
        left = right = nullptr;
    }
    int data;
    TNode *left, *right;
};

template <typename T>
class BST {
public:
    BST(T k) {
        root = new TNode<T>(k);
    }

    int search(TNode<T>* node, T key)
    {
        if (node == nullptr)
            return 0;

        if (node->data == key)
            return 1;

        if (node->data < key)
            return search(node->right, key);

        return search(node->left, key);
    }

    TNode<T>* insert(TNode<T>* node, T key)
    {
        if (node == nullptr) {
            TNode<T> *newNode = new TNode<T>(key);
            return newNode;
        }

        if (key == node->data)
            std::cout << "Error, duplicate\n";

        else if (key < node->data)
            node->left = insert(node->left, key);

        else if (key > node->data)
            node->right = insert(node->right, key);

        return node;
    }

    TNode<T>* minNodeData(TNode<T>* node)
    {
        TNode<T>* current = node;
        while (current->left != nullptr && current)
            current = current->left;

        return current;
    }

    TNode<T>* deleteNode(TNode<T>* node, T key)
    {
        if (node == nullptr)
            return node;

        if (key < node->data)
            node->left = deleteNode(node->left, key);

        else if (key > node->data)
            node->right = deleteNode(node->right, key);

        else
        {
            if (node->left == nullptr)
            {
                TNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                TNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            TNode<T>* temp = minNodeData(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }

        return node;
    }

    void intersection(TNode<T>* node, BST<T>* node2) {
        if (node != nullptr)
        {
            intersection(node->left, node2);
            intersection(node->right, node2);
            if (!node2->search(node2->getRoot(), node->data))
                deleteNode(getRoot(), node->data);
        }
    }

    void inorder(TNode<T>* node) //Централизованный обход
    {
        if (node != nullptr)
        {
            inorder(node->left);
            std::cout << node->data << '\n';
            inorder(node->right);
        }
    }

    void postorder(TNode<T>* node) //Обратный обход
    {
        if (node != nullptr)
        {
            postorder(node->left);
            postorder(node->right);
            std::cout << node->data << '\n';
        }
    }

    TNode<T>* getRoot() {
        return root;
    }

private:
    TNode<T>* root;
};

int main() {
    BST<int> a(50);
    a.insert(a.getRoot(), 30);
    a.insert(a.getRoot(), 70);
    a.insert(a.getRoot(), 60);
    a.insert(a.getRoot(), 80);
    a.insert(a.getRoot(), 20);
    a.insert(a.getRoot(), 40);

    std::cout << "A postorder:\n";
    std::cout << "----\n";
    a.postorder(a.getRoot());
    std::cout << "----\n";

    BST<int> b(50);
    b.insert(b.getRoot(), 30);
    b.insert(b.getRoot(), 70);
    b.insert(b.getRoot(), 60);
    b.insert(b.getRoot(), 85);
    b.insert(b.getRoot(), 25);
    b.insert(b.getRoot(), 40);

    std::cout << "----\n";
    std::cout << "B inorder:\n";
    b.inorder(b.getRoot());
    std::cout << "----\n";

    a.intersection(a.getRoot(), &b);

    std::cout << "----\n";
    std::cout << "After A = A & B\n";
    a.postorder(a.getRoot());
    std::cout << "----\n";

    getchar();
}