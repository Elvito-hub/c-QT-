#include "delegate.h"

Delegate::Delegate(QObject *parent):
    QStyledItemDelegate(parent)
{

}
void Delegate::initStyleOption(QStyleOptionViewItem *option,
                             const QModelIndex &index) const
{
    QStyledItemDelegate::initStyleOption(option, index);

    if(index.column()==3&&index.data()<5&&index.data()!="")
    {
        option->backgroundBrush = QBrush(QColor().fromRgba(qRgb(255, 122, 102)));
    }else if(index.column()==3&&index.data()>=5&&index.data()!=""){
        option->backgroundBrush = QBrush(QColor().fromRgba(qRgb(116, 219, 120)));
    }

}
