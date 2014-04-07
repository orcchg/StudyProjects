#include <cstdio>
#include "getchungetch.h"

#define EOF -1

/* getword: принимает следующее слово или символ из ввода */
int getword (char *word, int lim)
{
    int c, Getch(void);
    void Ungetch(int);
    char *w = word;

    while (isspace(c = Getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = Getch())) {
            Ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

