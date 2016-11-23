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

// Returns the speed in counts per second for the motor specified by |motor|.
// Time interval used in speed calculation specified by |tMs|.
float getSpeed(tMotor motor, int tMs = 50) {
    int d1 = nMotorEncoder[motor];
    wait1Msec(tMs);
    return (nMotorEncoder[motor] - d1) / (float) tMs;
}

#endif
