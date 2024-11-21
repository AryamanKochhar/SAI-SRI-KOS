#include <stdio.h>
#include <math.h>

// Function to calculate parity bits
void calculateParityBits(int data[], int hammingCode[])
{
    // Place data bits in appropriate positions
    hammingCode[2] = data[0]; // d1
    hammingCode[4] = data[1]; // d2
    hammingCode[5] = data[2]; // d3
    hammingCode[6] = data[3]; // d4

    // Calculate parity bits
    hammingCode[0] = hammingCode[2] ^ hammingCode[4] ^ hammingCode[6]; // p1
    hammingCode[1] = hammingCode[2] ^ hammingCode[5] ^ hammingCode[6]; // p2
    hammingCode[3] = hammingCode[4] ^ hammingCode[5] ^ hammingCode[6]; // p4
}

// Function to detect and correct errors
void detectAndCorrect(int received[])
{
    // Calculate syndrome bits
    int s1 = received[0] ^ received[2] ^ received[4] ^ received[6];
    int s2 = received[1] ^ received[2] ^ received[5] ^ received[6];
    int s4 = received[3] ^ received[4] ^ received[5] ^ received[6];

    int errorPosition = s4 * 4 + s2 * 2 + s1;

    if (errorPosition == 0)
    {
        printf("No error in transmission.\n");
    }
    else
    {
        printf("Error detected at position: %d\n", errorPosition);
        received[errorPosition - 1] ^= 1; // Correct the error
        printf("Corrected code: ");
        for (int i = 0; i < 7; i++)
        {
            printf("%d", received[i]);
        }
        printf("\n");
    }
}

int main()
{
    int data[4];
    int hammingCode[7];
    int received[7];

    // Input 4-bit data
    printf("Enter 4-bit data (space-separated, e.g., 1 0 1 1): ");
    for (int i = 0; i < 4; i++)
    {
        scanf("%d", &data[i]);
    }

    // Generate Hamming Code
    calculateParityBits(data, hammingCode);
    printf("Generated Hamming Code: ");
    for (int i = 0; i < 7; i++)
    {
        printf("%d", hammingCode[i]);
    }
    printf("\n");

    // Input received data
    printf("Enter received 7-bit Hamming Code (space-separated, e.g., 1 0 1 0 1 1 0): ");
    for (int i = 0; i < 7; i++)
    {
        scanf("%d", &received[i]);
    }

    // Detect and correct errors
    detectAndCorrect(received);

    return 0;
}