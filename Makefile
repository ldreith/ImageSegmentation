all: k-means
k-means: k-means.c k-means.h
	gcc k-means.c -o k-means -g
clean:
	rm k-means
