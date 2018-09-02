#include <stdio.h>
#include <assert.h>

typedef struct
{
    int x;
    int y;
} point_t;

typedef struct
{
    point_t first;
    point_t last;
} line_t;

int read_data(FILE *f, line_t *line, int *n, line_t *lines)
{
    assert(fscanf(f, "%d", &line->first.x) == 1);
    assert(fscanf(f, "%d", &line->first.y) == 1);
    assert(fscanf(f, "%d", &line->last.x) == 1);
    assert(fscanf(f, "%d", &line->last.y) == 1);

    assert(fscanf(f, "%d", n) == 1);
    for (int i = 0; i < (*n); i++)
    {
        assert(fscanf(f, "%d", &lines[i].first.x) == 1);
        assert(fscanf(f, "%d", &lines[i].first.y) == 1);
        assert(fscanf(f, "%d", &lines[i].last.x) == 1);
        assert(fscanf(f, "%d", &lines[i].last.y) == 1);
    }

    return 1;
}

int intersection(point_t start1, point_t end1, point_t start2, point_t end2)
   {
       point_t dir1;
       dir1.x = end1.x - start1.x;
       dir1.y = end1.y - start1.y;
       point_t dir2;
       dir2.x = end2.x - start2.x;
       dir2.y = end2.y - start2.y;

       float a1 = -dir1.y;
       float b1 = +dir1.x;
       float d1 = -(a1*start1.x + b1*start1.y);

       float a2 = -dir2.y;
       float b2 = +dir2.x;
       float d2 = -(a2*start2.x + b2*start2.y);

       float seg1_line2_start = a2*start1.x + b2*start1.y + d2;
       float seg1_line2_end = a2*end1.x + b2*end1.y + d2;

       float seg2_line1_start = a1*start2.x + b1*start2.y + d1;
       float seg2_line1_end = a1*end2.x + b1*end2.y + d1;

       if (seg1_line2_start * seg1_line2_end >= 0 || seg2_line1_start * seg2_line1_end >= 0)
       {
           return 0;
       }

       return 1;
   }


int main(void)
{
    char file_name[255];
    puts("File:");
    scanf("%s", file_name);

    FILE *f = fopen(file_name, "r");
    assert(f);

    line_t line;
    int n;
    line_t lines[1000];

    assert(read_data(f, &line, &n, lines));

    int crs = 0;
    for (int i = 0; i < n; i++)
    {
        if (intersection(line.first, line.last, lines[i].first, lines[i].last))
        {
            crs = 1;
            break;
        }
    }

    if (crs)
    {
        puts("NO");
    }
    else
    {
        puts("YES");
    }

    return 0;
}
