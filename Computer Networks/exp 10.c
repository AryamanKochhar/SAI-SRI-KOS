#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_WORD_LENGTH 50
#define MAX_DEFINITION_LENGTH 200
#define DICTIONARY_SIZE 52  
#define PORT 8080
#define MAX_CONNECTIONS 5

typedef struct {
    char word[MAX_WORD_LENGTH];
    char definition[MAX_DEFINITION_LENGTH];
} DictionaryEntry;

DictionaryEntry dictionary[DICTIONARY_SIZE] = {
    {"apple", "A round fruit with red or green skin and a white interior"},
    {"aardvark", "A nocturnal African mammal that feeds on ants and termites"},
    {"banana", "A long curved fruit with a yellow skin"},
    {"book", "A written or printed work consisting of pages glued or sewn together"},
    {"cat", "A small domesticated carnivorous mammal with soft fur"},
    {"computer", "An electronic device for storing and processing data"},
    {"dog", "A domesticated carnivorous mammal that typically has a long snout and tail"},
    {"database", "A structured set of data held in a computer"},
    {"elephant", "A very large plant-eating mammal with a long trunk and tusks"},
    {"egg", "An oval or round object laid by a female bird, reptile, fish, or invertebrate"},
    {"frog", "A tailless amphibian with a short squat body, moist smooth skin, and long hind legs"},
    {"forest", "A large area covered chiefly with trees and undergrowth"},
    {"giraffe", "A large African mammal with a very long neck and forelegs"},
    {"guitar", "A musical instrument with strings played by plucking or strumming"},
    {"hat", "A shaped covering for the head worn for warmth, as a fashion item, or as part of a uniform"},
    {"house", "A building for human habitation"},
    {"igloo", "A dome-shaped Inuit house, typically built from blocks of solid snow"},
    {"ice", "Water frozen into a solid state"},
    {"jacket", "A short coat, typically extending to the hips"},
    {"jellyfish", "A free-swimming marine coelenterate with a jellylike bell- or saucer-shaped body"},
    {"kite", "A light frame covered with thin material, flown in the wind at the end of a long string"},
    {"kangaroo", "A large plant-eating marsupial with a long powerful tail and strong hind legs"},
    {"lemon", "A yellow citrus fruit with acidic juice"},
    {"library", "A building or room containing collections of books for use or borrowing"},
    {"monkey", "A primate with a long tail, typically arboreal and found in forests"},
    {"moon", "The natural satellite of the earth, visible by reflected light from the sun"},
    {"nest", "A structure or place made or chosen by a bird for laying eggs and sheltering its young"},
    {"notebook", "A book with blank or ruled pages for writing notes in"},
    {"orange", "A round juicy citrus fruit with a tough bright reddish-yellow rind"},
    {"ocean", "A very large expanse of sea"},
    {"penguin", "A flightless seabird of the southern hemisphere"},
    {"piano", "A large keyboard musical instrument with a wooden case enclosing a soundboard and metal strings"},
    {"quilt", "A warm bed covering made of padding enclosed between layers of fabric"},
    {"quokka", "A small wallaby found in southwestern Australia"},
    {"rabbit", "A small mammal with long ears, long hind legs, and a short fluffy tail"},
    {"river", "A large natural stream of water flowing in a channel to the sea, a lake, or another river"},
    {"sun", "The star around which the earth orbits"},
    {"sandwich", "An item of food consisting of two pieces of bread with a filling between them"},
    {"tree", "A woody perennial plant, typically having a single stem or trunk"},
    {"telephone", "A system for transmitting voices over a distance using wire or radio"},
    {"umbrella", "A device consisting of a circular canopy of cloth on a folding metal frame"},
    {"unicorn", "A mythical animal typically represented as a horse with a single straight horn projecting from its forehead"},
    {"volcano", "A mountain or hill, typically conical, having a crater or vent through which lava, rock fragments, hot vapor, and gas are or have been erupted from the earth's crust"},
    {"violin", "A stringed musical instrument of treble pitch, played with a horsehair bow"},
    {"whale", "A very large marine mammal with a streamlined hairless body, a horizontal tail fin, and a blowhole on top of the head"},
    {"water", "A colorless, transparent, odorless liquid that forms the seas, lakes, rivers, and rain"},
    {"xylophone", "A musical instrument played by striking a row of wooden bars of graduated length with small wooden hammers"},
    {"x-ray", "An electromagnetic wave of high energy and very short wavelength, able to pass through many materials opaque to light"},
    {"yacht", "A medium-sized sailing boat equipped for cruising or racing"},
    {"yogurt", "A semi-solid sourish food prepared from milk fermented by added bacteria"},
    {"zebra", "An African wild horse with black-and-white stripes and an erect mane"},
    {"zucchini", "A green variety of smooth-skinned summer squash"}
};

const char* lookup_word(const char* word) {
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        if (strcasecmp(dictionary[i].word, word) == 0) {
            return dictionary[i].definition;
        }
    }
    return "Word not found in the dictionary.";
}

void handle_client(int client_socket) {
    char buffer[MAX_WORD_LENGTH];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        buffer[bytes_received] = '\0';
        
        if (strcmp(buffer, "quit") == 0) {
            break;
        }

        const char* definition = lookup_word(buffer);
        send(client_socket, definition, strlen(definition), 0);
    }

    close(client_socket);
}

void run_server() {
    int server_socket, client_socket;
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

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
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
}

void run_client() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAX_DEFINITION_LENGTH] = {0};
    char word[MAX_WORD_LENGTH];

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
        printf("Enter a word to look up (or 'quit' to exit): ");
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = 0;

        send(sock, word, strlen(word), 0);

        if (strcmp(word, "quit") == 0) {
            break;
        }

        int valread = read(sock, buffer, MAX_DEFINITION_LENGTH);
        buffer[valread] = '\0';
        printf("Definition: %s\n", buffer);
    }

    close(sock);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process runs the server
        run_server();
    } else if (pid > 0) {
        // Parent process runs the client
        sleep(1);  // Give the server a moment to start
        run_client();
        
        // Wait for the server to finish
        wait(NULL);
    } else {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}



