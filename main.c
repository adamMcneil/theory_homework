#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()
#include <string.h>
#include <stdbool.h> 

struct Point {
    double x;
    double y;
};

struct Point* buildPoint(double x, float y) {
    struct Point* point = (struct Point*) malloc(sizeof(struct Point));
    point->x = x;
    point->y = y;
    return point;
}

struct LineSegment {
    struct Point* start;
    struct Point* end;
};

struct LineSegment* buildLineSegment(double x1, float y1, float x2, float y2) {
    struct LineSegment* lineSegment = (struct LineSegment*) malloc(sizeof(struct LineSegment));
    lineSegment->start = buildPoint(x1, y1);
    lineSegment->end = buildPoint(x2, y2);
    return lineSegment;
}

struct LineSegments {
    int numberOfLines;
    struct LineSegment** lineSegments;
};

struct LineSegments* buildLineSegments(int numberOfLines) {
    struct LineSegments* lineSegments = (struct LineSegments*) malloc(sizeof(struct LineSegments*));
    lineSegments->numberOfLines = numberOfLines;
    lineSegments->lineSegments = (struct LineSegment**) malloc(sizeof(struct LineSegment) * numberOfLines);
    return lineSegments;
}

void printLineSegments(struct LineSegments* lineSegments) {
    for (int i = 0; i < lineSegments->numberOfLines; i++) {
        printf("(%lf, %lf), (%lf, %lf)\n", lineSegments->lineSegments[i]->start->x, lineSegments->lineSegments[i]->start->y, lineSegments->lineSegments[i]->end->x, lineSegments->lineSegments[i]->end->y);
    }
}

bool isAbove(struct Point* point, struct LineSegment* lineSegment) {
    double slope = (lineSegment->end->y - lineSegment->start->y) / (lineSegment->end->x - lineSegment->start->x);
    double intercept = lineSegment->start->y - (lineSegment->start->x * slope);
    double y = (slope * point->x) + intercept;
    return point->y > y;
}

bool intersect(struct LineSegment* l1, struct LineSegment* l2) {
    return (isAbove(l1->start, l2) && !isAbove(l1->end, l2)) || ((!isAbove(l1->start, l2) && isAbove(l1->end, l2))) &&
            (isAbove(l2->start, l1) && !isAbove(l2->end, l1)) || ((!isAbove(l2->start, l1) && isAbove(l2->end, l1)));
}

struct LineSegments* readInputFile(char* fileName) {
    int numberOfLineSegments;
    FILE *file;
    file = fopen(fileName, "r");
    fscanf(file, "%d\n", &numberOfLineSegments);
    printf("%d\n", numberOfLineSegments);
    struct LineSegments* lineSegments = buildLineSegments(numberOfLineSegments);
    for (int i = 0; i < numberOfLineSegments; i++) {
        double x1;
        double y1;
        double x2;
        double y2;
        fscanf(file, "(%lf,%lf), (%lf,%lf)\n", &x1, &y1, &x2, &y2);
        printf("%lf\n", x1);
        lineSegments->lineSegments[i] = buildLineSegment(x1, y1, x2, y2);
    }
    return lineSegments;
}

bool anyIntersection(struct LineSegments* lineSegments) {
    for (int i = 0; i < lineSegments->numberOfLines-1; i++) {
        for (int j = i+1; j < lineSegments->numberOfLines; j++) {
            if (intersect(lineSegments->lineSegments[i], lineSegments->lineSegments[j])) {
                return true;
            }
        }
    }
    return false;
}


int countIntersection(struct LineSegments* lineSegments) {
    int count = 0;
    for (int i = 0; i < lineSegments->numberOfLines-1; i++) {
        for (int j = i+1; j < lineSegments->numberOfLines; j++) {
            if (intersect(lineSegments->lineSegments[i], lineSegments->lineSegments[j])) {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    char* inputFileName = argv[1];
    char* outputFileName = argv[2];
    
    struct LineSegments* lineSegments = readInputFile(inputFileName);
    bool value = anyIntersection(lineSegments);
    printLineSegments(lineSegments);
    printf("%d\n", value);    


    int count = countIntersection(lineSegments);
    printf("%d\n", count);    
    return 0;
}
