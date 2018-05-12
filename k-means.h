#ifndef k_means
#define k_means
void normalize_vals(double  *pixel_data, int size, int * min_vals, int * max_vals);
void print_pixel(double  *pixel_data, int size);
void print_pixel(double * arr, int size);
double normalize_val(double value, double max_vals, double min_vals);
double * place_k(int * min_vals, int * max_vals);
double get_distance(double * centroid_location, double * pixel_data);
#endif
