/*
 * FlxRect.h
 *
 *  Created on: 24.04.2020
 *      Author: martin
 */

#ifndef FLTK_EXT_FLXRECT_H_
#define FLTK_EXT_FLXRECT_H_

#include <memory>

struct FlxRect {
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
};

typedef std::unique_ptr<FlxRect> FlxRectPtr;

#endif /* FLTK_EXT_FLXRECT_H_ */
