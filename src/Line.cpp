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

bool Line::isPointInSegment( const Point& p ) const {
	return isPointInSegment( p.x, p.y );
}

bool Line::isPointInSegment( int x, int y ) const {
	if( _isVertical ) {
		int ymax = max( _y1, _y2 );
		int ymin = min( _y1, _y2 );
		return ( x == _x1 && y <= ymax && y >= ymin );
	} else {
		if( x > _x1 && x > _x2 ) return false;
		if( x < _x1 && x < _x2 ) return false;
		if( y > _y1 && y > _y2 ) return false;
		if( y < _y1 && y < _y2 ) return false;
		return (y == _m*x + _b);
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
	Intersection intersect;
	LinesRelation rel = getLinesRelation( line );
	if( rel.parallel || rel.collinear ) {
		intersect.intersects = false;
		intersect.linesParallel = rel.parallel;
		intersect.linesCollinear = rel.collinear;
		return intersect;
	}

	if( _isVertical || line.isVertical() ) {
		return getIntersectionVertical( line );
	}

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
	intersect.x = round( ( line.b() - this->_b ) / ( this->_m - line.m() ) );
	// Now having x, we can easily compute y:
	intersect.y = this->_m * intersect.x + this->_b;

	Point X = {intersect.x, intersect.y};
	//Now check, if the intersection is within the defined segments:
	if( !isLinePointInSegment( X ) ||  !line.isLinePointInSegment( X ) ) {
		intersect.withinSegments = false;
	} else {
		intersect.withinSegments = true;
	}

	return intersect;
}

inline Intersection Line::getIntersectionVertical( const Line& line ) const {
	Intersection intersect;
	const Line* vline = _isVertical ? this : &line;
	const Line* other = ( vline == this ) ? &line : this;

	intersect.x = vline->x1();
	intersect.y = other->m() * intersect.x + other->b();

	Point X = {intersect.x, intersect.y};
	//Now check, if the intersection is within the defined segments:
	if( !isLinePointInSegment( X ) ||  !line.isLinePointInSegment( X ) ) {
		intersect.withinSegments = false;
	} else {
		intersect.withinSegments = true;
	}

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

LinesRelation Line::getLinesRelation(const Line& line ) const {
	LinesRelation rel;
	if( _isVertical && line.isVertical() ) {
		//either m and b is 0
		rel.intersecting = false;
		if( _x1 == line.x1() ) {
			rel.collinear = true;
 		} else {
 			rel.parallel = true;
 		}
		return rel;
	}
	if( _m == line.m() && !(_m == 0 && line.m() == 0 ) ) {
		//lines are parallel, maybe even collinear
		rel.intersecting = false;
		if( _b == line.b() ) {
			rel.collinear = true;
		} else {
			rel.parallel = true;
		}
		return rel;
	}
	//still here ==> intersecting lines
	return rel;
}

bool Line::isPointNearby(int x, int y, int radius) const {
	//distance of point from line:
	// see https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
	//If the line passes through two points P1=(x1,y1) and P2=(x2,y2)
	//then the distance of (x0,y0) from the line is:

	//int dist = abs( (y2 - y1)*x0 - (x2 - x1)*y0 + x2*y1 - y2*x1  ) /
	// 		     sqrt( (y2 - y1) * (y2 - y1) + (x2 - x1) * (x2 - x1) );
}

















