/*
 * Line.cpp
 *
 *  Created on: 07.04.2020
 *      Author: martin
 */

#include <fltk_ext/Line.h>
#include <cmath>
#include <stdexcept>

using namespace std;

Line::Line( Point p1, Point p2 ) : Line( p1.x, p1.y, p2.x, p2.y ) {
}

Line::Line( int x1, int y1, int x2, int y2 ) :
		_x1(x1), _y1(y1), _x2(x2), _y2(y2)
{
	if( _x1 == _x2 ) {
		if( _y1 == _y2 ) {
			throw runtime_error( "Can't construct line - "
					             "two identical points are given." );
		}
		//vertical lines can't be expressed by y = mx + b;
		//a division by zero will result.
		_isVertical = true;
	} else {
		computeLine();
	}
}

bool Line::isPointOnLine( Point& p ) const {
	if( _isVertical ) {
		return (p.x == _x1);
	}
	return (p.y == _m*p.x + _b);
}

bool Line::isPointInSegment( Point& p ) const {
	if( _isVertical ) {
		int ymax = max( _y1, _y2 );
		int ymin = min( _y1, _y2 );
		return ( p.x == _x1 && p.y <= ymax && p.y >= ymin );
	} else {
		if( p.x > _x1 && p.x > _x2 ) return false;
		if( p.x < _x1 && p.x < _x2 ) return false;
		if( p.y > _y1 && p.y > _y2 ) return false;
		if( p.y < _y1 && p.y < _y2 ) return false;
		return (p.y == _m*p.x + _b);
	}
}

bool Line::isLinePointInSegment( Point& p ) const {
	if( _isVertical ) {
		return isPointInSegment( p );
	} else {
		if( p.x > _x1 && p.x > _x2 ) return false;
		if( p.x < _x1 && p.x < _x2 ) return false;
		if( p.y > _y1 && p.y > _y2 ) return false;
		if( p.y < _y1 && p.y < _y2 ) return false;

		return true;
	}
}

void Line::computeLine() {
	//general form of the equation of a line: y = m*x + b
	//from the given points p1 and p2 we calculate m and b.
	//see https://www.arndt-bruenner.de/mathe/9/geradedurchzweipunkte.htm
	_m = (float)( _y2 - _y1 ) / (float)( _x2 - _x1 );
	_b = _y2 - (float)(_m * _x2);
}

Intersection Line::getIntersection(const Line &line ) const {
	if( _isVertical || line.isVertical() )
		return getIntersectionVertical( line );

	Intersection intersect;
	// line equation: y = m*x + b
	// We have _m and _b of our line and of the given line.
	// The Intersection point we are searching for is contained
	// either by this line and the passed line, so we have:
	// y = this->_m * x + this->_b   and
	// y = line._m * x + line._b
	// We equate both equations:
	// this->_m * x + this->_b = line._m * x + line._b
	// and solve it for x:
	// this->_m*x - line._m*x = line._b - this->_b
	// x * (this->_m - line._m) = line._b - this->_b
	// x = (line._b - this->_b) / (this->_m - line._m)
	int x = round( ( line.b() - this->_b ) / ( this->_m - line.m() ) );
	// Now having x, we can easily compute y:
	int y = this->_m * x + this->_b;

	Point X = {x, y};
	//Now check, if the intersection is within the defined segments:
	if( !isLinePointInSegment( X ) ||  !line.isLinePointInSegment( X ) ) {
		intersect.intersects = false;
	} else {
		intersect.intersects = true;
		intersect.x = x;
		intersect.y = y;
	}

	return intersect;
}

inline Intersection Line::getIntersectionVertical( const Line& line ) const {
	Intersection intersect;
	if( m() == line.m() ) { //lines parallel
		intersect.intersects = false;
		return intersect;
	}
	const Line* vline = _isVertical ? this : &line;
	const Line* other = vline == this ? &line : this;

	intersect.x = vline->x1();
	intersect.intersects = ???
	return intersect;
}

inline int Line::max(int a, int b) const {
	return ( a > b ) ? a : b;
}

inline int Line::min(int a, int b) const {
	return ( a < b ) ? a : b;
}

bool Line::getY(int x, int &y) const {
	if( _isVertical ) {
		return false;
	}
	y = _m * x + _b;
	return true;
}



