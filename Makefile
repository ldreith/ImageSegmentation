all: k-means
k-means: k-means.c k-means.h
	gccx k-means.c -o k-means -lm
clean:
	rm k-means
