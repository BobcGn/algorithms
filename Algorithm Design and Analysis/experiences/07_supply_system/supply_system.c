#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} BrightRegion;

typedef struct {
    double left;
    double right;
} Interval;

static Interval coverage_interval(BrightRegion point, double radius)
{
    double d = sqrt(radius * radius - point.y * point.y);
    return (Interval){
        .left = point.x - d,
        .right = point.x + d
    };
}

static int compare_by_right(const void *first, const void *second)
{
    const Interval *a = first;
    const Interval *b = second;

    if (a->right < b->right) return -1;
    if (a->right > b->right) return 1;
    return 0;
}

int minimum_stations(const BrightRegion regions[], int n, double radius)
{
    Interval intervals[100];  // 手册保证 1 ≤ n ≤ 100
    for (int i = 0; i < n; i++) {
        intervals[i] = coverage_interval(regions[i], radius);
    }
    qsort(intervals, n, sizeof intervals[0], compare_by_right);

    double last = intervals[0].right;
    int count = 1;
    for (int i = 1; i < n; i++) {
        if (intervals[i].left > last) {
            last = intervals[i].right;
            count++;
        }
    }
    return count;
}

int main(void)
{
    int k;
    if (scanf("%d", &k) != 1) return 1;

    for (int group = 0; group < k; group++) {
        int n;
        double radius;
        BrightRegion regions[100];

        if (scanf("%d %lf", &n, &radius) != 2) return 1;
        if (n < 1 || n > 100) return 1;

        for (int i = 0; i < n; i++) {
            if (scanf("%lf %lf", &regions[i].x, &regions[i].y) != 2) return 1;
        }

        printf("%d\n", minimum_stations(regions, n, radius));
    }
    return 0;
}
