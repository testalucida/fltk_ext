/*
 * FlxDialog.cpp
 *
 *  Created on: 24.04.2020
 *      Author: martin
 */

#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <fltk_ext/FlxDialog.h>

FlxDialog::FlxDialog( int x, int y, int w, int h, const char* title )
: Fl_Double_Window( x, y, w, h, title ), FlxIdent()
{
	box( FL_FLAT_BOX );
	color( FL_LIGHT2 );

	int btn_h = 25;
	int btn_w = 70;
	int btn_x = this->w() - 2*btn_w - _spacing_x - _margin_x;
	int btn_y = this->h() - btn_h - _margin_y;
	_btnOk = new Fl_Return_Button( btn_x, btn_y, btn_w, btn_h, "OK" );
	_btnOk->callback( onOkCancel_static, this );
	setButtonLook( _btnOk );
	btn_x += btn_w + _spacing_x;
	_btnCancel = new Fl_Button( btn_x, btn_y, btn_w, btn_h, "Cancel" );
	setButtonLook( _btnCancel );
	_btnCancel->callback( onOkCancel_static, this );
}

FlxDialog::~FlxDialog() {
	// TODO Auto-generated destructor stub
}

void FlxDialog::setButtonLook( Fl_Button *btn ) {
	btn->box( FL_THIN_UP_BOX );
	btn->down_box( FL_THIN_DOWN_BOX );
	btn->color( (Fl_Color) 53 );
	btn->down_color( FL_LIGHT1 );
	btn->clear_visible_focus();
}

FlxRect& FlxDialog::getClientArea() const {
	_clientArea.x = _margin_x;
	_clientArea.y = _margin_y;
	_clientArea.w = this->w() - 2*_margin_x;
	_clientArea.h = this->h() - 2*_margin_y - _btnOk->h() - _spacing_y;
	return _clientArea;
}

void FlxDialog::printClientAreaMeasures() const {
	FlxRect& rect = getClientArea();
	fprintf( stderr, "FlxDialog::printClientArea(): x=%d, y=%d, w=%d, h=%d",
			         rect.x, rect.y, rect.w, rect.h );
}

Fl_Group* FlxDialog::createClientAreaGroup( Fl_Boxtype boxtype,
		                                    Fl_Color color )
{
	FlxRect& rect = getClientArea();
	Fl_Group* grp = new Fl_Group( rect.x, rect.y, rect.w, rect.h );
	grp->box( boxtype );
	grp->color( color );
	add( grp );
	return grp;
}


int FlxDialog::show( bool modally ) {
	if( modally ) {
		Fl_Double_Window::set_modal();
		//Note: dialog will be placed int0 the middle of the
		//application disregarding given x and y position
	} else {
		Fl_Double_Window::set_non_modal();
	}

	Fl_Widget* w = getFocusWidget();
	w ? w->take_focus() : 0;

	Fl_Double_Window::show();

	while( shown() ) {
		Fl::wait();
	}
	return _ok ? 1 : 0;
}

void FlxDialog::onOkCancel_static( Fl_Widget *w, void *data ) {
	FlxDialog* pThis = (FlxDialog*)data;
	pThis->onOkCancel( (Fl_Button*)w );
}

void FlxDialog::onOkCancel( Fl_Button *btn ) {
	if( btn == _btnOk  ) {
		_ok = true;
		hide();
	} else {
		_ok = false;
		hide();
	}
}
