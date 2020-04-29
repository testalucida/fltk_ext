/*
 * FlxButton.h
 *
 *  Created on: 29.04.2020
 *      Author: martin
 */

#ifndef FLTK_EXT_FLXBUTTON_H_
#define FLTK_EXT_FLXBUTTON_H_

#include <fltk_ext/FlxIdent.h>
#include <FL/Fl_Button.H>

class FlxButton: public Fl_Button, public FlxIdent {
public:
	FlxButton( int x, int y, int w, int h, const char* lbl = NULL);
	virtual ~FlxButton();
};

#endif /* FLTK_EXT_FLXBUTTON_H_ */
