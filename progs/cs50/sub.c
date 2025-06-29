#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char encrypt(char let, char *abc, char *key)
{
    for (int i = 0; i < strlen(abc); i++)
    {
        if (let == abc[i])
        {
            return key[i];
        }
    }
}

char decrypt(char let, char *abc, char *key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (let == key[i])
        {
            return abc[i];
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./sub key\n");
        return 1;
    }

    // printf("%i\n", argc); // argc == 2
    // printf("key 1 is %s\n", argv[1]); (for debug)

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters. but there are %ld \n", strlen(argv[1]));
        return 1;
    }

    // argc == 2 and strlen(argv[1]) == 26
    const string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // argv[1] is type string like
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!(isalpha(argv[1][i])))
        {
            printf("Key must contain only letters \n");
            return 1;
        }
        argv[1][i] = toupper(argv[1][i]);
    }

    for (int i = 0; i < strlen(argv[1]) - 1; i++)
    {
        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("The key must not have repeated characters\n");
                return 1;
            }
        }
    }

    char ans = get_char("Do you want to encrypt (type 0) or to decrypt(type 1)? ");
    while (ans != '0' && ans != '1')
    {
        char ans = get_char("type 0 to encrypt or 1 to decrypt ");
    }
    if (ans == '0')
    {
        string text = get_string("plaintext: ");
        // text = "This is CS50"
        for (int i = 0; i < strlen(text); i++)
        {
            if (isalpha(text[i]))
            {
                if (islower(text[i]))
                {
                    text[i] = tolower(encrypt(toupper(text[i]), abc, argv[1]));
                }
                else
                {
                    text[i] = encrypt(text[i], abc, argv[1]);
                }
            }
        }

        printf("ciphertext: %s\n", text);
    }
    else
    {
        string text = get_string("ciphertext: ");
        // text = "sjdk sdjvn skd"
        for (int i = 0; i < strlen(text); i++)
        {
            if (isalpha(text[i]))
            {
                if (islower(text[i]))
                {
                    text[i] = tolower(decrypt(toupper(text[i]), abc, argv[1]));
                }
                else
                {
                    text[i] = decrypt(text[i], abc, argv[1]);
                }
            }
        }

        printf("plaintext: %s\n", text);
    }
    return 0;
}
