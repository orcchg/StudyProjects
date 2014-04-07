//������� �����������: ��������� ���� �������� � ������ � ���������� ������� �� �������
//����� �� ������ ������� ����������. Unsigned ����������� ����������������� ���-����.

unsigned hash(char* s){ //��������� ���-���� ��� ������ s
	
	unsigned hashval;
	
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
		
	return hashval % HASHSIZE;
}

//����������� ��������� ��������� ������ � ������� hashtab.
//���� � ���-������� ������� �������, �������������� ��������� �����, �� �� �����
//���� ��������� ������ � ������� ������ ������, �� ������ �������� ���������
//������� ������� hashtab � ���� ��������. ����� �������� �������������� �������� lookup.

#include <cstring>

struct nlist* lookup(char* s){ //����� ��������, �������� �������� ����� ������ s

	struct nlist* np;
	
	for(np = hashtab[hash(s)]; np != NULL; np = np->next){
		if(strcmp(s, np->name) == 0)
			return np; //������� ������, ������� ��������� �� ���� (������)
	}

	return NULL; //������� �� ������
}

//������� install ���������� � lookup, ����� ����������, ������� �� ��� � �������
//������� ����������� ���. ���� ��, �� ������ ��� ����� �������� �����, �����
//����� ��������� ����� ������� �������. ���� �� ��� ��������� ������, ����������� NULL.

#include <cstdlib>
#include "strdup.h"

struct nlist* install(char* name, char* defn){ //������� ��� � ���������� ����� � �������

	struct nlist* np;
	unsigned hashval;
	
	if((np = lookup(name)) == NULL{ //��� �� �������
		np = (struct nlist*) malloc(sizeof(*np)); //��������� ������ ��� ����� �������
		
		if(np == NULL || (np->name = strdup(name)) == NULL) //�������� ������
			return NULL;
			
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np; //��������� ������� ����� �����
		
	} else //��� ��� �������
		free((void*) np->defn); //������������ ������, ���������� ������� defn
	
	if((np->defn = strdup(defn)) == NULL)
		return NULL;
		
	return np;
}
		