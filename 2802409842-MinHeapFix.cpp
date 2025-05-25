#include <stdio.h>
#include <stdlib.h>

int minHeap[100];
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
        printf("Your Heap is Empty. Insert more data!\n\n");
    } else {
        for (int i = 1; i < dataCount; i++) {
            printf("Heap[%2d] = %d\n", i, minHeap[i]);
        }
        puts("");
    }
}

void swapValue(int parentIndex, int currIndex) {
    int temp = minHeap[parentIndex];
    minHeap[parentIndex] = minHeap[currIndex];
    minHeap[currIndex] = temp;
}

void HeapUp(int index) {
    if (index <= 1) return;

    int parentIndex = getParentIndex(index);
    if (minHeap[parentIndex] <= minHeap[index]) return;

    swapValue(parentIndex, index);
    HeapUp(parentIndex);
}

void HeapDown(int index) {
    if (index >= dataCount) return;

    int smallest = index;
    int left = getLeftIndex(index);
    int right = getRightIndex(index);

    // fix overflow isu
    if (left < dataCount && minHeap[left] < minHeap[smallest]) {
        smallest = left;
    }

    // fix child check
    if (right < dataCount && minHeap[right] < minHeap[smallest]) {
        smallest = right;
    }

    // fix swap
    if (smallest != index) {
        swapValue(index, smallest); 
        HeapDown(smallest);
    }
}

void push(int input) {
    minHeap[dataCount] = input;
    HeapUp(dataCount);
    dataCount++;
}

int pop() {
    int removed = minHeap[1];
    swapValue(1, dataCount - 1);
    dataCount--;
    HeapDown(1); // fix swapping
    return removed;
}

void createMenu() {
    printf("1. Insert\n");
    printf("2. Delete\n");
    printf("3. Exit\n");
}

int main() {
    int input = -1, num;
    do {
        // fix Removed unused format argument
        printf("Data:\n");
        viewHeap();
        createMenu();

        do {
            printf("Input your choice: ");
            scanf("%d", &input); getchar();
        } while (input < 1 || input > 3);

        switch (input) {
            case 1:
                printf("What data should be inputted into the heap? ");
                scanf("%d", &num); getchar();
                push(num);
                printf("%d has been inputted into the heap\n\n", num);
                break;
            case 2:
                if (dataCount <= 1) {
                    printf("Your heap is empty. Insert more data!\n\n");
                } else {
                    printf("%d has been deleted\n\n", pop());
                }
                break;
        }
    } while (input != 3);

    return 0; // fix proper return value
}

