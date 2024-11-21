#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_FRAMES 8 // Maximum number of frames in the sliding window

void sendFrames(int windowSize, int totalFrames) {
    int sent = 0;      // Index of the last frame sent
    int ack = 0;       // Index of the last acknowledgment received
    bool frameAck[MAX_FRAMES] = {false}; // Track acknowledgments for each frame

    while (ack < totalFrames) {
        // Send frames within the window
        for (int i = 0; i < windowSize && sent < totalFrames; i++) {
            if (!frameAck[sent]) {
                printf("Sending frame %d\n", sent + 1);
                sent++;
            }
        }

        // Simulate acknowledgments
        for (int i = ack; i < sent; i++) {
            if (!frameAck[i]) {
                printf("Waiting for acknowledgment for frame %d...\n", i + 1);
                usleep(500000); // Simulate delay (0.5 seconds)
                
                // Randomly decide if the frame is acknowledged
                if (rand() % 2 == 0) {
                    frameAck[i] = true;
                    printf("Acknowledgment received for frame %d\n", i + 1);
                } else {
                    printf("No acknowledgment for frame %d. Resending...\n", i + 1);
                    sent = i; // Move the sent pointer back to resend
                    break;
                }
            }
        }

        // Slide the window
        while (frameAck[ack] && ack < totalFrames) {
            ack++;
        }
    }

    printf("All frames sent and acknowledged.\n");
}

int main() {
    int windowSize, totalFrames;

    printf("Enter the window size: ");
    scanf("%d", &windowSize);

    if (windowSize > MAX_FRAMES) {
        printf("Window size cannot exceed %d frames. Setting to %d.\n", MAX_FRAMES, MAX_FRAMES);
        windowSize = MAX_FRAMES;
    }

    printf("Enter the total number of frames to send: ");
    scanf("%d", &totalFrames);

    printf("\nStarting transmission...\n");
    sendFrames(windowSize, totalFrames);

    return 0;
}
