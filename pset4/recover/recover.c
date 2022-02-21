#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Missing file name");
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    if (!card)
    {
        printf("Invalid File\n");
        return 1;
    }
    typedef uint8_t
    BYTE;
    int counter = 0;
    int img_counter = 0;
    char *filename = malloc(8);
    FILE *img;
    BYTE buffer[512];
    for (int i = 0; i > -1; i++)
    {
        if (fread(buffer, 512, 1, card) != 1)
        {
            //printf("Done\n");
            return 0;
        }
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (counter == 1)
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", img_counter);
            img_counter++;
            //printf("Image counter: %i\n", img_counter);
            counter = 1;
            img = fopen(filename, "w");
            fwrite(buffer, 512, 1, img);
        }
        else if (counter == 1)
        {
            fwrite(buffer, 512, 1, img);
        }
    }
    fclose(card);
    free(filename);
}
