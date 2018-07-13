/*
 * EIllegalBlockingModeException.hh
 *
 *  Created on: 2013-12-16
 *      Author: cxxjava@163.com
 */

#ifndef EILLEGALBLOCKINGMODEEXCEPTION_HH_
#define EILLEGALBLOCKINGMODEEXCEPTION_HH_

#include "EIllegalStateException.hh"

namespace efc {

#define EILLEGALBLOCKINGMODEEXCEPTION       EIllegalBlockingModeException(__FILE__, __LINE__, errno)
#define EILLEGALBLOCKINGMODEEXCEPTIONS(msg) EIllegalBlockingModeException(__FILE__, __LINE__, msg)

/**
 * Unchecked exception thrown when a blocking-mode-specific operation
 * is invoked upon a channel in the incorrect blocking mode.
 *
 * @version 1.9, 01/11/19
 * @since 1.4
 */

class EIllegalBlockingModeException: public EIllegalStateException {
public:
	/**
	 * Constructs an <code>EIllegalBlockingModeException</code> with no
	 * detail message.
	 *
	 * @param   _file_   __FILE__
	 * @param   _line_   __LINE__
	 * @param   errn     errno
	 */
	EIllegalBlockingModeException(const char *_file_, int _line_, int errn = 0) :
		EIllegalStateException(_file_, _line_, errn) {
	}

	/**
	 * Constructs an <code>EIllegalBlockingModeException</code> with the
	 * specified detail message.
	 *
	 * @param   _file_   __FILE__.
	 * @param   _line_   __LINE__.
	 * @param   s   the detail message.
	 */
	EIllegalBlockingModeException(const char *_file_, int _line_,
			const char *s) :
			EIllegalStateException(_file_, _line_, s) {
	}
};

} /* namespace efc */
#endif /* EILLEGALBLOCKINGMODEEXCEPTION_HH_ */
