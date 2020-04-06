/*
 * TextMeasure.cpp
 *
 *  Created on: 04.04.2020
 *      Author: martin
 */

#include <fltk_ext/TextMeasure.h>


#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>

#include <string>
#include <cmath>

TextMeasure* TextMeasure::_pThis = NULL;

TextMeasure::TextMeasure() {
	_len_teststring = strlen(_pTeststring);
}

TextMeasure& TextMeasure::inst() {
	if (!_pThis) {
		_pThis = new TextMeasure();
	}
	return *_pThis;
}

Size TextMeasure::get_size(char const *pTxt,
		                   Fl_Font font, Fl_Fontsize fontsize) const
{
	fl_font(font, fontsize);
	Size size;
	fl_measure(pTxt, size.w, size.h);
	return size;
}

Size TextMeasure::get_size(int chars,
						   Fl_Font font, Fl_Fontsize fontsize) const
{
	float f = chars / _len_teststring;
	Size teststring_size = get_size(_pTeststring, font, fontsize);
	int w = int(ceil(f) * teststring_size.w);
	Size sz {w, teststring_size.h};
	return sz;
}
