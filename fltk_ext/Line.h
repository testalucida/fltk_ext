/*
 * Line.h
 *
 *  Created on: 07.04.2020
 *      Author: martin
 */

#ifndef FLTK_EXT_LINE_H_
#define FLTK_EXT_LINE_H_

struct Point {
	int x = 0;
	int y = 0;
};

class Line {
public:
	Line( Point p1, Point p2 );

	bool isPointOnLine( Point& p );

private:
	float _m = 0;
	float _b = 0;
};



#endif /* FLTK_EXT_LINE_H_ */
