#ifndef k_means
#define k_means
struct pixel{
int pixel_num;
double lowest_dist;
int centroid;
double * location;
};
void free_all(struct pixel ** arr, int count);
struct pixel * add_pixel(double * location);
void normalize_vals(double  *pixel_data, int size, int * min_vals, int * max_vals);
void print_pixel(struct pixel * p);
double normalize_val(double value, double max_vals, double min_vals);
double * place_k(int * min_vals, int * max_vals);
double get_distance(double * centroid_location, double * pixel_data);
#endif
