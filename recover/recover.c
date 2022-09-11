#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
//define the block size of the FAT file system which is 512 bytes
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    //program should accept exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }
    // open memory card
    FILE *input = fopen(argv[1], "r");
    //If the forensic image cannot be opened for reading,
    if (input == NULL)
    {
        printf("The file can not be opened");
        return 1;
    }
    // create a new type to store a byte of data
    typedef uint8_t BYTE;
    // buffer for reading one block of 512 bytes at a time
    BYTE buffer[BLOCK_SIZE];
    // counter for numbering the output file
    int i = 0;
    // allocate memory for the filename
    char *filename = malloc(8);
    bool found = false;
    FILE *img = NULL;
    //repeat until end of card and read 512 bytes into a buffer
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // if start of new JPEG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            found = true;
            // if first JPEG
            if (i == 0)
            {
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
                i++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
                i++;
            }

        }
        else
        {
            // if already found JPEG
            if (found == true)
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
        }
    }
    fclose(img);
    free(filename);
}