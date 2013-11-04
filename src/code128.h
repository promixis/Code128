/*

    Code128

    Code 128 is a very high-density barcode symbology. It is used
    for alphanumeric or numeric-only barcodes. This implementation
    can encode all 128 characters of ASCII. The implementation can
    switch between mode B and mode C to compress numbers.

    https://en.wikipedia.org/wiki/Code_128


    The MIT License (MIT)

    Copyright (c) 2013 Promixis, LLC

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

*/

#ifndef _PROMIXIS_CODE128_H
#define _PROMIXIS_CODE128_H

#include <QString>
#include <QList>
#include <QStringList>

class Code128
{
    typedef char * Symbol;
    enum Symbols { SYM_CodeC=99, SYM_CodeB = 100, SYM_StartA=103, SYM_StartB, SYM_StartC, SYM_Stop, SYM_NA };
    static Code128::Symbol symbols[108];

    enum Mode { MODE_A, MODE_B, MODE_C, IDLE };
    static Symbol symbolCode(quint8 c );
    static void addSymbolCodeChar( char c, QStringList & symbols, int & checksum );
    static void addSymbolCodeInt(quint8 value, QStringList & symbols, int & checksum );
    static quint8 digitCount( const QString & data, int startPos );

public:

    typedef QList<quint8> BarCode;

    /* Code128 encoding of data
     *
     * Accepts characters in the basic ASCII set (ASCII values 32-126).
     * Maximum length is 100 characters, though I doubt any bar code
     * scanner will read that.
     *
     * Returns a list of bar widths. For example 2 3 1 4. This would mean
     * to draw a set of bars with widths 2, 3, 1 and 4. The odd numbered bars
     * are dark and the even numbered bars a light. 4 is the maximum width
     * returned.
     */
    static BarCode encode( const QString & data );

};

#endif // _PROMIXIS_CODE128_H
