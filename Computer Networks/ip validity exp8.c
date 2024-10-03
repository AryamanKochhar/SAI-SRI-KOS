#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to validate the IP address
int validate_ip(const char *ip) {
    int num, dots = 0;
    char ip_copy[16]; // Create a copy for strtok use
    strcpy(ip_copy, ip); // Copy original IP to avoid modifying the input
    char *ptr = strtok(ip_copy, ".");
    
    if (ptr == NULL) return 0;

    while (ptr) {
        if (!isdigit(*ptr)) return 0;
        num = atoi(ptr);
        if (num >= 0 && num <= 255) {
            ptr = strtok(NULL, ".");
            if (ptr != NULL) dots++;
        } else return 0;
    }
    if (dots != 3) return 0;
    return 1;
}

// Function to determine the class of the IP address
char ip_class(int first_octet) {
    if (first_octet >= 1 && first_octet <= 126) return 'A';
    else if (first_octet >= 128 && first_octet <= 191) return 'B';
    else if (first_octet >= 192 && first_octet <= 223) return 'C';
    else if (first_octet >= 224 && first_octet <= 239) return 'D';
    else return 'E';
}

// Function to calculate the first and last address of the block
void calculate_block_addresses(const char *ip, char *first_address, char *last_address) {
    int octets[4];
    sscanf(ip, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);
    char class = ip_class(octets[0]);
    if (class == 'A') {
        sprintf(first_address, "%d.0.0.0", octets[0]);
        sprintf(last_address, "%d.255.255.255", octets[0]);
    } else if (class == 'B') {
        sprintf(first_address, "%d.%d.0.0", octets[0], octets[1]);
        sprintf(last_address, "%d.%d.255.255", octets[0], octets[1]);
    } else if (class == 'C') {
        sprintf(first_address, "%d.%d.%d.0", octets[0], octets[1], octets[2]);
        sprintf(last_address, "%d.%d.%d.255", octets[0], octets[1], octets[2]);
    } else {
        strcpy(first_address, "N/A");
        strcpy(last_address, "N/A");
    }
}

int main() {
    char ip[16];
    printf("Enter an IP address: ");
    scanf("%15s", ip);

    if (validate_ip(ip)) {
        printf("Valid IP address\n");
        int first_octet;
        sscanf(ip, "%d", &first_octet);
        char class = ip_class(first_octet);
        printf("Class of IP address: %c\n", class);

        char first_address[16], last_address[16];
        calculate_block_addresses(ip, first_address, last_address);
        printf("First address of the block: %s\n", first_address);
        printf("Last address of the block: %s\n", last_address);
    } else {
        printf("Invalid IP address\n");
    }
    printf("ARYAMAN KOCHHAR 23BRS1047");

    return 0;
}
