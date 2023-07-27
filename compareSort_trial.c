#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void merge(int pData[], int l, int m, int r)
{
	int i;
	int j;
	int k;
	int n1 = m - l + 1;
	int n2 = r - m;

	//creates temporary arrays
	int *L = (int*) malloc(n1*sizeof(int));
	int *R = (int*) malloc(n2*sizeof(int));


	//copy the data over to the temporary arrays
	for (i = 0; i < n1; i++)
		L[i] = pData[l + i];
	for (j = 0; j < n2; j++)
		R[j] = pData[m + 1 + j];


	//the next section merges the temporry arrays back into pData array
	i = 0;
	j = 0;
	k = l;

	while (i < n1 && j < n2){
		if (L[i] <= R[j]){
			pData[k] = L[i];
			i++;
		}
		else{
			pData[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1){
		pData[k] = L[i];
		i++;
		k++;
	}
	while (j < n2){
		pData[k] = R[j];
		j++;
		k++;
	}
	//frees the temporary arrays
	free(L);
	free(R);
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{


int *tempArray;

if (l < r)
{
int m = (l+r)/2;

// Only allocate a temporary array for the first recursive call
if (l == 0)
{
tempArray = (int*) malloc(sizeof(int)*(r - l + 1));
}

// Sort first and second halves
mergeSort(pData, l, m);
mergeSort(pData, m+1, r);

merge(pData, l, m, r);

// Free the temporary array
if (l == 0)
{
free(tempArray);
}

// Update the extra memory allocated
if (l == 0)
{
extraMemoryAllocated += sizeof(int)*(r - l + 1);
}
}
}

	


// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, item, j;
for (i = 1; i < n; i++)
{
item = pData[i];
/* Move elements of pData[0..i-1], that are
greater than key, to one position ahead
of their current position */
for(j=i-1; j>=0; j--)
{
if(pData[j]>item)
pData[j+1] = pData[j];
else
break;
}
pData[j+1] = item;
}
	// Update the extra memory allocated
extraMemoryAllocated += sizeof(int);
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int i, j,temp;
for (i = 0; i < n-1; i++)
{
for (j = 0; j < n-i-1; j++)
{
if (pData[j] > pData[j+1])
{//then swap
temp=pData[j];
pData[j]=pData[j+1];
pData[j+1]=temp;
}
}
}
	// Update the extra memory allocated
extraMemoryAllocated += sizeof(int);
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int i, j, min_idx, temp;
// One by one move boundary of unsorted subarray
for (i = 0; i < n-1; i++)
{
// Find the minimum element in unsorted array
min_idx = i;
for (j = i+1; j < n; j++)
if (pData[j] < pData[min_idx])
min_idx = j;
// Swap the found minimum element with the first element
temp = pData[i];
pData[i] = pData[min_idx];
pData[min_idx] = temp;

}
// Update the extra memory allocated
extraMemoryAllocated += sizeof(int);	
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for (int i = 0; i < dataSz; i++)
        {
            fscanf(inFile, "%d", &((*ppData)[i]));
        }

        fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}