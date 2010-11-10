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
 * curve.cpp
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */

#include "curve.h"
#include <iostream>
#include <cassert>
using namespace std;

#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCTION__
#endif

namespace TestLib {

    inline Point::Point(double xpos, double ypos)
        : x(xpos), y(ypos)
    {
    }

    inline Point::Point(const Point &p)
        : x(p.x), y(p.y)
    {
    }


    //
    // Friend functions
    //
    inline const Point operator+(const Point &p1, const Point &p2) {
        return Point( p1.x + p2.x, p1.y + p2.y);
    }
    inline const Point operator-(const Point &p1, const Point &p2) {
        return Point( p1.x - p2.x, p1.y - p2.y);
    }

    Curve::Curve(CurveType type) {
        initialized = false;
        curveType = type;
    }

    void Curve::addPoint(double x, double y) {
        Point p(x,y);
        points.push_back( p);
        initialized = false;
        return;
    }

    void Curve::addPoint(Point p) {
        points.push_back(p);
        initialized = false;
        return;
    }
    void Curve::addPoints(std::vector<Point> ps) {
        for(unsigned int i=0; i<ps.size(); i++)
            points.push_back(ps[i]);
        initialized = false;
        return;
    }

    void Curve::addPoints(std::vector< std::pair<double,double> > ps) {
        for(unsigned int i=0; i<ps.size(); i++)
            points.push_back(Point(ps[i].first, ps[i].second));
        initialized = false;
        return;
    }

    vector<Point> Curve::getPoints(void) {
        return points;
    }

    bool Curve::init(void) {
        initialized = false;
        unsigned int size = points.size();

        if(size <= 2) return false;

        a.clear(); b.clear(); c.clear();
        a.resize( size - 1, 0.0);
        b.resize( size - 1, 0.0);
        c.resize( size - 1, 0.0);

        if(curveType == LINEAR) {
        }
        else if(curveType == NATURAL_CUBIC_SPLINE) {

            std::vector<double> h(size, 0.0);
            for(unsigned int i=0; i < (size - 1); i++) {
                h[i] = points[i+1].x - points[i].x;
                if(h[i] <= 0) return false;
            }

            std::vector<double> d(size, 0.0);
            double dy1 = (points[1].y - points[0].y)/h[0];
            for(unsigned int i=1; i < (size - 1); i++) {
                b[i] = c[i] = h[i];
                a[i] = 2.0 * (h[i] + h[i-1]);
                double dy2 = (points[i+1].y - points[i].y) / h[i];
                d[i] = 6.0 * (dy1 - dy2);
                dy1 = dy2;
            }

            for(unsigned int i=1; i < size - 2; i++) {
                c[i] /= a[i];
                a[i+1] -= b[i] * c[i];
            }

            std::vector<double> s(size, 0.0);
            s[1] = d[1];
            for(unsigned int i=2; i < size - 1; i++)
                s[i] = d[1] - c[i-1]*s[i-1];

            s[size - 2] = - s[size -2] / a[size - 2];
            for(unsigned int i=size-3; i > 0; i--)
                s[i] = - (s[i] + b[i]*s[i+1]) / a[i];
            s[size-1] = s[0] = 0.0;

            for(unsigned int i=0; i < size - 1; i++) {
                a[i] = (s[i+1] - s[i])/(6.0*h[i]);
                b[i] = 0.5*s[i];
                c[i] = (points[i+1].y - points[i].y)/h[i]  -  (s[i+1] + 2.0*s[i])*h[i]/6.0;
            }

            initialized = true;
        }
        return true;
    }

    double Curve::value(double xpos) {
        double result = 0.0;
        unsigned int size = points.size();

        if(initialized == false) {
            cerr << __PRETTY_FUNCTION__
                << " : Curve data Not Initialized. Call init() first" << endl;
            cerr << "\tNum data points " << size << endl;
            //assert(initialized);
            //return 0.0;
            init();
        }
        if((xpos > points[size-1].x) || (xpos < points[0].x)) return 0.0;


        unsigned int index = 0;
        for(unsigned int i=0; i < size - 1; i++) {
            //        if(xpos == points[i].x) { 
            //            result = points[i].y;
            //            return result;
            //        }

            //cout << i << "\t" << xpos << "\t" << points[i].x << "\t" << points[i+1].x << endl;

            if((xpos >= points[i].x) && (xpos < points[i+1].x)) {
                index = i;
                break;
            }
        }
        if(xpos == points[size-1].x) { result = points[size-1].y; return result; }

        double dx = xpos - points[index].x;
        double dx2 = dx * dx;
        double dx3 = dx2 * dx;
        //cout << index << "\t";
        result = a[index]*dx3 + b[index]*dx2 + c[index]*dx + points[index].y;

        return result;
    }

    void Curve::printPoints(ostream &os) {
        unsigned int size = points.size();

        for(unsigned int i=0; i < size; i++) {
            os << i << "\t" << points[i].x << "\t" << points[i].y << endl;
        }

        return;
    }

    void Curve::clear(void) {
        points.clear();
        a.clear();
        b.clear();
        c.clear();
        initialized = false;
        return;
    }

    int Curve::size(void) {
        return points.size();
    }


}

