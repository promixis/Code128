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

QRectF Code128Item::boundingRect() const
{
    return QRectF(0,0, m_Width, m_Height);
}

void Code128Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    float lineWidth = m_Width / m_CodeLength;

    // we need to round here as the widths are
    // required to be quite precise. Rounding
    // in the rendering system will through off
    // the widths of the bars if we don't start
    // with integers.

    lineWidth = qRound(lineWidth);

    float left = 0;
    for (int i=0;i<m_Code.length();i++)
    {

        float width = m_Code[i] * lineWidth;

        if ( i % 2 == 0 )
        {
            QRectF bar(left, 0, width, m_TextVisible ? m_Height * .8 : m_Height);
            painter->fillRect(bar, Qt::SolidPattern);
        }

        left+= width;
    }

    if ( m_TextVisible )
    {
        QRectF box(0, m_Height * 0.8, left, m_Height * 0.2);
        painter->drawText(box, m_Text, Qt::AlignHCenter | Qt::AlignVCenter);
    }
}

