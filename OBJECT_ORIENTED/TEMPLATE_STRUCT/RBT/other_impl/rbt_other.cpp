#include <cstdio>
#include <algorithm>
#include <string>


enum rbt_color { RED, BLACK };

struct rbt_node
{
    int key; //klucz
    int sub_tree; //wielkosc poddrzewa
    std::string data; //wartosc (napis do 21 znakow)
    rbt_node *left; //lewy syn
    rbt_node *right; //prawy syn
    rbt_node *parent;
    rbt_color color; //kolor
};


int is_RED(rbt_node *root)
{
    return root != NULL && root->color == RED;
}

int is_BLACK(rbt_node *root)
{
    return root != NULL && root->color == BLACK;
}

rbt_node *make_node(int key, std::string data)
{
    rbt_node *new_node = new rbt_node; 
    new_node->key = key;
    new_node->data = data;
    new_node->color = RED;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->sub_tree = 1; //inicjalna wartosc
    return new_node;
}

void add_node(rbt_node *&tree, rbt_node *node, rbt_node *parent)
{
        if(tree == NULL)
        {
            node->parent = parent;
            tree = node;
        }
        else if(node->key < tree->key)
        {
            tree->sub_tree += 1;
            add_node(tree->left, node, tree);
        }
        else if(node->key > tree->key)
        {
            tree->sub_tree += 1;
            add_node(tree->right, node, tree);
        }
}


//funkcja testujaca drzewo, zrodlo http://www.eternallyconfuzzled.com/tuts/datastructures/jsw_tut_rbtree.aspx (troche ulepszylem)
int rbt_assert (rbt_node *root)
{
   int lh, rh;

   if ( root == NULL )
     return 1;
   else {
     rbt_node *ln = root->left;
     rbt_node *rn = root->right;

     /* Consecutive RED links */
     if ( is_RED ( root ) ) {
       if ( is_RED ( ln ) || is_RED ( rn ) ) {
         puts ( "RED violation" );
         printf("VIOLATION AT KEY: %d\n", root->key);
        //return 0;
       }
     }

     lh = rbt_assert ( ln );
     rh = rbt_assert ( rn );

     if (1 + (ln ? ln->sub_tree : 0) + (rn ? rn->sub_tree : 0) != root->sub_tree) 
     {
          puts ("Subtree violation");
          printf("VIOLATION AT KEY: %d\n", root->key);
          return 0;
     }

     if (root->left != NULL && root->left->parent != root || root->right != NULL && root->right->parent != root) 
     {
          puts ("Parent violation");
          printf("VIOLATION AT KEY: %d\n", root->key);
          return 0;
     }

     /* Invalid binary search tree */
     if ( ( ln != NULL && ln->key >= root->key )
       || ( rn != NULL && rn->key <= root->key ) )
     {
       puts ( "Binary tree violation" );
       return 0;
     }

     /* BLACK height mismatch */
     if ( lh != 0 && rh != 0 && lh != rh ) {
       puts ( "BLACK violation" );
       return 0;
     }

     /* Only count BLACK links */
     if ( lh != 0 && rh != 0 )
       return is_RED ( root ) ? lh : lh + 1;
     else
       return 0;
   }
 }




void left_rotate(rbt_node *&root, rbt_node *&node)
{
    rbt_node *new_node = node->right;
    if(new_node != NULL)
    {
        node->right = new_node->left;
        if(new_node->left != NULL)
            new_node->left->parent = node;

        if(node->parent == NULL)
            root = new_node;
        else if(node == node->parent->left)
            node->parent->left = new_node;
        else
            node->parent->right = new_node;

        new_node->left = node;

        //aktualizujemy rozmiar poddrzewa
        new_node->sub_tree = node->sub_tree;
        node->sub_tree = 1;
        if(node->left != NULL)
            node->sub_tree += node->left->sub_tree;
        if(node->right != NULL)
            node->sub_tree += node->right->sub_tree;

        new_node->parent = node->parent;
        new_node->left->parent = new_node;


    }
}

void right_rotate(rbt_node *&root, rbt_node *& node)
{

    rbt_node *new_node = node->left;
    if(new_node != NULL)
    {
        node->left = new_node->right;
        if(new_node->right != NULL)
            new_node->right->parent = node;



        if(node->parent == NULL)
            root = new_node;
        else if(node == node->parent->right)
            node->parent->right = new_node;
        else
            node->parent->left = new_node;

        new_node->right = node;

            //aktualizujemy rozmiar poddrzewa
        new_node->sub_tree = node->sub_tree;
        node->sub_tree = 1;
        if(node->left != NULL)
            node->sub_tree += node->left->sub_tree;
        if(node->right != NULL)
            node->sub_tree += node->right->sub_tree;

        new_node->parent = node->parent;
        new_node->right->parent = new_node;

    }
}


void add_rbt_node(rbt_node *&root, int key, std::string data, rbt_node *parent)
{
    rbt_node *element = make_node(key, data);
    add_node(root, element, parent);
    while(element != root && element->parent->color == RED)
    {
        if(element->parent == element->parent->parent->left)
        {
            rbt_node *uncle = element->parent->parent->right;
            if(uncle != NULL && uncle->color == RED)
            {
                element->parent->color = BLACK;
                uncle->color = BLACK;
                element->parent->parent->color = RED;
                element = element->parent->parent;
            }
            else
            {
                if(element == element->parent->right)
                {
                    element = element->parent;
                    left_rotate(root, element);
                }
                element->parent->color = BLACK;
                element->parent->parent->color = RED;
                right_rotate(root, element->parent->parent);
            }
        }
        else
        {
            rbt_node *uncle = element->parent->parent->left;
            if(uncle != NULL && uncle->color == RED)
            {
                element->parent->color = BLACK;
                uncle->color = BLACK;
                element->parent->parent->color = RED;
                element = element->parent->parent;
            }
            else
            {
                if(element == element->parent->left)
                {
                    element = element->parent;
                    right_rotate(root, element);
                }
                element->parent->color = BLACK;
                element->parent->parent->color = RED;
                left_rotate(root, element->parent->parent);
            }
        }
    }
    root->color = BLACK;

}

void search_key(rbt_node *root, int key)
{
    if(root == NULL)
        printf("-\n");
    else if(root->key == key)
        printf("%s\n", root->data.c_str());
    else if(root->key < key)
        search_key(root->right, key);
    else if(root->key > key)
        search_key(root->left, key);
}

void min_key(rbt_node *root, int number)
{
    if(root != NULL)
    {
        int rank = 1;
        if(root->left != NULL)
            rank += root->left->sub_tree;
        if(rank == number)
            printf("%s\n", root->data.c_str());
        else if(number < rank)
            min_key(root->left, number);
        else
            min_key(root->right, number - rank);
    }
}

void print_out(rbt_node *root)
{
    if(root != NULL)
    {
        printf("%d %s ", root->key, root->data.c_str());
        if(root->color == BLACK)
            printf("black ");
        else
            printf("red ");
        if(root->parent != NULL)
            printf("%d ",root->parent->key);
        else
            printf("- ");
        if(root->left != NULL)
            printf("%d ",root->left->key);
        else
            printf("- ");
        if(root->right != NULL)
            printf("%d ",root->right->key);
        else
            printf("- ");
        printf("\n");

        print_out(root->left);
        if(root->right != NULL)
        {
            print_out(root->right);
        }
    }
}



int main()
{

    int key;
    char data [21];
    char operation;
    rbt_node *root = NULL;
    while(scanf("%c",&operation) != EOF)
    {
        switch(operation)
        {
            case 'I':
                scanf("%d",&key);
                scanf("%s",data);
                add_rbt_node(root, key, data, NULL);
                break;
            case 'S':
                scanf("%d",&key);
                search_key(root, key);
                break;
            case 'F':
                scanf("%d",&key);
                if(key <= root->sub_tree && key != 0)
                    min_key(root, key);
                else
                    printf("-\n");
                break;
            case 'G':
                printf("%d\n", rbt_assert(root));
                break;
            case 'P':
                //print_out(root);
                break;
        }
    }
}