#ifndef __STIL_STIL_H__
#define __STIL_STIL_H__

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
                STIL_SPEC_ITEM
    };

    class Object {
        protected:
        public:
            Object(Type type) { _type = type; }
            virtual void setName  ( string name)  { _name  = name;  }
            virtual void setLevel ( int    level) { _level = level; }
            virtual void setScope ( string scope) { _scope = scope; }

            virtual string getName() { return _name; }

            virtual string toStil() = 0;
        public:
            string _name;
            int    _level;
            string _scope;
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

            string       getName(void) { return _name; }
            SignalType   getSignalType(void) { return _subType; }
            void         setSignalType(SignalType type) { _subType = type; }
            void         setSignalType(string type);

            string       toStil()  { string str = _name;  return str; }

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

            string toStil()  { string str = _name;  return str; }

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
            SpecItem(string name) : Object(STIL_SPEC_ITEM), order(++count) { _name = name; }

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

}

#endif

