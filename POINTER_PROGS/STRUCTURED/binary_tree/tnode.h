//yzel - NODE

struct tnode{ //PARENT NODE
	
	char* word; //POINTS TO THE TEXT LINE
	int count; //NUMBER OF OCCURENCES
	struct tnode* left; //LEFT CHILD
	struct tnode* right; //RIGHT CHILD
	
};