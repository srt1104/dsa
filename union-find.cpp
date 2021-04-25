/*
 * Union-Find data structure including path compression.
 */ 

#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
    int val, size;
    Node *parent;
    
    Node(int _val):
        val(_val), size(1), parent(nullptr)
    {}
};

class UnionFind {
private:
    unordered_map<int, Node*> mapping;
    
    Node* findUtil(Node *node) {
        if (node->parent == nullptr)
            return node;
            
        Node *rep = findUtil(node->parent);
        node->parent = rep;
        return rep;
    }
    
public:
    void insert(int val) {
        Node *node = new Node(val);
        mapping[val] = node;
    }
    
    int find(int val) {
        Node *node = mapping[val];
        
        Node *rep = findUtil(node);
        return rep->val;
    }
    
    bool setUnion(int val1, int val2) {
        Node *node1 = mapping[val1];
        Node *node2 = mapping[val2];
        
        if (node1 == node2)
            return false;
            
        Node *rep1 = findUtil(node1);
        Node *rep2 = findUtil(node2);
        
        if (rep1 == rep2)
            return false;
            
        if (rep1->size <= rep2->size) {
            rep1->parent = rep2;
            rep2->size += rep1->size;
        }
        else {
            rep2->parent = rep1;
            rep1->size += rep2->size;
        }
            
        return true;
    }
    
    friend ostream& operator<< (ostream& out, const UnionFind& UF) {
        for (const pair<int, Node*>& p: UF.mapping) {
            Node *node = p.second;
            
            out << '(' << node->val << ',' << node->parent << ") ";
        }
        
        return out;
    }
};

int main() {
    UnionFind UF;
    
    for (int i = 0; i < 5; ++i)
        UF.insert(i);
    cout << UF << endl;
    
    cout << UF.find(3) << endl;
    
    UF.setUnion(0, 2);
    cout << UF.find(0) << ' ' << UF.find(2) << endl;
    
    UF.setUnion(2, 3);
    cout << UF.find(2) << ' ' << UF.find(3) << endl;
    
    UF.setUnion(1, 4);
    cout << UF.find(1) << ' ' << UF.find(4) << endl;
    
    UF.setUnion(1, 2);
    cout << UF.find(1) << ' ' << UF.find(2) << endl;
    
    cout <<
        UF.find(0) << ' ' <<
        UF.find(1) << ' ' <<
        UF.find(2) << ' ' <<
        UF.find(3) << ' ' <<
        UF.find(4) << endl;
    
    return 0;
}
