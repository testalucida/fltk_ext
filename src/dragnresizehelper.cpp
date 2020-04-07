/*
 * dragnresizehelper.cpp
 *
 *  Created on: 03.04.2020
 *      Author: martin
 */

#include <fltk_ext/dragnresizehelper.h>

//+++++++++++++++++++++++++++++++++++++++++++++++++

void DragHelper::prepareDragging( int x, int y ) {
	_x = x;
	_y = y;
	_offset_x = x - Fl::event_x();    // save where user clicked for dragging
	_offset_y = y - Fl::event_y();
}

DragDelta& DragHelper::getDragDelta() {
	_dragDelta.new_x = _offset_x + Fl::event_x();
	_dragDelta.new_y = _offset_y + Fl::event_y();
	_dragDelta.delta_x = _dragDelta.new_x - _x;
	_dragDelta.delta_y = _dragDelta.new_y - _y;
	_x = _dragDelta.new_x;
	_y = _dragDelta.new_y;
	return _dragDelta;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++

void ResizeHelper::prepareResizing( Fl_Widget* w ) {
	_widget = w;
	_dragHelper.prepareDragging( w->x(), w->y() );
}

 DeltaXY ResizeHelper::resizeWidget() {
	DragDelta& dd = _dragHelper.getDragDelta();
	int x, w;
	int event_x = Fl::event_x();
	int event_y = Fl::event_y();
	getXW( dd, event_x, x, w );
	int y, h;
	getYH( dd, event_y, y, h );

	_widget->resize( x, y, w, h );
	return { dd.delta_x, dd.delta_y };
}

inline void ResizeHelper::getXW( const DragDelta& dd, int event_x, int& x, int& w ) {
	x = _widget->x();
	w = _widget->w();

	bool drag_right_side = false;
	bool enlarging_w = false;
	int x2 = x + w;
	if( dd.delta_x >= 0 ) { //dragging to the right (but not necessarily the right side)
		if( x2 == whichIsCloser( event_x, x, x2 ) ) {
			drag_right_side = true;
			enlarging_w = true;
		}
	} else { //dragging to the left
		if( x == whichIsCloser( event_x, x, x2 ) ) {
			enlarging_w = true;
		} else {
			drag_right_side = true;
		}
	}

	int delta_x = abs( dd.delta_x );
	if( drag_right_side ) {
		//dragging right side...
		if( enlarging_w ) {
			//...to the right -- width becomes wider
			w += dd.delta_x;
		} else {
			//...to the left -- width becomes smaller
			w -= delta_x;
		}
	} else {
		//dragging left side...
		if( enlarging_w ) {
			//...to the left - x becomes lesser, right side stable so w must increase
			x -= delta_x;
			w += delta_x;
		} else {
			//...to the right - x becomes greater, right side stable so w must decrease
			x += delta_x;
			w -= delta_x;
		}
	}
}

inline void ResizeHelper::getYH( const DragDelta& dd, int event_y, int& y, int& h ) {
	y = _widget->y();
	h = _widget->h();
	bool drag_bottom_side = false;
	bool enlarging_h = false;

	int y2 = y + h;
	if( dd.delta_y >= 0 ) { //dragging to the bottom (but not necessarily the bottom side)
		if( y2 == whichIsCloser( event_y, y, y2 ) ) {
			drag_bottom_side = true;
			enlarging_h = true;
		}
	} else { //dragging to the top
		if( y == whichIsCloser( event_y, y, y2 ) ) {
			enlarging_h = true;
		} else {
			drag_bottom_side = true;
		}
	}

	int delta_y = abs( dd.delta_y );
	if( drag_bottom_side ) {
		//dragging bottom side...
		if( enlarging_h ) {
			//...to the bottom -- height becomes higher
			h += dd.delta_y;
		} else {
			//...to the left -- width becomes smaller
			h -= delta_y;
		}
	} else {
		//dragging top side...
		if( enlarging_h ) {
			//...to the top - y becomes lesser, bottom side stable so h must increase
			y -= delta_y;
			h += delta_y;
		} else {
			//...to the bottom - y becomes greater, bottom side stable so h must decrease
			y += delta_y;
			h -= delta_y;
		}
	}
}

/**
 * Checks if x1 or x2 is nearer to check
 */
inline int ResizeHelper::whichIsCloser( int check, int a1, int a2 ) {
	int d1 = abs( check - a1 );
	int d2 = abs( check - a2 );
	return ( d1 < d2 ) ? a1 : a2;
}





