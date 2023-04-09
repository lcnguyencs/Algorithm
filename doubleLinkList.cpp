#include<iostream>
#include<Memory>

struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;
};

void InorderTreeWalk(Node *x){
    if (x != NULL){
        InorderTreeWalk(x->left);
        std::cout<< x->key << " ";
        InorderTreeWalk(x->right);
    }
}

void PreorderTreeWalk(Node *x){
    if (x != NULL){
        std::cout<< x->key << " ";
        PreorderTreeWalk(x->left);
        PreorderTreeWalk(x->right);
    }
}

void PostorderTreeWalk(Node *x){
    if (x != NULL){
        PostorderTreeWalk(x->left);
        PostorderTreeWalk(x->right);
        std::cout<< x->key << " ";
    }
}

Node *TreeSearch(Node *x, int k){
    if (x == NULL || k == x->key)
        return x;
    if (k < x->key)
        return TreeSearch(x->left, k);
    else
        return TreeSearch(x->right, k);
}

Node *IterativeTreeSearch(Node *x, int k){
    while (x != NULL && k != x->key){
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

Node *TreeMinimum(Node *x){
    while (x->left != NULL)
        x = x->left;
    return x;
}

Node *TreeMaximum(Node *x){
    while (x->right != NULL)
        x = x->right;
    return x;
}

Node *TreeSuccessor(Node *x){
    if (x->right != NULL)
        return TreeMinimum(x->right);
    Node *y = x->parent;  // x->parent is not NULL
    while (y != NULL && x == y->right){ // x is right child
        x = y; // x is left child
        y = y->parent;  // y is not NULL
    }
    return y;
}

Node *TreePredecessor(Node *x){
    if (x->left != NULL)
        return TreeMaximum(x->left);
    Node *y = x->parent;
    while (y != NULL && x == y->left){
        x = y;
        y = y->parent;
    }
    return y;
}

void TreeInsert(Node *&T, Node *z){
    Node *y = NULL;
    Node *x = T;
    while (x != NULL){ // find the position of z
        y = x; // y is the parent of x
        if (z->key < x->key) // z is left child of x
            x = x->left; // x is left child of y
        else
            x = x->right; // x is right child of y
    }
    z->parent = y; // z is the child of y
    if (y == NULL) // T is empty
        T = z;
    else if (z->key < y->key) // z is left child of y
        y->left = z; // z is left child of y
    else
        y->right = z; 
}

void Transplant(Node *&T, Node *u, Node *v){ // v is the child of u
    if (u->parent == NULL) // u is root
        T = v;
    else if (u == u->parent->left) // u is left child
        u->parent->left = v;
    else
        u->parent->right = v; // u is right child
    if (v != NULL)
        v->parent = u->parent; // v is the child of u
}

void BSTSort(int *a, int n){
    Node *T = NULL;
    for (int i = 0; i < n; i++){
        Node *z = new Node;
        z->key = a[i];
        z->left = NULL;
        z->right = NULL;
        z->parent = NULL;
        TreeInsert(T, z);
    }
    InorderTreeWalk(T);
}

void TreeDelete(Node* &T, Node *z){
    Node *y = NULL; // y is the node to be deleted
    if (z->left == NULL) // z has no left child
        Transplant(T, z, z->right); // z is replaced by z->right
    else if (z->right == NULL) // z has no right child
        Transplant(T, z, z->left); // z is replaced by z->left
    else{
        y = TreeMinimum(z->right); // y is the successor of z
        if (y->parent != z){ // y is not z's right child
            Transplant(T, y, y->right); // y is replaced by y->right
            y->right = z->right; // y->right is z->right
            y->right->parent = y; // y->right is the child of y
        }
        Transplant(T, z, y); // z is replaced by y
        y->left = z->left; // y->left is z->left
        y->left->parent = y; // y->left is the child of y
    }
}

void DeleteTree(Node *x){
    if (x != NULL){
        DeleteTree(x->left);
        DeleteTree(x->right);
        delete x;
    }
}

int main(){
    int a[] = {5, 2, 4, 6, 1, 3};
    BSTSort(a, 6);
    std::cout<< std::endl;
    Node *T = NULL;
    for (int i = 0; i < 6; i++){
        Node *z = new Node;
        z->key = a[i];
        z->left = NULL;
        z->right = NULL;
        z->parent = NULL;
        TreeInsert(T, z);
    }
    InorderTreeWalk(T);
    std::cout<< std::endl;
    PreorderTreeWalk(T);
    std::cout<< std::endl;
    PostorderTreeWalk(T);
    std::cout<< std::endl;
    Node *x = TreeSearch(T, 4);
    std::cout<< x->key << std::endl;
    x = IterativeTreeSearch(T, 4);
    std::cout<< x->key << std::endl;
    x = TreeMinimum(T);
    std::cout<< x->key << std::endl;
    x = TreeMaximum(T);
    std::cout<< x->key << std::endl;
    x = TreeSuccessor(T->right);
    if (x != NULL) {
        std::cout << x->key << std::endl;
    } else {
        std::cout << "No successor found" << std::endl;
    }
    x = TreePredecessor(T->right);
    if (x != NULL) {
        std::cout << x->key << std::endl;
    } else {
        std::cout << "No predecessor found" << std::endl;
    }
    std::cout<< x->key << std::endl; // Segmentation fault here
    x = TreePredecessor(T->right);
    std::cout<< x->key << std::endl;
    Node *z = new Node;
    z->key = 7;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    TreeInsert(T, z);
    InorderTreeWalk(T);
    std::cout<< std::endl;
    TreeDelete(T, T->right);
    InorderTreeWalk(T);
    std::cout<< std::endl;
    DeleteTree(T);
    return 0;
}