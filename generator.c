#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#define FACTOR 0.15f

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("Usage: ./generator <N>\n");
		return 1;
	}
	int n = atoi(argv[1]);
	uint8_t (*matrix)[n] = malloc(n*n*sizeof(uint8_t));
	srand(time(NULL));
	for (int row=0; row<n; row++)
		for (int col=0; col<row; col++)
			matrix[row][col]=matrix[col][row] = rand()/(float)RAND_MAX<=FACTOR;
	for (int i=0; i<n; i++) matrix[i][i]=1;
	
	freopen("matrix.txt","w",stdout);
	printf("%d\n",n);
	for (int row=0; row<n; row++)
	{
		for (int col=0; col<n; col++) printf("%hhd ",matrix[row][col]);
		printf("\n");
	}
}
