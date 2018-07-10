/*
 * EIterable.hh
 *
 *  Created on: 2013-3-19
 *      Author: cxxjava@163.com
 */

#ifndef EITERABLE_HH_
#define EITERABLE_HH_

#include "EIterator.hh"

namespace efc {

/**
 * Implementing this interface allows an object to be the target of
 * the "foreach" statement.
 *
 * @param <T> the type of elements returned by the iterator
 *
 * @since 1.5
 */

#ifdef CPP11_SUPPORT
template<typename T>
class RangeIter {
public:
	RangeIter() {}
	RangeIter(sp<EIterator<T> > i) : i(i) {}

	bool operator!=(const RangeIter<T>& other) const {
		return i->hasNext();
	}

	const T operator*() {
		return i->next();
	}

	const RangeIter& operator++() {
		return *this;
	}

private:
	sp<EIterator<T> > i;
};
#endif

template<typename T>
interface EIterable : virtual public EObject
{
	virtual ~EIterable(){}

	/**
     * Returns an iterator over a set of elements of type T.
     *
     * @return an Iterator.
     */
    virtual sp<EIterator<T> > iterator(int index=0) = 0;

#ifdef CPP11_SUPPORT
    RangeIter<T> begin() {
    	return RangeIter<T>(iterator());
    }
    RangeIter<T> end() {
    	return RangeIter<T>();
    }
#endif
};

} /* namespace efc */
#endif /* EITERABLE_HH_ */
