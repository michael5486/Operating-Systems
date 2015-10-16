#include <stdlib.h>
#include <stdio.h>
void foo(void *);

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    int i;
    float *fltArr;
    Point *point;
    double dbl;
} functionData;

int main(int argumentCount, char *argumentArray[]) {

    int x = 5;
    int *ptr;
    Point *point = malloc(sizeof(point));
    point->x = 22.1; //same as (*point).x = 22.1
    point->y =-4;
    
    
    ptr = &x;
        
    void *voidPtr;
    voidPtr = &x;
        
    printf("*ptr = %d, *voidPtr = %d\n", *ptr, *((int *)voidPtr));
    
    double dbl = 3.14;
    voidPtr = &dbl;
    
    printf("*voidPtr (double) => %f\n", *((double *)voidPtr));
    
    float fltArr[4] = {1.1, 2.25, 3, 4.0};
    voidPtr = fltArr;
    
    printf("*voidPtr[3] = %f\n", ((float *)voidPtr)[3]);
    
    voidPtr = point;
    printf("*voidPtr.x = %f\n", ((Point *)voidPtr)->x);
    
    void *voidArr[4];
    voidArr[0] = &x;
    voidArr[1] = fltArr;
    voidArr[2] = point;
    voidArr[3] = &dbl;
    
    printf("*voidArr[3] = %f\n", *((double *)voidArr[3]));
        
    functionData data;
    
    data.i = x;
    data.fltArr = fltArr;
    data.point = point;
    data.dbl = dbl;
        
    foo(&data);    
}

void foo(void *data) {
   // void **voidArr = (void **)data;
    //printf("*voidArr[3] = %f\n", *((double *)voidArr[3]));
    functionData myData;
    myData = *((functionData *)data);
    printf("myData.dbl = %f\n", myData.dbl);
}