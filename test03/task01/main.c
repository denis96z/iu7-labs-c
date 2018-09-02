#include <stdio.h>
#include <assert.h>

int main(void)
{
    char file_name[255];
    puts("File:");
    scanf("%s", file_name);

    FILE *f = fopen(file_name, "r");
    assert(f);

    int n;
    int numbers[1000];

    puts("\nNumbers:");
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        assert(fscanf(f, "%d", &numbers[i]) == 1);
        printf("%5d", numbers[i]);
    }
    puts("\n");

    int crossed = 0;
    for (int i = 0; i < (n - 1); i++)
    {
        if (numbers[i] <= numbers[i + 1])
        {
            crossed++;
        }
    }
    printf("Numbers left: %d", n - crossed);

    return 0;
}
