#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE; // uint8_t is an 8 bit integer
typedef char *string;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
    }

    string card = argv[1];
    
    // Open the memory card
    FILE *f = fopen(card, "r");
    if (f == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];

    // Number of jpeg files
    int n = 0;
    // Check if reached the fist if stetment atleat once
    bool firstStart = false;
    FILE *img = NULL;

    // fread returns 0 when reaching the end of file
    // Read 512 data elements, each of which is 1 byte long.
    while ((fread(buffer, sizeof(BYTE), BLOCK_SIZE, f)))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            // if recoverd the whole img corectly, close it
            if (firstStart)
            {
                fclose(img);
            }
            firstStart = true;
            char filename[8] ;
            sprintf(filename, "%03i.jpg", n); // Print to string
            n++;
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
        else if (firstStart)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }


    }
    fclose(img);
    fclose(f);
    return 0;
}