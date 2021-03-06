/*
 * EURLEncoder.hh
 *
 *  Created on: 2013-3-16
 *      Author: cxxjava@163.com
 */

#ifndef EURLEncoder_HH_
#define EURLEncoder_HH_

#include "EString.hh"

namespace efc {

/**
 * Utility class for HTML form encoding. This class contains static methods
 * for converting a String to the <CODE>application/x-www-form-urlencoded</CODE> MIME
 * format. For more information about HTML form encoding, consult the HTML 
 * <A HREF="http://www.w3.org/TR/html4/">specification</A>. 
 *
 * <p>
 * When encoding a String, the following rules apply:
 *
 * <p>
 * <ul>
 * <li>The alphanumeric characters &quot;<code>a</code>&quot; through
 *     &quot;<code>z</code>&quot;, &quot;<code>A</code>&quot; through
 *     &quot;<code>Z</code>&quot; and &quot;<code>0</code>&quot; 
 *     through &quot;<code>9</code>&quot; remain the same.
 * <li>The special characters &quot;<code>.</code>&quot;,
 *     &quot;<code>-</code>&quot;, &quot;<code>*</code>&quot;, and
 *     &quot;<code>_</code>&quot; remain the same. 
 * <li>The space character &quot;<code>&nbsp;</code>&quot; is
 *     converted into a plus sign &quot;<code>+</code>&quot;.
 * <li>All other characters are unsafe and are first converted into
 *     one or more bytes using some encoding scheme. Then each byte is
 *     represented by the 3-character string
 *     &quot;<code>%<i>xy</i></code>&quot;, where <i>xy</i> is the
 *     two-digit hexadecimal representation of the byte. 
 *     The recommended encoding scheme to use is UTF-8. However, 
 *     for compatibility reasons, if an encoding is not specified, 
 *     then the default encoding of the platform is used.
 * </ul>
 *
 * <p>
 * For example using UTF-8 as the encoding scheme the string &quot;The
 * string &#252;@foo-bar&quot; would get converted to
 * &quot;The+string+%C3%BC%40foo-bar&quot; because in UTF-8 the character
 * &#252; is encoded as two bytes C3 (hex) and BC (hex), and the
 * character @ is encoded as one byte 40 (hex).
 *
 * @version 1.32, 04/22/06
 * @since   JDK1.0
 */
class EURLEncoder {
public:
	
	/**
     * Translates a string into <code>x-www-form-urlencoded</code>
     * format. This method uses the platform's default encoding
     * as the encoding scheme to obtain the bytes for unsafe characters.
     *
     * @param   s   <code>String</code> to be translated.
     * @deprecated The resulting string may vary depending on the platform's
     *             default encoding. Instead, use the encode(String,String)
     *             method to specify the encoding.
     * @return  the translated <code>String</code>.
     */
	static EString encode(const char* s, int len=0);
};

} /* namespace efc */
#endif //!EURLEncoder_HH_
