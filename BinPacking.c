#include <stdio.h>

#define CAPACITY 10 // 상자의 최대 용량

// 물건 리스트
int items[] = {7, 5, 6, 4, 2, 3, 7, 5};
int num_items = sizeof(items) / sizeof(items[0]);

// 출력 함수
void print_bins(const char* algorithm, int bins[][CAPACITY], int bin_count, int bin_sizes[]) {
    printf("%s: ", algorithm);
    for (int i = 0; i < bin_count; i++) {
        printf("bin%d = [", i + 1);
        for (int j = 0; j < bin_sizes[i]; j++) {
            printf("%d", bins[i][j]);
            if (j < bin_sizes[i] - 1) printf(", ");
        }
        printf("]");
        if (i < bin_count - 1) printf(", ");
    }
    printf("\n");
}

// First Fit 알고리즘
void first_fit() {
    int bins[CAPACITY][CAPACITY] = {0};
    int bin_sizes[CAPACITY] = {0};
    int bin_remain[CAPACITY] = {0};
    int bin_count = 0;

    for (int i = 0; i < num_items; i++) {
        int placed = 0;
        for (int j = 0; j < bin_count; j++) {
            if (bin_remain[j] >= items[i]) {
                bins[j][bin_sizes[j]++] = items[i];
                bin_remain[j] -= items[i];
                placed = 1;
                break;
            }
        }
        if (!placed) {
            bins[bin_count][bin_sizes[bin_count]++] = items[i];
            bin_remain[bin_count] = CAPACITY - items[i];
            bin_count++;
        }
    }
    print_bins("Output1 (First Fit)", bins, bin_count, bin_sizes);
}

// Next Fit 알고리즘
void next_fit() {
    int bins[CAPACITY][CAPACITY] = {0};
    int bin_sizes[CAPACITY] = {0};
    int bin_remain = CAPACITY;
    int bin_count = 0;

    for (int i = 0; i < num_items; i++) {
        if (bin_remain >= items[i]) {
            bins[bin_count][bin_sizes[bin_count]++] = items[i];
            bin_remain -= items[i];
        } else {
            bin_count++;
            bins[bin_count][bin_sizes[bin_count]++] = items[i];
            bin_remain = CAPACITY - items[i];
        }
    }
    print_bins("Output2 (Next Fit)", bins, bin_count + 1, bin_sizes);
}

// Best Fit 알고리즘
void best_fit() {
    int bins[CAPACITY][CAPACITY] = {0};
    int bin_sizes[CAPACITY] = {0};
    int bin_remain[CAPACITY] = {0};
    int bin_count = 0;

    for (int i = 0; i < num_items; i++) {
        int best_index = -1, min_remain = CAPACITY + 1;

        for (int j = 0; j < bin_count; j++) {
            if (bin_remain[j] >= items[i] && bin_remain[j] - items[i] < min_remain) {
                best_index = j;
                min_remain = bin_remain[j] - items[i];
            }
        }

        if (best_index == -1) {
            bins[bin_count][bin_sizes[bin_count]++] = items[i];
            bin_remain[bin_count] = CAPACITY - items[i];
            bin_count++;
        } else {
            bins[best_index][bin_sizes[best_index]++] = items[i];
            bin_remain[best_index] -= items[i];
        }
    }
    print_bins("Output3 (Best Fit)", bins, bin_count, bin_sizes);
}

// Worst Fit 알고리즘
void worst_fit() {
    int bins[CAPACITY][CAPACITY] = {0};
    int bin_sizes[CAPACITY] = {0};
    int bin_remain[CAPACITY] = {0};
    int bin_count = 0;

    for (int i = 0; i < num_items; i++) {
        int worst_index = -1, max_remain = -1;

        for (int j = 0; j < bin_count; j++) {
            if (bin_remain[j] >= items[i] && bin_remain[j] > max_remain) {
                worst_index = j;
                max_remain = bin_remain[j];
            }
        }

        if (worst_index == -1) {
            bins[bin_count][bin_sizes[bin_count]++] = items[i];
            bin_remain[bin_count] = CAPACITY - items[i];
            bin_count++;
        } else {
            bins[worst_index][bin_sizes[worst_index]++] = items[i];
            bin_remain[worst_index] -= items[i];
        }
    }
    print_bins("Output4 (Worst Fit)", bins, bin_count, bin_sizes);
}

int main() {
    first_fit();
    next_fit();
    best_fit();
    worst_fit();
    return 0;
}
