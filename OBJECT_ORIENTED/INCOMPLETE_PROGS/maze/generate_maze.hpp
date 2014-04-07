#include <stdlib.h>

char** generate_maze(const int N, const int M)
{
	int rnd = 0;
	char MAZE[N][M];
	char** ptr = &MAZE[0][0];
	
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			rnd = rand();
			if(rnd > RAND_MAX/2) {
				MAZE[i][j] = '#';
			} else {
				MAZE[i][j] = '.';
			}
		}
	}
	
	return ptr;
}