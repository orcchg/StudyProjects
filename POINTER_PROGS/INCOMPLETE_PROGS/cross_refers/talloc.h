#include <stdlib.h>
#include "tnode.h"

/* talloc: ������� tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}