#include <iostream>
#include <string>
#include <fstream>

using namespace std;




struct node {
        string data;
        string color;
        int height;
        node* parent;
        node* right;
        node* left;
};


class RBTree {
        private:
                node* root;
                //node* nil;
        protected:
                void insertfixup(node *);
                void removefix(node *);
                void right_rotate( node *);
                void left_rotate( node *);
                node* tree_minimum(node *);
                void transplant(node *, node*);
                void checktree(node *);                 //called by check()
                void inorder(node *);                     //called by print()
                int black_height(node *);               //claeed by check to assign the right height for each node;

        public:

                //Constructor
                RBTree(){
                        root = NULL;
                }

                node* search(string z);
                void insert(string z);
                void remove(string z);
                void check();
                void print();

};


int RBTree::black_height(node *y){
        int h = 0;
        node *x = y->left;
        while (x != NULL){
                if (x->color == "preto"){
                        h++;
                }
                x = x->left;
        }
        h++; //increments the height of the sentinel node
        return h;
}

node* RBTree::search(string z){
        node *p;
        p = root;
        bool found = false;

          if (root == NULL){
                return p;
        }

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

        return p;
}


void RBTree::insert(string z){
        node *y = NULL;
        node *x = root;
        node *t = new node;
        t->data = z;
        while ( x != NULL){
                y = x;
                if (t->data < x->data){
                        x = x->left;
                } else {
                        x = x->right;
                }
        }
        t->parent = y;
        if (y == NULL){
                root = t;
        } else if(t->data < y->data){
                y->left = t;
        } else {
                y->right = t;
        }
        t->left = NULL;
        t->right = NULL;
        t->color = "vermelho";
        insertfixup(t);
}

void RBTree::insertfixup(node *z){
        node *y;        //tio
        node *p = NULL; //pai
        node *g = NULL; //avo

        string aux = "";

        while (z != root && z->parent->color == "vermelho"  && z->color != "preto") {

                p = z->parent;
                g =z->parent->parent;

                if (p == g->left){
                        y = g->right;
                        if (y != NULL && y->color == "vermelho"){
                                g->color = "vermelho";
                                p->color = "preto";
                                y->color = "preto";
                                z->parent->parent->color = "vermelho";
                                z = g;
                        } else {
                                if (z == p->right){
                                        z = z->parent;
                                        left_rotate(z);
                                }
                                z->parent->color = "preto";
                                z->parent->parent->color = "vermelho";
                                right_rotate(z->parent->parent);
                        }
                } else {
                        y = g->left;
                        if (y != NULL && y->color == "vermelho"){
                                g->color = "vermelho";
                                p->color = "preto";
                                y->color = "preto";
                                z->parent->parent->color = "vermelho";
                                z = g;
                        } else {
                                if (z == p->left){
                                        z = z->parent;
                                        right_rotate(z);
                                }
                                z->parent->color = "preto";
                                z->parent->parent->color = "vermelho";
                                left_rotate(z->parent->parent);
                        }

                }
        }
        root->color = "preto";
}

node* RBTree::tree_minimum(node *p){
        node *y = NULL;
        if(p->left != NULL){
                y = p->left;
                while(y->left != NULL){
                        y = y->left;
                }
        }
        return y;
}

void RBTree::transplant(node *u, node *v) {
        if(u->parent == NULL){
                root =v;
        } else if (u == u->parent->left){
                u->parent->left = v;
        } else {
                u->parent->right = v;
        }
        if(v != NULL){
                v->parent = u->parent;
        }

}

//usahsuahusa
void RBTree::remove(string z){

        node *x;
        node *t = search(z);
        node *y = t;

        if(y == NULL){
                cout<< "A palavra "<<z<<" foi removida anteriormente ou nao foi inserida."<<endl;
                cout<<endl;
                return;
        }

        cout<<"Removendo a palavra "<<z<<endl;
        string y_original_color = y->color;
        if(t->left == NULL){
                x = t->right;
                transplant(t, t->right);
        } else if(t->right == NULL) {
                x = t->left;
                transplant(t,t->left);
        } else {
                y = tree_minimum(t->right);
                y_original_color = y->color;
                x = y->right;
                if(y->parent == t){
                        x->parent = y;
                } else {
                        transplant(y,y->right);
                        y->right = t->right;
                        y->right->parent = y;
                }
                transplant(t,y);
                y->left = t->left;
                y->left->parent = y;
                y->color = t->color;
        }

        if(y_original_color == "preto"){
                removefix(x);
        }
        print();
        cout<<endl;
        check();

}



void RBTree::removefix(node *x){
        node *w;
        while(x != root && x->color == "preto"){
                if (x == x->parent->left){
                        w = x->parent->right;
                        if(w->color == "vermelho"){
                                w->color = "preto";
                                x->parent->color = "vermelho";
                                left_rotate(x->parent);
                                w = x->parent->right;
                        }

                        if(w->left->color == "preto" && w->right->color == "preto") {
                                w->color = "vermelho";
                                x = x->parent;
                        } else {
                                if(w->right->color == "preto"){
                                        w->left->color = "preto";
                                        w->color = "vermelho";
                                        right_rotate(w);
                                        w = x->parent->right;
                                }
                                w->color = x->parent->color;
                                x->parent->color = "preto";
                                w->right->color = "preto";
                                left_rotate(x->parent);
                                x = root;
                        }
                } else {
                        //same thing with left and right exchanged
                        w = x->parent->left;
                        if(w->color == "vermelho"){
                                w->color = "preto";
                                x->parent->color = "vermelho";
                                right_rotate(x->parent);
                                w = x->parent->left;
                        }

                        if(w->right->color == "preto" && w->left->color == "preto") {
                                w->color = "vermelho";
                                x = x->parent;
                        } else {
                                if(w->left->color == "preto"){
                                        w->right->color = "preto";
                                        w->color = "vermelho";
                                        left_rotate(w);
                                        w = x->parent->left;
                                }
                                w->color = x->parent->color;
                                x->parent->color = "preto";
                                w->left->color = "preto";
                                right_rotate(x->parent);
                                x = root;
                        }
                }
                 x->color = "preto";
                 root->color = "preto";
        }
}


void RBTree::left_rotate(node *p){
        node * y = p->right;
        p->right = y->left;

        if(y->left != NULL){
                y->left->parent = p;
        }

        y->parent = p->parent;

        if (p->parent == NULL){
                root = y;
        } else if (p == p->parent->left){
                p->parent->left =y;
        } else {
                p->parent->right = y;
        }

        y->left = p;
        p->parent =y;
}


void RBTree::right_rotate(node *p){
        node * y = p->left;
        p->left = y->right;

        if(y->right != NULL){
                y->right->parent = p;
        }

        y->parent = p->parent;

        if (p->parent == NULL){
                root = y;
        } else if (p == p->parent->right){
                p->parent->right =y;
        } else {
                p->parent->left = y;
        }

        y->right = p;
        p->parent =y;
}


void RBTree::check(){
        checktree(root);
}

void RBTree::checktree(node *y){
        if (y != NULL){
                string p,n,l,r;
                if (y->parent != NULL){
                        p = y->parent->data;
                } else {
                        p = "Nil";
                }

                if (y->left != NULL){
                        l = y->left->data;
                } else {
                        l = "Nil";
                }

                if (y->right != NULL){
                        r = y->right->data;
                } else {
                        r = "Nil";
                }

                n = y->data;

                cout<< "("<<p << ", "<< n << ", "<< y->color << ", " <<y->height <<", " << l << ", " <<r <<")"<<endl<<endl;
                checktree(y->left);
                checktree(y->right);
        }
}


void RBTree::print(){
        inorder(root);
}

void RBTree::inorder(node *y){
        if(y != NULL){
                inorder(y->left);
                y->height =  black_height(y);
                cout << y->data<<", ";
                inorder(y->right);
        }
}




int main(int argc, char *argv[]){

        RBTree T;
        char *s = argv[1];
        std::ifstream file(     s);
        string str, n;

        while (std::getline(file, str))
        {
                n = str[str.length() - 1];
                if(n.compare("0") == 0){
                        str.pop_back();
                        str.pop_back();
                        T.remove(str);
                } else if (n.compare("1") == 0 ){
                        str.pop_back();
                        str.pop_back();
                        T.insert(str);
                }
        }

        T.print();
        cout<<endl;
        T.check();


        return 0;
}