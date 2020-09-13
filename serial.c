#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

int* degree;
int compare(const void *a, const void *b)
{
	return degree[*(const int*)a]-degree[*(const int*)b];
}

int main()
{
	freopen("matrix.txt","r",stdin);
	FILE* fout = fopen("perm.out","w");
	int n;
	scanf("%d",&n);
	int8_t (*matrix)[n] = malloc(n*n*sizeof(int8_t));
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++) scanf("%hhd",&matrix[i][j]);
	
	//start the timer
	struct timeval begin;
	gettimeofday(&begin,NULL);
	printf("Finished reading, timer started!\n");
	
		 degree = calloc(n,sizeof(int)); //precompute degree of all nodes
	int* perm	= malloc(n*sizeof(int)); //final permutation (not reversed)
	int** alist = malloc(n*sizeof(int*)); //adjacency list of every node
	int8_t* vis = calloc(n,sizeof(int8_t)); //bool set to 1 if node already in perm
	
	for (int row=0; row<n; row++)
		for (int col=0; col<n; col++) 
			degree[row] += matrix[row][col];
	
	for (int i=0; i<n; i++) perm[i]=i;
	qsort(perm,n,sizeof(int),compare);
	
	for (int row=0; row<n; row++)
	{
		alist[row] = malloc(degree[row]*sizeof(int));
		for (int tail=0,i=0; tail<degree[row]; i++) 
			if (matrix[row][perm[i]]) 
				alist[row][tail++] = perm[i]; 
	}
	for (int row=0; row<n; row++)
		if (degree[row] < degree[perm[0]])
			perm[0] = row;
	
	vis[perm[0]]=1;
	for (int tail=1, i=0; tail<n; i++) //for every element in perm
		for (int j=0; j<degree[perm[i]]; j++) //for every neighbor of the element
			if (!vis[ alist[perm[i]][j] ])
			{
				vis[ alist[perm[i]][j] ] = 1;
				perm[tail++] = alist[perm[i]][j];
			}
			
	struct timeval now;
	gettimeofday(&now,NULL);
	printf("Computation finished in %lf ms.\n",(now.tv_sec-begin.tv_sec)*1000 + (now.tv_usec-begin.tv_usec)/1000.0);

	for (int i=n-1; i>=0; i--) fprintf(fout,"%d ",perm[i]);	
}
