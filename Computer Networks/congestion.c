#include <stdio.h>
#include <stdlib.h>

#define THRESHOLD 32
#define MAX_CWND 64

int main() {
    int cwnd = 1; // Initial congestion window
    int step = 1; // Additive increase step after threshold

    printf("Starting TCP Congestion Control:\n");
    printf("Initial cwnd: %d\n", cwnd);

    while (cwnd < MAX_CWND) {
        if (cwnd < THRESHOLD) {
            // Slow Start: Exponential Growth
            cwnd *= 2;
            if (cwnd > THRESHOLD) {
                cwnd = THRESHOLD; // Ensure cwnd doesn't overshoot threshold
            }
            printf("Slow Start - cwnd: %d\n", cwnd);
        } else {
            // Additive Increase
            cwnd += step;
            printf("Additive Increase - cwnd: %d\n", cwnd);
        }
    }

    printf("Congestion Window reached maximum (cwnd: %d). Exiting...\n", cwnd);
    return 0;
}