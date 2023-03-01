#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

string get_text(void);
int count_letters(string text);
int count_words(string text);
int count_setences(string text);
void print_grade(int letters, int words, int setences);

int main(void)
{
    // getting user input
    string text = get_text();
    // count letters
    int letters = count_letters(text);
    // count words
    int words = count_words(text);
    // count setences
    int setences = count_setences(text);
    // print readability
    print_grade(letters, words, setences);
}

string get_text(void)
{
    string s = get_string("Text: ");
    return s;
}

int count_letters(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            sum += 1;
        }
    }
    return sum;
}

int count_words(string text)
{
    int sum = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            sum += 1;
        }
    }
    return sum;
}

int count_setences(string text)
{
    int sum = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sum += 1;
        }
    }
    return sum;
}

void print_grade(int letters, int words, int setences)
{
    float L = (float) letters / words * 100;
    float S = (float) setences / words * 100;
    int index = roundf((0.0588 * L - 0.296 * S - 15.8));
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}