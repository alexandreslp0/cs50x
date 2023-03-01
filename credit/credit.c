#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

long get_card_number();
int sum_of_digits(int number);
int magical_card_number_sum(long card_number);
void check_card(long card_number);

int main(void)
{
    // Get card number from user
    long card_number = get_card_number();

    // check card
    check_card(card_number);
}

long get_card_number()
{
    long n;
    do
    {
        n = get_long("Credit card number: ");
    }
    while (n < 1);
    return n;
}

int sum_of_digits(int number)
{
    int t, sum = 0, remainder;
    t = number;

    while (t != 0)
    {
        remainder = t % 10;
        sum       = sum + remainder;
        t         = t / 10;
    }
    return sum;
}

int magical_card_number_sum(long card_number)
{
    char card_number_str[256];
    sprintf(card_number_str, "%ld", card_number); // transform card_number in str

    int sum = 0;
    int card_length = strlen(card_number_str);

    for (int i = 0; i < card_length; i++)
    {
        char number_char = card_number_str[(card_length - i - 1)]; // get char starting with the last
        int number = (int)number_char - 48; // transform char in int
        if ((i % 2) != 0) // to pass in every other digit
        {
            int double_number = number * 2;
            if (double_number > 9) // to decide if get sum or just the digit
            {
                sum = sum + sum_of_digits(double_number);
            }
            else
            {
                sum = sum + double_number;
            }
        }
        else
        {
            sum = sum + number;
        }
    }
    return sum;
}

void check_card(long card_number)
{
    int card_sum = magical_card_number_sum(card_number);

    char card_number_str[256];
    sprintf(card_number_str, "%ld", card_number); // transform card_number in str

    int card_length = strlen(card_number_str);

    if (card_sum % 10 == 0)
    {
        if (card_number_str[0] == '4')
        {
            if (card_length == 13 || card_length == 16)
            {

                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        if (card_number_str[0] == '3')
        {
            if (card_number_str[1] == '4' || card_number_str[1] == '7')
            {
                if (card_length == 15)
                {

                    printf("AMEX\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }

        if (card_number_str[0] == '5')
        {
            if (strchr("12345", card_number_str[1]))
            {
                if (card_length == 16)
                {

                    printf("MASTERCARD\n");
                }
                else
                {
                    printf("INVALID\n");
                }
            }
            else
            {
                printf("INVALID\n");
            }
        }
        if (strchr("1267890", card_number_str[0]))
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}