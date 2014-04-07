#include <conio.h>
#include "getword.h"
#include "tree.h"

#define MAXWORD 100

/* подсчет частоты встречаемости слов */
int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword (word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);
    treeprint(root);
	
	_getch();
    return 0;
}

