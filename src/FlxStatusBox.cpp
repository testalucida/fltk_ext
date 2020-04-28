/*
 * FlxStatus.cpp
 *
 *  Created on: 28.04.2020
 *      Author: martin
 */

#include <fltk_ext/FlxStatusBox.h>
#include <FL/Fl.H>

FlxStatusBox::FlxStatusBox( int x, int y, int w, int h )
: Fl_Box( x, y, w, h )
{
	// TODO Auto-generated constructor stub
}

FlxStatusBox::~FlxStatusBox() {
	// TODO Auto-generated destructor stub
}

void FlxStatusBox::setStatusText( const char *text, float time_to_reset ) {
	copy_label( text );
	Fl::add_timeout( time_to_reset, resetStatus_static, this );
}

void FlxStatusBox::resetStatus() {
	label( "" );
}

void FlxStatusBox::resetStatus_static( void* data ) {
	FlxStatusBox* pThis = (FlxStatusBox*)data;
	pThis->resetStatus();
}
