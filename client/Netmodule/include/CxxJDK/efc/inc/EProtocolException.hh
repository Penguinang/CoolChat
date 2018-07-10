/*
 * EProtocolException.hh
 *
 *  Created on: 2013-3-14
 *      Author: cxxjava@163.com
 */

#ifndef EPROTOCOLEXCEPTION_HH_
#define EPROTOCOLEXCEPTION_HH_

#include "EIOException.hh"

namespace efc {

#define EPROTOCOLEXCEPTION       EProtocolException(__FILE__, __LINE__, errno)
#define EPROTOCOLEXCEPTIONS(msg) EProtocolException(__FILE__, __LINE__, msg)

/**
 * Thrown to indicate that there is an error in the underlying
 * protocol, such as a TCP error.
 *
 * @since   JDK1.0
 */

class EProtocolException: public EIOException {
public:
	/**
	 * Constructs an <code>EProtocolException</code> with no
	 * detail message.
	 *
	 * @param   _file_   __FILE__
	 * @param   _line_   __LINE__
	 * @param   errn     errno
	 */
	EProtocolException(const char *_file_, int _line_, int errn = 0) :
			EIOException(_file_, _line_, errn) {
	}

	/**
	 * Constructs an <code>EProtocolException</code> with the
	 * specified detail message.
	 *
	 * @param   _file_   __FILE__.
	 * @param   _line_   __LINE__.
	 * @param   s   the detail message.
	 */
	EProtocolException(const char *_file_, int _line_, const char *s, int errn = 0) :
			EIOException(_file_, _line_, s, errn) {
	}
};

} /* namespace efc */
#endif /* EPROTOCOLEXCEPTION_HH_ */
