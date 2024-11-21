#include <stdio.h>
#include <stdbool.h>

#define WINDOW_SIZE 3
#define MAX_FRAMES 7

typedef struct {
    int base;               // First frame in the window
    int next_frame_to_send; // Next frame to send
    bool ack_received[MAX_FRAMES];
} Sender;

typedef struct {
    bool received_frames[MAX_FRAMES];
} Receiver;

// Initialize the sender and receiver structures
void initialize(Sender* sender, Receiver* receiver) {
    sender->base = 0;
    sender->next_frame_to_send = 0;
    for (int i = 0; i < MAX_FRAMES; ++i) {
        sender->ack_received[i] = false;
        receiver->received_frames[i] = false;
    }
}

// Simulate sending frames in the current window
void sendFrames(Sender* sender) {
    printf("\nSender: Sending frames...\n");
    for (int i = sender->base; i < sender->base + WINDOW_SIZE && i < MAX_FRAMES; ++i) {
        if (!sender->ack_received[i]) {
            printf("  Sent frame %d\n", i);
        }
    }
}

// Simulate the receiver acknowledging frames
void receiveAck(Sender* sender, Receiver* receiver, int frame_number) {
    if (frame_number >= 0 && frame_number < MAX_FRAMES) {
        printf("Receiver: Acknowledged frame %d\n", frame_number);
        sender->ack_received[frame_number] = true;
        receiver->received_frames[frame_number] = true;

        // Slide the window forward
        while (sender->ack_received[sender->base] && sender->base < MAX_FRAMES) {
            printf("Sliding window: Frame %d acknowledged\n", sender->base);
            sender->base++;
        }
    }
}

// Simulate frame loss and retransmission
void simulateLossAndRetransmission(Sender* sender, Receiver* receiver, int frame_number) {
    printf("Simulating loss of frame %d\n", frame_number);
    sender->ack_received[frame_number] = false; // Mark as not acknowledged
    printf("Resending frame %d...\n", frame_number);
    receiveAck(sender, receiver, frame_number); // Acknowledge after retransmission
}

int main() {
    Sender sender;
    Receiver receiver;

    initialize(&sender, &receiver);

    // Step 1: Send initial frames
    sendFrames(&sender);

    // Receiver acknowledges frames 0 and 1
    receiveAck(&sender, &receiver, 0);
    receiveAck(&sender, &receiver, 1);

    // Step 2: Send next batch of frames
    sendFrames(&sender);

    // Receiver acknowledges frame 3
    receiveAck(&sender, &receiver, 3);

    // Simulate frame loss for frame 6
    simulateLossAndRetransmission(&sender, &receiver, 6);

    // Receiver acknowledges frame 6
    receiveAck(&sender, &receiver, 6);

    printf("\nAll operations complete. Sliding window protocol simulation ended.\n");
    return 0;
}