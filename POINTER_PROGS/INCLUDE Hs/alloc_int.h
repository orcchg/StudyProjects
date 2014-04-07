#define NULL 0 //ERROR POINTER VALUE
#define ALLOCSIZE 1000 //SIZE OF AVAILABLE SPACE

static int ALLOCBUF[ALLOCSIZE]; //STORAGE FOR ALLOC
static int* pALLOC = ALLOCBUF; //NEXT FREE POSITION

int* alloc(int N){ //RETURN POINTER TO 1st position of AREA FOR next N CHARACTERS

	if(pALLOC + N <= ALLOCBUF + ALLOCSIZE){
		pALLOC += N;
		return(pALLOC - N); //OLD POINTER position
	} else { //NOT ENOUGH ROOM IN ALLOCSIZE
		return(NULL);
	}
}

void free(int* pP){ //FREE STORAGE POINTED BY pP

	if(pP >= ALLOCBUF && pP < ALLOCBUF + ALLOCSIZE)
		pALLOC = pP;
}