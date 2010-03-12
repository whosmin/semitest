#ifndef __STIL_STIL_H__
#define __STIL_STIL_H__

#include "../../../common/common.h"
#include "Singleton.h"
#include "Expr.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace Stil {

    enum Type { STIL_OBJECT,
        STIL_SIGNAL,
        STIL_SIGNALS,
        STIL_SIGNALGROUPS,
        STIL_GROUPSITEM,
        STIL_SPEC,
        STIL_CATEGORY,
        STIL_SPEC_ITEM,
        STIL_WAVEFORMTABLE
    };

    class Object {
        protected:
        public:
            Object(Type type) { _type = type; indent = "\t"; }
            virtual void setName  ( string instName)  { name  = instName;  }
            virtual void setLevel ( int    level) { _level = level; }
            virtual void setScope ( string scope) { _scope = scope; }

            virtual string getName() { return name; }

            virtual string toStil() = 0;
        public:
            string name;
            int    _level;
            string _scope;
            string indent;
        protected:
            Type   _type;
    };

    class SymbolTable : public Singleton<SymbolTable> {
        public:
            SymbolTable();

            bool add    ( Object& obj);
            //bool add    ( string name, string scope);
            bool exists ( string name);
            Type getType ( string name) { if(exists(name)) return table[name].second; }

        protected:
            map<string, pair<string, Type> > table;
    };

    template<class Type>
        class Collection : public map< string, Type> {
            public:
                Collection() {}

            public:

        };

    enum SignalType { INOUT, INPUT, OUTPUT, SUPPLY, PSEUDO };

    class Signal : public Object {
        public:
            Signal(string name="");
            Signal(string name, SignalType type);
            Signal(string name, string type);

            string       getName(void) { return name; }
            SignalType   getSignalType(void) { return _subType; }
            void         setSignalType(SignalType type) { _subType = type; }
            void         setSignalType(string type);

            string       toStil()  { string str = name;  return str; }

        private:
            SignalType   _subType;
    };

    class Signals : public Object {
        //protected:
        //Signals(const Signals& signals) { table = signals.table; }
        public:
            Signals();

            bool addSignal(Signal signal);
            bool addSignal(string name, SignalType type);

            string toStil()  { string str = name;  return str; }

        protected:
            map<string, Signal> signalMap;
    };

    class GroupsItem : public Object {
        public:
            GroupsItem() : Object(STIL_GROUPSITEM) {}
            virtual string toStil();

            //string name;
            string expr;
            vector<string> pinVec;
    };
    class SignalGroups : public Object {
        public:
            SignalGroups();
            string toStil();

            bool add( string name, string expr);
            void clear() { groups.clear(); }

        protected:
            map<string, GroupsItem> groups;
    };

    class SpecItem : public Object {
        public:
            SpecItem() : Object(STIL_SPEC_ITEM) { order = ++count;}
            SpecItem(string instName) : Object(STIL_SPEC_ITEM), order(++count) { name = instName; }

            double setExprString(string exprStr);

            string toStil();
        public:
            unsigned long int order;
            Expr expr;
            Expr minExpr, typExpr, maxExpr;
        protected:
            static unsigned long int count;
    };

    class Category : public Object {
        public:
            Category() : Object( STIL_CATEGORY) {}
            string toStil();

            Collection<SpecItem> specs;
    };

    class Spec : public Object {
        public:
            Spec();
            string toStil();

            Collection<Category> categories;
    };


    class WaveformTable : public Object {
        public:
            //typedef map<string, vector< pair<Expr, State> > > WfcList ;
            //        typedef map<string, vector< pair<double, State> > > WfcList ;
            //        typedef map<string, map< double, State> > WfcList ;

            //typedef map<double, State> EventList;
            typedef map<Expr, State> EventList;
            typedef map<char, EventList > WfcList;

            WaveformTable();
            WaveformTable(string wftName);

            void   clear (void);
            string toStil();
            void   print (ostream& os);

            void   getEvents           ( const string pinName, const char wfc, EventList& events);
            double getEventResolution  ();


            Expr period;
            /// pinGroup to WfcList map
            map<string, WfcList> waveforms;
    };
#if 0
    class WaveformTable : public Object {
        public:
            WaveformTable();

            Expr period;
    };
#endif

}

#endif

