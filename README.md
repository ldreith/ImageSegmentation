# Image Segmentation Using K-Means
Using K-Means to segment an input image by RGB value.

# Contributors
- Lars Dreith
- David Gold
- Jiachen Liu
- Leo Schumann

We have adhered to the honor code on this assignment.
Team.

Parts:

K-means abstract: David Gold and Jiachen Liu 


k-means.c -- all methods for k-means algorithm. Implemented by David Gold. Pseudo code for get_diff and update_centroids from Jiachen Liu. Ways of implementing discussed by Jiachen Liu and David Gold

k-means.h -- header for k-means algorithm. Implemented by David Gold. 

problems: Valgrind errors for conditonal jump or move based off ininitalized value for file name being passed in. 

memory leaks: None.


image-input.c -- gets X,Y,R,G,B values for image. Implemented by Lars Dreith

image-input.h -- header for image-input.c. Implemented by Lars Dreith

problems: None.

memory leaks: 1 still available at exit.


image-output.c -- takes output from k-means, a 1D array and prints it as JPEG. Implemented by Leo Schumann.

image-output.c -- header for a image-output. Implemented by Leo Schumann.

problems: Conditonal jump or move based off uninitalized value.

memory leaks: None.


ImageSegmentation.c -- Implements all other programs correctly. Handles user input. Implemented by Jiachen Liu

ImageSegmentation.h -- Header for image Segmentation. Impelmented by Jiachen Liu.


Makefile -- implemented by Jiachen Liu.


Readme.md -- implemented by David Gold.


ImageSegmentation.1 -- Man page for image segmentation program. Implemented by David Gold.


