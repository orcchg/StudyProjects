#include <cstdio>
//Header File

typedef int mkey_t; //key type
typedef int value_t; //value type

const value_t errval = -999;

class DLlist {
	struct Block {
		mkey_t key;
		value_t value;
		struct Block* next;
		struct Block* previous;
				
		Block(mkey_t k, value_t val, Block* ptrNext = NULL, Block* ptrPrev = NULL){
			key = k;
			value = val;
			next = ptrNext;
			previous = ptrPrev;
		}
	};
	
	Block* first;
	Block* last;
			  
	public:
		int BlockCount;
	
		DLlist() {
			BlockCount = 0;
			first = last = NULL;
		}
		
		DLlist(const DLlist& obj);
		~DLlist();
		
		value_t take_head() const {
			return first->value;
		}
		
		value_t take_tail() const {
			return last->value;
		}
		
		void add_list_to_last(const DLlist& obj); //add new linked list to tail of previous Ll
		void add_val_to_first(mkey_t key, value_t val);
		void add_val_to_last(mkey_t key, value_t val);
		value_t find_el_dir(mkey_t key, int& rStepD);
		value_t find_el_rev(mkey_t key, int& rStepR);
		value_t delete_first();
		value_t delete_el(mkey_t key);
		void insert(mkey_t key, value_t val);
		
		int get_count() const {
			return BlockCount;
		}
		
		void get_list_info();
};

//Source File

DLlist::DLlist(const DLlist& obj) 
{
	BlockCount = 0;
	first = last = NULL;
	add_list_to_last(obj);
}

DLlist::~DLlist()
{
	Block* current = NULL;
	Block* next = first;
	Block* previous = NULL;
	
	while(next) {
		current = next;
		next = next->next;
		next->previous = NULL;
		delete current;
	}
}

void DLlist::add_list_to_last(const DLlist& obj)
{
	for(Block* cur = obj.first; cur; cur = cur->next)
		add_val_to_last(cur->key, cur->value);
}

void DLlist::add_val_to_first(mkey_t key, value_t val)
{
	Block* newBlock = new Block(key, val, first, NULL);
	if(!first) {
		last = newBlock;
	}
	
	first = newBlock;
	BlockCount++;
}

void DLlist::add_val_to_last(mkey_t key, value_t val)
{
	Block* newBlock = new Block(key, val, NULL, last);
	if(!last) {
		first = newBlock;
	} else {
		last->next = newBlock;
	}
	
	newBlock->previous = last;
	BlockCount++;
}

value_t DLlist::find_el_dir(mkey_t key, int& rStepD)
{
	Block* current = first;
	rStepD = 0;
	while(current) {
		if(current->key == key) {
			return current->value;
		}
		current = current->next;
		rStepD++;
	}
	return errval;
}

value_t DLlist::find_el_rev(mkey_t key, int& rStepR)
{
	Block* current = last;
	rStepR = 0;
	while(current) {
		if(current->key == key) {
			return current->value;
		}
		current = current->previous;
		rStepR++;
	}
	return errval;
}
	
value_t DLlist::delete_first()
{
		value_t result = first->value;
		first = first->next;
		first->previous = NULL;
		BlockCount--;
		return result;
}

value_t DLlist::delete_el(mkey_t key)
{
	Block* prev = NULL, *current = first;
	value_t val = 0;
	
	while(current) {
		if(current->key == key) {
			if(prev && current->next != NULL) {
				prev->next = current->next;
				current->next->previous = current->previous;
			} else {
				delete_first();
				BlockCount++;
			}
			if(current == last) {
				last = prev;
			}
			val = current->value;
			
			delete current;
			BlockCount--;
			return val;
			
		} else {
			prev = current;
			current = current->next;
		}
	}
	return errval;
}

void DLlist::insert(mkey_t key, value_t val)
{
	Block* prev = NULL, *current = first;
	
	while(current != NULL && current->key < key) {
		prev = current;
		current = current->next;
	}
	
	Block* newBlock = new Block(key, val, current, prev);
	if(current == NULL) {
		last = newBlock;
	} else {
		current->previous = newBlock;
	}
	
	if(prev == NULL) {
		first = newBlock;
	} else {
		prev->next = newBlock;
	}
	
	BlockCount++;
}

void DLlist::get_list_info()
{
	Block* current = first;
	while(current) {
		printf("(%d, %d)<-->", current->key, current->value);
		current = current->next;
	}
}