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

#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

#include "lut.h"

using namespace std;

template<typename Type> Type toValue(string& str) {
    Type value;
    stringstream sstr(str);

    sstr >> value;

    return value;
}

template unsigned int toValue(string& str);
template string toValue(string& str);

string trim( string& s, const string& unwanted)
{
        string r=s.erase(s.find_last_not_of(unwanted)+1);
        return r.erase(0,r.find_first_not_of(unwanted));
}

string trim( const string& str, const string& unwanted)
{
        string temp = str;
        temp = temp.erase( temp.find_last_not_of(unwanted)+1);
        return temp.erase( 0, temp.find_first_not_of(unwanted));
}


vector<string> split(string str, string delim) {
    vector<string> vec;

    string::size_type begin = 0;
    string::size_type pos   = str.find(delim, 0);
    while(pos != string::npos) {
        string found = str.substr( begin, pos - begin);
        vec.push_back(found);
        begin = pos + delim.size();
        pos   = begin;
        pos   = str.find(delim, begin);
    }

    if(begin < str.size())
        vec.push_back(str.substr(begin, string::npos));

    return vec;
}

/*
template<typename KeyType, typename ValueType>
    Lut<KeyType,ValueType>::Lut() {
    }
    */


template<typename KeyType, typename ValueType>
        ValueType& Lut<KeyType,ValueType>::operator[]( const KeyType& key) {
            if(count(key) == 0) {
                std::cerr << "ERROR : Invalid key [" << key << "] given." << std::endl;
                assert(count(key) == 1);
            }
            else {
#ifdef __GNUG__
# define GCC_VERSION (__GNUC__ * 10000 \
                               + __GNUC_MINOR__ * 100 \
                               + __GNUC_PATCHLEVEL__)
# if GCC_VERSION > 40000
                return this->find(key)->second;
# else
                return find(key)->second;
# endif
#else

# ifdef _MSC_VER
                return find(key)->second;
# else
                return find(key)->second;
# endif
#endif
            }
        }

template<typename KeyType, typename ValueType>
    bool Lut<KeyType,ValueType>::read(string fileName, string delim) {
        bool result = true;

        ifstream ifile;

        ifile.open(fileName.c_str(), ios::in);

        if(ifile.is_open()) {
            string line;
            while(! ifile.eof()) {
                line = "";
                getline( ifile, line);
                vector<string> vec = split( line, delim);

                for(unsigned int i=0; i < vec.size(); i++) {
                    vec[i] = trim(vec[i], " ");
                    cout << vec[i] << delim;
                }
                cout << endl;

                if(vec.size() >= 2) {
                    KeyType key     = toValue<KeyType>(vec[0]);
                    ValueType value = toValue<ValueType>(vec[1]);
                    this->insert( pair<KeyType,ValueType>(key,value));
                }
            }

            ifile.close();
        }
        else {
            cerr << "ERROR : Unable to open file " << fileName << endl;
            result = false;
        }

        return result;
    }

template<typename KeyType, typename ValueType>
    bool Lut<KeyType,ValueType>::write(string fileName) {
        bool result = true;

        return result;
    }

template<typename KeyType, typename ValueType>
        bool Lut<KeyType,ValueType>::print ( ostream& os) {
//            ::iterator iter;

//            for(iter = begin(); iter != end(); iter++) {
//                os << (*iter).first << " : " << (*iter).second << endl;
//            }
            
            return true;
        }

template class Lut<string, unsigned int>;

