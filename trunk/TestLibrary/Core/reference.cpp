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
 * reference.cpp
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */

#include "reference.h"
#include <iostream>
#include <cassert>
using namespace std;

#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCTION__
#endif

namespace TestLib {

#if 0
	template<class Collection, class Type>
	ostream& operator<<(ostream& os, ContainerReference<Collection, Type>& contRef) {
		os << contRef.objRef.get(contRef.index);

		return os;
	}
#endif

}

