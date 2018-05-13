#ifndef k_means
#define k_means
#define NUMPIX (max_vals[3]*max_vals[4])
struct pixel{
int pixel_num;
double lowest_dist;
int centroid;
double * location;
};
double get_diff(double * cent, double * old_cent);
double update_centroid_location(double **centroid, int centroid_num, int numpix);
void free_all(struct pixel ** arr, int count);
struct pixel * add_pixel(double * location);
void normalize_vals(double  *pixel_data, int size, int * min_vals, int * max_vals);
void print_pixel(struct pixel * p);
double normalize_val(double value, double max_vals, double min_vals);
double * place_k(int * min_vals, int * max_vals);
double get_distance(double * centroid_location, double * pixel_data);
#endif
