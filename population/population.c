#include <cs50.h>
#include <stdio.h>

int get_start_size(void);
int get_end_size(int start_size);
int calculate_years_to_grow(int start_size, int end_size);

int main(void)
{
    // Prompt for start size
    int start_size = get_start_size();

    // Prompt for end size
    int end_size = get_end_size(start_size);

    // Calculate number of years until we reach threshold
    int years = calculate_years_to_grow(start_size, end_size);

    // Print number of years
    printf("Years: %i\n", years);
}

int get_start_size(void)
{
    int n;
    do
    {
        n = get_int("Start size: ");
    }
    while (n < 9);
    return n;
}

int get_end_size(int start_size)
{
    int n;
    do
    {
        n = get_int("End size: ");
    }
    while (n < start_size);
    return n;
}

int calculate_years_to_grow(int start_size, int end_size)
{
    int size = start_size;
    int years = 0;
    if (size < end_size)
    {
        do
        {
            size = size + (size / 3) - (size / 4);
            years++;
        }
        while (size < end_size);
    }
    return years;
}