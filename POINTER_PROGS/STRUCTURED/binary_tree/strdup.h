#include <cstdlib>

char *strdup(char *s) /* ������ �������� s */
{
    char *p;

    p = (char *) malloc(strlen(s)+1); /* +1 ��� '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}