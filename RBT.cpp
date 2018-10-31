#include <iostream>
#include <string>

using namespace std;


int MAX = 20;

struct node {
        string data;
        string color;
        node* parent;
        node* right;
        node* left;
};


class RBTree {
        protected:
                void right_rotate( node *);
                void left_rotate( node *);
                void transplant(node *, node*);
        public:

                node* root;
                node* q;
                //Constructor
                RBTree(){
                        q = NULL;
                        root = NULL;
                }

                //basic operations
                void insert(string z);
                void remove(string z);
                //void search(string z);
                //RBT operations
                void insertfix(node *);
                void removefix(node *);
                node* successor(node *);
                void inorder(node *);


};


void RBTree::insert(string z){
                node *p, *q;
                node *t = new node;
                t->data = z;
                p = root;
                q = NULL;
                if(root == NULL){
                        root = t;
                        t->parent = NULL;
                } else{
                        while(p != NULL){
                                q = p;
                                if(p->data > t->data){
                                        p = p->right;
                                } else{
                                        p = p->left;
                                }

                        }
                        t->parent = q;
                        if(p->data < t->data){
                                q->right = t;
                        } else {
                                q->left = t;
                        }
                }
                t->left = NULL;
                t->right = NULL;
                t->color = "red";
                insertfix(t);
}


void RBTree::insertfix(node *t){
        node *u;
        if(root == t){
                t->color = "black";
                return;
        }
        while(t->parent != NULL && t->color == "red"){
                node *g = t->parent->parent;    //avô de t
                if(g->left == t->parent){       //se o pai de t é filho à esquerda de g
                        if(g->right != NULL){
                                u = g->right;
                                if(u->color == "red") {
                                        t->parent->color = "black";
                                        u->color = "black";
                                        g->color = "red";
                                        t = g;
                                }
                        } else {
                                if(t->parent->right == t){
                                        t = t->parent;
                                        left_rotate(t);
                                }
                                t->parent->color = "black";
                                g->color = "red";
                                right_rotate(g);
                        }

                } else {
                        if(g->left !=NULL) {
                                u = g->left;
                                if(u->color == "red"){
                                        t->parent->color = "black";
                                        u->color = "black";
                                        g->color = "red";
                                        t = g;
                                }
                        } else {
                                if(t->parent->left == t){
                                        t = t->parent;
                                        right_rotate(t);
                                }
                                t->parent->color = "black";
                                g->color = "red";
                                left_rotate(g);
                        }
                }
                root->color = "black";
        }
}

void RBTree::transplant(node *u, node *v) {
        if(u->parent == NULL){
                root =v;
        } else if (u == u->parent->left){
                u->parent->left = v;
        } else {
                u->parent->right = v;
        }
        v->parent = u->parent;
}

void RBTree::remove(string z) {
        if (root == NULL){
                cout<<"Árvore vazia!\n";
                return;
        }

        node *p;
        p = root;
        node *y = NULL;
        node *q = NULL;
        bool found = false;

        while(p != NULL && !found){
                if (p->data == z){
                        found = true;
                }
                if(!found){
                        if(p->data < z){
                                p = p->right;
                        } else {
                                p = p->left;
                        }
                }
        }

        if(!found){
                cout<<"Elemento não está na árvore\n";
                return;
        } else {
                if (p->left == NULL || p->right == NULL){
                        y = p;
                } else {
                        y =successor(p);
                }
                if(y->left != NULL){
                        q = y->left;
                } else {
                        if(y->right != NULL){
                                q = y->right;
                        } else {
                                q = NULL;
                        }
                }
                if (q != NULL){
                        q->parent = y->parent;
                }

                if(y->parent ==NULL){
                        root = q;
                } else{
                        if(y == y->parent->left){
                                y->parent->left = q;
                        } else {
                                y->parent->right = q;
                        }
                }

                if(y != p){
                        p->color = y->color;
                        p->data = y->data;
                }

                if(y->color == "black"){
                        removefix(q);
                }

        }
}


void RBTree::removefix(node *p) {
        node *s;
        while(p != root && p->color == "black"){
                if(p->parent->left == p){       //p é filho da esquerda
                        s = p->parent->left;
                        if(s->color == "red"){
                                s->color = "black";
                                p->parent->color = "red";
                                left_rotate(p->parent);
                                s = p->parent->right;
                        }
                        if(s-> right->color == "black" && s->left->color == "black"){
                                s->color = "red";
                                p = p->parent;
                        } else {
                                if(s->right->color == "black"){
                                        s->left->color = "black";
                                        s->color = "red";
                                        right_rotate(s);
                                        s = p->parent->right;
                                }
                                s->color = p->parent->color;
                                p->parent->color = "black";
                                s->right->color = "black";
                                left_rotate(p->parent);
                                p = root;
                        }

                } else {        //p é filho da direita
                        s=p->parent->left;
                        if(s->color=="red") {
                                s->color="black";
                                p->parent->color="red";
                                right_rotate(p->parent);
                                s=p->parent->left;
                        }
                        if(s->left->color=="black"&&s->right->color=="black") {
                                s->color="red";
                                p=p->parent;
                        } else {
                                if(s->left->color=="black") {
                                      s->right->color="black";
                                      s->color="red";
                                      left_rotate(s);
                                      s=p->parent->left;
                                }
                                s->color=p->parent->color;
                                p->parent->color="black";
                                s->left->color="black";
                                right_rotate(p->parent);
                                p=root;
                        }
                }
                p->color ="black";
                root->color = "black";
        }
}


void RBTree::left_rotate(node *p){
        if(p->right == NULL){
                return;
        } else {
                node *y = p->right;
                if( y->left != NULL){
                        p->right = y->left;
                        y->left->parent = p;
                } else {
                        p->right = NULL;
                }

                if(p->parent != NULL){
                        y->parent = p->parent;
                }
                if(p->parent == NULL){
                        root = y;
                } else {
                        if(p == p->parent->left){
                                p->parent->left = y;
                        } else {
                                p->parent->right = y;
                        }
                }
                y->left = p;
                p->parent = y;
        }
}


void RBTree::right_rotate(node *p){
        if(p->left == NULL){
                return;
        } else {
                node *y = p->left;
                if( y->right != NULL){
                        p->left = y->right;
                        y->right->parent = p;
                } else {
                        p->left = NULL;
                }

                if(p->parent != NULL){
                        y->parent = p->parent;
                }
                if(p->parent == NULL){
                        root = y;
                } else {
                        if(p == p->parent->right){
                                p->parent->right = y;
                        } else {
                                p->parent->left = y;
                        }
                }
                y->right = p;
                p->parent = y;
        }
}


node * RBTree::successor(node *p){
        node *y = NULL;
        if(p->left != NULL){
                y = p->left;
                while(y->right != NULL){
                        y = y->right;
                }
        } else {
                y = p->right;
                while(y->left != NULL){
                        y = y->left;
                }
        }
        return y;
}


void RBTree::inorder(node *y){
        if (y != NULL){
                inorder(y->left);
                cout<< y->data;
                inorder(y->right);
        }
}


int main(){

        RBTree T;
        T.insert("haha");
        T.insert("zuno");
        //T.insert("sylpi");
        T.inorder(T.root);
       // T.remove("zuno");
        //T.insert("jess");
       //T.insert("valmir");
      //  T.insert("valmiro");
      //  T.inorder(T.root);

        return 0;
}