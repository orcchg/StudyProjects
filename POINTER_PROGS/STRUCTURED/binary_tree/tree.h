#include <cstring>
#include "talloc.h"
#include "strdup.h"

struct tnode *talloc(void);
char *strdup(char *);

/* addtree: добавляет узел со словом w в р или ниже него */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

	if (p == NULL) {  /* слово встречается впервые */
        p = talloc(); /* создается новый узел */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) 
        p->count++;           /* это слово уже встречалось */
    else if (cond < 0)        /* меньше корня левого поддерева */
        p->left = addtree(p->left, w);
    else                      /* больше корня правого поддерева */
        p->right = addtree(p->right, w);
    return p;
}

/* treeprint: упорядоченная печать дерева р */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint (p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}