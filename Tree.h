//
// Created by luis- on 7/30/2025.
//
#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T> class BPTree {
private:
    struct Node {
        bool leaf;
        vector<T> data;
        vector<Node*>  children;
        Node* next;
        Node (bool BoolLeaf = false) : leaf(BoolLeaf), next(nullptr) {} // defaults node to not leaf
    };
    Node* root;
    int size; // number of keys
    void split(Node* parent, int In, Node* child) {
       int full = child->data.size(); // This size should be 2*size-1 right when we split
        Node* newNode = new Node(child-> leaf);
        for (int i = size; i < full; i++) {
            newNode->data.push_back(child->data[i]); // push every node down by one
        }
        if (!child->leaf) { // incase is not a leaf we also move their kids
            for (int i = size; i < full; i++) {
                newNode->children.push_back(child->children[i]);
            }
            child->children.resize(size);
        }
        child->data.resize(size);
        // insert new node into parents kid array
        parent->children.insert(parent->children.begin()+1+In, newNode);
        T MoveUp = (child->leaf ? newNode->data[0] : child->data.back()); // if the key needs to become a parent make it one
        parent->data.insert(parent->data.begin()+In, MoveUp);
        if (child->leaf) { // if we split on the leaf, connect the leaf nodes correctly
            newNode->next =  child->next;
            child->next = newNode;
        }
    }
    void inserthelper(Node* key,T value) {
        if (key->leaf) {
            key->data.insert(upper_bound(key->data.begin(), key->data.end(), value), value);
        } else { // we go into the correct internal node
            int pos = key->data.size()-1;
            while (pos>=0 && value < key->data[pos]) {
                pos--;
            }
            pos++; // if the child where this would go is full we split and compare
            if (key->children[pos]->data.size()==2*size-1) {
                split(key,pos,key->children[pos]);
                if (value > key->data[pos]) {
                    pos++;
                }
            }
            inserthelper(key->children[pos], value);
        }
    }
    void removehelper(Node* key, T value) {
        int Keypos= 0;
        while (Keypos < key->data.size() && value > key->data[Keypos]) { Keypos++;} // find where this value is
        if (key->leaf) {
            key->data.erase(key->data.begin()+Keypos);
            return;
        }
        Node* kid = key->children[Keypos];
        int min = size-1;
        if (kid->data.size() < min) {
            GrabFromPrev(key,Keypos);
        } else if (Keypos+1 < key->children.size() && key->children[Keypos+1]->data.size() > min+1) {
            GrabFromNext(key,Keypos);
        } else {
            merge(key,Keypos);
            // kid might be at either Keypos or Keypos -1, so we account for that
            if (Keypos == key->data.size()+1) {
                kid = key->children[Keypos-1];
            }
        }
        removehelper(kid, value);
    }
    void merge(Node* key, int In) {
        Node* kid = key->children[In];
        Node* sibling = key->children[In+1];
        if (sibling->leaf) { //leaf merge
            kid->data.insert(kid->data.end(),sibling->data.begin(),sibling->data.end());
            kid->next =  sibling->next; // cut the right leaf from the linked leafs
            key->data.erase(key->data.begin()+In); // updating after moving the right child
            key->children.erase(key->children.begin()+In+1);
        } else {
            kid->data.push_back(key->data[In]);
            kid->data.insert(kid->data.end(),sibling->data.begin(),sibling->data.end());
            kid->children.insert(kid->children.end(),sibling->children.begin(),sibling->children.end());
            key->data.erase(key->data.begin()+In);
            key->children.erase(key->children.begin()+In+1);
        }
        delete sibling;
    }
    void GrabFromPrev(Node* key, int In) {
        Node* kid = key->children[In];
        Node* sibling = key->children[In-1];
        if (kid->leaf) {
            kid->data.insert(kid->data.begin(),sibling->data.back());
            sibling->data.pop_back();
            key->data[In-1] = kid->data[0];
        } else {
            kid->data.insert(kid->data.begin(),key->data[In-1]);
            key->data[In-1] = sibling->data.back();
            sibling->data.pop_back();
            kid->children.insert(kid->children.begin(),sibling->children.back());
            sibling->children.pop_back();
        }
    }
    void GrabFromNext(Node* key, int In) {
        Node* kid = key->children[In];
        Node* sibling = key->children[In+1];
        if (kid->leaf) {
            kid->data.push_back(sibling->data[0]);
            sibling->data.erase(sibling->data.begin()); // .begin() to not only erase the value at 0
            key->data[In] = sibling->data[0];
        } else {
            kid->data.push_back(key->data[In]);
            key->data[In] = sibling->data[0];
            sibling->data.erase(sibling->data[0]);
            kid->children.push_back(sibling->children[0]);
            sibling->children.erase(sibling->children.begin());
        }
    }
    void printTreeHelper(Node* key, int curr) {
        Node* p = root;
        if (p != nullptr) {
            for (int i=0; i< curr; i++) {
                cout << " ";
            }
            for (auto it& value : p->data) {
                cout << value << " ";
            }
            cout << endl;
            for (Node*it : p->children) {
                printTreeHelper(it, curr+1);
            }
        }
    }
    public:
    BPTree(int degree) : root(nullptr), size(degree) {}
    bool search(T value){
        Node* p = root;
        while (p) {
            int it =0;
            for (int i=0; value > p->data[i] && i < p->data.size(); i++) {it++;}
            if (value == p->data[it]) {
                return true;
            }
            if (p->leaf) {
                return false;
            }
            p = p->children[it];
        }
        return false;
    }
    void insert(T value) {
        if (root == nullptr) {
            root = new Node(true);
            root->data.push_back(value);
        } else if (root->data.size() == 2*size-1) {
            Node* newNode = new Node();
            newNode->children.push_back(root);
            split(newNode,0,root);
            root = newNode;
        }
        inserthelper(root,value);
    }
    void remove(T value){
        removehelper(root, value);
        if (root->data.empty() && !root->leaf) {
            Node* temp = root;
            root = root->children[0];
            delete temp;
        }
    }
    void print(){printTreeHelper(root, 0);}

};
