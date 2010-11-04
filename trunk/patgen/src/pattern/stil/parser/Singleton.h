#ifndef __STIL_SINGLETON_H__
#define __STIL_SINGLETON_H__

#include <iostream>

using namespace std;

namespace Stil {

template<class Derived>
class Singleton {
	public:
		static Derived* getPointer() {
			if(pInstance == 0 || pInstance == NULL) {
				pInstance = new Derived;
                //cout << "Creating new object" << endl;
            }

			return pInstance;
		}
		static Derived& getReference() {
			if(pInstance == 0 || pInstance == NULL) {
				pInstance = new Derived;
                //cout << "Creating new object" << endl;
            }

			return *pInstance;
		}
        static void destroy() {
            //cout << "Destroying new object" << endl;
            if(pInstance != 0 || pInstance != NULL)
                delete pInstance;

            pInstance = 0;
        }
//        virtual ~Singleton() {
//            cout << "Destroying new object" << endl;
//            if(pInstance != 0 || pInstance != NULL)
//                delete pInstance;
//        }
	protected:
		Singleton() {}
	private:
		static Derived* pInstance;
};

template<class Derived>
	Derived* Singleton<Derived>::pInstance = 0;

}

#endif

