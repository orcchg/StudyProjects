#include <conio.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "binary_word_search.h"
#include "getword.h"

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* подсчет ключевых слов Си */
main()
{
    int n;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
	
	_getch();
    return 0;
}
