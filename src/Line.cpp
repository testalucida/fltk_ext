/*
 * Line.cpp
 *
 *  Created on: 07.04.2020
 *      Author: martin
 */

#include <fltk_ext/Line.h>

Line::Line( Point p1, Point p2 ) {
	//general form of the equation of a line: y = m*x + b
	//from the given points p1 and p2 we calculate m and b.
	//see https://www.arndt-bruenner.de/mathe/9/geradedurchzweipunkte.htm
	_m = (float)(p2.y - p1.y) / (float)(p2.x - p1.x);
	_b = p2.y - (float)(_m*p2.x);
}

bool Line::isPointOnLine( Point& p ) {
	return (p.y == _m*p.x + _b);
}
