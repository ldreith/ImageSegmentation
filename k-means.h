#ifndef k_means
#define k_means
double normalize_vals(double value, double max_value, double min_value);
double * place_k(int * min_vals, int * max_vals);
double get_distance(double * centroid_location, double * pixel_data);
#endif
