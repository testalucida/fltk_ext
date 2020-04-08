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
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Enumerations.H>

#include <vector>

#include "dragnresizehelper.h"
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

typedef void (*PushCallback) ( Fl_Widget* pushed, void* userdata );

class Canvas : public Fl_Scroll {
public:
	Canvas( int x, int y, int w, int h );
	~Canvas() {}

	void unselectAllDragBoxes();

	void registerPushCallback( PushCallback push_cb, void* userdata ) {
		_push_cb = push_cb;
		_push_cb_userdata = userdata;
	}

	void add( DragBox* );

	void end();

	virtual void draw();

	std::vector<DragBox*> getSelectedDragBoxes() const;

protected:
	int handle(int evt);
	/** Override this for drawing before canvas draws itself */
	//virtual void draw_before() {}
	/** Override this for drawing after canvas drew itself */
	virtual void draw_then() {}

private:
	DragBox* tryDragBoxCast( Fl_Widget* ) const;

	static void onDragBoxSelected_static(
			DragBox* box, bool shift_pressed, void* data=NULL );

	void onDragBoxSelected( DragBox*, bool shift_pressed );

	static void onChildMoved_static( DragBox* box, int delta_x, int delta_y, void* data ) {
		Canvas* pThis = (Canvas*)data;
		pThis->onChildMoved( box, delta_x, delta_y );
	}

	void onChildMoved( DragBox* box, int delta_x, int delta_y );

private:
	Position _start;
	Position _end;
	SelectionBox* _selectionBox = NULL;
	DragHelper _dragHelper;
	ResizeHelper _resizeHelper;
	PushCallback _push_cb = NULL;
	void* _push_cb_userdata = NULL;
};


#endif /* CANVAS_H_ */
