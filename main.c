#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()
#include <string.h>
#include <stdbool.h> 

#define INFINITY 200000000

struct Point {
    int x;
    int y;
};

struct LineSegment {
    struct Point start;
    struct Point end;
};

bool intersect(struct LineSegment l1, struct LineSegment l2) {
    return (isAbove(l1.start, l2) && !isAbove(l1.end, l2)) || (((!isAbove(l1.start, l2) && isAbove(l1.end, l2)))) &&
            (isAbove(l2.start, l1) && !isAbove(l2.end, l1)) || (((!isAbove(l2.start, l1) && isAbove(l2.end, l1))));
}

bool isAbove(struct Point point, struct LineSegment lineSegment) {
    
}

int main(int argc, char* argv[]) {
    char* inputFileName = argv[1];
    char* outputFileName = argv[2];
    

    return 0;
}
