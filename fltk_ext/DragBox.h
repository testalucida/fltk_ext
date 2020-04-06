/*
 * DragBox.h
 *
 *  Created on: 03.04.2020
 *      Author: martin
 */

#ifndef FLTK_EXT_DRAGBOX_H_
#define FLTK_EXT_DRAGBOX_H_

#include <fltk_ext/IChild.h>
#include <fltk_ext/dragnresizehelper.h>

#include <FL/Fl_Box.H>

class DragBox;
typedef void (*SelectionCallback)( DragBox*, bool shift_pressed, void* userdata );
typedef void (*MoveCallback)( DragBox*, int delta_x, int delta_y, void* userdata );

/**
 * Draggable, resizable and selectable Fl_Box.
 * Default box is FL_FLAT_BOX, color is FL_LIGHT2.
 * You are supposed to inherit YourDragBox from DragBox and
 * override method draw_custom().
 */
class DragBox : public Fl_Box /*, public IChild*/ {
public:
	DragBox( int x, int y, int w, int h, const char* lbl = NULL );
	virtual ~DragBox();
	virtual void registerSelectionCallback(SelectionCallback cb, void* userdata );
	virtual void registerMoveCallback( MoveCallback cb, void* userdata );
	virtual void toggleSelection( bool on );
	virtual bool isSelected() const;
	/** Called whenever a PUSH event occurs triggered
	 * by the right mouse button.
	 * Override this method to achieve custom behaviour.
	 */
	virtual void onRightMouse() { fprintf(stderr, "PUSH with right mouse\n"); }
	virtual void move( int delta_x, int delta_y );
	/** Overrides Fl_Box::draw() due to drawing selectionSquares when selected. */
	virtual void draw();
protected:
	/** Implement your own drawing code.
	 * It will be invoked whenever Fl_Box::draw() is called. */
	virtual void draw_custom();

	int handle( int );
	/**
	 * Draws 4 small yellow squares in the corners of this box.
	 * They are completely drawn within the box.
	 */
	void drawSelectionSquares( int x, int y, int w, int h, Fl_Color );
	Fl_Cursor getDragOrResizeCursor( int x, int y );
	/**
	 * checks if given x, y are in one of the 4 selection squares.
	 * returns 1 if x/y are in the top left square
	 * returns 2 if x/y are in the top right square and so on.
	 * returns 0 if x/y are not in one of the squares.
	 */
	int isInSelectionSquare( int x, int y );

private:
	bool _selected = false;
	bool _selectionChanged = false;
	int _selectionsquare_len = 10;
	SelectionCallback _selectionCallback = NULL;
	void* _selcb_userdata = NULL;
	DragHelper _dragHelper;
	ResizeHelper _resizeHelper;
	MoveCallback _moveCallback = NULL;
	void* _movecb_userdata = NULL;
	bool _draggingPrepared = false;
};


#endif /* FLTK_EXT_DRAGBOX_H_ */
