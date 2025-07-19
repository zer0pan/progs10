#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage : ./recover <filename.raw>");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("card could not be opened");
        return 1;
    }

    uint8_t buffer[512];
    int fcount = -1; // file count

    FILE *jpeg;

    while (fread(buffer, 1, 512, card) == 512) // fread returns the number (int) of elements it read from card
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if the above condition is true , then i discovered a NEW jpeg file

            char *filename = malloc(sizeof(char) * 8); // ###.jpg (== 7 characters + \0)

            fcount++;

            if (fcount == 0)
            {

                sprintf(filename, "%03i.jpg", fcount);
                jpeg = fopen(filename, "w");
                if (jpeg == NULL)
                {
                    printf("card could not be opened");
                    return 1;
                }
                fwrite(buffer, 1, 512, jpeg);
            }
            else
            {
                // close the previous file
                fclose(jpeg);
                sprintf(filename, "%03i.jpg", fcount);
                jpeg = fopen(filename, "w");
                if (jpeg == NULL)
                {
                    printf("card could not be opened");
                    return 1;
                }
                fwrite(buffer, 1, 512, jpeg);
            }
            free(filename);
        }
        else if (fcount >= 0)
        {
            fwrite(buffer, 1, 512, jpeg);
        }
    }
    if (jpeg != NULL) // for security reasons
    {
        fclose(jpeg);
    }

    fclose(card);

    return 0;
}