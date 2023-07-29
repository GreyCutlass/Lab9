#include <stdio.h>
#include <stdlib.h>

#define HASHTABLE_SIZE 8
// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
typedef struct HashType
{
	int id;
	char name;
	int order;
	struct HashType* next;

} HashType_t;

// Compute the hash function
int hash(int x)
{

	return x % HASHTABLE_SIZE;

}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	struct HashType * nextPtr = NULL;

	for (i=0;i<hashSz;++i)
	{

		printf("Index: %d\n", i);
		nextPtr = (pHashArray+i);

		printf("%d ", nextPtr->id);
		printf("%c ", nextPtr->name);
		printf("%d ", nextPtr->order);
		nextPtr = nextPtr->next;

		while (nextPtr != NULL)
		{
			
			printf("-> ");
			printf("%d ", nextPtr->id);
			printf("%c ", nextPtr->name);
			printf("%d ", nextPtr->order);

			nextPtr = nextPtr->next;
		};

		printf("\n");
		
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	struct HashType phTable[HASHTABLE_SIZE];

	int hashNumber = 0;

	for(int index = 0; index < HASHTABLE_SIZE; ++index)
	{

		phTable[index].id = 0;
		phTable[index].order = 0;
		phTable[index].name = '\0';
		phTable[index].next = NULL;

	}

	for(int index = 0; index < recordSz; ++index)
	{

		hashNumber = hash(pRecords[index].id);
		if(phTable[hashNumber].id == 0)
		{

			phTable[hashNumber].id = pRecords[index].id;
			phTable[hashNumber].name = pRecords[index].name;
			phTable[hashNumber].order = pRecords[index].order;

		}
		else
		{


			
			if(phTable[hashNumber].next != NULL)
			{

			
				struct HashType* nextPtr = NULL;
				nextPtr = phTable[hashNumber].next;
				while(nextPtr->next != NULL)
				{

					nextPtr = nextPtr->next;

				}

				nextPtr->next = (struct HashType*)malloc(sizeof(struct HashType));
				nextPtr = nextPtr->next;
				nextPtr->id = pRecords[index].id;
				nextPtr->name = pRecords[index].name;
				nextPtr->order = pRecords[index].order;
				nextPtr->next = NULL;

			}
			else
			{

				phTable[hashNumber].next = (struct HashType*)malloc(sizeof(struct HashType));
				struct HashType* nextPtr = phTable[hashNumber].next;
				nextPtr->id = pRecords[index].id;
				nextPtr->name = pRecords[index].name;
				nextPtr->order = pRecords[index].order;
				nextPtr->next = NULL;

			}
			


		}


	}


	displayRecordsInHash(phTable, HASHTABLE_SIZE);

	for(int index = 0; index < HASHTABLE_SIZE; ++index)
	{

		if(phTable[index].next != NULL)
		{

			struct HashType *nextPtr = phTable[index].next;
			struct HashType *tempPtr;
			

			while(nextPtr != NULL)
			{

				tempPtr = nextPtr->next;
				free(nextPtr);
				nextPtr = tempPtr;

			}

		}



	}
}