#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CWND 16    // Maximum congestion window size
#define INITIAL_CWND 1 // Initial congestion window size

void simulateCongestionControl()
{
    int cwnd = INITIAL_CWND; // Congestion window
    int ssthresh = 8;        // Slow start threshold
    int acked;               // Number of acknowledged packets
    int packets;             // Number of packets in the current round
    int round = 1;

    srand(time(NULL)); // Seed for random loss simulation

    printf("Simulating TCP Congestion Control\n");
    printf("Initial cwnd = %d, ssthresh = %d\n\n", cwnd, ssthresh);

    while (cwnd > 0)
    {
        printf("Round %d: cwnd = %d, ssthresh = %d\n", round, cwnd, ssthresh);

        // Simulate sending packets
        packets = cwnd;
        printf("Sending %d packets...\n", packets);

        // Simulate acknowledgment or packet loss
        acked = 0;
        for (int i = 0; i < packets; i++)
        {
            if (rand() % 10 < 8)
            { // 80% chance of acknowledgment
                acked++;
            }
            else
            { // Simulate packet loss
                printf("Packet %d lost!\n", i + 1);
                ssthresh = cwnd / 2; // Update threshold on loss
                cwnd = 1;            // Reset cwnd to 1 (slow start)
                break;
            }
        }

        // If no loss, adjust congestion window
        if (acked == packets)
        {
            if (cwnd < ssthresh)
            {
                // Slow start phase
                printf("In Slow Start Phase. Doubling cwnd.\n");
                cwnd *= 2; // Exponential growth
            }
            else
            {
                // Congestion avoidance phase
                printf("In Congestion Avoidance Phase. Incrementing cwnd by 1.\n");
                cwnd += 1; // Linear growth
            }
            if (cwnd > MAX_CWND)
            { // Enforce maximum window size
                cwnd = MAX_CWND;
            }
        }

        printf("Acknowledged %d packets, cwnd now = %d\n\n", acked, cwnd);
        round++;

        // Stop if the congestion window reaches zero
        if (round > 10)
        { // Limit the simulation to 10 rounds
            break;
        }
    }

    printf("Simulation ended. Final cwnd = %d, ssthresh = %d\n", cwnd, ssthresh);
}

int main()
{
    simulateCongestionControl();
    return 0;
}
