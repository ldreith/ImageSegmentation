# Image Segmentation Using K-Means
Using K-Means to segment an input image by RGB value.

# Contributors
- Lars Dreith
- David Gold
- Jiachen Liu
- Leo Schumann

Parts:

k-means.c -- all methods for k-means algorithm. Implemented by David Gold. get_diff and update_centroids adapted fromt the implementation by Jiachen Liu.
k-means.h -- header for k-means algorithm. Implemented by David Gold. 
problems: None. Valgrind 
memory leaks: None.

image-input.c -- gets X,Y,R,G,B values for image. Implemented by Lars Dreith
image-input.h -- header for image-input.c. Implemented by Lars Dreith
problems: passes null values for some pixel arrays causeing k-means to segfault. These null values are the R,G and B.
memory leaks: all mallocs.

image-output.c -- takes output from k-means, a 1D array and prints it as JPEG. Implemented by Leo Schumann.
image-output.c -- header for a image-output. Implemented by Leo Schumann.
problems: None.
memory leaks: None.

ImageSegmentation.c -- Implements all other programs correctly. Handles user input. Implemented by Jiachen Liu
ImageSegmentation.h -- Header for image Segmentation. Impelmented by Jiachen Liu.

Makefile -- implemented by Jiachen Liu.

Readme.md -- implemented by David Gold.

ImageSegmentation.1 -- Man page for image segmentation program. Implemented by David Gold.Modified by Jiachen Liu


