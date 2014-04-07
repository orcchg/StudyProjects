#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include "binary_ptr.h"
#include "getword.h"

#define MAXWORD 100
#define NKEYS (sizeof(keytab)/sizeof(struct key))

int getword(char *, int);
struct key *binsearch(char *, struct key *, int);

/* подсчет ключевых слов Си: версия с указателями */
int main()
{
    char word[MAXWORD];
    struct key *p;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((p = binsearch(word, keytab, NKEYS)) != NULL)
                p->count++;
    for (p = keytab; p < keytab + NKEYS; p++)
        if (p->count > 0)
            printf("%4d %s\n", p->count, p->word);
			
	_getch();		
    return 0;
}
