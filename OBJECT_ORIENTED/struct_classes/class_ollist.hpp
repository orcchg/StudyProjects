#include <cstdio>
//Header File

typedef int mkey_t; //key type
typedef int value_t; //value type

const value_t errval = -999;

class OLlist {
	struct Block {
		mkey_t key;
		value_t value;
		struct Block* next;
				
		Block(mkey_t k, value_t val, Block* ptr = NULL){
			key = k;
			value = val;
			next = ptr;
		}
	};
	
	Block* first;
	Block* last;
			  
	public:
		int BlockCount;
	
		OLlist() {
			BlockCount = 0;
			first = last = NULL;
		}
		
		OLlist(const OLlist& obj);
		~OLlist();
		
		value_t take_head() const {
			return first->value;
		}
		
		value_t take_tail() const {
			return last->value;
		}
		
		void add_list_to_last(const OLlist& obj); //add new linked list to tail of previous Ll
		void add_val_to_first(mkey_t key, value_t val);
		void add_val_to_last(mkey_t key, value_t val);
		value_t find_el(mkey_t key);
		value_t delete_first();
		value_t delete_el(mkey_t key);
		void insert(mkey_t key, value_t val);
		
		int get_count() const {
			return BlockCount;
		}
		
		void get_list_info();
};

//Source File

OLlist::OLlist(const OLlist& obj) 
{
	BlockCount = 0;
	first = last = NULL;
	add_list_to_last(obj);
}

OLlist::~OLlist()
{
	Block* current = NULL;
	Block* next = first;
	
	while(next) {
		current = next;
		next = next->next;
		delete current;
	}
}

void OLlist::add_list_to_last(const OLlist& obj)
{
	for(Block* cur = obj.first; cur; cur = cur->next)
		add_val_to_last(cur->key, cur->value);
}

void OLlist::add_val_to_first(mkey_t key, value_t val)
{
	Block* newBlock = new Block(key, val, first);
	if(!first) {
		last = newBlock;
	}
	
	first = newBlock;
	BlockCount++;
}

void OLlist::add_val_to_last(mkey_t key, value_t val)
{
	Block* newBlock = new Block(key, val, NULL);
	if(!last) {
		first = newBlock;
	} else {
		last->next = newBlock;
	}
	
	last = newBlock;
	BlockCount++;
}

value_t OLlist::find_el(mkey_t key)
{
	Block* current = first;
	while(current) {
		if(current->key == key) {
			return current->value;
		}
		current = current->next;
	}
	return errval;
}
	
value_t OLlist::delete_first()
{
		value_t result = first->value;
		first = first->next;
		BlockCount--;
		return result;
}

value_t OLlist::delete_el(mkey_t key)
{
	Block* prev = NULL, *current = first;
	value_t val = 0;
	
	while(current) {
		if(current->key == key) {
			if(prev) {
				prev->next = current->next;
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

void OLlist::insert(mkey_t key, value_t val)
{
	Block* prev = NULL, *current = first;
	
	while(current != NULL && current->key < key) {
		prev = current;
		current = current->next;
	}
	
	Block* newBlock = new Block(key, val, current);
	if(current == NULL) {
		last = newBlock;
	}
	
	if(prev == NULL) {
		first = newBlock;
	} else {
		prev->next = newBlock;
	}
	
	BlockCount++;
}

void OLlist::get_list_info()
{
	Block* current = first;
	while(current) {
		printf("(%d, %d)-->", current->key, current->value);
		current = current->next;
	}
}