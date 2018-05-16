#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "k-means.h"
#include "image-output.h"
#include "image-input.h"
#include <ctype.h>
#include <string.h>
#include <strings.h>


void free_array(int * arr){
    for (int i=0; i<=4; i++){
	free(arr+i);
    }
}

int main(int argc, char **argv){
    char *output_filename = "default_out";
    if (argc < 3){
	printf("invalid input1");
	exit(1);    				
    }
    if (!isdigit(*argv[2])){
	printf("invalid input");
	exit(1);
    }
    if (argc ==4){
	output_filename = argv[3];
    }
    char *filename = argv[1];
    char *ptr = argv[2];
    int k = 0;
    while (*ptr != '\0'){
	k = k*10 + *ptr-'0';
	ptr ++;
    } 
    int min_array[5];
    int max_array[5];
    double ** pixel_raw_data= read_JPEG_file(filename, min_array, max_array);
    int * cluster = kmeans(min_array, max_array, k, 5, pixel_raw_data);
    output_image(cluster, max_array[1], max_array[0], k, output_filename) ;    
    //free_array(min_array);
    //free_array(max_array);
    return 0;
}
