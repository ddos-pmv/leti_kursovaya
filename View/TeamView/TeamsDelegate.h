//
// Created by Сергей Перлин on 24.12.2024.
//

#ifndef DRIVERSDELEGATE_H
#define DRIVERSDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "../MainThemeVars.h"

class TeamsDelegate : public QStyledItemDelegate {
public:
    explicit TeamsDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        // Извлекаем данные
        QString property1 = index.data(Qt::UserRole + 2).toString();
        QString property2 = index.data(Qt::UserRole + 3).toString();
        QString property3 = QString::number(index.data(Qt::UserRole + 4).toInt());
        // QString property4 = QString::number(index.data(Qt::UserRole + 5).toInt());

        // Подготовка
        painter->save();
        QRect rect = option.rect;

        // Выбор цвета фона в зависимости от состояния
        QColor backgroundColor;
        if (option.state & QStyle::State_Selected) {
            backgroundColor = MainTheme::SidebarSelectedBackgroundColor;
        } else if (option.state & QStyle::State_MouseOver) {
            backgroundColor = MainTheme::SidebarSelectedBackgroundColor;
        } else {
            backgroundColor = MainTheme::SidebarHoverBackgroundColor;
        }

        painter->fillRect(rect, backgroundColor);

        // Отрисовка текста
        QFont font = option.font;
        font.setPointSize(12);
        painter->setFont(font);

        int width = rect.width() / 3;
        QRect nameRect(rect.left(), rect.top(), width, rect.height());
        QRect ageRect(nameRect.right(), rect.top(), width, rect.height());
        QRect teamRect(ageRect.right(), rect.top(), width, rect.height());
        // QRect pointsRect(teamRect.right(), rect.top(), width, rect.height());

        QColor textColor;
        if (option.state & QStyle::State_Selected) {
            textColor = MainTheme::SidebarSelectedTextColor;
        } else if (option.state & QStyle::State_MouseOver) {
            textColor = MainTheme::SidebarSelectedTextColor;
        } else {
            textColor = MainTheme::SidebarHoverTextColor;
        }

        painter->setPen(textColor);

        painter->drawText(nameRect, Qt::AlignCenter, property1);
        painter->drawText(ageRect, Qt::AlignCenter, property2);
        painter->drawText(teamRect, Qt::AlignCenter, property3);
        // painter->drawText(pointsRect, Qt::AlignCenter, property4);

        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        Q_UNUSED(index);
        return QSize(option.rect.width(), MainTheme::RowHeight);
    }
};

#endif //DRIVERSDELEGATE_H
