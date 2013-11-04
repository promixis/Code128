#ifndef CODE128ITEM_H
#define CODE128ITEM_H

#include <QGraphicsItem>
#include "code128.h"

class Code128Item : public QGraphicsItem
{
    float m_Width;
    float m_Height;
    QString m_Text;
    Code128::BarCode m_Code;
    int m_CodeLength;

public:
    Code128Item();
    void setText ( const QString & text );
    void setWidth( float width );
    void setHeight( float height );

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * widget);
};
#endif // CODE128ITEM_H
