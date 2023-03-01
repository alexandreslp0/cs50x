#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_char_n_times(char c, int n);
void print_pyramid(int size);

int main(void)
{
    // Get size for pyramid
    int size = get_size();

    // Print pyramid
    print_pyramid(size);

}

int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);
    return n;
}

void print_char_n_times(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}

void print_pyramid(int size)
{
    int init_spaces = size - 1;
    for (int i = 0; i < size; i++)
    {
        print_char_n_times(' ', init_spaces);
        print_char_n_times('#', (i + 1));
        printf("  ");
        print_char_n_times('#', (i + 1));
        printf("\n");
        init_spaces--;
    }
}
