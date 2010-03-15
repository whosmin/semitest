//
// This file is part of SemiTest
//
// Copyright (c) 2009 - 2010 Tushar Jog
//
// SemiTest is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Foobar is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
//
/*
 * curve.h
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */


#ifndef __CORE_REFERENCE_H__
#define __CORE_REFERENCE_H__

#include <iostream>
#include <vector>

using namespace std;

namespace TestLib {

    class Point {
        public:
            Point(double xpos = 0, double ypos = 0);
            Point(const Point &p);

            double getX(void) { return x; }
            double getY(void) { return y; }

            friend inline const Point operator+(const Point &, const Point &);
            friend inline const Point operator-(const Point &, const Point &);
        public:
            double x;
            double y;
    };

    class Curve {
        public:
            enum CurveType { CUBIC_SPLINE, NATURAL_CUBIC_SPLINE, B_SPLINE };
            Curve(CurveType type = NATURAL_CUBIC_SPLINE);

            void addPoint( double x, double y);
            void addPoint( Point p);
            void addPoints(vector<Point> ps);
            void addPoints(vector< pair<double,double> > ps);
            vector<Point> getPoints(void);

            bool init(void);
            bool isInitialized(void) { return initialized; }

            double value(double xpos);

            void printPoints(ostream &os);
            void clear(void);
            int size(void);
        private:
            vector<Point> points;
            vector<double> a, b, c;
            bool initialized;
    };
}

#endif

