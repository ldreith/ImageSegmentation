#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "k-means.h"
#include <math.h>
#include <time.h>
#include <float.h>
#define DIMENSIONS 5
#define CENTROIDS 2

//max 10 pixels
//what is being passed from image program
double  * pixel_raw_data[6];
struct pixel * pixel_data[6];
//max 20 pixels can belong to centroid. Should be arraylist.
struct pixel * centroids[CENTROIDS];

//For testing purposes
int main(){
//R G B X Y
int min_vals[DIMENSIONS]={0,0,0,0,0};
int max_vals[DIMENSIONS]={252,250,255,3,2};
    time_t t;
    srand((unsigned) time(&t));
    //placing centroids in random initial locations
    for(int i=0;i<CENTROIDS;i++){
	centroids[i]= add_pixel(place_k(min_vals, max_vals));
	normalize_vals(centroids[i]->location, DIMENSIONS, min_vals, max_vals);
    }
    //setting random values for pixels(as we dont have an image yet) and normalizing said values
    double tmp[DIMENSIONS]={10,10,10,0,0};
    pixel_data[0]=add_pixel(tmp);
    double tmp2[DIMENSIONS]={8,11,9,0,1};
    pixel_data[1]=add_pixel(tmp2);
    double tmp3[DIMENSIONS]={7,5,2,1,0};
    pixel_data[2]=add_pixel(tmp3);
    double tmp4[DIMENSIONS] ={201,200,190,2,1};
    pixel_data[3]=add_pixel(tmp4);
    double tmp5[DIMENSIONS]={200,199,198,2,2};
    pixel_data[4]=add_pixel(tmp5);
    double tmp7[DIMENSIONS]={212,227,225,3,2};
    pixel_data[5]=add_pixel(tmp7); 
    for(int i=0;i<NUMPIX;i++){
	//pixel_data[i]= add_pixel(place_k(min_vals, max_vals));
	normalize_vals(pixel_data[i]->location, DIMENSIONS, min_vals, max_vals);
    }
    //for how much centroids are moving
    double largest_change=0;
    double comp=0;
    //keep updating centroids and recalculating all given pixels distances to said centroids until the centroids stop moving, that is once largest_chage<0.01;
    do{
    largest_change=0;
    //gets each pixels centroid distance
    for(int i=0;i<NUMPIX;i++){
	for(int j=0;j<CENTROIDS;j++){
	comp=get_distance(centroids[j]->location, pixel_data[i]->location);
	if(pixel_data[i]->lowest_dist>comp){
	pixel_data[i]->lowest_dist=comp; 
	pixel_data[i]->centroid=j;
	}
	}
    }
    //updating each centroid
    double temp=0;
    for(int l=0;l<CENTROIDS;l++){
	if((temp=update_centroid_location(centroids[l]->location, l, NUMPIX))>largest_change)
	    largest_change=temp;
	printf("Centroid %i moved: %f\n",l, temp);
    }
    } while(largest_change>0.0001);
    for(int i=0;i<NUMPIX;i++){
	printf("Pixel %i's Centroid: %i\n",i,pixel_data[i]->centroid);
    }
    printf("Averadge Distance: %f\n",(get_avg_dist(NUMPIX)));
    free_all(pixel_data, NUMPIX);
    free_all(centroids, CENTROIDS);
}
double get_avg_dist(int numpix){
    double avg=0;
    for(int i=0;i<numpix;i++){
	avg+=pixel_data[i]->lowest_dist;
    }
    return (avg/numpix);
}
//returns difference between the centroid
//useful to know how a centroid is changing
double update_centroid_location(double *centroid, int centroid_num, int numpix){
    double old_cent[DIMENSIONS];
    memcpy(old_cent,centroid,DIMENSIONS*sizeof(double));
    double *sum=malloc(DIMENSIONS*sizeof(double));
    if(!sum){
    perror("couldnt allocate memory");
    exit(4);
    }
    memset(sum, 0, DIMENSIONS*sizeof(double));
    int pixcount=0;
    for(int i=0;i<numpix;i++){
	if(pixel_data[i]->centroid==centroid_num){
	    pixcount++;
	    for(int j=0;j<DIMENSIONS;j++){
		sum[j]+=pixel_data[i]->location[j];
	    }
	}
    }
    for(int m=0;m<DIMENSIONS;m++){
    sum[m]=(sum[m]/numpix);
    }
    memcpy(centroid,sum,DIMENSIONS*sizeof(double));
    free(sum);
    return get_diff(centroid, old_cent);
}
double get_diff(double * cent, double * old_cent){
    double diff=0;
    for(int i=0;i<DIMENSIONS; i++){
	diff+=sqrt(pow(cent[i]-old_cent[i],2));
    }
    return diff;
}
void free_all(struct pixel ** arr, int count){
    for(int i=0;i<count;i++){
	//comment next line for demo
	//free(arr[i]->location);
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
    printf("] Centroid: %i Distance: %f", p->centroid, p->lowest_dist);
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
