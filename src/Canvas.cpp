/*
 * Canvas.cpp
 *
 *  Created on: 03.04.2020
 *      Author: martin
 */

#include <fltk_ext/Canvas.h>

Canvas::Canvas(int x, int y, int w, int h) :
		Fl_Group(x, y, w, h) {
	box(FL_FLAT_BOX);
	color(FL_WHITE);
}

void Canvas::unselectAllSymbols() {
	for (int i = 0, imax = children(); i < imax; i++) {
		Fl_Widget* w = child( i );
		if( _selectionBox && w == _selectionBox ) continue;
		DragBox *box = (DragBox*)w;
		box->toggleSelection(false);
	}
}

void Canvas::end() {
	Fl_Group::end();
	for (int i = 0, imax = children(); i < imax; i++) {
		Fl_Widget* w = child( i );
		if( _selectionBox && w == _selectionBox ) continue;
		DragBox* ch = (DragBox*)w;
		ch->registerMoveCallback(onChildMoved_static, this);
	}
}

void Canvas::onChildMoved(DragBox *box, int delta_x, int delta_y) {
	for (int i = 0, imax = children(); i < imax; i++) {
		DragBox *ch = (DragBox*) child(i);
		if (ch != box && ch->isSelected()) {
			ch->move(delta_x, delta_y);
		}
	}
}

int Canvas::handle(int evt) {
	switch (evt) {
	case FL_PUSH: {
		Fl_Widget *w = Fl::belowmouse();
		if (w == this) {
			//clicking on canvas results in unselecting all selected symbols:
			unselectAllSymbols();

			//prepare resizing
			if (!_selectionBox) {
				_selectionBox = new SelectionBox(Fl::event_x() - x(),
						Fl::event_y() - y(), 1, 1);
				add(_selectionBox);
			}

			_resizeHelper.prepareResizing(_selectionBox);

			return 1;
		} else {
			return Fl_Group::handle(evt);
		}
	}
	case FL_RELEASE: {
		if (_selectionBox) {
			//dragging finished, select children enclosed by _selectionBox
			int sel_x = _selectionBox->x();
			int sel_y = _selectionBox->y();
			int sel_xmax = sel_x + _selectionBox->w();
			int sel_ymax = sel_y + _selectionBox->h();
			for (int i = 0, imax = children(); i < imax; i++) {
				Fl_Widget *ch = child(i);
				if( ch == _selectionBox ) continue;
				int ch_x = ch->x();
				int ch_y = ch->y();
				int ch_xmax = ch_x + ch->w();
				int ch_ymax = ch_y + ch->h();
				if (ch_x >= sel_x && ch_y >= sel_y) {
					if (ch_xmax <= sel_xmax && ch_ymax <= sel_ymax) {
						((DragBox*) ch)->toggleSelection(true);
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

	return Fl_Group::handle(evt);
}
