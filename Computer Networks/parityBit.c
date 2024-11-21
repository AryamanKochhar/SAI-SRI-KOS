#include <stdio.h>
#include <string.h>

int calculateParityBit(unsigned char data)
{
    int parity = 0;
    for (int i = 0; i < 8; i++)
    {
        parity ^= (data >> i) & 1;
    }
    return parity;
}

unsigned char binaryToByte(const char *binary)
{
    unsigned char result = 0;
    for (int i = 0; i < 8 && binary[i] != '\0'; i++)
    {
        result = (result << 1) | (binary[i] - '0');
    }
    return result;
}

void getBinaryInput(char *buffer, const char *prompt)
{
    int valid = 0;
    while (!valid)
    {
        printf("%s", prompt);
        scanf("%s", buffer);
        valid = (strlen(buffer) == 8 && strspn(buffer, "01") == 8);
        if (!valid)
        {
            printf("Invalid input. Please enter 8-bit binary data.\n");
        }
    }
}

int main()
{
    char input1[9], input2[9];
    getBinaryInput(input1, "Enter the first 8-bit binary data: ");
    unsigned char data1 = binaryToByte(input1);
    int parity1 = calculateParityBit(data1);
    printf("Parity Bit for first data: %d\n", parity1);

    getBinaryInput(input2, "Enter the second 8-bit binary data: ");
    unsigned char data2 = binaryToByte(input2);
    int parity2 = calculateParityBit(data2);
    printf("Parity Bit for second data: %d\n", parity2);

    if (data1 == data2 && parity1 == parity2)
    {
        printf("Transmission successful, data is correct.\n");
    }
    else
    {
        printf("Transmission failed, data is incorrect.\n");
    }

    return 0;
}
