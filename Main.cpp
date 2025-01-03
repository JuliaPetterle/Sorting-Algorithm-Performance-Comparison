#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For getcwd()
#include <stdint.h> // For INT16_MAX

// Define the Heap structure
struct Heap {
    unsigned long *arr;
    unsigned int heapsize, length;
};

// Function prototypes
void MAX_HEAPIFY(struct Heap *h, unsigned int i);
void BUILD_MAX_HEAP(struct Heap *h);
void heap_sort(struct Heap *h);
void insertion_sort(unsigned long *arr, unsigned int length);
void merge_sort(unsigned long *arr, unsigned int left, unsigned int right);
void merge(unsigned long *arr, unsigned int left, unsigned int mid, unsigned int right);

int main() {
    unsigned int array_size = 128; // A small array size of 2^7
    struct Heap h;
    unsigned long *f, *g;

    printf("Allocating memory...\n");
    h.arr = (unsigned long *)malloc((array_size + 1) * sizeof(unsigned long));
    f = (unsigned long *)malloc((array_size + 1) * sizeof(unsigned long));
    g = (unsigned long *)malloc((array_size + 1) * sizeof(unsigned long));

    if (!h.arr || !f || !g) {
        printf("Memory allocation failed.\n");
        free(h.arr);
        free(f);
        free(g);
        return 1;
    }
    printf("Memory allocation successful.\n");

    // Initialize arrays
    srand(time(NULL));
    printf("Initializing arrays...\n");
    int tmp;
    for (unsigned int i = 1; i <= array_size; i++) {
        // Fill arrays with the same random numbers
        tmp = rand() % INT16_MAX;
        f[i] = (unsigned long)tmp;
        g[i] = (unsigned long)tmp;
        h.arr[i] = (unsigned long)tmp;
    }
    h.length = array_size;
    printf("Arrays initialized.\n");

    // Timing variables
    clock_t start, end;
    double heap_time, insertion_time, merge_time;

    // Heapsort
    printf("Starting heap sort...\n");
    start = clock();
    heap_sort(&h);
    end = clock();
    heap_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Heap sort completed in %.6f seconds.\n", heap_time);

    // Insertion sort
    printf("Starting insertion sort...\n");
    start = clock();
    insertion_sort(g, array_size);
    end = clock();
    insertion_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Insertion sort completed in %.6f seconds.\n", insertion_time);

    // Merge sort
    printf("Starting merge sort...\n");
    start = clock();
    merge_sort(f, 1, array_size);
    end = clock();
    merge_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Merge sort completed in %.6f seconds.\n", merge_time);

    // Debug current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }

    // Write results to CSV
    printf("Writing results to results.csv...\n");
    FILE *fp = fopen("results.csv", "w");
    if (!fp) {
        printf("Failed to open results.csv for writing.\n");
        perror("Error");
        free(h.arr);
        free(f);
        free(g);
        return 1;
    }
    fprintf(fp, "Algorithm,Time (s)\n");
    fprintf(fp, "Heap Sort,%.6f\n", heap_time);
    fprintf(fp, "Insertion Sort,%.6f\n", insertion_time);
    fprintf(fp, "Merge Sort,%.6f\n", merge_time);
    fclose(fp);
    printf("Results written successfully to results.csv.\n");

    // Free memory
    free(h.arr);
    free(f);
    free(g);

    printf("Program completed successfully.\n");
    return 0;
}

// Heapsort functions
void MAX_HEAPIFY(struct Heap *h, unsigned int i) {
    if (i < 1 || i > h->length) {
        printf("Invalid index in MAX_HEAPIFY: %u\n", i);
        return;
    }

    unsigned int largest = i;
    unsigned int left = 2 * i;
    unsigned int right = 2 * i + 1;

    if (left <= h->heapsize && h->arr[left] > h->arr[largest]) {
        largest = left;
    }
    if (right <= h->heapsize && h->arr[right] > h->arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        unsigned long temp = h->arr[i];
        h->arr[i] = h->arr[largest];
        h->arr[largest] = temp;
        MAX_HEAPIFY(h, largest);
    }
}

void BUILD_MAX_HEAP(struct Heap *h) {
    h->heapsize = h->length;
    for (int i = h->length / 2; i >= 1; i--) {
        MAX_HEAPIFY(h, i);
    }
}

void heap_sort(struct Heap *h) {
    BUILD_MAX_HEAP(h);
    for (int i = h->length; i >= 2; i--) {
        unsigned long temp = h->arr[1];
        h->arr[1] = h->arr[i];
        h->arr[i] = temp;
        h->heapsize--;
        MAX_HEAPIFY(h, 1);
    }
}

// Insertion sort function
void insertion_sort(unsigned long *arr, unsigned int length) {
    if (!arr) {
        printf("Null pointer passed to insertion_sort.\n");
        return;
    }

    for (unsigned int i = 2; i <= length; i++) {
        unsigned long key = arr[i];
        int j = i - 1;
        while (j >= 1 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;

        // Debug message every 100000 iterations
        if (i % 100000 == 0) {
            printf("Processed %u elements in insertion sort...\n", i);
        }
    }
}

// Merge sort functions
void merge_sort(unsigned long *arr, unsigned int left, unsigned int right) {
    if (!arr) {
        printf("Null pointer passed to merge_sort.\n");
        return;
    }
    if (left >= right || left < 1 || right > 1048576) { // Assuming array_size = 1048576
        printf("Invalid bounds in merge_sort: left=%u, right=%u\n", left, right);
        return;
    }

    unsigned int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void merge(unsigned long *arr, unsigned int left, unsigned int mid, unsigned int right) {
    if (!arr) {
        printf("Null pointer passed to merge.\n");
        return;
    }

    unsigned int n1 = mid - left + 1;
    unsigned int n2 = right - mid;

    unsigned long *L = (unsigned long *)malloc((n1 + 1) * sizeof(unsigned long));
    unsigned long *R = (unsigned long *)malloc((n2 + 1) * sizeof(unsigned long));

    if (!L || !R) {
        printf("Memory allocation failed in merge().\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (unsigned int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    unsigned int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}
