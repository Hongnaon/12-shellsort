#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

// 랜덤 숫자 생성 함수
void generateRandomNumbers(int numbers[]) {
    for (int idx = 0; idx < ARRAY_SIZE; idx++) {
        numbers[idx] = rand() % 1000; // 0부터 999까지의 난수 생성
    }
}

// 배열의 일부(최대 20개)를 출력하는 함수
void printTruncatedArray(int numbers[], int size) {
    for (int idx = 0; idx < 20 && idx < size; idx++) {
        printf("%d ", numbers[idx]);
    }
    if (size > 20) {
        printf("...");
    }
    printf("\n\n");
}

// 배열 전체를 출력하는 함수
void printFullArray(int numbers[], int size) {
    for (int idx = 0; idx < size; idx++) {
        printf("%d ", numbers[idx]);
    }
    printf("\n\n");
}

// 배열 복사 함수
void copyArray(int source[], int destination[]) {
    for (int idx = 0; idx < ARRAY_SIZE; idx++) {
        destination[idx] = source[idx];
    }
}

// 쉘 정렬 수행 함수
void doShellSort(int original[], int gapType, int* compCount, int* moveCount) {
    int gap, idx, innerIdx, tempValue;
    *compCount = 0;
    *moveCount = 0;

    int sortedArray[ARRAY_SIZE];
    copyArray(original, sortedArray); // 원본 배열 복사

    // n/2 간격 방식
    if (gapType == 2) {
        gap = ARRAY_SIZE / 2;
        while (gap > 0) {
            printf("Sorting with gap = %d: \n", gap);
            for (idx = gap; idx < ARRAY_SIZE; idx++) {
                tempValue = sortedArray[idx];
                innerIdx = idx;

                // 현재 간격에 따라 요소 이동
                while (innerIdx >= gap) {
                    (*compCount)++;
                    if (sortedArray[innerIdx - gap] > tempValue) {
                        sortedArray[innerIdx] = sortedArray[innerIdx - gap];
                        innerIdx -= gap;
                        (*moveCount)++;
                    }
                    else {
                        break;
                    }
                }
                sortedArray[innerIdx] = tempValue;
                (*moveCount)++;
            }
            printTruncatedArray(sortedArray, ARRAY_SIZE);
            gap /= 2;
        }
    }
    // n/3 간격 방식
    else if (gapType == 3) {
        gap = ARRAY_SIZE / 3;
        while (gap > 0) {
            printf("Sorting with gap = %d: \n", gap);
            for (idx = gap; idx < ARRAY_SIZE; idx++) {
                tempValue = sortedArray[idx];
                innerIdx = idx;

                while (innerIdx >= gap) {
                    (*compCount)++;
                    if (sortedArray[innerIdx - gap] > tempValue) {
                        sortedArray[innerIdx] = sortedArray[innerIdx - gap];
                        innerIdx -= gap;
                        (*moveCount)++;
                    }
                    else {
                        break;
                    }
                }
                sortedArray[innerIdx] = tempValue;
                (*moveCount)++;
            }
            printTruncatedArray(sortedArray, ARRAY_SIZE);
            gap /= 3;
        }
    }
    printf("Sorted shellArray (gap = %d):\n", gapType);
    printFullArray(sortedArray, ARRAY_SIZE);
}

// 삽입 정렬 수행 함수
void doInsertionSort(int original[], int* compCount, int* moveCount) {
    int idx, innerIdx, tempValue;
    *compCount = 0;
    *moveCount = 0;

    int sortedArray[ARRAY_SIZE];
    copyArray(original, sortedArray); // 원본 배열 복사

    for (idx = 1; idx < ARRAY_SIZE; idx++) {
        tempValue = sortedArray[idx];
        innerIdx = idx - 1;

        // 현재 요소를 정렬된 위치로 이동
        while (innerIdx >= 0 && sortedArray[innerIdx] > tempValue) {
            sortedArray[innerIdx + 1] = sortedArray[innerIdx];
            innerIdx--;
            (*compCount)++;
            (*moveCount)++;
        }
        sortedArray[innerIdx + 1] = tempValue;
        (*moveCount)++;
        if (innerIdx >= 0) {
            (*compCount)++;
        }
    }
    printf("Sorted insertionArray:\n");
    printFullArray(sortedArray, ARRAY_SIZE);
}

int main() {
    srand(time(NULL)); // 난수 생성을 위한 시드 설정

    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;

    generateRandomNumbers(array);

    // Shell Sort
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Insertion Sort - 보너스
    printf("\nInsertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
