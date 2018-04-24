#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "k-means.h"
#include <math.h>
#include <time.h>
#define DIMENSIONS 5
#define CENTROIDS 3

//max 10 pixels
double pixel_data[10][DIMENSIONS];
//max 20 pixels can belong to centroid. Should be arraylist.
double centroids[CENTROIDS][20];
double centroid_location[CENTROIDS][DIMENSIONS];

//For testing purposes
int main(){
//R G B X Y
int min_vals[DIMENSIONS]={0,0,0,0,0};
int max_vals[DIMENSIONS]={252,250,255,1920,1080};

    for(int i=0;i<CENTROIDS;i++){
    centroid_location[i] = place_k(min_vals, max_vals);
    }
    
}

double normalize_vals(double value, double max_value, double min_value){
    return (value-min_value)/(max_value-min_value);
}
double * place_k(int * min_vals, int * max_vals){
    static double tmp[DIMENSIONS];
    srand((unsigned) time(NULL));
    for(int i=0;i<DIMENSIONS;i++){
	//Only line not working. Will ask Hoyle tomorrow.
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
