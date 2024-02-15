#include<stdlib.h>
#include<stdio.h>

void add_fractions(int* f1, int* f2)
{
    int result[2];

    int num_1 = f1[0];
    int den_1 = f1[1];
    int num_2 = f2[0];
    int den_2 = f2[1];

    if (den_1 == den_2)
    {
        result[0] = num_1 + num_2;
        result[1] = den_1;
        printf("result: %i/%i\n", result[0], result[1]);
        return;
    }

    int num_3 = num_1 * den_2;
    int num_4 = num_2 * den_1;

    result[0] = num_3 + num_4;
    result[1] = den_1 * den_2;
    printf("result: %i/%i\n", result[0], result[1]);
    return;
}

int main(int argc, char const *argv[])
{
    int f1[2] = {1, 2};
    int f2[2] = {1, 4};

    add_fractions(f1, f2);

    return 0;
}


