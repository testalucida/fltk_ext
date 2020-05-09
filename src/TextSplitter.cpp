/*
 * TextSplitter.cpp
 *
 *  Created on: 09.05.2020
 *      Author: martin
 */

#include <fltk_ext/TextSplitter.h>
#include <fltk_ext/TextMeasure.h>
#include <cstring>

using namespace std;

TextSplitter::TextSplitter( Fl_Font font, Fl_Fontsize size ) :
_font(font), _fontsize(size)
{
}

TextSplitter::~TextSplitter() {
}

string& TextSplitter::split( const char *txt, int w, int h ) {
	init( txt );
	int sum_w = 0;
	string word;
	while( getNextWord( word ) ) {
		Size size = TextMeasure::inst().get_size( word.c_str(), _font, _fontsize );
		sum_w += size.w;
		if( sum_w >= w ) {
			_splitText += '\n';
			sum_w = 0;
		}
		_splitText += word;
		word.clear();
	}
	return _splitText;
}

inline void TextSplitter::init( const char* txt ) {
	_splitText.clear();
	_raw = txt;
	_current = txt;
	_text_end = txt + strlen( txt );
}

inline bool TextSplitter::getNextWord( std::string& word) {
	for( ; _current < _text_end; _current++ ) {
		word += *_current;
		if( isLimiter( *_current ) ) {
			++_current;
			return true;
		}
	}
	return( word.size() > 0 );
}

inline bool TextSplitter::isLimiter( char c ) const {
	return (c == ' ' or c == '\n' or c == '.' or c == ':' or
			c == ',' or c == ';' or c == '_' or
			c == '-' or c == '/' or c == '\\' or
			c == '(' or c == ')' or
			c == '[' or c == ']' or
			c == '{' or c == '}' );
}


