/*
 * Line.h
 *
 *  Created on: 07.04.2020
 *      Author: martin
 */

#ifndef FLTK_EXT_LINE_H_
#define FLTK_EXT_LINE_H_

#include <memory>

struct Point {
	int x = 0;
	int y = 0;
};

#define PI 3.14159265

/**
 * Relation of 2 Lines in a plane
 */
struct LinesRelation {
	bool intersecting = true;
	bool parallel = false;
	bool collinear = false;
};

struct Intersection : public Point {
	/**
	 * 2 lines always intersect somewhere except of
	 * them being parallel or collinear.
	 */
	bool intersects = true;

	/** lines intersect but the intersection
	 * is beyond of one of the segments.
	 */
	bool withinSegments = false;
	bool linesParallel = false;
	bool linesCollinear = false;
};

typedef std::unique_ptr<Intersection> IntersectionPtr;

class Line {
public:
	Line( Point p1, Point p2 );
	Line( int x1, int y1, int x2, int y2 );
	virtual ~Line() {}

	/**
	 * vertical lines are special because they can't be
	 * expressed by the general line equation y = m*x + b
	 */
	bool isVertical() const { return _isVertical; }

	/**
	 * checks if p is within the line segment defined
	 * by the points used for creating this line.
	 */
	bool isPointInSegment( const Point& ) const;
	bool isPointInSegment( int x, int y ) const;

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
	 * Gets the distance between a point given by
	 * x, y and this line.
	 */
	int getDistance( int x, int y ) const;

	/**
	 * checks position of this line related to the
	 * passed line.
	 */
	LinesRelation getLinesRelation( const Line& ) const;

	/**
	 * checks if the given line intersects
	 * with this line and if so returns the
	 * intersection point.
	 * Querying Intersection.withinSegment one may differentiate
	 * if the intersection is located within the segments
	 * of both of the involved lines.
	 * The segment of a line is defined by the points used to create them.
	 */
	IntersectionPtr getIntersection( const Line& ) const;

	/** gets the center of the line segment defined by
	 * the points used to construct this line.
	 */
	Point getCenter() const;

	/** gets y value to a given x value.
	 * It is not guaranteed that x/y is located within
	 * the segment defined by the points used to create
	 * this line instance.
	 * Return false if this is a vertical line so that
	 * an y value cannot be determined unambiguously.
	 */
	bool getY( int x, int& y ) const;
	/** returns the gradient of this line */
	inline float m() const { return _m; }
	/** return the y shift of this line */
	inline float b() const { return _b; }
	inline int x1() const { return _x1; }
	inline int x2() const { return _x2; }
	inline int y1() const { return _y1; }
	inline int y2() const { return _y2; }
	/** gets the angle of this line with the x axis */
	double getGradientAngle() const;

private:
	inline void computeLine();
	inline int max( int a, int b ) const;
	inline int min( int a, int b ) const;
	inline IntersectionPtr getIntersectionVertical( const Line& ) const;

private:
	int _x1, _y1, _x2, _y2;
	float _m = 0;
	float _b = 0;
	bool _isVertical = false;
};

typedef std::unique_ptr<Line> LinePtr;

#endif /* FLTK_EXT_LINE_H_ */
