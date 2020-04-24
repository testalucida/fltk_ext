/*
 * FlxIdent.cpp
 *
 *  Created on: 23.04.2020
 *      Author: martin
 */

#include <fltk_ext/FlxIdent.h>

FlxIdent::FlxIdent() {
}

FlxIdent::~FlxIdent() {
}

int FlxIdent::getId() {
	return _id;
}

void FlxIdent::setId( int id ) {
	_id = id;
}

void* FlxIdent::getIdentData() {
	return _ident_data;
}

void FlxIdent::setIdentData( void *ident_data ) {
	_ident_data = ident_data;
}
