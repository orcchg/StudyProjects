//Функция хеширования: суммирует коды символов в строке и возвращает остаток от деления
//суммы на размер массива указателей. Unsigned гарантирует неотрицательность хеш-кода.

unsigned hash(char* s){ //получение хеш-кода для строки s
	
	unsigned hashval;
	
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
		
	return hashval % HASHSIZE;
}

//Хеширование порождает начальный индекс у массива hashtab.
//Если в хеш-таблице имеется элемент, представляющий некоторое слово, то он может
//быть обнаружен только в связном списке блоков, на начало которого указывает
//элемент массива hashtab с этим индексом. Поиск элемента осуществляется функцией lookup.

#include <cstring>

struct nlist* lookup(char* s){ //поиск элемента, значение которого равно строке s

	struct nlist* np;
	
	for(np = hashtab[hash(s)]; np != NULL; np = np->next){
		if(strcmp(s, np->name) == 0)
			return np; //элемент найден, возврат указателя на него (строку)
	}

	return NULL; //элемент не найден
}

//Функция install обращается к lookup, чтобы определить, имеется ли уже в таблице
//текущее вставляемое имя. Если да, то старое имя будет заменено новым, иначе
//будет образован новый элемент таблицы. Если на это нехватает памяти, возвращется NULL.

#include <cstdlib>
#include "strdup.h"

struct nlist* install(char* name, char* defn){ //заносит имя и замещающий текст в таблицу

	struct nlist* np;
	unsigned hashval;
	
	if((np = lookup(name)) == NULL){ //имя не найдено
		np = (struct nlist*) malloc(sizeof(*np)); //выделение памяти под новый элемент
		
		if(np == NULL || (np->name = strdup(name)) == NULL) //нехватка памяти
			return NULL;
			
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np; //замещение старого имени новым
		
	} else //имя уже имеется
		free((void*) np->defn); //освобождение памяти, занимаемой прежним defn
	
	if((np->defn = strdup(defn)) == NULL)
		return NULL;
		
	return np;
}

//Функция undef удаляет имя и соответствующий элемент из хеш-таблицы 
//при использовании функций lookup и install.

struct nlist* undef(char* name){ //удаление элемента по значению его ключа (имени)

	struct nlist* np, *head, *prev;
	
	head = hashtab[hash(name)]; //указатель на начало связного списка
	
	if(head == NULL) //попытка удаления элемента из пусктого списка
		return NULL;
	
	if((np = lookup(name)) == NULL){ //имя не найдено
		return NULL;
		
	} else { //имя уже имеется
		if(np == head)
			head = np->next; //если удаляется первый элемент в списке
		
		else { //удаление из середины списка
			prev = head->next;
			while(prev->next != np && prev->next != NULL)
				prev = prev->next;
				
			prev->next = np->next; //предыдущий элемент указывает на следующий за удаляемым
		}
	}
	
	free((void* ) np->defn);
	free((void* ) np->name);
	
	return prev;
}
	