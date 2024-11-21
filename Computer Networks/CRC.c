#include <stdio.h>
#include <string.h>

void computeCRC(char *data, char *div, int datalen, int divlen, char *remainder)
{
    int i, j;
    char temp[20];

    // Copy data to a temporary buffer and append zeros
    strcpy(temp, data);
    for (i = 0; i < divlen - 1; i++)
    {
        temp[datalen + i] = '0';
    }
    temp[datalen + divlen - 1] = '\0';

    // Perform division using XOR
    for (i = 0; i < datalen; i++)
    {
        if (temp[i] == '1')
        {
            for (j = 0; j < divlen; j++)
            {
                temp[i + j] = (temp[i + j] == div[j]) ? '0' : '1';
            }
        }
    }

    // Extract the remainder
    strncpy(remainder, temp + datalen, divlen - 1);
    remainder[divlen - 1] = '\0';
}

int checkCRC(char *received, char *div, int len, int divlen)
{
    int i, j;
    char temp[20];

    strcpy(temp, received);

    // Perform division using XOR
    for (i = 0; i < len - divlen + 1; i++)
    {
        if (temp[i] == '1')
        {
            for (j = 0; j < divlen; j++)
            {
                temp[i + j] = (temp[i + j] == div[j]) ? '0' : '1';
            }
        }
    }

    // Check if remainder is all zeros
    for (i = len - divlen + 1; i < len; i++)
    {
        if (temp[i] != '0')
        {
            return 0; // Error detected
        }
    }
    return 1; // No error
}

int main()
{
    int datalen, divlen;
    char data[20], div[20], remainder[20], transmitted[40];

    printf("Enter the total bit of data: ");
    scanf("%d", &datalen);
    printf("Enter the total bit of divisor: ");
    scanf("%d", &divlen);

    printf("Enter the data: ");
    scanf("%s", data);
    printf("Enter the divisor: ");
    scanf("%s", div);

    computeCRC(data, div, datalen, divlen, remainder);

    printf("CRC: %s\n", remainder);

    // Append the remainder to the data
    strcpy(transmitted, data);
    strcat(transmitted, remainder);
    printf("Transmitted Code Word: %s\n", transmitted);

    // Simulate reception
    char received[40];
    printf("\nEnter the received code word: ");
    scanf("%s", received);

    if (checkCRC(received, div, strlen(received), divlen))
    {
        printf("\nSuccessful..!!\n\n");
    }
    else
    {
        printf("\nReceived code word contains errors...\n");
    }

    return 0;
}
