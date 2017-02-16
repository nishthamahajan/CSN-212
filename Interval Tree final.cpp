#include<iostream>
#include<cstdlib>
using namespace std;
struct interval
{
    int low;
    int high;
};
int max (int a, int b)
{
    return a>b ? a : b;
};
class int_tree;
class node
{
    interval i;
    int key;
    char colour;
    node *p;
    node *left;
    node *right;
public:
    node(interval k)
    {
        i.low=k.low;
        i.high=k.high;
        key=i.high;
        colour='r';
        p=0;
        left=0;
        right=0;
    }
    friend int_tree;
};
class int_tree
{
    node *root;
public :
    int_tree (){root=0;}
    void left_rotate(node*);
    void right_rotate(node*);
    void insert(interval);
    void insert_fixup(node*);
    void transplant(node*,node*);
    node* tree_min(node*);
    void del(node*);
    void del_fixup(node*);
    void search(interval);
};
void int_tree::left_rotate(node* x)
{
    if (x->right==0) return;
    node *y;
    y=x->right;
    x->right=y->left;
    if (y->left) y->left->p=x;
    y->p=x->p;
    if (x->p==0) root=y;
    else if (x==x->p->left) x->p->left=y;
    else x->p->right=y;
    y->left=x;
    x->p=y;
    x->key=max(x->key, max(x->left->key,x->right->key));
    y->key=max(y->key, max(y->left->key,y->right->key));
};
void int_tree::right_rotate(node* y)
{
    if (y->left==0) return;
    node *x;
    x=y->left;
    y->left=x->right;
    if (x->right) x->right->p=y;
    x->p=y->p;
    if (y->p==0) root=x;
    else if (y==y->p->left) y->p->left=x;
    else y->p->right=x;
    x->right=y;
    y->p=x;
    x->key=max(x->key, max(x->left->key,x->right->key));
    y->key=max(y->key, max(y->left->key,y->right->key));
};
void int_tree::insert(interval k)
{
    node *n=new node(k);
    node *x, *y;
    x=root;
    while (x)
    {
        y=x;
        x->key=max(n->i.high,x->key);
        if (n->i.low < x->i.low) x=x->left;
        else x=x->right;
    };
    n->p=y;
    if (root==0) root=n;
    else if (n->i.low < y->i.low) y->left=n;
         else y->right=n;
    insert_fixup(n);
};
void int_tree::insert_fixup(node* z)
{
    node *y;
    while (z->p->colour=='r')
        {
            if (z->p==z->p->p->left)
               {
                y=z->p->p->right;
                if (y->colour=='r')
                   {
                    z->p->colour='b';
                    y->colour='b';
                    z->p->p->colour='r';
                    z=z->p->p;
                   }
                else {if (z==z->p->right)
                         {
                          z=z->p;
                          left_rotate(z);
                         };
                      z->p->colour='b';
                      z->p->p->colour='r';
                      right_rotate(z->p->p);
                     };
                    }
            else
                {
                y=z->p->p->left;
                if (y->colour=='r')
                   {
                    z->p->colour='b';
                    y->colour='b';
                    z->p->p->colour='r';
                    z=z->p->p;
                    }
                else {if (z==z->p->left)
                         {
                          z=z->p;
                          right_rotate(z);
                         };
                      z->p->colour='b';
                      z->p->p->colour='r';
                      left_rotate(z->p->p);
                      };
                };
    };
    root->colour='b';
};
void int_tree::transplant(node* u, node *v)
{
    if (u->p==0) root=v;
    else if (u==u->p->left) u->p->left=v;
    else u->p->right=v;
    v->p=u->p;
};
node* int_tree::tree_min(node* x)
{
    while (x->left) x=x->left;
    return x;
};
void int_tree::del(node *n)
{
    node *x, *y;
    y=n;
    char y_original_colour=y->colour;
    if (n->left==0)
    {
        x=n->right;
        transplant(n, n->right);
    }
    else if (n->right==0)
    {
        x=n->left;
        transplant(n, n->left);
    }
    else
    {
        y=tree_min(n->right);
        y_original_colour=y->colour;
        x=y->right;
        if (y->p==n) x->p=y;
        else
        {
            transplant(y, y->right);
            y->right=n->right;
            y->right->p=y;
        };
        transplant(n,y);
        y->left=n->left;
        y->left->p=y;
        y->colour=n->colour;
    };
    if (y_original_colour=='b') del_fixup(x);
};
void int_tree::del_fixup(node* x)
{
    node *w;
    while (x!=0 && x->colour=='b')
    {
        if (x==x->p->left)
        {
            w=x->p->right;
            if (w->colour=='r')
            {
                w->colour='b';
                x->p->colour='r';
                left_rotate(x->p);
                w=x->p->right;
            };
            if (w->left->colour=='b' && w->right->colour=='b')
            {
                w->colour='r';
                x=x->p;
            }
            else {if (w->right->colour=='b')
                 {
                  w->left->colour='b';
                  w->colour='r';
                  right_rotate(w);
                  w=x->p->right;
                  };
                  w->colour=x->p->colour;
                  x->p->colour='b';
                  w->right->colour='b';
                  left_rotate(x->p);
                  x=root;
                 };
        }
        else
        {
            w=x->p->left;
            if (w->colour=='r')
            {
                w->colour='b';
                x->p->colour='r';
                right_rotate(x->p);
                w=x->p->left;
            };
            if (w->right->colour=='b' && w->left->colour=='b')
            {
                w->colour='r';
                x=x->p;
            }
            else {if (w->left->colour=='b')
                 {
                  w->right->colour='b';
                  w->colour='r';
                  left_rotate(w);
                  w=x->p->left;
                  };
                  w->colour=x->p->colour;
                  x->p->colour='b';
                  w->left->colour='b';
                  right_rotate(x->p);
                  x=root;
                 };
        };
    };
    x->colour='b';
};
void int_tree::search(interval k)
{
    node *x;
    x=root;
    while (x!=0 && (k.low > x->i.high || x->i.low > k.high))
    {
        if (x->left!=0 && k.low <= x->left->key) x=x->left;
        else x=x->right;
    };
    if(x) cout<<" The interval overlapping with the given interval {"<<k.low<<", "<<k.high<<"} is {"<<x->i.low<<", "<<x->i.high<<"}.\n";
    else cout<<"No interval overlaps with the given interval {"<<k.low<<", "<<k.high<<"}.\n";
};
//---------------------------------------
int main()
{
    interval ints[6]={{15, 20}, {10, 30}, {17, 19}, {5, 20}, {12, 15}, {30, 40}};
    int_tree IT;
    for (int k=0; k<6; k++)
    {
        IT.insert(ints[k]);
    };
    interval i1={14,16};
    interval i2={21,23};
    IT.search(i1);
    IT.search(i2);
    system ("pause");
    return 0;
}
