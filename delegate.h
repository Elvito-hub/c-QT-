#ifndef DELEGATE_H
#define DELEGATE_H

#include<QModelIndex>
#include<QStyledItemDelegate>
#include<QPainter>

class Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit Delegate(QObject *parent = 0);
    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;
};

#endif // DELEGATE_H
