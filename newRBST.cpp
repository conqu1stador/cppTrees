#include <iostream>
#include <fstream>
#include <vector>

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

long long duplicate = 0;


template <typename T>
class RBST {
public:
    std::ofstream outTgf, help;
    RBST(T k) {
        root = new TNode<T>(k);
        outTgf.open("outputRBST.tgf");
        help.open("helpRBST.txt");
        help << "#\n";
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

        if(node->left != nullptr && node->right != nullptr) {
            if((node->left->size > node->right->size*2) || (node->left->size*2 < node->right->size))
                return insertRoot(node, key);  
        }

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
        root = node;
        return node; 
    }
    int counter;
    void order(TNode<T>* node) //Прямой обход
    {
        if (node != nullptr) 
        { 
            //std::cout << node->data << '\n';
            outTgf << counter << " " << node->data << '\n';
            counter++;
            if(node->left != nullptr) {
                //std::cout << "Слева " << node->left->data << '\n';
                help << node->data << " " << node->left->data << '\n';
            }
            if(node->right != nullptr) {
                //std::cout << "Справа " << node->right->data << '\n';
                help << node->data << " " << node->right->data << '\n';
            }
            //std::cout << "-----" << '\n';
            order(node->left);  
            order(node->right); 
        } 
    }

    TNode<T>* getRoot() {
        return root;
    }

    int height(TNode<T>* node) {
        if (node == nullptr) 
            return 0;
        int left, right;
        if(node->left != nullptr)
            left = height(node->left);
        else 
            left = -1;
        if(node->right != nullptr)
            right = height(node->right);
        else
            right = -1;
        return (left > right ? left : right) + 1;
    }

    void printFile() {
        counter = 1;
        order(getRoot());
        outTgf.close();
        help.close();
        std::ifstream readHelp;
        outTgf.open("outputRBST.tgf", std::ios::app);
        readHelp.open("helpRBST.txt");
        std::string line;
        while(std::getline(readHelp, line)) {
            outTgf << line << '\n';
        }
    }

private:
    TNode<T>* root;
};

template <typename T>
struct BTNode {
    BTNode(T k) {
        data = k;
        left = right = nullptr;
    }
    int data;
    BTNode *left, *right;
};

template <typename T>
class BST {
public:
    BST(T k) {
        root = new BTNode<T>(k);
        outTgf.open("outputBST.tgf");
        help.open("helpBST.txt");
        help << "#\n";
    }
    std::ofstream outTgf, help;
    BTNode<T>* search(BTNode<T>* node, T key) 
    { 
        if (node == nullptr || node->data == key) 
            return root; 
        
        if (node->data < key) 
            return search(node->right, key); 

        return search(node->left, key); 
    } 

    BTNode<T>* insert(BTNode<T>* node, T key) 
    {
        if (node == nullptr) {
            BTNode<T> *newNode = new BTNode<T>(key);
            return newNode;
        }
        
        if (key == node->data)
            duplicate++;

        else if (key < node->data) 
            node->left = insert(node->left, key);

        else if (key > node->data) 
            node->right = insert(node->right, key);
            
        return node; 
    }

    BTNode<T>* minNodeData(BTNode<T>* node) 
    { 
        BTNode<T>* current = node; 
        while (current->left != nullptr && current) 
            current = current->left; 
    
        return current; 
    } 

    BTNode<T>* deleteNode(BTNode<T>* node, T key) 
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
                BTNode<T>* temp = node->right; 
                delete node; 
                return temp; 
            } 
            else if (node->right == nullptr) 
            { 
                BTNode<T>* temp = node->left; 
                delete node;
                return temp; 
            } 

            BTNode<T>* temp = minNodeData(node->right); 
            node->data = temp->data; 
            node->right = deleteNode(node->right, temp->data); 
        }

        return node; 
    } 
    
    void inorder(BTNode<T>* node) //Централизованный обход
    { 
        if (node != nullptr) 
        { 
            inorder(node->left); 
            std::cout << node->data << '\n'; 
            inorder(node->right); 
        } 
    }
    void order(BTNode<T>* node) //Прямой обход
    {
        if (node != nullptr) 
        { 
            //std::cout << node->data << '\n';
            outTgf << counter << " " << node->data << '\n';
            counter++;
            if(node->left != nullptr) {
                //std::cout << "Слева " << node->left->data << '\n';
                help << node->data << " " << node->left->data << '\n';
            }
            if(node->right != nullptr) {
                //std::cout << "Справа " << node->right->data << '\n';
                help << node->data << " " << node->right->data << '\n';
            }
            //std::cout << "-----" << '\n';
            order(node->left);  
            order(node->right); 
        } 
    }

    BTNode<T>* getRoot() {
        return root;
    }
    int counter;
    void printFile() {
        counter = 1;
        order(getRoot());
        outTgf.close();
        help.close();
        std::ifstream readHelp;
        outTgf.open("outputBST.tgf", std::ios::app);
        readHelp.open("helpBST.txt");
        std::string line;
        while(std::getline(readHelp, line)) {
            outTgf << line << '\n';
        }
    }
    int height(BTNode<T>* node) {
        if (node == nullptr) 
            return 0;
        int left, right;
        if(node->left != nullptr)
            left = height(node->left);
        else 
            left = -1;
        if(node->right != nullptr)
            right = height(node->right);
        else
            right = -1;
        return (left > right ? left : right) + 1;
    }
private:
    BTNode<T>* root;
};

int main() {
    clock_t start = clock();
    srand(time(NULL));
    int size = 100;
    int rbstArr[size], bstArr[size];
    for(int k = 0; k != size; ++k) {
        int rnd = rand() % (size*10); 
        RBST<int> a(rnd);
        BST<int> c(rnd);
        int b[size];
        for(int i = 0; i != size; ++i) {
            int temp = rand() % (size*10);
            for(int j = 0; j != size; ++j) {
                while(b[j] == temp) {
                    temp = rand() % (size*10); 
                }
            }
            b[i] = temp;
            //std::cout << b[i] << ' '; 
        }
        //std::cout << rnd << '\n'; 
        for(int i = 0; i != size; ++i) {
            a.insert(a.getRoot(), b[i]);
        }
        for(int i = 0; i != size; ++i) {
            c.insert(c.getRoot(), b[i]);
        }
        a.printFile();
        c.printFile();
        rbstArr[k] = a.height(a.getRoot());
        bstArr[k] = c.height(c.getRoot());
    }
    std::cout << "RBST / BST \n";
    std::ofstream wordRbst, wordBst, wordDraw;
    wordRbst.open("wordRbst.txt"); wordBst.open("wordBst.txt");
    int countRbst = 0, countBst = 0, draw = 0;
    for(int i = 0; i != size; ++i) {
        wordRbst << rbstArr[i] << "\n"; wordBst << bstArr[i] << '\n'; 
        if(rbstArr[i] < bstArr[i])  ++countRbst;
        if(rbstArr[i] > bstArr[i])  ++countBst;
        if(rbstArr[i] == bstArr[i])  ++draw;
    }
    std::cout << "RBST better " << countRbst << " / All " << size << '\n';
    std::cout << "BST better " << countBst << " / All " << size << '\n';
    std::cout << "draw " << draw << " / All " << size << '\n';
    std::cout << "duplicate " << duplicate << '\n';
    clock_t end = clock();
    std::cout << (((double)end-start)/CLOCKS_PER_SEC)*1000 << "ms";
}