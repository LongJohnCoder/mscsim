/****************************************************************************//*
 * Copyright (C) 2020 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef FDM_STRING_H
#define FDM_STRING_H

////////////////////////////////////////////////////////////////////////////////

#include <limits>
#include <string>
#include <vector>

#include <fdm/fdm_Defines.h>

////////////////////////////////////////////////////////////////////////////////

namespace fdm
{

/**
 * @brief Text string utilities class.
 */
class FDMEXPORT String
{
public:

    /**
     * @brief Returns string first line;
     * @param str string to be processed
     * @return string first line
     */
    static std::string getFirstLine( const std::string &str );

    /**
     * @brief Compares strings. This function is case insensitive.
     * @param str_1 1st string to compare
     * @param str_2 2nd string to compare
     * @return integer result of the comparison (returns 0 if strings are equal)
     */
    static int icompare( const std::string &str_1, const std::string &str_2 );

    /**
     * @brief Splits string with the given delimeter.
     * @param str string to be splitted
     * @param sep string separator
     * @return vector of strings
     */
    static std::vector< std::string > split( const std::string &str, const std::string &sep );

    /**
     * @brief Returns string with leading white spaces removed.
     * @param str string to be processed
     * @return string with leading white spaces removed
     */
    static std::string stripLeadingSpaces( const std::string &str );

    /**
     * @brief Returns string with trailing white spaces removed.
     * @param str string to be processed
     * @return string with trailing white spaces removed
     */
    static std::string stripTrailingSpaces( const std::string &str );

    /**
     * @brief Returns string with both leading and trailing white spaces removed.
     * @param str string to be processed
     * @return string with leading and trailing white spaces removed
     */
    static std::string stripSpaces( const std::string &str );

    /**
     * @brief Converts string into variable.
     * @param str string to be processed
     * @param def default value
     * @return result value
     */
    static bool toBool( const std::string &str,
                        bool def = std::numeric_limits< bool >::quiet_NaN() );

    /**
     * @brief Converts string into variable.
     * @param str string to be processed
     * @param def default value
     * @return result value
     */
    static int toInt( const std::string &str,
                      int def = std::numeric_limits< int >::quiet_NaN() );

    /**
     * @brief Converts string into variable.
     * @param str string to be processed
     * @param def default value
     * @return result value
     */
    static double toDouble( const std::string &str,
                            double def = std::numeric_limits< double >::quiet_NaN() );

    /**
     * @brief Converts variable into string.
     * @param val value to be processed
     * @return result string
     */
    static std::string toString( int val );

    /**
     * @brief Converts variable into string.
     * @param val value to be processed
     * @return result string
     */
    static std::string toString( float val );

    /**
     * @brief Converts variable into string.
     * @param val value to be processed
     * @return result string
     */
    static std::string toString( double val );

    /**
     * @brief Converts string to lower case.
     * @param str string to be processed
     * @return result string
     */
    static std::string toLower( const std::string &str );

    /**
     * @brief Converts string to upper case.
     * @param str string to be processed
     * @return result string
     */
    static std::string toUpper( const std::string &str );
};

} // end of fdm namespace

////////////////////////////////////////////////////////////////////////////////

#endif // FDM_STRING_H
