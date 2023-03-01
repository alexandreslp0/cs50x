#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Array of candidates
int numbers_count = 18;
int numbers[] = {9, 5, 10, 101, 4, 6, 8, 0, 11, 1, 12, 3, 7, 78, 54, 21, 92, 2};

void merge_sort(int arr[], int init, int stop);
void merge(int arr[], int init, int mid, int stop);


int main(void)
{
    merge_sort(numbers, 0, numbers_count - 1);

    for (int i = 0; i < numbers_count; i++)
    {
        printf("%i ", numbers[i]);
    }
    printf("\n");
}


void merge_sort(int arr[], int init, int stop)
{
    if (init >= stop)
    {
        return;
    }

    // find mid value
    int mid = ((stop - init) / 2) + init;

    // sort left of array
    merge_sort(arr, init, mid);

    // sort right of array starting middle + 1 (small array in odd sizes)
    merge_sort(arr, mid + 1, stop);

    // merge sorted arrays
    merge(arr, init, mid, stop);

}

void merge(int arr[], int init, int mid, int stop)
{
    // find size of left and right arrays
    int size_left = mid - init + 1;
    int size_right = stop - mid;

    // create two temp arrays
    int left_arr[size_left], right_arr[size_right];

    // populate temp arrays
    for (int i = 0; i < size_left; i++)
    {
        left_arr[i] = arr[init + i];
    }
    for (int j = 0; j < size_right; j++)
    {
        right_arr[j] = arr[mid + 1 + j];
    }

    int i = 0; // represent left_array index
    int j = 0; //represent right_array index
    int k = init; // represent original array index

    while (i < size_left && j < size_right)
    {
    if (left_arr[i] <= right_arr[j])
    {
        arr[k] = left_arr[i];
        i++;
    }
    else
    {
        arr[k] = right_arr[j];
        j++;
    }
    k++;
    }

    // copying items of left that have been left
    while (i < size_left)
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }

    // copying items of right that have been left
    while (j < size_right)
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}