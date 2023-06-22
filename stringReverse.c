#include <stdio.h>
#include <string.h>
#include <time.h>
#include "myString.h"

#define STRSIZE(str) (unsigned long)sizeof(str) - 1
#define ASCIISIZE (size_t)(128 - 32)
#define SORTME "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book."

int verbose = 0;

// function to swap two characters in the string
void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

// function to partition the string and return the pivot
// index
int partition(char *str, int low, int high)
{
    char pivot = str[high]; // choose the last character as
                            // the pivot
    int i = low - 1;        // index of the smaller element

    // loop through the sub-array to partition it around the
    // pivot
    for (int j = low; j <= high - 1; j++)
    {
        // if the current character is smaller than or equal
        // to the pivot
        if (str[j] <= pivot)
        {
            i++;                    // increment the index of the smaller
                                    // element
            swap(&str[i], &str[j]); // swap the current
                                    // character with str[i]
        }
    }
    swap(&str[i + 1],
         &str[high]); // swap the pivot with str[i + 1]
    return i + 1;     // return the pivot index
}

// function to sort the string using the Quick Sort
// algorithm
void quickSort(char *str, int low, int high)
{

    if (low < high)
    {
        int pivotIndex = partition(
            str, low, high); // partition the string and get
                             // the pivot index
        quickSort(str, low,
                  pivotIndex - 1); // sort the left sub-array
        quickSort(str, pivotIndex + 1,
                  high); // sort the right sub-array
    }
}

char* timeMeQuickSort()
{

    char str[] = SORTME;
    int n = strlen(str);

    quickSort(str, 0, n - 1);
    if (verbose)
    {
        printf("\nString (quickSort): %s", str);
    }

    return str;
}

int swapSort(char *str)
{
    char nextChar;
    int sorted = 0;

    while (*(str + 1))
    {
        nextChar = *(str + 1);

        if (*str > nextChar)
        {
            sorted = 1;

            *(str + 1) = *str;
            *str = nextChar;
        }

        str++;
    }
    return sorted;
}

size_t getCharacterIndex(char ch)
{
    return ch - 32;
}

char* timeMeSwapsort()
{
    char str[] = SORTME;
    while (swapSort(str))
    {
    }
    if (verbose)
    {
        printf("\nString (swapSort) : %s", str);
    }

    return str;
}
char* timeMeHashing()
{
    char str[] = SORTME;
    char str_new[sizeof(str)] = {'\0'};

    size_t idx;
    int letterCount[ASCIISIZE + 1] = {0};

    for (size_t i = 0; i < sizeof(str) - 1; i++)
    {
        idx = getCharacterIndex(str[i]);
        letterCount[idx] += 1;
    }

    idx = 0;

    for (size_t i = 0; i < sizeof(letterCount) / sizeof(letterCount[0]); i++)
    {
        for (size_t j = 0; j < letterCount[i]; j++)
        {
            str_new[idx] = (char)(i + 32);

            idx += 1;
        }
    }

    printf("\nidx = %zu, sentence = %zu", sizeof(str_new), sizeof(str));

    if (verbose)
    {
        printf("\nString (hashing)  : %s", str_new);
    }

    return str_new;
}

int main()
{
    clock_t start, end;
    double cpu_time_used;
    char *hash;
    char *swap;
    char *quick;

    start = clock();

    hash = timeMeHashing();

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime elapsed (hashing)  : %lf", cpu_time_used);

    start = clock();

    swap = timeMeSwapsort();

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime elapsed (swapSort) : %lf", cpu_time_used);

    start = clock();

    quick = timeMeQuickSort();

    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime elapsed (quickSort): %lf", cpu_time_used);


    mystrcmp(hash,quick);
    mystrcmp(hash,swap);
    mystrcmp(swap,quick);
    printf("\n%zu",stringLength(hash));
    printf("\n%zu",stringLength(quick));
    printf("\n%zu",stringLength(swap));

    return 0;
}