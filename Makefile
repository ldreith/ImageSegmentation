all: k-means
k-means: k-means.c k-means.h image-output.h
	gccx -o -lm -ljepg image_segmentation image_segmentation.c image-input.c image-output.c k-means.c
clean:
	rm k-means
