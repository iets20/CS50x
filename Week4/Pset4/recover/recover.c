#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //define where a data to store bytes
    typedef uint8_t BYTE;
    //ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    //Open file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    int counter = 0;
    BYTE *buffer = malloc(512);
    if (buffer == NULL)
    {
        return 1;
    }
    char *filename = malloc(8) ;
    FILE *new_file = NULL;
    while (fread(buffer, 1, 512, inptr) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter != 0)
            {
                fclose(new_file);
            }
            // create a JPEG file
            sprintf(filename, "%03i.jpg", counter);

            //open this JPEG file to w
            new_file = fopen(filename, "w");
            if (new_file == NULL)
            {
                printf("Could not create file\n");
                return 1;
            }
            //write in the new file and update the counter of images
            fwrite(buffer, 1, 512, new_file);
            counter++;

        }
        //VERY IMPORTANT check if the new_file is open first
        else if (new_file != NULL)
        {
            fwrite(buffer, 1, 512, new_file);
        }

    }
    fclose(inptr);
    fclose(new_file);
    free(filename);
    free(buffer);
}