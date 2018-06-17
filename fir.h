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

#ifndef _FIR_H_
#define _FIR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

enum {
	RECTANGULAR_WINDOW_TYPE,
	BARLETT_WINDOW_TYPE,
	HANNING_WINDOW_TYPE,
	HAMMING_WINDOW_TYPE,
	BLACKMAN_WINDOW_TYPE,
	NB_WINDOW_TYPE
};

extern struct WindowType {
	const char* str;
	int value;
} WINDOW_TYPES[];

void fir_gen( const int window_type,
	      int length_window,
	      const unsigned int sampling_rate,
	      const unsigned int cutoff_frequency,
	      double* coef,
	      double* window,
	      double* weight );

#ifdef __cplusplus
}
#endif

#endif /* !_FIR_H_ */
