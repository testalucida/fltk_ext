/*
 * DragBox.cpp
 *
 *  Created on: 03.04.2020
 *      Author: martin
 */

#include <fltk_ext/DragBox.h>

#include <FL/Fl_Group.H>
#include <FL/fl_draw.H>

DragBox::DragBox(int x, int y, int w, int h, const char *lbl) :
		Fl_Box(x, y, w, h, lbl) {
	box(FL_FLAT_BOX);
	color( FL_LIGHT2 );
}

DragBox::~DragBox() {
	fprintf( stderr, "deleting DragBox\n" );
}

void DragBox::registerSelectionCallback(SelectionCallback cb, void *userdata) {
	_selectionCallback = cb;
	_selcb_userdata = userdata;
}

void DragBox::registerMoveCallback(MoveCallback cb, void *userdata) {
	_moveCallback = cb;
	_movecb_userdata = userdata;
}

void DragBox::toggleSelection(bool selected) {
	_selected = selected;
	_selectionChanged = true;
	redraw();
	_selectionChanged = false;
}

bool DragBox::isSelected() const {
	return _selected;
}

void DragBox::move(int delta_x, int delta_y) {
	//fprintf( stderr, "moving %d, %d\n", delta_x, delta_y );
	position(x() + delta_x, y() + delta_y);
}

void DragBox::draw_custom() {
	Fl_Color memo = fl_color();
	fl_color(FL_DARK3);
	//todo: needs clipping
	fl_draw( "your", x() + 3, y() + 15 );
	fl_draw( "drawing", x() + 3, y() + 30 );
	fl_draw( "code", x() + 3, y() + 45 );
	fl_draw( "here", x() + 3, y() + 60 );
	fl_color( memo );
}

void DragBox::draw() {
	draw_box();
	int xx = this->x();
	int yy = this->y();
	int ww = this->w();
	int hh = this->h();

	if( !_selected ) {
		//make selection squares invisible
		Fl_Color colr = box() == FL_NO_BOX ? parent()->color() : color();
		drawSelectionSquares( xx, yy, ww, hh, colr );
	}

	draw_custom(); //call user's drawing code

	if( _selected ) {
		drawSelectionSquares(xx, yy, ww, hh, FL_YELLOW );
	}
}

void DragBox::drawSelectionSquares( int x, int y, int w, int h, Fl_Color color ) {
	int len = _selectionsquare_len;

	//small square top left:
	fl_rectf( x, y, len, len, color );
	//small square top right:
	fl_rectf( x + w - len, y, len, len, color );
	//small square bottom right:
	fl_rectf( x + w - len, y + h - len, len, len, color );
	//small square bottom left:
	fl_rectf( x, y + h - len, len, len, color );
}

int DragBox::handle(int e) {
	//static int offset[2] = { 0, 0 };
	switch (e) {
	case FL_PUSH: {
		fprintf( stderr, "DragBox::handle( PUSH )\n" );
		if( Fl::event_button() == FL_RIGHT_MOUSE ) {
			if( _selected ) {
				//let inherited classes do their own work:
				onRightMouse();
			}
			return 1;
		}
		//prepare resizing if PUSH event occured within the resizing area,
		//else prepare dragging:
		Fl_Cursor crsr = getDragOrResizeCursor(Fl::event_x(), Fl::event_y());
		fl_cursor(crsr);

		if (crsr == FL_CURSOR_MOVE) {
			_dragHelper.prepareDragging(x(), y());
			fprintf( stderr, "prepare drag\n");
			_draggingPrepared = true;
		} else {
			_resizeHelper.prepareResizing(this);
			fprintf( stderr, "prepare resize\n");
		}

		//do selection callback to unselect other selected symbols
		bool draw = false;
		if (!_selected) {
			_selected = true;
			draw = true;
			bool shift_pressed = Fl::event_key(FL_Shift_L);
			if (_selectionCallback) {
				(_selectionCallback)(this, shift_pressed, _selcb_userdata);
			}
		}
		if (draw) {
			redraw();
		}
		return 1;
	}
	case FL_RELEASE:
		fl_cursor(FL_CURSOR_DEFAULT);
		_draggingPrepared = false;
		return 1;
	case FL_DRAG: {
		//fprintf( stderr, "MyBox::handle(FL_DRAG\n)" );
		if (_draggingPrepared) {
			DragDelta &dd = _dragHelper.getDragDelta();
			move(dd.delta_x, dd.delta_y);

			if (_moveCallback) {
				(_moveCallback)(this, dd.delta_x, dd.delta_y, _movecb_userdata);
			}
			onMovedOrResized( false, dd.delta_x, dd.delta_y );
		} else {
			//resize
			DeltaXY delta = _resizeHelper.resizeWidget();
			onMovedOrResized( true, delta.delta_x, delta.delta_y );
		}
		parent()->redraw();
		return (1);
	}
	default:
		return Fl_Box::handle(e);
	}
}

Fl_Cursor DragBox::getDragOrResizeCursor(int x, int y) {
	int sq = isInSelectionSquare(x, y);
	if (sq == 1 || sq == 3) {
		return FL_CURSOR_NW;
	}
	if (sq > 0) {
		return FL_CURSOR_NE;
	}

	return FL_CURSOR_MOVE;
}

int DragBox::isInSelectionSquare(int x, int y) {
	int X = this->x();
	int W = this->w();
	int Y = this->y();
	int H = this->h();

	if (x < (X + _selectionsquare_len)) {
		//maybe one of the left hand squares
		if (y < (Y + _selectionsquare_len)) {
			//top left square
			return 1;
		} else if (y > (Y + H - _selectionsquare_len)) {
			//bottom left square
			return 4;
		}
	} else {
		if (x > (X + W - _selectionsquare_len)) {
			//maybe one of the right hand squares
			if (y < (Y + _selectionsquare_len)) {
				//top right square
				return 2;
			}
			if (y > (Y + H - _selectionsquare_len)) {
				//bottom right square
				return 3;
			}
		}
	}

	return 0;
}

void DragBox::getCenter(int &x, int &y) const {
	x = (2 * this->x() + this->w()) / 2;
	y = (2 * this->y() + this->h()) / 2;
}




