#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "k-means.h"
#include <math.h>
#include <time.h>
#define DIMENSIONS 5
#define CENTROIDS 3

//max 10 pixels
double  * pixel_data[10];
//max 20 pixels can belong to centroid. Should be arraylist.
double * centroids[CENTROIDS];
double * centroid_location[CENTROIDS];

//For testing purposes
int main(){
//R G B X Y
int min_vals[DIMENSIONS]={0,0,0,0,0};
int max_vals[DIMENSIONS]={252,250,255,1920,1080};
    srand((unsigned) time(NULL));
    for(int i=0;i<CENTROIDS;i++){
    centroid_location[i] = place_k(min_vals, max_vals);
    }
    for(int i=0;i<10;i++){
    pixel_data[i]=place_k(min_vals,max_vals);
    print_pixel(pixel_data[i],DIMENSIONS);
    normalize_vals(&pixel_data[i], DIMENSIONS, min_vals, max_vals);
    print_pixel(pixel_data[i], DIMENSIONS);
    }
}
void print_pixel(double * pixel_data, int size){
static int pixel=0;
printf("Pixel %i: ", pixel++);
for(int i=0;i<size;i++){
printf("%f ", pixel_data[i]);
}
}
void normalize_vals(double  **pixel_data, int size, int * min_vals, int * max_vals){
for(int i=0;i<size; i++){
*pixel_data[i]=normalize_val(*pixel_data[i],max_vals[i],min_vals[i]);
}
}
double normalize_val(double value, double max_vals, double min_vals){
    return (value-value-min_vals)/(max_vals-min_vals);
}
double * place_k(int * min_vals, int * max_vals){
    double * tmp= malloc(DIMENSIONS*sizeof(double));
    if(!tmp){
    perror("Could not allocate space");
    exit(4);
    }
    for(int i=0;i<DIMENSIONS;i++){
	tmp[i]=rand() % (max_vals[i]+1 - min_vals[i])+min_vals[i];
    }
    return tmp;
}
double get_distance(double * centroid_location, double * pixel_data){
    double total;
    for(int i=0; i<DIMENSIONS;i++){
	total+=pow(centroid_location[i]-pixel_data[i],2);
    }
    return sqrt(total);
}
