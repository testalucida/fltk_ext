/*
 * FlxIdent.h
 *
 *  Created on: 23.04.2020
 *      Author: martin
 */

#ifndef FLTK_EXT_FLXIDENT_H_
#define FLTK_EXT_FLXIDENT_H_

class FlxIdent {
public:
	FlxIdent();
	virtual ~FlxIdent();
	int getId();
	void setId( int id );
	void* getIdentData();
	void setIdentData( void* ident_data );
private:
	int _id = -1;
	void* _ident_data = 0;
};

#endif /* FLTK_EXT_FLXIDENT_H_ */
