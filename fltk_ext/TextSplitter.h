/*
 * TextSplitter.h
 *
 *  Created on: 09.05.2020
 *      Author: martin
 */

#ifndef FLTK_EXT_TEXTSPLITTER_H_
#define FLTK_EXT_TEXTSPLITTER_H_

#include <FL/Enumerations.H>
#include <string>
#include <vector>

class TextSplitter {
public:
	TextSplitter( Fl_Font, Fl_Fontsize );
	virtual ~TextSplitter();
	std::string& split( const char* txt, int w, int h );
private:
	inline void init( const char* txt );
	inline bool getNextWord( std::string& );
	inline bool isLimiter( char c ) const;
	//inline void deleteWords();
private:
	Fl_Font _font;
	Fl_Fontsize _fontsize;
	std::string _splitText; //the string to return
	std::string _raw;
	const char* _current = NULL;
	const char* _text_end = NULL;
};

#endif /* FLTK_EXT_TEXTSPLITTER_H_ */
