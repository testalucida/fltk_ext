/*
 * FlxCheckButton.h
 *
 *  Created on: 23.04.2020
 *      Author: martin
 */

#ifndef FLXCHECKBUTTON_H_
#define FLXCHECKBUTTON_H_

#include <fltk_ext/FlxIdent.h>
#include <FL/Fl_Check_Button.H>

class FlxCheckButton : public Fl_Check_Button, public FlxIdent {
public:
	FlxCheckButton( int x, int y, int w, int h, const char* label = NULL );
	virtual ~FlxCheckButton();
};

#endif /* FLXCHECKBUTTON_H_ */
