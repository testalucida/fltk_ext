/*
 * FlxDialog.h
 *
 *  Created on: 24.04.2020
 *      Author: martin
 */

#ifndef FLTK_EXT_FLXDIALOG_H_
#define FLTK_EXT_FLXDIALOG_H_

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <fltk_ext/FlxIdent.h>
#include <fltk_ext/FlxRect.h>

class Fl_Button;
class Fl_Return_Button;
class Fl_Group;

class FlxDialog : public Fl_Double_Window, public FlxIdent {
public:
	FlxDialog( int x, int y, int w, int h, const char* title = NULL );
	virtual ~FlxDialog();
	/** Provides position and size of the usable area in this FlxDialog.*/
	FlxRect& getClientArea() const;
	/** For test purposes: print position and size of the
	 * client area of this dialog. */
	void printClientAreaMeasures() const;
	/** creates adds and returns a Fl_Group positioned and sized according the
	 * client area's measures.  */
	Fl_Group* createClientAreaGroup( Fl_Boxtype boxtype, Fl_Color color );
	/** Shows this dialog. Returns 1 when the user hits OK else 0 */
	int show( bool modally );
protected:
	static void onOkCancel_static( Fl_Widget* w, void* data );
	void onOkCancel( Fl_Button* pBtn );
	/** override this method in order to set a custom boxtype color etc.
	 * Default is FL_THIN_UP_BOX, color 53 and visible focus turned off.*/
	virtual void setButtonLook( Fl_Button* btn );
	/** To be overridden by inherited classes.
	 *  Returns the widget to focus when show()ing this dialog. */
	virtual Fl_Widget* getFocusWidget() { return NULL; }
private:
	Fl_Return_Button* _btnOk = NULL;
	Fl_Button* _btnCancel = NULL;
	mutable FlxRect _clientArea;
	int _margin_x = 10;
	int _margin_y = 10;
	int _spacing_x = 5;
	int _spacing_y = 5;
	bool _ok = false;
};

#endif /* FLTK_EXT_FLXDIALOG_H_ */
