/*
 * Canvas.h
 *
 *  Created on: 03.04.2020
 *      Author: martin
 */

#ifndef CANVAS_H_
#define CANVAS_H_

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Enumerations.H>

#include "dragnresizehelper.h"
//#include "IChild.h"
#include "DragBox.h"


class SelectionBox : public Fl_Box {
public:
	SelectionBox( int x, int y, int w, int h ) : Fl_Box( x, y, w, h ) {
	}

	void draw() {
		if( _w > 0 ) {
			fl_rect( _x, _y, _w, _h, FL_WHITE );
		}
		int X = x() + 1;
		int Y = y() + 1;
		int W = w() - 2;
		int H = h() - 2;
		fl_rect( X, Y, W, H, FL_BLACK );
		_x = X;
		_y = Y;
		_w = W;
		_h = H;
	}

private:
	int _x = 0, _y = 0, _w = 0, _h = 0;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++

class Canvas : public Fl_Group {
public:
	Canvas( int x, int y, int w, int h );

	void unselectAllSymbols();

	void end();

	static void onChildMoved_static( DragBox* box, int delta_x, int delta_y, void* data ) {
		Canvas* pThis = (Canvas*)data;
		pThis->onChildMoved( box, delta_x, delta_y );
	}

	void onChildMoved( DragBox* box, int delta_x, int delta_y );

protected:
	int handle(int evt);

private:
	Position _start;
	Position _end;
	SelectionBox* _selectionBox = NULL;
	DragHelper _dragHelper;
	ResizeHelper _resizeHelper;
};


#endif /* CANVAS_H_ */
