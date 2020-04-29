/*
 * FlxButton.cpp
 *
 *  Created on: 29.04.2020
 *      Author: martin
 */

#include <fltk_ext/FlxButton.h>

FlxButton::FlxButton( int x, int y, int w, int h, const char* label )
: Fl_Button( x, y, w, h, label ), FlxIdent()
{
}

FlxButton::~FlxButton() {
	// TODO Auto-generated destructor stub
}

