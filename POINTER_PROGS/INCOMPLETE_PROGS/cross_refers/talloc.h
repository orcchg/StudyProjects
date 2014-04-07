#include <stdlib.h>
#include "tnode.h"

/* talloc: создает tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}