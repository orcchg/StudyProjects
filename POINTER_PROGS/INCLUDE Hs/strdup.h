#include <cstdlib>

char *strdup(char *s) /* делает дубликат s */
{
    char *p;

    p = (char *) malloc(strlen(s)+1); /* +1 для '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}