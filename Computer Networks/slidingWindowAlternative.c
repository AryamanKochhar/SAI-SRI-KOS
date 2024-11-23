#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FRAMES 10 // Maximum number of frames

void slidingWindowProtocol(int totalFrames, int windowSize)
{
    int frames[MAX_FRAMES];
    int sent = 0; // First frame to send
    int ack = 0;  // Acknowledgment pointer

    // Initialize frame numbers
    for (int i = 0; i < totalFrames; i++)
    {
        frames[i] = i + 1;
    }

    printf("\nTotal frames to send: %d\n", totalFrames);
    printf("Window size: %d\n", windowSize);

    srand(time(0)); // Seed for randomness

    while (ack < totalFrames)
    {
        printf("\nSending frames: ");
        for (int i = sent; i < sent + windowSize && i < totalFrames; i++)
        {
            printf("%d ", frames[i]);
        }
        printf("\n");

        // Simulate acknowledgments
        for (int i = sent; i < sent + windowSize && i < totalFrames; i++)
        {
            // Simulate a chance for frame loss
            if (rand() % 10 < 2)
            { // 20% chance of frame loss
                printf("Frame %d lost! Retransmitting...\n", frames[i]);
                break; // Stop further transmissions in this window
            }
            else
            {
                ack = frames[i]; // Simulate successful acknowledgment
            }
        }

        printf("Last acknowledged frame: %d\n", ack);

        // Slide the window
        sent = ack;
    }

    if (ack >= totalFrames)
    {
        printf("\nAll frames sent and acknowledged successfully!\n");
    }
}

int main()
{
    int totalFrames, windowSize;

    printf("Enter the total number of frames: ");
    scanf("%d", &totalFrames);

    if (totalFrames > MAX_FRAMES)
    {
        printf("Total frames exceed the maximum limit (%d).\n", MAX_FRAMES);
        return 1;
    }

    printf("Enter the window size: ");
    scanf("%d", &windowSize);

    slidingWindowProtocol(totalFrames, windowSize);

    return 0;
}
