all: image_segmentation
image-output.o: image-output.c image-output.h
	gccx image-output.c -c 

k-means.o: k-means.c k-means.h
	gccx k-means.c -c

image-input.o: image-input.c image-input.h
	gccx image-input.c -c 


image_segmentation:  k-means.h image-output.h image-input.h image-input.c image-output.c k-means.c image_segmentation.c image-output.o k-means.o image-input.o
	gccx image_segmentation.c image-input.o image-output.o k-means.o -o image_segmentation -ljpeg -lm

clean:
	rm image_segmentation image-output.o image-input.o k-means.o
