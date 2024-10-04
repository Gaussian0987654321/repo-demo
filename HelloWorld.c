#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 100
#define MAX_PAGES 100

// Structure to represent a page frame
typedef struct {
    int pageNumber;
    int frequency;
} PageFrame;

// Function to find the index of the least frequently used page
int findLFU(PageFrame frames[], int frameCount) {
    int minFrequency = frames[0].frequency;
    int lfuIndex = 0;

    for (int i = 1; i < frameCount; i++) {
        if (frames[i].frequency < minFrequency) {
            minFrequency = frames[i].frequency;
            lfuIndex = i;
        }
    }
    return lfuIndex;
}

// Function to implement LFU page replacement algorithm
void lfuPageReplacement(int referenceString[], int referenceLength, int n) {
    PageFrame frames[MAX_FRAMES];
    int frameCount = 0;
    int pageFaults = 0;

    // Initialize frames
    for (int i = 0; i < n; i++) {
        frames[i].pageNumber = -1;
        frames[i].frequency = 0;
    }

    printf("Reference String: ");
    for (int i = 0; i < referenceLength; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n");

    // Process each page reference
    for (int i = 0; i < referenceLength; i++) {
        int page = referenceString[i];
        int found = 0;

        // Check if the page is already in a frame
        for (int j = 0; j < frameCount; j++) {
            if (frames[j].pageNumber == page) {
                found = 1;
                frames[j].frequency++; // Increment frequency
                break;
            }
        }

        // Page fault occurs
        if (!found) {
            pageFaults++;
            // If there is space in frames, add the new page
            if (frameCount < n) {
                frames[frameCount].pageNumber = page;
                frames[frameCount].frequency = 1;
                frameCount++;
            } else {
                // Replace the least frequently used page
                int lfuIndex = findLFU(frames, frameCount);
                frames[lfuIndex].pageNumber = page;
                frames[lfuIndex].frequency = 1;
            }
        }

        // Print current page frames
        printf("Page Frames after accessing %d: ", page);
        for (int j = 0; j < frameCount; j++) {
            printf("%d ", frames[j].pageNumber);
        }
        printf("\n");
    }

    // Output total page faults
    printf("Total Page Faults: %d\n", pageFaults);
}

// Main function
int main() {
    int referenceString[] = {3, 4, 5, 4, 3, 4, 7, 2, 4, 5, 6, 7, 2, 4, 6};
    int referenceLength = sizeof(referenceString) / sizeof(referenceString[0]);
    int n; // Number of frames

    printf("Enter the number of frames: ");
    scanf("%d", &n);

    lfuPageReplacement(referenceString, referenceLength, n);
    return 0;
}