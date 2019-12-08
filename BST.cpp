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

    TNode<T>* search(TNode<T>* node, T key) 
    { 
        if (node == nullptr || node->data == key) 
            return root; 
        
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
    
    void inorder(TNode<T>* node) //Централизованный обход
    { 
        if (node != nullptr) 
        { 
            inorder(node->left); 
            std::cout << node->data << '\n'; 
            inorder(node->right); 
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
    a.insert(a.getRoot(), 40);
    a.insert(a.getRoot(), 70);
    a.insert(a.getRoot(), 60);
    a.insert(a.getRoot(), 80);
    a.inorder(a.getRoot());
    a.deleteNode(a.getRoot(), 50);
    std::cout << "----\n";
    std::cout << a.getRoot()->data << '\n'; 
    a.inorder(a.getRoot());
}