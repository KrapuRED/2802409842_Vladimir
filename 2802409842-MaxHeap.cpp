#include <stdio.h>
#include <stdlib.h>

// MaxHeap
int maxHeap[100];
int dataCount = 1;

int getParentIndex(int index) {
    return index / 2;
}

int getLeftIndex(int index) {
    return index * 2;
}

int getRightIndex(int index) {
    return index * 2 + 1;
}

void viewHeap() {
    if (dataCount <= 1) {
        printf("Heap empty.\n\n");
    } else {
        for (int i = 1; i < dataCount; i++) {
            printf("[%2d] = %d\n", i, maxHeap[i]);
        }
        puts("");
    }
}

void swapValue(int parentIndex, int currIndex) {
    int temp = maxHeap[parentIndex];
    maxHeap[parentIndex] = maxHeap[currIndex];
    maxHeap[currIndex] = temp;
}

void HeapUp(int index) {
    if (index <= 1) return;

    int parentIndex = getParentIndex(index);
    if (maxHeap[parentIndex] >= maxHeap[index]) return;

    swapValue(parentIndex, index);
    HeapUp(parentIndex);
}

void HeapDown(int index) {
    if (index >= dataCount) return;

    int largest = index;
    int left = getLeftIndex(index);
    int right = getRightIndex(index);

    if (left < dataCount && maxHeap[left] > maxHeap[largest]) {
        largest = left;
    }

    if (right < dataCount && maxHeap[right] > maxHeap[largest]) {
        largest = right;
    }

    if (largest != index) {
        swapValue(index, largest);
        HeapDown(largest);
    }
}

void push(int input) {
    maxHeap[dataCount] = input;
    HeapUp(dataCount);
    dataCount++;
}

int pop() {
    int removed = maxHeap[1];
    swapValue(1, dataCount - 1);
    dataCount--;
    HeapDown(1);
    return removed;
}

void createMenu() {
    printf("1. Add\n");
    printf("2. Pop\n");
    printf("3. Quit\n");
}

int main() {
    int input = -1, num;
    do {
        printf("Data:\n");
        viewHeap();
        createMenu();

        do {
            printf(">> ");
            scanf("%d", &input); getchar();
        } while (input < 1 || input > 3);

        switch (input) {
            case 1:
                printf("Input: ");
                scanf("%d", &num); getchar();
                push(num);
                printf("Added: %d\n\n", num);
                break;
            case 2:
                if (dataCount <= 1) {
                    printf("Heap empty!\n\n");
                } else {
                    printf("Popped: %d\n\n", pop());
                }
                break;
        }
    } while (input != 3);

    return 0;
}

