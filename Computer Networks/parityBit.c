#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to calculate the parity bit based on binary division by 2
int calculateParityBit(const char *binary)
{
    int count = 0;
    int len = strlen(binary);

    // Loop through the binary string from left to right
    for (int i = 0; i < len; i++)
    {
        if (binary[i] == '1')  // If the bit is '1', increment the count
        {
            count++;
        }
    }

    // Return the parity bit based on whether the count is even or odd
    return (count % 2 == 0) ? 0 : 1;
}

// Function to get valid binary input from the user
void getBinaryInput(char *buffer, const char *prompt)
{
    int valid = 0;
    while (!valid)
    {
        printf("%s", prompt);
        scanf("%s", buffer);
        valid = (strspn(buffer, "01") == strlen(buffer));  // Check if input is binary
        if (!valid)
        {
            printf("Invalid input. Please enter binary data consisting of only 0s and 1s.\n");
        }
    }
}

int main()
{
    char input1[100], input2[100];
    
    // Get the first binary input
    getBinaryInput(input1, "Enter the first binary data: ");
    int parity1 = calculateParityBit(input1);
    printf("Parity Bit for first data: %d\n", parity1);

    // Get the second binary input
    getBinaryInput(input2, "Enter the second binary data: ");
    int parity2 = calculateParityBit(input2);
    printf("Parity Bit for second data: %d\n", parity2);

    // Compare the binary data and parity bits
    if (strcmp(input1, input2) == 0 && parity1 == parity2)
    {
        printf("Transmission successful, data is correct.\n");
    }
    else
    {
        printf("Transmission failed, data is incorrect.\n");
    }

    return 0;
}
