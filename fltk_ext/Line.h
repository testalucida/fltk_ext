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


struct Intersection : public Point {
	bool intersects = false;
};

class Line {
public:
	Line( Point p1, Point p2 );
	Line( int x1, int y1, int x2, int y2 );

	/**
	 * vertical lines a specific because they can't be
	 * expressed by the general line equation y = m*x + b
	 */
	bool isVertical() const { return _isVertical; }

	/**
	 * checks if p is within the line segment defined
	 * by the points used for creating this line.
	 */
	bool isPointInSegment( Point& ) const;

	/**
	 * Checks if the passed Point which is part of
	 * this line, is located within the segment defined
	 * by the points used for creating it.
	 */
	bool isLinePointInSegment( Point& ) const;

	/**
	 * checks if p is on the line defined
	 * by the points used for creating this line.
	 */
	bool isPointOnLine( Point& p ) const;

	/**
	 * checks if the given line segment (!) intersects
	 * with this line segment and if so returns the
	 * intersection point.
	 */
	Intersection getIntersection( const Line& ) const;

	/** gets y value to a given x value.
	 * It is not guaranteed that x/y is located within
	 * the segment defined by the points used to create
	 * this line instance.
	 * Return false if this is a vertical line so that
	 * an y value cannot be determined unambiguously.
	 */
	bool getY( int x, int& y ) const;

	inline float m() const { return _m; }
	inline float b() const { return _b; }
	inline int x1() const { return _x1; }
	inline int x2() const { return _x2; }
	inline int y1() const { return _y1; }
	inline int y2() const { return _y2; }

private:
	inline void computeLine();
	inline int max( int a, int b ) const;
	inline int min( int a, int b ) const;
	inline Intersection getIntersectionVertical( const Line& ) const;

private:
	int _x1, _y1, _x2, _y2;
	float _m = 0;
	float _b = 0;
	bool _isVertical = false;
};



#endif /* FLTK_EXT_LINE_H_ */
