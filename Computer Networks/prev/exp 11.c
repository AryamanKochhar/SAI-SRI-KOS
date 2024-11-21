#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 15
#define PHONE_BOOK_SIZE 10
#define PORT 8080
#define MAX_CONNECTIONS 5

typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} PhoneBookEntry;

PhoneBookEntry phone_book[PHONE_BOOK_SIZE] = {
    {"John Doe", "123-456-7890"},
    {"Jane Smith", "987-654-3210"},
    {"Alice Johnson", "456-789-0123"},
    {"Bob Brown", "789-012-3456"},
    {"Charlie Davis", "321-654-9870"},
    {"Diana Evans", "654-987-3210"},
    {"Edward Foster", "147-258-3690"},
    {"Fiona Green", "369-258-1470"},
    {"George Harris", "741-852-9630"},
    {"Hannah Irving", "852-963-7410"}
};

int server_socket;
volatile sig_atomic_t keep_running = 1;

void handle_sigterm(int signum) {
    keep_running = 0;
}

const char* lookup_phone(const char* name) {
    for (int i = 0; i < PHONE_BOOK_SIZE; i++) {
        if (strcasecmp(phone_book[i].name, name) == 0) {
            static char result[MAX_NAME_LENGTH + MAX_PHONE_LENGTH + 20];
            snprintf(result, sizeof(result), "%s: %s", phone_book[i].name, phone_book[i].phone);
            return result;
        }
    }
    return "Name not found in the phone book.";
}

void handle_client(int client_socket) {
    char buffer[MAX_NAME_LENGTH];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_received] = '\0';
        
        if (strcmp(buffer, "quit") == 0) {
            break;
        }

        const char* phone_info = lookup_phone(buffer);
        send(client_socket, phone_info, strlen(phone_info), 0);
    }

    close(client_socket);
}

void run_server() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, MAX_CONNECTIONS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Phone book server listening on port %d...\n", PORT);

    while (keep_running) {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            if (keep_running) {
                perror("Accept failed");
            }
            continue;
        }

        printf("New connection accepted\n");

        if (fork() == 0) {
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        } else {
            close(client_socket);
        }
    }

    close(server_socket);
    printf("Server shutting down...\n");
}

void run_client() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAX_NAME_LENGTH + MAX_PHONE_LENGTH + 20] = {0};
    char name[MAX_NAME_LENGTH];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return;
    }

    while (1) {
        printf("Enter a name to look up (or 'quit' to exit): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        send(sock, name, strlen(name), 0);

        if (strcmp(name, "quit") == 0) {
            break;
        }

        int valread = read(sock, buffer, sizeof(buffer));
        buffer[valread] = '\0';
        printf("%s\n", buffer);
    }

    close(sock);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process runs the server
        signal(SIGTERM, handle_sigterm);
        run_server();
    } else if (pid > 0) {
        // Parent process runs the client
        sleep(1);  // Give the server a moment to start
        run_client();
        
        // Send termination signal to the server
        kill(pid, SIGTERM);
        
        // Wait for the server to finish
        int status;
        waitpid(pid, &status, 0);
        
        printf("Program terminated.\n");
    } else {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
