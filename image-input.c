/**
 * Source code for reading in an image for the Image Segmentation project
 * @author Lars Dreith
 */

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include <jerror.h>
#include "image-input.h"

int main() {
	int min_array[5];
	int max_array[5];
	double ** array = read_JPEG_file("red.jpg", min_array, max_array);
	printf(" %d %d %d %d %d \n", min_array[0], min_array[1], min_array[2], min_array[3], min_array[4]);
}

/*
 * Reads in a JPEG file
 * Structure inspired by https://stackoverflow.com/questions/5616216/need-help-in-reading-jpeg-file-using-libjpeg#22463461
 *
 * This can't be copied over in its current form. It needs to be reorganized to allow the array to be accessed.
 */
double ** read_JPEG_file (char * filename, int * min_array, int * max_array)
{
    unsigned long x, y;
    unsigned long data_size;	// length of file
    unsigned char * jdata;	// data for the image
    struct jpeg_decompress_struct info;	// for our jpeg info
    struct jpeg_error_mgr err;		// the error handler
    unsigned char r, g, b;

    // dereferencing pointers & setting default min for x and y
    min_array[0] = 0;
    min_array[1] = 0;


    FILE * file = fopen(filename, "rb"); // open the file

    info.err = jpeg_std_error(& err);
    jpeg_create_decompress( & info ); // fills info structure

    // if the jpeg file doesn't load
    if( !file ){
	fprintf(stderr, "Error reading JPEG file %s", filename);
	return 0;
    }

    jpeg_stdio_src(&info, file);
    jpeg_read_header(&info, TRUE); // read jpeg file header

    jpeg_start_decompress(&info); // decompress the file

    // set width and height
    x = info.output_width;
    y = info.output_height;
    data_size = x * y * 3;
    max_array[0] = (int) x;
    max_array[1] = (int) y;

    // creating array of appropriate size
    double ** array=malloc(sizeof(double)*(x*y));
    if(!array){
	perror("Could not allocate space.");
	exit(4);
    }
    for(int i=0;i<=(int) (y * x);i++){
	array[i]=malloc(sizeof(double)*5);
	if(!array[i]){
	    perror("Could not allocate space");
	    exit(4);
	}
    }

    // setting variables for max and min RGB values
    int r_max, g_max, b_max, r_min, g_min, b_min;

    // making JPEG buffer
    JSAMPARRAY pJpegBuffer = (JSAMPARRAY)malloc(sizeof(JSAMPROW));
    pJpegBuffer[0] = (JSAMPROW)malloc(sizeof(JSAMPLE) * x * info.output_components);

    // read scanlines one at a time & put bytes in jdata[] array.
    jdata = (unsigned char *)malloc(data_size);
    int row = 0;
    int count = 0;
    while( info.output_scanline < info.output_height )
    {
	jpeg_read_scanlines(&info, pJpegBuffer, 1); 
	if( count == 0 ){
	    r = pJpegBuffer[0][info.output_components * 0];
	    g = pJpegBuffer[0][info.output_components * 1];
	    b = pJpegBuffer[0][info.output_components * 2];
	    r_max = r; r_min = r;
	    g_max = g; g_min = g;
	    b_max = b; b_min = b;
	}
	    for (int i = 0; i < (int) x; i++){
		array[count][0] = i; array[count][1] = row;
		r = pJpegBuffer[0][info.output_components * i];
		g = pJpegBuffer[0][info.output_components * i + 1];
		b = pJpegBuffer[0][info.output_components * i + 2];
	        array[count][2] = r; array[count][3] = g; array[count][4] = b;
		if( r > r_max ){ r_max = r; }
		if( r < r_min ){ r_min = r; }
		if( g > g_max ){ g_max = g; }
		if( g < g_min ){ g_min = g; }
		if( b > b_max ){ b_max = b; }
		if( b < b_min ){ b_min = b; }
		count++;
	}

	row++;
    }

    // setting info in max and min arrays
    max_array[2] = (int) r_max; min_array[2] = (int) r_min;
    max_array[3] = (int) g_max; min_array[3] = (int) g_min;
    max_array[4] = (int) b_max; min_array[4] = (int) b_min;

    jpeg_finish_decompress(&info); // finish decompressing
    
    fclose(file);
    return array;
}
