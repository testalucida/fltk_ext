/*
 * FlxStatus.cpp
 *
 *  Created on: 28.04.2020
 *      Author: martin
 */

#include <fltk_ext/FlxStatusBox.h>
#include <FL/Fl.H>
#include <cstdarg>

using namespace std;

FlxStatusBox::FlxStatusBox( int x, int y, int w, int h )
: Fl_Box( x, y, w, h )
{
	// TODO Auto-generated constructor stub
}

FlxStatusBox::~FlxStatusBox() {
}

void FlxStatusBox::setStatusTextV( const char* fmt... ) {
	va_list args;
	va_start( args, fmt );
	_temp.clear();

	while( *fmt != 0x00 ) {
		if( *fmt == 'c' ) {
			int c = va_arg( args, int );
			_temp.append( 1, (char)c );
		} else if( *fmt == 's' ) {
			const char* cs = va_arg( args, const char* );
			_temp.append( cs );
		} else if( *fmt == 'd' ) {
			int i = va_arg( args, int );
			_temp.append( to_string( i ) );
		} else if( *fmt == 'f' ) {
			double d = va_arg( args, double );
			_temp.append( to_string( d ) );
		}
		++fmt;

	}
	va_end( args );
	setStatusText( _temp );
}

void FlxStatusBox::setStatusText( const std::string& text, float time_to_reset ) {
	setStatusText( text.c_str(), time_to_reset );
}

void FlxStatusBox::setStatusText( const char *text, float time_to_reset ) {
	Fl::remove_timeout( resetStatus_static, this );
	copy_label( text );
	redraw();
	Fl::check();
	Fl::add_timeout( time_to_reset, resetStatus_static, this );
}

void FlxStatusBox::resetStatus() {
	label( "" );
	Fl::remove_timeout( resetStatus_static, this );
}

void FlxStatusBox::resetStatus_static( void* data ) {
	FlxStatusBox* pThis = (FlxStatusBox*)data;
	pThis->resetStatus();
}
