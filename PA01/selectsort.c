#ifdef SELECTION_SORT
#include "pa01.h"
void selectSort(int * arr, int size)
//arr : the array to be sorted
//size : the number of elements in the array

// In each iteration, the number of elements to be sorted shrinks by one
// i.e., one element is at the correct position.
//
// Among the remaining elements, find the smallest value and put it 
// before the other unsorted elements
{
	for(int count = 0; count < (size - 1); count++)
	{
		int spot = count;
		int change;

		for(int location = count + 1; location < size; location++)
		{
			if(arr[spot] > arr[location])
			{
				spot = location;
			}
		}
		if(spot != count)
		{
			change = arr[count];
			arr[count] = arr[spot];
			arr[spot] = change;
		}
	}
}
#endif
