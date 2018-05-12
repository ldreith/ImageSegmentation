#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "k-means.h"
#include <math.h>
#include <time.h>
#include <float.h>
#define DIMENSIONS 5
#define CENTROIDS 3

//max 10 pixels
//what is being passed from image program
double  * pixel_raw_data[10];
struct pixel * pixel_data[10];
//max 20 pixels can belong to centroid. Should be arraylist.
struct pixel * centroids[CENTROIDS];

//For testing purposes
int main(){
//R G B X Y
int min_vals[DIMENSIONS]={0,0,0,0,0};
int max_vals[DIMENSIONS]={252,250,255,1920,1080};
    time_t t;
    srand((unsigned) time(&t));
    //placing centroids in random initial locations
    for(int i=0;i<CENTROIDS;i++){
	centroids[i]= add_pixel(place_k(min_vals, max_vals));
	normalize_vals(centroids[i]->location, DIMENSIONS, min_vals, max_vals);
    }
    //setting random values for pixels(as we dont have an image yet) and normalizing said values
    for(int i=0;i<10;i++){
    pixel_data[i]=add_pixel(place_k(min_vals,max_vals));
    normalize_vals(pixel_data[i]->location, DIMENSIONS, min_vals, max_vals);
    }
    double comp;
    comp=0;
    for(int i=0;i<10;i++){
	for(int j=0;j<CENTROIDS;j++){
	comp=get_distance(centroids[j]->location, pixel_data[i]->location);
	if(pixel_data[i]->lowest_dist>comp){
	pixel_data[i]->lowest_dist=comp; 
	pixel_data[i]->centroid=j;
	}
	}
    print_pixel(pixel_data[i]);
    }
free_all(pixel_data, 10);
free_all(centroids, CENTROIDS);
}
void free_all(struct pixel ** arr, int count){
    for(int i=0;i<count;i++){
	free(arr[i]->location);
	free(arr[i]);
    }
}
struct pixel * add_pixel(double * location){
    struct pixel * new=malloc(sizeof(struct pixel));
    if(!new){
    perror("Could not allocate space for pixel");
    exit(4);
    }
    new->lowest_dist=DBL_MAX;
    new->centroid=0;
    new->location=location;
    return new;
}
void print_pixel(struct pixel * p){
    printf("Location: [");
    for(int i=0;i<DIMENSIONS;i++){
	printf("%f,", p->location[i]);
    }
    printf("] Centroid: %i Distance: %f \n", p->centroid, p->lowest_dist);
}
void normalize_vals(double  *pixel_data, int size, int * min_vals, int * max_vals){
    for(int i=0;i<size; i++){
	pixel_data[i]=normalize_val(pixel_data[i],max_vals[i],min_vals[i]);
    }
}
double normalize_val(double value, double max_vals, double min_vals){
    return (value-min_vals)/(max_vals-min_vals);
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
    double total=0;
    for(int i=0; i<DIMENSIONS;i++){
	total+=pow(centroid_location[i]-pixel_data[i],2);
    }
    return sqrt(total);
}
