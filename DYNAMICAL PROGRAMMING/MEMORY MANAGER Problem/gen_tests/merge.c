#include <stdio.h>
#include <assert.h>

#define MAXN 100000

//const char* merged = "merged.in";

size_t n = 0;
int res[MAXN] = {0};
size_t count = 0;
size_t sum = 0;

int main(int argc, char** argv)
{
    int i = 0;
    int j = 0;
    int cur_n = 0;
    int cur_m = 0;
    int cur = 0;
    FILE* inpf = NULL;

    if (2 > argc)
    {
        printf("Amount of files should be more than 1\n");
        return 0;
    }

    for (i = 1; i < argc; i++)
    {
        inpf = fopen(argv[i], "rt");
        fscanf(inpf, "%d %d", &cur_n, &cur_m);
        if (1 == i)
        {
            n = cur_n;
        }
        else
        {
            assert(n == cur_n);
        }

        for (j = 0; j < cur_m; j++)
        {
            fscanf(inpf, "%d", &cur);
            if (0 > cur)
            {
                cur = -cur;
                cur += sum;
                cur = -cur;
            }
            res[count] = cur;
            count++;
            if (MAXN < count)
            {
                printf("Too many operations...\n");
                break;
            }
        }

        fclose(inpf);
        sum += cur_m;
    }

    //inpf = fopen(merged, "wt");
    inpf = stdout;

    fprintf(inpf, "%d %d\n", n, count);

    for (i = 0; i < count; i++)
    {
        fprintf(inpf, "%d\n", res[i]);
    }

    fclose(inpf);
    return 0;
}
