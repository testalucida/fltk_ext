/*
 * FlxStatus.h
 *
 *  Created on: 28.04.2020
 *      Author: martin
 */

#include <FL/Fl_Box.H>

#ifndef FLTK_EXT_FLXSTATUS_H_
#define FLTK_EXT_FLXSTATUS_H_

#include <string>

class FlxStatusBox : public Fl_Box {
public:
	FlxStatusBox( int x, int y, int w, int h );
	/** Set status text and time to elapse until reset.
	 * The passed text will be copied. */
	void setStatusText( const char* text, float time_to_reset = 3.0 );
	void setStatusText( const std::string& text, float time_to_reset = 3.0 );
	void setStatusTextV( const char* fmt... );
	virtual ~FlxStatusBox();
private:
	static void resetStatus_static( void* );
	void resetStatus();
private:
	std::string _temp;
};

#endif /* FLTK_EXT_FLXSTATUS_H_ */
