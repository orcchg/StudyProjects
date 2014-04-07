#include <fstream>
    #include <string>
    #include <cstring>
    #include <vector>
    #include <cmath>
    #include <queue>
    #include <map>
    #include <set>
    #include <stack>
    #include <sstream>
    #include <time.h>
    #include <queue>

    #define fori(i,n) for(int i=0;i<n;i++)
    #define for1(i,n) for(int i=1;i<=n;i++)
    #define vi vector<int>
    #define vb vector<bool>
    #define vvi vector<vi >
    #define sz(v) (int)v.size()
    #define mmin(a,b,c) min(a,min(b,c))
    #define sqr(x) (x)*(x)
    #define all(v) v.begin(),v.end()
    #define great (unsigned int)(-1)/4
    #define mmax(a,b,c) max(a,max(b,c))
    #define ii pair<int,int>
    #define vii vector<ii >
    #define vvii vector<vii >
    #define vvi vector<vi >
    const double pi = acos(0.0)*2;
    const double eps = 1e-7;
    
    using namespace std;
    #ifndef ONLINE_JUDGE
    ifstream cin("input.txt");
    ofstream cout("output.txt");
    #else
    #include <iostream>
    #endif
    const int black=1;
    const int red=0;

    struct node{
        int key,color;
        node *left, *right, *parent;
        node(){
            right=NULL;
            left=NULL;
            parent=NULL;
            key=NULL;
        }
        node(int _key){
            right=NULL;
            left=NULL;
            parent=NULL;
            key=_key;
            color=black;
        }
                node* operator->(){
            return this;
        }
                
        
    };
    node* Root=new node();
    node* NIL= new node(-1);
    


void LeftRotate(node* &R, node* x){
    R->parent=NIL;
    
    node* y=x->right;
    x->right=y->left;
    if (y->left!=NIL) 
    y->left->parent=x;
    y->parent=x->parent;
    
    //if (x->parent==NULL) x->parent=NIL;
    if (x->parent==NIL){ 
        R=y;
        y->parent=NIL;}
    else
        if (x==x->parent->left) 
            x->parent->left=y;
        else
            x->parent->right=y;
    y->left=x;
    x->parent=y;
    
}
void RightRotate(node* &R, node* x){
    R->parent=NIL;
    
    node* y=x->left;
    x->left=y->right;
    if (y->right!=NIL) 
        y->right->parent=x;
    //x->parent=NIL;
    y->parent=x->parent;
    if (x->parent==NIL) {
        R=y;
        y->parent=NIL;}
    else
        if (x==x->parent->right) 
            x->parent->right=y;
        else
            x->parent->left=y;
    y->right=x;
    x->parent=y;
    
}
void RB_Insert_Fixup(node* &R, node* z){
    node* y;
    while (z->parent->color==red){
        if (z->parent==z->parent->parent->left){
            y=z->parent->parent->right;
            if (y->color==red){
                z->parent->color=black;
                y->color=black;
                z->parent->parent->color=red;
                z=z->parent->parent;
            }
            else{
                if (z==z->parent->right){
                    z=z->parent;
                    LeftRotate(R,z);
                }
                z->parent->color=black;
                z->parent->parent->color=red;
                RightRotate(R,z->parent->parent);
            }
        }
        else{
            y=z->parent->parent->left;
            if (y->color==red){
                z->parent->color=black;
                y->color=black;
                z->parent->parent->color=red;
                z=z->parent->parent;
            }
            else{
                if (z==z->parent->left){
                    z=z->parent;
                    RightRotate(R,z);
                }
                z->parent->color=black;
                z->parent->parent->color=red;
                LeftRotate(R,z->parent->parent);
            }
        }
            
    }
    R->color=black;
}    
void RBInsert(node* &R, node* z){
    node* y=NIL;
    node* x=R;
    R->parent=NIL;
    while (x!=NIL){
        y=x;
        if (z->key<x->key)
            x=x->left;
        else
            x=x->right;
    }
    z->parent=y;
    if (y==NIL)
        R=z;
    else
        if (z->key<y->key)
            y->left=z;
        else
            y->right=z;
    z->left=NIL;
    z->right=NIL;
    z->color=red;
    if (R->left==NULL) R->left=NIL;
    if (R->right==NULL) R->right=NIL;
    RB_Insert_Fixup(R, z);
}
void TreePrint(node* x){
    if (x!=NIL) {
        TreePrint(x->right);
        cout<<x->key<<endl;
        TreePrint(x->left);
    }
}
int main(){
    node* y=new node(1);
    Root=NIL;
    int n,x;
    cin>>n;
    fori(i,n){
        cin>>x;
        y=new node(x);
        RBInsert(Root,y);
    }
    TreePrint(Root);
	return 0;
}
