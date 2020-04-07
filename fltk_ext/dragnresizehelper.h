/*
 * dragnresizehelper.h
 *
 *  Created on: 03.04.2020
 *      Author: martin
 */

#ifndef FLTK_EXT_DRAGNRESIZEHELPER_H_
#define FLTK_EXT_DRAGNRESIZEHELPER_H_

#include <FL/Fl_Widget.H>
#include <math.h>

struct Position {
	int x = 0;
	int y = 0;
};

//struct Rectangle {
//	int x = 0;
//	int y = 0;
//	int w = 0;
//	int h = 0;
//};

struct DragDelta {
	int new_x = 0;
	int new_y = 0;
	int delta_x = 0;
	int delta_y = 0;
};

struct DeltaXY {
	int delta_x = 0;
	int delta_y = 0;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++

class DragHelper {
public:
	DragHelper() {}
	/**
	 * Call this method after having received a PUSH event
	 * and before receiving the first DRAG event.
	 * x and y have to be the upper left corner of the Widget to be dragged.
	 */
	void prepareDragging( int x, int y );

	/**
	 * Call this for dragging purposes. (Opposite to resizing dragging means
	 * moving the widget as a whole according to the dragging amount
	 * in x and y direction)
	 * Gets the amount of dragging into x and y direction.
	 * Gets the new calculated top left corner of the widget to draw.
	 */
	DragDelta& getDragDelta();

private:
	int _x = 0;
	int _y = 0;
	int _offset_x = 0;
	int _offset_y = 0;
	DragDelta _dragDelta;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++

class ResizeHelper {
public:
	ResizeHelper() {}

	void prepareResizing( Fl_Widget* w );

	DeltaXY resizeWidget();

	void getDragDelta( int& x, int& y ) {
		x = _dragHelper.getDragDelta().delta_x;
		y = _dragHelper.getDragDelta().delta_y;
	}

private:
	inline void getXW( const DragDelta& dd, int event_x, int& x, int& w );
	inline void getYH( const DragDelta& dd, int event_y, int& y, int& h );

	/**
	 * Checks if x1 or x2 is nearer to check
	 */
	inline int whichIsCloser( int check, int a1, int a2 );

private:
	Fl_Widget* _widget = NULL;
	//Position _dragstart;
	DragHelper _dragHelper;
};



#endif /* FLTK_EXT_DRAGNRESIZEHELPER_H_ */
