# fir
Finite Impulse Response (fir) is very straightforward ANSI-C library to generate normalized coefficients of a FIR filter. 

First coefficients of a **window** is computed, then the sinc() **weight** function is apply on it, finally a normalization of coefficients is performed to generate output **coef**.

The library provides a single function : 
```
void fir_gen( const int window_type,
              int length_window,
              const unsigned int sampling_rate,
              const unsigned int cutoff_frequency,
              double* coef,
              double* window,
              double* weight );
```

- **window_type** can be choose among the following values : 
```
enum {
        RECTANGULAR_WINDOW_TYPE,
        BARLETT_WINDOW_TYPE,
        HANNING_WINDOW_TYPE,
        HAMMING_WINDOW_TYPE,
        BLACKMAN_WINDOW_TYPE,
        /* NB_WINDOW_TYPE */
};
```
- **coef** : contain normalized coefficients of the FIR filter
- **window** / **weight** : optional (can be set to NULL) : contain respectively computed coefficients of the window and weight sinc function.

Thanks to following website for their formulae : http://www.labbookpages.co.uk/audio/firWindowing.html
