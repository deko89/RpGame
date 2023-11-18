#ifndef MassivPtr_H
#define MassivPtr_H

#include <vector>

/// Массив указателей.
template<class C> class MassivPtr: public std::vector<C*>
{   public:
    typedef std::vector<C*> Base;
	~MassivPtr() { for (C* e: *this) delete e; }
	C* Add() { C* p = new C;   push_back(p);   return p; }
	C* Add(C* p) { push_back(p);   return p; }
	MassivPtr& operator= (const MassivPtr& B) = delete;
	typename Base::iterator erase(typename Base::const_iterator i) = delete;
	typename Base::iterator erase(typename Base::const_iterator first, typename Base::const_iterator last) = delete;
};

#endif
