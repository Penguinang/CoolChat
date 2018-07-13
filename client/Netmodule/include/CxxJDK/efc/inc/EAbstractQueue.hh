/*
 * EAbstractQueue.hh
 *
 *  Created on: 2014-6-27
 *      Author: cxxjava@163.com
 */

#ifndef EABSTRACTQUEUE_HH_
#define EABSTRACTQUEUE_HH_

#include "EQueue.hh"
#include "EAbstractCollection.hh"
#include "EIllegalStateException.hh"
#include "ENoSuchElementException.hh"
#include "EUnsupportedOperationException.hh"

/**
 * This class provides skeletal implementations of some {@link Queue}
 * operations. The implementations in this class are appropriate when
 * the base implementation does <em>not</em> allow <tt>null</tt>
 * elements.  Methods {@link #add add}, {@link #remove remove}, and
 * {@link #element element} are based on {@link #offer offer}, {@link
 * #poll poll}, and {@link #peek peek}, respectively, but throw
 * exceptions instead of indicating failure via <tt>false</tt> or
 * <tt>null</tt> returns.
 *
 * <p> A <tt>Queue</tt> implementation that extends this class must
 * minimally define a method {@link Queue#offer} which does not permit
 * insertion of <tt>null</tt> elements, along with methods {@link
 * Queue#peek}, {@link Queue#poll}, {@link Collection#size}, and a
 * {@link Collection#iterator} supporting {@link
 * Iterator#remove}. Typically, additional methods will be overridden
 * as well. If these requirements cannot be met, consider instead
 * subclassing {@link AbstractCollection}.
 *
 * <p>This class is a member of the
 * <a href="{@docRoot}/../technotes/guides/collections/index.html">
 * Java Collections Framework</a>.
 *
 * @since 1.5
 * @param <E> the type of elements held in this collection
 */
namespace efc {

template<typename E>
abstract class EAbstractQueue: virtual public EAbstractCollection<E>,
		virtual public EQueue<E> {
protected:
	/**
	 * Constructor for use by subclasses.
	 */
	EAbstractQueue() {
	}

public:
	typedef typename ETraits<E>::indexType idxE;

	virtual ~EAbstractQueue(){}

	virtual boolean offer(E e) {
		throw EUnsupportedOperationException(__FILE__, __LINE__);
	}
	virtual E poll() {
		throw EUnsupportedOperationException(__FILE__, __LINE__);
	}
	virtual E peek() {
		throw EUnsupportedOperationException(__FILE__, __LINE__);
	}

	/**
	 * Inserts the specified element into this queue if it is possible to do so
	 * immediately without violating capacity restrictions, returning
	 * <tt>true</tt> upon success and throwing an <tt>IllegalStateException</tt>
	 * if no space is currently available.
	 *
	 * <p>This implementation returns <tt>true</tt> if <tt>offer</tt> succeeds,
	 * else throws an <tt>IllegalStateException</tt>.
	 *
	 * @param e the element to add
	 * @return <tt>true</tt> (as specified by {@link Collection#add})
	 * @throws IllegalStateException if the element cannot be added at this
	 *         time due to capacity restrictions
	 * @throws ClassCastException if the class of the specified element
	 *         prevents it from being added to this queue
	 * @throws NullPointerException if the specified element is null and
	 *         this queue does not permit null elements
	 * @throws IllegalArgumentException if some property of this element
	 *         prevents it from being added to this queue
	 */
	virtual boolean add(E e) {
		if (offer(e))
			return true;
		else
			throw EIllegalStateException(__FILE__, __LINE__, "Queue full");
	}

	/**
	 * {@inherit from super for c++ hides overloaded virtual function}
	 */
	virtual boolean remove(idxE o) {
		return EAbstractCollection<E>::remove(o);
	}

	/**
	 * Retrieves and removes the head of this queue.  This method differs
	 * from {@link #poll poll} only in that it throws an exception if this
	 * queue is empty.
	 *
	 * <p>This implementation returns the result of <tt>poll</tt>
	 * unless the queue is empty.
	 *
	 * @return the head of this queue
	 * @throws NoSuchElementException if this queue is empty
	 */
	virtual E remove() {
		E x = poll();
		if (!obj_is_null(x))
			return x;
		else
			throw ENoSuchElementException(__FILE__, __LINE__);
	}

	/**
	 * Retrieves, but does not remove, the head of this queue.  This method
	 * differs from {@link #peek peek} only in that it throws an exception if
	 * this queue is empty.
	 *
	 * <p>This implementation returns the result of <tt>peek</tt>
	 * unless the queue is empty.
	 *
	 * @return the head of this queue
	 * @throws NoSuchElementException if this queue is empty
	 */
	virtual E element() {
		E x = peek();
		if (!obj_is_null(x))
			return x;
		else
			throw ENoSuchElementException(__FILE__, __LINE__);
	}

	/**
	 * Removes all of the elements from this queue.
	 * The queue will be empty after this call returns.
	 *
	 * <p>This implementation repeatedly invokes {@link #poll poll} until it
	 * returns <tt>null</tt>.
	 */
	virtual void clear() {
		try {
			while (!obj_is_null(poll()))
						;
		} catch (ENoSuchElementException& ignore) {
		}
	}

	/**
	 * Adds all of the elements in the specified collection to this
	 * queue.  Attempts to addAll of a queue to itself result in
	 * <tt>IllegalArgumentException</tt>. Further, the behavior of
	 * this operation is undefined if the specified collection is
	 * modified while the operation is in progress.
	 *
	 * <p>This implementation iterates over the specified collection,
	 * and adds each element returned by the iterator to this
	 * queue, in turn.  A runtime exception encountered while
	 * trying to add an element (including, in particular, a
	 * <tt>null</tt> element) may result in only some of the elements
	 * having been successfully added when the associated exception is
	 * thrown.
	 *
	 * @param c collection containing elements to be added to this queue
	 * @return <tt>true</tt> if this queue changed as a result of the call
	 * @throws ClassCastException if the class of an element of the specified
	 *         collection prevents it from being added to this queue
	 * @throws NullPointerException if the specified collection contains a
	 *         null element and this queue does not permit null elements,
	 *         or if the specified collection is null
	 * @throws IllegalArgumentException if some property of an element of the
	 *         specified collection prevents it from being added to this
	 *         queue, or if the specified collection is this queue
	 * @throws IllegalStateException if not all the elements can be added at
	 *         this time due to insertion restrictions
	 * @see #add(Object)
	 */
	virtual boolean addAll(ECollection<E>* c) {
		if (c == null)
			throw ENullPointerException(__FILE__, __LINE__);
		if (c == this)
			throw EIllegalArgumentException(__FILE__, __LINE__);
		boolean modified = false;
		sp<EIterator<E> > e = c->iterator();
		while (e->hasNext()) {
			if (add(e->next()))
				modified = true;
		}
		return modified;
	}
};

} /* namespace efc */
#endif /* EABSTRACTQUEUE_HH_ */
