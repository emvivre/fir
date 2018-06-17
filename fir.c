/*
  ===========================================================================

  Copyright (C) 2018 Emvivre

  This file is part of FIR_DESIGN.

  FIR_DESIGN is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FIR_DESIGN is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FIR_DESIGN.  If not, see <http://www.gnu.org/licenses/>.

  ===========================================================================
*/

/** formula comes from http://www.labbookpages.co.uk/audio/firWindowing.html */

#include "fir.h"
#include <math.h>

#ifndef NULL
#define NULL (void*)0
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct WindowType WINDOW_TYPES[] = {
	{ "rectangular", RECTANGULAR_WINDOW_TYPE },
	{ "barlett", BARLETT_WINDOW_TYPE },
	{ "hanning", HANNING_WINDOW_TYPE },
	{ "hamming", HAMMING_WINDOW_TYPE },
	{ "blackman", BLACKMAN_WINDOW_TYPE }
};


static const double PI = M_PI;

void fir_gen( const int window_type,
	      int length_window,
	      const unsigned int sampling_rate,
	      const unsigned int cutoff_frequency,
	      double* coef,
	      double* window,
	      double* weight )
{
	int i;
	double sum = 0;
	double ft = cutoff_frequency * 1. / sampling_rate;
	int off = (length_window % 2)==0 ? 0 : -1;
	switch( window_type ) {
	case RECTANGULAR_WINDOW_TYPE:
		for( i = 0; i < length_window; i++ ) {
		        coef[i] = 1;
		}
		break;
	case BARLETT_WINDOW_TYPE:
		for ( i = 0; i < length_window; i++ ) {
			coef[i] = 1 - (2 * fabs(i - length_window/2.))/length_window;
		}
		break;
	case HANNING_WINDOW_TYPE:
		for ( i = 0; i < length_window; i++ ) {
			coef[i] = 0.5 - 0.5 * cos( 2 * PI * i / length_window );
		}
		break;
	case HAMMING_WINDOW_TYPE:
		for ( i = 0; i < length_window; i++ ) {
			coef[i] = 0.54 - 0.46 * cos( 2 * PI * i / length_window );
		}
		break;
	case BLACKMAN_WINDOW_TYPE:
	default:
		for ( i = 0; i < length_window; i++ ) {
			coef[i] = 0.42 - 0.5 * cos(2 * PI * i / length_window) + 0.08 * cos( 4 * PI * i / length_window );
		}
	}

	if ( window != NULL ) {
		for ( i = 0; i < length_window; i++ ) {
			window[ i ] = coef[ i ];
		}
	}
	for ( i = 0; i < length_window; i++ ) {
		double w = 0;
		if ( i == (length_window+off)/2 ) {
			w = 2 * ft;
		} else {
			w = sin( 2 * PI * ft * (i - (length_window+off)/2.)) / (PI * (i - (length_window+off)/2.));
		}
	        if ( weight != NULL ) {
			weight[ i ] = w;
		}
		coef[ i ] *= w;
		sum += coef[ i ];
	}
	for ( i = 0; i < length_window; i++ ) {
		coef[ i ] /= sum;
	}
}
