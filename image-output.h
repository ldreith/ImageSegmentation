#ifndef image_output
#define image_output
#include <jpeglib.h>

#define CHANNELS 3
void write_JPEG_file(char * filename, int quality, JSAMPLE * image_buffer, int image_height, int image_width);
void color_image(int * clustered_array, int image_pixels, int k, JSAMPLE * image_buffer);
void output_image(int * clustered_array, int image_height, int image_width, int k);

#endif
