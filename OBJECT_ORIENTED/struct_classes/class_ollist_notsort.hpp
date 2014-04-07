#include <cstdio>
//Header File

typedef int mkey_tns; //key type
typedef int value_tns; //value type

const value_tns errval = -999;
const value_tns success = +999;

class OLlist_NotSort {
	struct Block {
		mkey_tns key;
		value_tns value;
		struct Block* next;
				
		Block(mkey_tns k, value_tns val, Block* ptr = NULL){
			key = k;
			value = val;
			next = ptr;
		}
	};
	
	Block* first;
	Block* last;
			  
	public:
		int BlockCount;
	
		OLlist_NotSort() {
			BlockCount = 0;
			first = last = NULL;
		}
		
		OLlist_NotSort(const OLlist_NotSort& obj);
		~OLlist_NotSort();
		
		value_tns take_head() const {
			return first->value;
		}
		
		value_tns take_tail() const {
			return last->value;
		}
		
		void add_list_to_last(const OLlist_NotSort& obj); //add new linked list to tail of previous Ll
		void add_val_to_first(mkey_tns key, value_tns val);
		void add_val_to_last(mkey_tns key, value_tns val);
		value_tns find_el(mkey_tns);
		value_tns delete_first();
		value_tns delete_el(mkey_tns key);
		value_tns insert_any_pos(mkey_tns key, value_tns val, int pos);
		
		int get_count() const {
			return BlockCount;
		}
		
		void get_list_info();
};

//Source File

OLlist_NotSort::OLlist_NotSort(const OLlist_NotSort& obj) 
{
	BlockCount = 0;
	first = last = NULL;
	add_list_to_last(obj);
}

OLlist_NotSort::~OLlist_NotSort()
{
	Block* current = NULL;
	Block* next = first;
	
	while(next) {
		current = next;
		next = next->next;
		delete current;
	}
}

void OLlist_NotSort::add_list_to_last(const OLlist_NotSort& obj)
{
	for(Block* cur = obj.first; cur; cur = cur->next)
		add_val_to_last(cur->key, cur->value);
}

void OLlist_NotSort::add_val_to_first(mkey_tns key, value_tns val)
{
	Block* newBlock = new Block(key, val, first);
	if(!first) {
		last = newBlock;
	}
	
	first = newBlock;
	BlockCount++;
}

void OLlist_NotSort::add_val_to_last(mkey_tns key, value_tns val)
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

value_tns OLlist_NotSort::find_el(mkey_tns key)
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
	
value_tns OLlist_NotSort::delete_first()
{
		value_tns result = first->value;
		first = first->next;
		BlockCount--;
		return result;
}

value_tns OLlist_NotSort::delete_el(mkey_tns key)
{
	Block* prev = NULL, *current = first;
	value_tns val = 0;
	
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

value_tns OLlist_NotSort::insert_any_pos(mkey_tns key, value_tns val, int pos)
{
	Block* prev = NULL, *current = first;
	int point=0,sum=0;
	
	//Number of positions: first = 0; last = L:
	while(current) {
		current = current->next;
		sum+=1;
	}
	
	current = first;
	if(pos < 0 || pos > sum)
		return errval;
	
	while(point < pos) {
		prev = current;
		current = current->next;
		point++;
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
	
	return success;
}

void OLlist_NotSort::get_list_info()
{
	Block* current = first;
	while(current) {
		printf("(%d, %d)-->", current->key, current->value);
		current = current->next;
	}
}