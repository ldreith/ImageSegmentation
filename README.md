# Image Segmentation Using K-Means
Using K-Means to segment an input image by RGB value and the x,y coordinates.

# Contributors
- Lars Dreith
- David Gold
- Jiachen Liu
- Leo Schumann

Parts:

K-means abstract 


k-means.c -- all methods for k-means algorithm. 

k-means.h -- header for k-means algorithm.

problems: Valgrind errors for conditonal jump or move based off ininitalized value for file name being passed in. 

memory leaks: None.


image-input.c -- gets X,Y,R,G,B values for image. 

image-input.h -- header for image-input.c. 

problems: None.

memory leaks: 1 still available at exit.


image-output.c -- takes output from k-means, a 1D array and prints it as JPEG. 

image-output.c -- header for a image-output. 

problems: Conditonal jump or move based off uninitalized value.

memory leaks: None.


ImageSegmentation.c -- Implements all other programs correctly. Handles user input. 

ImageSegmentation.h -- Header for image Segmentation. 


Makefile 


Readme.md 


ImageSegmentation.1 -- Man page for image segmentation program. 


