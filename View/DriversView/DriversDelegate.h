//
// Created by Сергей Перлин on 24.12.2024.
//

#ifndef DRIVERSDELEGATE_H
#define DRIVERSDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "../MainThemeVars.h"

class DriversDelegate : public QStyledItemDelegate {
public:
    explicit DriversDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        // Извлекаем данные
        QString name = index.data(Qt::UserRole + 2).toString();
        int age = index.data(Qt::UserRole + 3).toInt();
        QString team = index.data(Qt::UserRole + 4).toString();
        int points = index.data(Qt::UserRole + 5).toInt();

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

        int width = rect.width() / 4;
        QRect nameRect(rect.left(), rect.top(), width, rect.height());
        QRect ageRect(nameRect.right(), rect.top(), width, rect.height());
        QRect teamRect(ageRect.right(), rect.top(), width, rect.height());
        QRect pointsRect(teamRect.right(), rect.top(), width, rect.height());

        QColor textColor;
        if (option.state & QStyle::State_Selected) {
            textColor = MainTheme::SidebarSelectedTextColor;
        } else if (option.state & QStyle::State_MouseOver) {
            textColor = MainTheme::SidebarSelectedTextColor;
        } else {
            textColor = MainTheme::SidebarHoverTextColor;
        }

        painter->setPen(textColor);

        painter->drawText(nameRect, Qt::AlignCenter, name);
        painter->drawText(ageRect, Qt::AlignCenter, QString::number(age));
        painter->drawText(teamRect, Qt::AlignCenter, team);
        painter->drawText(pointsRect, Qt::AlignCenter, QString::number(points));

        painter->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        Q_UNUSED(index);
        return QSize(option.rect.width(), MainTheme::RowHeight);
    }
};

#endif //DRIVERSDELEGATE_H
