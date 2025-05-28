#include "tests.h"
#include "../include/utils.h"

void realloc_tests()
{
    int *arr = malloc(3 * sizeof(int));
    int arr2[5] = {1, 2, 3, 4, 5};
    int success;
    int total_success;
    int fail;
    int total_fail;
    int i = 0;

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    success = 0;
    fail = 0;
    total_success = 0;
    total_fail = 0;

    printf("\n\n%s#######################################\n", CYAN);
    printf(">  Running tests for the ft_realloc:  <\n");
    printf("#######################################%s\n\n", RESET);

    printf("%sChecking ft_realloc is wotking on array of int:%s\n", PURPLE, RESET);
    arr = ft_realloc(arr, sizeof(int) * 3, sizeof(int) * 5);

    arr[3] = 4;
    arr[4] = 5;

    while (i < 5)
    {
        if (arr[i] == arr2[i])
            success++;
        else
            fail++;
        i++;
    }


    printf("%sSuccess: %d\n%sFailes:  %d%s\n", GREEN, success, RED, fail, RESET);

}