#include <limits.h>
#include <iostream>
using namespace std;

class templateType{
public:
    int value;
    int size, sum;
    friend std::ostream& operator<<(std::ostream& os, const templateType& t);
    bool operator<(const int& t) const {
        return value < t;
    }
    bool operator==(const templateType& t) const {
        return value == t.value;
    }
    templateType operator+(const templateType& t) {
        return (templateType){
            value == t.value ? value : 0, 
            size+t.size, 
            sum+t.sum
        };
    }
};
std::ostream& operator<<(std::ostream& os, const templateType& t) {
    os << "{" << t.value << "," << t.size << "," << t.sum << "}";
    return os;
}

class TreeSet{
public:
    class Node{
    public:
        Node* left;
        Node* right;
        templateType value;
        int count;
    };
    std::allocator<Node> alloc;
    Node* createNode(templateType value, int count = 1) {
        Node* newNode = alloc.allocate(1);
        new (newNode) Node{nullptr, nullptr, value, count};
        return newNode;
    }
    void deleteNode(Node* node) {
        if (node) {
            node->~Node();
            alloc.deallocate(node, 1);
        }
    }
    Node* root;
    TreeSet(){
        root = nullptr;
    }
    TreeSet(templateType initValue, int count = 1){
        root = createNode(initValue, count);
    }
    void display(){
        if (root == nullptr) return;
        cout << root->value << endl;
        display(root);
        cout << endl;
    }
    void display(Node* root, uint32_t l = 0, uint32_t r = INT_MAX){
        if (root == nullptr) return;
        uint32_t mid = (l + r + 1) >> 1;
        display(root->left, l, mid);
        display(root->right, mid, r);
        if (root->count) cout << root->value << " ";
    }
    void insert(templateType value, int count = 1){
        insert(value, count, root);
    }
    void insert(templateType value, int count, Node* &root, uint32_t l = 0, uint32_t r = INT_MAX){
        if (root == nullptr){
            root = createNode(value, count);
            return;
        }
        uint32_t mid = (l + r + 1) >> 1;
        if (root->count != 0){
            if (value == root->value){
                root->value = root->value + value;
                root->count += count;
                return;
            } else {
                if (root->value < mid) insert(root->value, root->count, root->left, l, mid);
                else insert(root->value, root->count, root->right, mid, r);
                root->count = 0;
            }
        }
        if (value < mid) insert(value, count, root->left, l, mid);
        else insert(value, count, root->right, mid, r);
        update(root);
    }
    void update(Node* root){
        templateType t0 = (templateType){0, 0, 0};
        templateType t1, t2;
        if (root->left == nullptr) t1 = t0; else t1 = root->left->value;
        if (root->right == nullptr) t2 = t0; else t2 = root->right->value;
        root->value = t1 + t2;
    }
    void merge(TreeSet &tree){
        merge(root, tree.root);
        tree.root = nullptr;
    }
    void merge(Node* &root, Node* &root2, uint32_t l = 0, uint32_t r = INT_MAX){
        if (root2 == nullptr) return;
        if (root == nullptr){
            root = root2;
            return;
        }
        if (root->count != 0 && root2->count == 0){
            insert(root->value, root->count, root2, l, r);
            root = root2;
            return;
        }
        if (root2->count != 0){
            insert(root2->value, root2->count, root, l, r);
            return;
        }
        uint32_t mid = (l + r + 1) >> 1;
        merge(root->left, root2->left, l, mid);
        merge(root->right, root2->right, mid, r);
        update(root);
    }
};