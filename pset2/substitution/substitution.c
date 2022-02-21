#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Missing Command Line Argument\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must be 26 characters\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (i != j)
            {
                if (argv[1][i] == argv[1][j])
                {
                    printf("Each character must be unique\n");
                    return 1;
                }
            }
        }
        if ((argv[1][i] < 65) || (argv[1][i] > 90 && argv[1][i] < 97) || argv[1][i] > 122)
        {
            printf("Letters Only\n");
            return 1;
        }

    }
    string plain = get_string("Plain Text: ");
    string key = argv[1];
    string cipher = plain;
    printf("ciphertext: ");
    for (int k = 0; plain[k] != '\0'; k++)
    {
        if (plain[k] > 64 && plain[k] < 91)
        {
            for (int l = 0; l < 26; l++)
            {
                key[l] = toupper(key[l]);
            }
            cipher[k] = key[plain[k] - 65];
            printf("%c", cipher[k]);
        }
        else if (plain[k] > 96 && plain[k] < 123)
        {
            for (int m = 0; m < 26; m++)
            {
                key[m] = tolower(key[m]);
            }
            cipher[k] = key[plain[k] - 97];
            printf("%c", cipher[k]);
        }
        else
        {
            cipher[k] = plain[k];
            printf("%c", cipher[k]);
        }
    }
    printf("\n");
    return 0;
}