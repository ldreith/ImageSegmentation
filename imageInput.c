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
 *
 * This can't be copied over in its current form. It needs to be reorganized to allow the array to be accessed.
 */
void read_JPEG_file (char * filename)
{
    unsigned long x, y;
    unsigned long data_size;	// length of file
    unsigned char * rowptf[1];	// pointer to an array
    unsigned char * jdata;	// data for the image
    struct jpeg_decompress_struct info;	// for our jpeg info
    struct jpeg_error_mgr err;		// the error handler
    unsigned char r, g, b;

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
    type = GL_RGB;
    data_size = x * y * 3;

    // creating array of appropriate size
    int array[x * y][5];

    // read scanlines one at a time & put bytes in jdata[] array.
    jdata = (unsigned char *)malloc(data_size);
    int row = 0;
    int count = 0;
    while( info.output_scanline < info.output_height )
    {
	/*rowptr[0] = (unsigned char *)jdata + 
	    3* info.output_width * info.output_scanline;*/ // what is this for???
	jpeg_read_scanlines(&info, rowptf, 1);

	for (int i = 0; i < x; i++){
	    array[count][0] = i; array[count][2] = row;
	    array[count][2] = pJpegBuffer[0][cinfo.output_components * i];
	    array[count][3] = pJpegBuffer[0][cinfo.output_components * i + 1];
	    array[count][4] = pJpegBuffer[0][cinfo.output_components * i + 2];
	    count++;
	}

	row++;
    }

    jpeg_finish_decompress(&info); // finish decompressing
    
    fclose(file);

    // variable "array" should be in the correct format for k-means
}
