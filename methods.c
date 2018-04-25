double centroid_diff(double *old, double *new){//return the sum squared difference of old and new centroids
    double diff = 0;
    for (int i =0; i<DIMENSIONS; i++){
	old = old + i;
	new = new + i;
	diff = diff + (*new - *old) * (*new - *old); 
    }
    return diff;
}

struct cluster{
    int num; //number of pixels in this cluster
    double **pixels; //dynamically allocated array of pixel arrays
    double centroid[DIMENSIONS];
};



void newcentroid(struct cluster group, double *newcen){ //get the new centroid, which is the average of the pixels in current cluster
    //second argument is the pointer to the new centroid array we want to write onto
    //cluster is a struct 
    //allclusters is an dynamically allocated array of struct cluster (k clusters)
    //cluster holds a member which is the number of pixels in current cluster
    //cluster also has an array member pixels, which is dynamically allocated using malloc and realloc
    //pixels is a 2D array, each inner array is a pixel array {x,y,r,g,b} 
    double sum[DIMENSIONS]={0};
    for (int i=0; i<DIMENSIONS; i++){//iterate through each dimension
	for (int j=0; j<group->num; j++){//iterate through each pixel
	    sum[i] = sum[i] + group.pixels[j][i];
	}
    }
    for (int k=0; k<DIMENSIONS; k++){
	newcen[k] = sum[k];
    }
}

