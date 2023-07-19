#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, 44, 1, input);

    // Use check_format to ensure WAV format
    if (check_format(header) == 1)
    {
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        return 1;
    }

    // Write header to file
    fwrite(&header, 44, 1, output);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

// Write reversed audio to file
    //array to store los bloques de audio
    BYTE *audio = malloc(block_size);
    //movemos el puntero hasta el final del archivo de audio
    fseek(input, 0, SEEK_END);
    // con ftell(input) obtenemos los bytes de todo el archivo
    //al restar sizeof(WAVHEADER) obtenemos los bytes de audio
    long audio_bytes = ftell(input) - sizeof(WAVHEADER);
    // al dividir block size que es la unidad de cada bloque de audio
    //obtenemos la cantidad de bloques de audio del archivo
    int block_audio = (int) audio_bytes / block_size;

    //iteramos para obtener los bloques de audio finales y copiarlos
    for (int i = 1; i <= block_audio; i++)
    {
        //recordar que al poner SEEK_END y querer ir de manera inversa es necesario usar -i
        //ya que sino nos moveriamos a la derecha y no la izquierda como queremos.
        fseek(input, -i * block_size, SEEK_END);
        fread(audio, block_size, 1, input);
        fwrite(audio, block_size, 1, output);
    }
    fclose(input);
    fclose(output);
    free(audio);
}

int check_format(WAVHEADER header)
{
    BYTE check[] = {'W', 'A', 'V', 'E'};
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != check[i])
        {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    //obtengo el tamaño de cada bloque de audio
    int bytesPerSample = header.bitsPerSample / 8;
    return (header.numChannels * bytesPerSample);
}