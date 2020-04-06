/*
 * TextMeasure.h
 *
 *  Created on: 04.04.2020
 *      Author: martin
 */

#ifndef FLTK_EXT_TEXTMEASURE_H_
#define FLTK_EXT_TEXTMEASURE_H_


#include <FL/Enumerations.H>

struct Size {
	int w = 0;
	int h = 0;
};

class TextMeasure {
public:
	~TextMeasure() {}
	static TextMeasure& inst();
	Size get_size(char const *pTxt, Fl_Font, Fl_Fontsize) const;
	Size get_size(int chars, Fl_Font, Fl_Fontsize) const;
private:
	TextMeasure();
	const char* _pTeststring = "wegfeiaulm";
	int _len_teststring = 0;
	static TextMeasure* _pThis;
};


#endif /* FLTK_EXT_TEXTMEASURE_H_ */
