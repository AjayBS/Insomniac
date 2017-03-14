#include "MemoryManager.h"
#include <stdio.h>


namespace MemoryManager
{
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT 
	//
	// This is the only static memory that you may use, no other global variables may be
	// created, if you need to save data make it fit in MM_pool
	//
	// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT
	void setGuardBand(int index);
	int getTheSizeOfTheBlock(int index);
	void clearGuardBandAndValues(int index);

	const int MM_POOL_SIZE = 50;
	char MM_pool[MM_POOL_SIZE];

	// Initialize set up any data needed to manage the memory pool
	void initializeMemoryManager(void)
	{
		// TODO : IMPLEMENT ME
		size_t initialMemorySize = sizeof(MM_pool);
		for (int i = 0; i < sizeof(MM_pool);i++) {
			MM_pool[i] = -2;
		}
		//sprintf_s(MM_pool, "%ld", initialMemorySize);
	}

	// return a pointer inside the memory pool
	// If no chunk can accommodate aSize call onOutOfMemory()
	void* allocate(int aSize)
	{
		// TODO: IMPLEMENT ME
		for (int i = 0; i < sizeof(MM_pool); i++) {
			if (MM_pool[i] == -2) {
				int j = i;
				bool sizeAvailable = true;
				for (int k = 0; k < aSize - 1 + 8; k++) {
					if (MM_pool[j] != -2) {
						sizeAvailable = false;
						break;
					}
					j++;
				}
				if (sizeAvailable)
				{					
					setGuardBand(i);
					int j = i + 4 + aSize;
					setGuardBand(j);
				
					return reinterpret_cast<void *>(&MM_pool[i + 4]);
				}
			}
		}

		onOutOfMemory();
		return ((void*)0);
	}

	// Free up a chunk previously allocated
	void deallocate(void* aPointer)
	{
		// TODO: IMPLEMENT ME
		bool itemFound = false;
		for (int i = 0; i < sizeof(MM_pool);i++) {
			if (aPointer == &MM_pool[i] && MM_pool[i] != -2) {
				printf("Found item");
				clearGuardBandAndValues(i);
				itemFound = true;
				break;
			}
		}

		if (!itemFound) {
			onIllegalOperation("Memory has already been freed for this address");
		}
	}

	//---
	//--- support routines
	//--- 

	// Will scan the memory pool and return the total free space remaining
	int freeRemaining(void)
	{
		int size = 0;
		// TODO: IMPLEMENT ME
		for (int i = 0; i < sizeof(MM_pool); i++) {
			if (MM_pool[i] == '0' && MM_pool[i + 1] == 'x' && MM_pool[i + 2] == 'D' && MM_pool[i + 3] == 'B') {
				i += 4;
				i += getTheSizeOfTheBlock(i) + 3;
			}
			else
			size++;
		}
		return size;
	}

	// Will scan the memory pool and return the largest free space remaining
	int largestFree(void)
	{
		// TODO: IMPLEMENT ME
		int size = 0;
		int largest = 0;
		// TODO: IMPLEMENT ME
		for (int i = 0; i < sizeof(MM_pool); i++) {
			if (MM_pool[i] == '0' && MM_pool[i + 1] == 'x' && MM_pool[i + 2] == 'D' && MM_pool[i + 3] == 'B') {
				i += 4;
				i += getTheSizeOfTheBlock(i) + 3;
				size = 0;
			}
			else
				size++;

			if (size > largest) {
				largest = size;
			}
		}
		return largest;
	}

	// will scan the memory pool and return the smallest free space remaining
	int smallestFree(void)
	{
		// TODO: IMPLEMENT ME
		int size = 0;
		int smallest = MM_POOL_SIZE;
		bool firstPass = true;
		// TODO: IMPLEMENT ME
		for (int i = 0; i < sizeof(MM_pool); i++) {
			if (MM_pool[i] == '0' && MM_pool[i + 1] == 'x' && MM_pool[i + 2] == 'D' && MM_pool[i + 3] == 'B') {
				i += 4;
				i += getTheSizeOfTheBlock(i) + 3;
				if (size < smallest && size!=0)
					smallest = size;

				size = 0;				
			}
			else
				size++;		
		}
		if (size != MM_POOL_SIZE && smallest == MM_POOL_SIZE)
			smallest = size;

		return smallest;
	}

	void setGuardBand(int index) {
		MM_pool[index++] = '0';
		MM_pool[index++] = 'x';
		MM_pool[index++] = 'D';
		MM_pool[index++] = 'B';
	}

	void clearGuardBandAndValues(int index) {
		index = index - 4;
		MM_pool[index++] = -2;
		MM_pool[index++] = -2;
		MM_pool[index++] = -2;
		MM_pool[index++] = -2;

		for (int i = index; i < sizeof(MM_pool); i++) {
			if (MM_pool[i] == '0' && MM_pool[i + 1] == 'x' && MM_pool[i + 2] == 'D' && MM_pool[i + 3] == 'B') {
				MM_pool[i++] = -2;
				MM_pool[i++] = -2;
				MM_pool[i++] = -2;
				MM_pool[i++] = -2;
				break;
			}
			MM_pool[i] = -2;
		}
	}

	int getTheSizeOfTheBlock(int index) {
		int blockSize = 0;
		for (int i = index; i < sizeof(MM_pool); i++) {
			if (MM_pool[i] != '0' && MM_pool[i + 1] != 'x' && MM_pool[i + 2] != 'D' && MM_pool[i + 3] != 'B') {
				blockSize++;
			}
			else
				break;
		}
		return blockSize;
	}
}