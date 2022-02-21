#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    printf("\n");
    float letters = strlen(text);
    float words = 1;
    float sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ((text[i] < 65) || (text[i] > 90 && text[i] < 97) || text[i] > 122)
        {
            letters -= 1;
        }
        if (text[i] == 32)
        {
            words += 1;
        }
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences += 1;
        }
    }
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    if ((index >= 1) && (index <= 16))
    {
        printf("Grade %i\n", index);
    }
}