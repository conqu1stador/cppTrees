#include <iostream>

template <typename T>
struct TNode {
    TNode(T k) {
        data = k;
        size = 1;
        left = right = nullptr;
    }
    int data, size;
    TNode *left, *right;
};

template <typename T>
class RBST {
public:
    RBST(T k) {
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

    int getSize(TNode<T>* node)
    {
        if(node == nullptr) 
            return 0;
        return node->size; 
    }

    void fixSize(TNode<T>* node)
    {
        node->size = getSize(node->left) + getSize(node->right) + 1; 
    }
   
    TNode<T>* rotateRight(TNode<T>* node)
    {
        TNode<T>* temp = node->left; 
        if(temp == nullptr) 
            return node; 
        node->left = temp->right; 
        temp->right = node;  
        temp->size = node->size; 
	    fixSize(node);
        root = temp; 
        return temp; 
    }

    TNode<T>* rotateLeft(TNode<T>* node)
    {
        TNode<T>* temp = node->right;
        if(temp == nullptr) 
            return node;
        node->right = temp->left;
        temp->left = node;
        temp->size = node->size;
	    fixSize(node);
        root = temp;
        return temp;
    }

    TNode<T>* insertRoot(TNode<T>* node, T key)
    {
        if(node == nullptr) {
            TNode<T> *newNode = new TNode<T>(key);
            return newNode; 
        }
        
        if(node->data > key) {
            node->left = insertRoot(node->left, key); 
            return rotateRight(node); 
        }

        else {
            node->right = insertRoot(node->right, key);
            return rotateLeft(node);
        }
    }

    TNode<T>* insert(TNode<T>* node, int key)
    {
        if(node == nullptr) {
            TNode<T> *newNode = new TNode<T>(key);
            return newNode; 
        }

        if(rand() % (node->size + 1) == 0) 
            return insertRoot(node, key); 
        if(node->data > key) 
            node->left = insert(node->left, key); 
        else
            node->right = insert(node->right, key); 
        fixSize(node);
        root = node; 
        return node; 
    }

    TNode<T>* join(TNode<T>* node1, TNode<T>* node2)
    {
        if(node1 == nullptr) 
            return node2;
        if(node2 == nullptr) 
            return node1;

        if(rand() % (node1->size + node2->size) < node1->size) 
        {
            node1->right = join(node1->right, node2); 
            fixSize(node1);
            root = node1;
            return node1; 
        }
        else 
        {
            node2->left = join(node1,node2->left); 
            fixSize(node2);
            root = node2;
            return node2; 
        }
    }

    TNode<T>* remove(TNode<T>* node, T key)
    {
        if(node == nullptr) 
            return node; 
        if(node->data == key) 
        {
            TNode<T>* temp = join(node->left, node->right); 
            delete node; 
            return temp; 
        }
        else if(key < node->data) 
            node->left = remove(node->left, key); 
        else 
            node->right = remove(node->right, key);

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

    void order(TNode<T>* node) //Прямой обход
    { 
        if (node != nullptr) 
        { 
            std::cout << node->data << '\n';
            if(node->left != nullptr) {
                std::cout << "Слева " << node->left->data << ' ';
            }
            if(node->right != nullptr) {
                std::cout << "Справа " << node->right->data << '\n';
            }
            std::cout << "-----" << '\n';
            order(node->left);  
            order(node->right); 
        } 
    }

    TNode<T>* getRoot() {
        return root;
    }

private:
    TNode<T>* root;
};

int main() {
    srand(time(NULL));
    RBST<int> a(50);
    int aaa;
    a.insert(a.getRoot(), 40);
    a.insert(a.getRoot(), 70);
    a.insert(a.getRoot(), 60);
    a.insert(a.getRoot(), 80);
    a.insert(a.getRoot(), 120);
    a.insert(a.getRoot(), 35);
    a.insert(a.getRoot(), 55);

    std::cout << a.getRoot() << " " << a.getRoot()->data << "\n\n\n";
    
    a.order(a.getRoot());
    std::cout << a.getRoot()->data << "\n\n\n";
    std::cin >> aaa;
    a.remove(a.getRoot(), aaa);
    a.order(a.getRoot());
}