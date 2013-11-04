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

#include "code128.h"

Code128::Symbol Code128::symbols[108] = {

    "212222", "222122", "222221", "121223", "121322", "131222", "122213", "122312", "132212", "221213",
    "221312", "231212", "112232", "122132", "122231", "113222", "123122", "123221", "223211", "221132",
    "221231", "213212", "223112", "312131", "311222", "321122", "321221", "312212", "322112", "322211",
    "212123", "212321", "232121", "111323", "131123", "131321", "112313", "132113", "132311", "211313",
    "231113", "231311", "112133", "112331", "132131", "113123", "113321", "133121", "313121", "211331",
    "231131", "213113", "213311", "213131", "311123", "311321", "331121", "312113", "312311", "332111",
    "314111", "221411", "431111", "111224", "111422", "121124", "121421", "141122", "141221", "112214",
    "112412", "122114", "122411", "142112", "142211", "241211", "221114", "413111", "241112", "134111",
    "111242", "121142", "121241", "114212", "124112", "124211", "411212", "421112", "421211", "212141",
    "214121", "412121", "111143", "111341", "131141", "114113", "114311", "411113", "411311", "113141",
    "114131", "311141", "411131", "211412", "211214", "211232", "2331112", ""
};


Code128::Symbol Code128::symbolCode(quint8 c)
{
    if ( c > SYM_Stop )
    {
        return symbols[107];
    }

    return symbols[c];
}



void Code128::addSymbolCodeChar(char c, QStringList &symbols, int &checksum)
{
    // keep characters in valid range.
    if ( c < 32 )
    {
        c = 32;
    }
    if ( c > 126 )
    {
        c = 32;
    }
    quint8 value = (unsigned int)c - 32;
    Code128::Symbol symbol = symbolCode(value);
    symbols += symbol;
    checksum += value * ( symbols.count() == 1 ? 1 : symbols.count() - 1 );
}

void Code128::addSymbolCodeInt(quint8 value, QStringList &symbols, int &checksum)
{
    Code128::Symbol symbol = symbolCode(value);
    symbols += symbol;
    checksum += value * ( symbols.count() == 1 ? 1 : symbols.count() - 1 );
}

quint8 Code128::digitCount(const QString &data, int startPos)
{
    quint8 cnt = 0;

    for ( ;startPos < data.length();startPos++ )
    {
        if ( !data.at(startPos).isDigit() )
        {
            break;
        }
        cnt++;
    }

    cnt &= 0xfe; // only pairs please.
    return cnt;
}

Code128::BarCode Code128::encode(const QString &data)
{
    QStringList symbols;
    int checkSum = 0;

    if ( data.length() > 100 || data.length() == 0 )
    {
        return BarCode();
    }

    int pos = 0;

    Mode mode = IDLE;

    while ( pos < data.length() )
    {
        quint8 dc = digitCount(data, pos);

        if ( dc >= 4 )
        {

            if ( mode != MODE_C )
            {
                if ( mode == IDLE )
                {
                    addSymbolCodeInt(SYM_StartC, symbols, checkSum);
                }
                else
                {
                    addSymbolCodeInt(SYM_CodeC, symbols, checkSum);
                }
                mode = MODE_C;
            }

            dc = dc>>1;
            for ( int i=0; i < dc; i++ )
            {
                QString v = data.mid(pos,2);
                int value = v.toInt();
                addSymbolCodeInt(value, symbols, checkSum);
                pos+=2;
            }
        }
        else
        {
            if ( mode != MODE_B )
            {
                if ( mode == IDLE )
                {
                    addSymbolCodeInt(SYM_StartB, symbols, checkSum);
                }
                else
                {
                    addSymbolCodeInt(SYM_CodeB, symbols, checkSum);
                }
                mode = MODE_B;
            }
            addSymbolCodeChar( data.at(pos).toLatin1(), symbols, checkSum );
            pos++;
        }
    }

    quint8 remainder = checkSum % 103;
    addSymbolCodeInt(remainder, symbols, checkSum);
    addSymbolCodeInt(SYM_Stop, symbols, checkSum);

    QString code = symbols.join("");
    BarCode b;
    for(int i=0;i<code.length();i++)
    {
        QString v = code.at(i);
        b << v.toInt();
    }

    return b;
}
