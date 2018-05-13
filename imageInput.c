/**
 * Source code for reading in an image for the Image Segmentation project
 * @author Lars Dreith
 */

#include <stdio.h>
#include <jpeglib.h>
#include <jerror.h>

/*
 * Reads in a JPEG file
 * Structure inspired by https://stackoverflow.com/questions/5616216/need-help-in-reading-jpeg-file-using-libjpeg#22463461
 */
void read_JPEG_file (char * filename) // change from void
{
    unsigned long x, y;
    unsigned long data_size;	// length of file
    int channels;		// 3 => RGB, 4 => RGBA
    unsigned char * rowptf[1];	// pointer to an array
    unsigned char * jdata;	// data for the image
    struct jpeg_decompress_struct info;	// for our jpeg info
    struct jpeg_error_mgr err;		// the error handler

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
    channels = info.num_components;
    type = GL_RGB;
    if( channels == 4 ){ 
	type = GL_RGBA; 
	data_size = x * y * 4;
    } else {
	type = GL_RGB;
	data_size = x * y * 3;
    }

    // read scanlines one at a time & put bypes in jdata[] array.
    jdata = (unsigned char *)malloc(data_size);
    while( info.output_scanline < info.output_height )
    {
	rowptr[0] = (unsigned char *)jdata + 
	    3* info.output_width * info.output_scanline;
	jpeg_read_scanlines(&info, rowptf, 1);
    }

    jpeg_finish_decompress(&info); // finish decompressing
    
    fclose(file);
}
