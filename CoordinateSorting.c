/*
 * Made by Kenley Rodriguez
 * 3/24/2020
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


typedef struct point{
    int x;
    int y;
}point;

struct point* points;

void ReadData(FILE * fp, int *centerX, int *centerY, int *radius, int *n );
void FilterData(int centerX, int centerY, int radius, int *n);
void merge(point* points, int l, int m, int r);
void mergeSort(point* points, int l, int r);
int binarySearch(struct point* points, int x, int y, int n);
void printFilteredPoints(int n, FILE * outfp);
void SearchPhase(int n);

void ReadData(FILE * fp, int *centerX, int * centerY, int *radius, int * n){

    points = (struct point*)malloc(*n * sizeof(struct point));

    fscanf(fp, "%d%d%d%d", centerX, centerY, radius, n);

    for(int i = 0; i < *n; i++ ){
        fscanf(fp, "%d%d", &points[i].x, &points[i].y);
    }
}


void FilterData(int centerX, int centerY, int radius, int * n){
    int counter = 0;
    int newSize;
    for (int i = 0; i < *n; i++){
        if(pow(points[i].x - centerX, 2) + pow(points[i].y - centerY, 2) > pow(radius,2))
            counter++;
    }
    newSize = *n - counter;
    int j = 0;
    point *temp = points;
    point* newList = (point*)malloc(newSize * sizeof( point));
    for(int i = 0; i < *n; i++){
        if(pow(points[i].x-centerX, 2) + pow(points[i].y-centerY, 2) <= pow(radius,2)){
            newList[j].x = points[i].x;
            newList[j].y = points[i].y;
            j++;
        }
    }
    *n = newSize;
    points = newList;
}

void merge(point * points, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    point * L = (point*)malloc(n1 * sizeof( point));
    point * R = (point*)malloc(n2 * sizeof(point));
    for (i = 0; i < n1; i++)
        L[i] = points[l + i];
    for (j = 0; j < n2; j++)
        R[j] = points[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2){
        if(L[i].x != R[j].x){

            if (L[i].x <= R[j].x){
                points[k] = L[i];
                i++;
            }
            else{
                points[k] = R[j];
                j++;

            }
        }
        else if(L[i].x == R[j].x){

            if (L[i].y <= R[j].y){
                points[k] = L[i];
                i++;

            }

            else{
                points[k] = R[j];
                j++;
            }
        }
        k++;
    }

    while (i < n1){

        points[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){

        points[k] = R[j];
        j++;
        k++;

    }
}
void mergeSort(point * points, int l, int r)
{
    if (l < r){
        int m = (l+r)/2;

        mergeSort(points, l, m);
        mergeSort(points, m+1, r);

        merge(points, l, m, r);
    }
}

int binarySearch(point * points, int x, int y, int len) {
    int l = 0, h = len - 1, mid;
    while (l <= h){
        mid = (l + h) / 2;
        if (points[mid].x == x)
            if(points[mid].y == y)
                return mid+1;
        if ((points[mid].x < x) || ((points[mid].x == x) && (points[mid].y < y)))
            l = mid + 1;

        else
            h = mid - 1;
    }
    return -1;
}

void printFilteredPoints( int n, FILE * outfp){
    for (int i=0; i < n; i++){
        fprintf(outfp, "%d %d\n", points[i].x, points[i].y);
    }
    printf("filtered and sorted data written to out.txt\n");
}
void SearchPhase(int n) {
    int x, y, record;
    while (x != -999) {

        printf("Search input (x, y): ");
        scanf("%d %d", &x, &y);
        if (x == -999) {
            printf("Output: exit\n");
            break;
        }
        record = binarySearch(points, x, y, n);
        if (record == -1)
            printf("Output: Not Found\n");
        else
            printf("Output: Found at record %d\n", record);

    }

}

int main() {
    point *center, *test;
    int centerX, centerY, radius, n;
    FILE *fp, *outfp;


    fp = fopen("in.txt", "r");
    outfp = fopen("out.txt", "w");

    ReadData(fp, &centerX, &centerY, &radius, &n );
    FilterData(centerX, centerY, radius, &n);
    mergeSort(points, 0, n -1);
    printFilteredPoints(n, outfp);
    fclose(fp);
    fclose(outfp);
    SearchPhase(n);

    return 0;
}
