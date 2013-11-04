#include "code128item.h"

#include <QPainter>
#include "code128.h"

Code128Item::Code128Item() :
    m_TextVisible(true),
    m_Width(200),
    m_Height(80),
    m_CodeLength(0)
{
}

void Code128Item::setText(const QString &text)
{
    m_Code = Code128::encode(text);
    m_Text = text;

    m_CodeLength = 0;
    for (int i=0;i<m_Code.length();i++)
    {
        m_CodeLength+=m_Code[i];
    }
}

void Code128Item::setWidth(float width)
{
    m_Width = width;
}

void Code128Item::setHeight(float height)
{
    m_Height = height;
}

void Code128Item::setTextVisible(bool visible)
{
    m_TextVisible = visible;
}

void Code128Item::setHighDPI(bool highDPI)
{
    m_HighDPI = highDPI;
}

QRectF Code128Item::boundingRect() const
{
    return QRectF(0,0, m_Width, m_Height);
}

void Code128Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    float lineWidth = m_Width / m_CodeLength;


    /*
     * This code tries to fit the barcode right inside the width. If the code
     * is too long this means that the bar width goes below one pixel. Which in
     * turn means we get no barcode. On printers this is not a problem too fast
     * as they have 600 DPI usually. Screens with 96 DPI run out faster.
     *
     */

    if ( !m_HighDPI )
    {
        lineWidth = qRound(lineWidth);
        if ( lineWidth < 1 )
        {
            lineWidth = 1;
        }
    }


    float fontHeight = painter->fontMetrics().height();

    float left = 0;
    for (int i=0;i<m_Code.length();i++)
    {

        float width = m_Code[i] * lineWidth;

        if ( i % 2 == 0 )
        {
            QRectF bar(left, 0, width, m_Height - fontHeight );
            painter->fillRect(bar, Qt::SolidPattern);
        }

        left+= width;
    }

    if ( m_TextVisible )
    {
        QRectF box(0, m_Height - fontHeight , left, fontHeight);
        painter->drawText(box, m_Text, Qt::AlignHCenter | Qt::AlignVCenter);
    }
}

