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
    bool isStart;
    int index;
};

struct Point* buildPoint(double x, float y, bool isStart, int index) {
    struct Point* point = (struct Point*) malloc(sizeof(struct Point*));
    point->x = x;
    point->y = y;
    point->isStart = isStart;
    point->index = index;
    return point;
}

struct Points {
    int numberOfPoints;
    struct Point** points;
};

void printPoints(struct Points* points) {
    for (int i = 0; i < points->numberOfPoints; i++) {
        printf("(%f, %f)\n", points->points[i]->x, points->points[i]->y);
    }
}

struct LineSegment {
    struct Point* start;
    struct Point* end;
};

struct LineSegment* buildLineSegment(double x1, float y1, float x2, float y2, int index) {
    struct LineSegment* lineSegment = (struct LineSegment*) malloc(sizeof(struct LineSegment*));
    if (x1 < x2) {
        lineSegment->start = buildPoint(x1, y1, true, index);
        lineSegment->end = buildPoint(x2, y2, false, index);
    }
    else {
        lineSegment->start = buildPoint(x1, y1, false, index);
        lineSegment->end = buildPoint(x2, y2, true, index);
    }
    return lineSegment;
}

struct LineSegments {
    int numberOfLines;
    struct LineSegment** lineSegments;
};

struct LineSegments* buildLineSegments(int numberOfLines) {
    struct LineSegments* lineSegments = (struct LineSegments*) malloc(sizeof(struct LineSegments*));
    lineSegments->numberOfLines = numberOfLines;
    lineSegments->lineSegments = (struct LineSegment*) malloc(sizeof(struct LineSegment) * numberOfLines);
    return lineSegments;
}

struct Points* buildPoints(struct LineSegments* lineSegments) {
    struct Points* points = (struct Points*) malloc(sizeof(struct Points*));
    points->numberOfPoints = 2 * lineSegments->numberOfLines; 
    points->points = (struct Point*) malloc(sizeof(struct Point*) * 2 * lineSegments->numberOfLines);
    for (int i = 0; i < lineSegments->numberOfLines; i++) {
        points->points[2 * i] = lineSegments->lineSegments[i]->start;
        points->points[2 * i + 1] = lineSegments->lineSegments[i]->end;
    }
    return points;
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
    struct LineSegments* lineSegments = buildLineSegments(numberOfLineSegments);
    for (int i = 0; i < numberOfLineSegments; i++) {
        double x1;
        double y1;
        double x2;
        double y2;
        fscanf(file, "(%lf,%lf), (%lf,%lf)\n", &x1, &y1, &x2, &y2);
        lineSegments->lineSegments[i] = buildLineSegment(x1, y1, x2, y2, i);
    }
    return lineSegments;
}

void sort(struct Points* points) {
    for (int i = 0; i < points->numberOfPoints-1; i++) {
        int minIndex = -1;
        double min = 10000000;
        for (int j = i; j < points->numberOfPoints; j++) {
            if (points->points[j]->x < min) {
                minIndex = j;
                min = points->points[j]->x;
            }
        }
        struct Point* temp = points->points[i]; 
        points->points[i] = points->points[minIndex];
        points->points[minIndex] = temp;
    }
}

struct Label{
    int index;
    int y;
};

void insert(int[] labels, int) {

}

bool anyIntersection(struct LineSegments* lineSegments) {
    struct Points* points = buildPoints(lineSegments);
    sort(points);
    printPoints(points);
    struct Label[] labels[points->numberOfPoints]; 
    for (int i = 0; i < points->numberOfPoints; i++) {
        
        int label = 0;
        if (points->points[i]->isStart) {
            if (intersect(lineSegments->lineSegments[i], lineSegments->lineSegments[])) {
                return true;
            }
            if (intersect(lineSegments->lineSegments[i], lineSegments->lineSegments[])) {
                return true;
            }
        }
        else {
            if (intersect(lineSegments->lineSegments[], lineSegments->lineSegments[]))
        }
    }
}

bool anyIntersectionBruteForce(struct LineSegments* lineSegments) {
    for (int i = 0; i < lineSegments->numberOfLines-1; i++) {
        for (int j = i+1; j < lineSegments->numberOfLines; j++) {
            if (intersect(lineSegments->lineSegments[i], lineSegments->lineSegments[j])) {
                return true;
            }
        }
    }
    return false;
}

int countIntersectionBruteForce(struct LineSegments* lineSegments) {
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
    // printLineSegments(lineSegments);
    // printf("%d\n", value);    

    // int count = countIntersectionBruteForce(lineSegments);
    // printf("%d\n", count);    
    return 0;
}
