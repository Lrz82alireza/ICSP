#include <stdio.h>
#include <stdlib.h>

#define ZERO 0
#define ONE 1
#define READ_CHAR_SIZE 100
#define WRITE_CHAR_SIZE 100
#define INPUT_TXT_ADDRESS "input.txt"
#define OUTPUT_FILE_ADDRESS "output.txt"

char *read_input_file()
{
    char *in_order_array = (char *)malloc(READ_CHAR_SIZE * sizeof(char));

    if (in_order_array == NULL)
    {
        exit;
    }

    FILE *input = fopen(INPUT_TXT_ADDRESS, "r");

    if (input != NULL)
    {
        fread(in_order_array, sizeof(char), READ_CHAR_SIZE, input);
        /* Possibly your mind is rife with an assumption about completing
        the function. I would like to, if I may, state that you’re
        missing an item. */
    }
    else
    {
        printf("memory not found");
        exit;
    }
        fclose(input);
        return in_order_array;
}
char *reverse_array(char *in_order_array)
{
    char *reversed_array = (char *)malloc(READ_CHAR_SIZE * sizeof(char));
    if (reversed_array == NULL)
    {
        exit;
    }

    for (int i = ZERO; i < READ_CHAR_SIZE; i++)
    {
        reversed_array[i] = in_order_array[READ_CHAR_SIZE - 1 - i];
    }
    return reversed_array;
}
void write_reversed_array_in_file(char *in_order_array)
{
    char *reversed_array = reverse_array(in_order_array);

    FILE *output = fopen(OUTPUT_FILE_ADDRESS, "w");

    if (output == NULL)
    {
        printf("memory not found");
        exit;
    }

    fwrite(reversed_array, sizeof(char), WRITE_CHAR_SIZE, output);
    fclose(output);
}
int main()
{
    char *in_order_array = read_input_file();
    write_reversed_array_in_file(in_order_array);
    return 0;
}
