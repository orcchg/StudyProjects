#include <cstring>
#include "talloc.h"
#include "strdup.h"

/* addtree: ��������� ���� �� ������ w � � ��� ���� ���� */
struct tnode* add(struct tnode* p, char* w, int key){

	int cond;
	
	if(p == NULL){ 			/* ����� ����������� ������� */
		p = talloc(); 				/* ��������� ����� ���� */
		printf("after talloc\n");
		p->word = strdup(w);
		p->count = 1;
		
	} else if((cond = strcmp(w, p->word))==0)
		p->count++; 			/* ��� ����� ��� ����������� */
		p->LineArr[key] = key;
		
	return p;
}

/* treeprint: ������������� ������ ������ � */
void Print(struct tnode *p)
{
    if (p != NULL) {
		printf("%s", p->word);
		for(int i=0; i < (sizeof(p->LineArr)/sizeof(p->LineArr[0])); i++)
			printf("%d", p->LineArr[i]);
		printf("\n");	
    }
}