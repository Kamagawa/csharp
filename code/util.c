#ifndef UTIL_C
#define UTIL_C

void swap(int * const a, int * const b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// insertion sort, chosen for small input size
void sort(int ar[], int len, bool ascending = true) {
    int i, j, k;

    for (i = 1; i < len; i++) {
        k = i;
        for (j = i - 1; j > -1; j--) {
            if (ar[k] >= ar[j] ^ ascending) {
                swap(ar + k, ar + j);
                k--;
            }
        }
    }
}

#endif
