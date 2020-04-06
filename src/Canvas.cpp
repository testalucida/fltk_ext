/*
 * Canvas.cpp
 *
 *  Created on: 03.04.2020
 *      Author: martin
 */

#include <fltk_ext/Canvas.h>

#include <typeinfo>

using namespace std;

Canvas::Canvas(int x, int y, int w, int h) :
		Fl_Scroll(x, y, w, h)
{
	box(FL_FLAT_BOX);
	color(FL_WHITE);
}

DragBox* Canvas::tryDragBoxCast( Fl_Widget* w ) const {
	DragBox* dragbox = dynamic_cast<DragBox*>( w );
	return dragbox;
}

void Canvas::onDragBoxSelected_static(
		DragBox* box, bool shift_pressed, void* data )
{
	Canvas* pThis = (Canvas*) data;
	pThis->onDragBoxSelected( box, shift_pressed );
}

void Canvas::onDragBoxSelected( DragBox* box, bool shift_pressed ) {
	if( !shift_pressed ) {
		unselectAllDragBoxes();
		box->toggleSelection( true );
	}
}

void Canvas::unselectAllDragBoxes() {
	for (int i = 0, imax = children(); i < imax; i++) {
		DragBox* dragbox;
		if( (dragbox = tryDragBoxCast( child( i ) ) ) ) {
			dragbox->toggleSelection(false);
		}
	}
}

void Canvas::add( DragBox* dragbox ) {
	Fl_Scroll::add( dragbox );
	dragbox->registerSelectionCallback( onDragBoxSelected_static, this );
	dragbox->registerMoveCallback( onChildMoved_static, this );
}

void Canvas::end() {
	Fl_Scroll::end();
	for (int i = 0, imax = children(); i < imax; i++) {
		Fl_Widget* w = child( i );
		DragBox* dragbox;
		if( (dragbox = tryDragBoxCast( w )) ) {
			dragbox->registerSelectionCallback( onDragBoxSelected_static, this );
			dragbox->registerMoveCallback(onChildMoved_static, this);
		}
	}
}

/**
 * Move all selected dragboxes synchronously to box
 */
void Canvas::onChildMoved(DragBox *box, int delta_x, int delta_y) {
	for (int i = 0, imax = children(); i < imax; i++) {
		DragBox* ch;
		if( (ch = tryDragBoxCast( child(i)) ) ) {
			if (ch != box && ch->isSelected()) {
				ch->move(delta_x, delta_y);
			}
		}
	}
}

int Canvas::handle(int evt) {
	switch (evt) {
	case FL_PUSH: {
		fprintf( stderr, "Canvas::handle( PUSH )\n" );
		int rc;
		Fl_Widget *w = Fl::belowmouse();
		if (w == this) {
			//clicking on canvas results in unselecting all selected symbols:
			unselectAllDragBoxes();

			//prepare resizing
			if (!_selectionBox) {
				_selectionBox = new SelectionBox(Fl::event_x(), Fl::event_y(), 1, 1);
				Fl_Scroll::add(_selectionBox);
			}

			_resizeHelper.prepareResizing(_selectionBox);

			rc = 1;
		} else {
			rc = Fl_Scroll::handle(evt);
		}

		if( _push_cb ) {
			(_push_cb)( w, _push_cb_userdata );
		}

		return rc;
	}
	case FL_RELEASE: {
		if (_selectionBox) {
			//dragging finished, select children enclosed by _selectionBox
			int sel_x = _selectionBox->x();
			int sel_y = _selectionBox->y();
			int sel_xmax = sel_x + _selectionBox->w();
			int sel_ymax = sel_y + _selectionBox->h();
			for (int i = 0, imax = children(); i < imax; i++) {
				DragBox* dragbox;
				if( (dragbox = tryDragBoxCast( child( i )) ) ) {
					int db_x = dragbox->x();
					int db_y = dragbox->y();
					int db_xmax = db_x + dragbox->w();
					int db_ymax = db_y + dragbox->h();
					if (db_x >= sel_x && db_y >= sel_y) {
						if( db_xmax <= sel_xmax && db_ymax <= sel_ymax ) {
							dragbox->toggleSelection( true );
						}
					}
				}
			}
			remove(_selectionBox);
			_selectionBox = NULL;
			redraw();
		}

		return 1;
	}
	case FL_DRAG: {

		_resizeHelper.resizeWidget();

		redraw();

		return 1;
	}
	default:
		break;
	} //swithc

	return Fl_Scroll::handle(evt);
}

vector<DragBox*> Canvas::getSelectedDragBoxes() const {
	vector<DragBox*> v;
	for( int i = 0, imax = children(); i < imax; i++ ) {
		DragBox* dragbox = tryDragBoxCast( child( i ) );
		if( dragbox && dragbox->isSelected() ) {
			v.push_back( dragbox );
		}
	}
	return v;
}
























