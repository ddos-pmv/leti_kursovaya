// src/Views/CustomTableWidget.h
#ifndef CUSTOMTABLEWIDGET_H
#define CUSTOMTABLEWIDGET_H

#include <QTableWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QStyleOptionViewItem>
#include <QStyledItemDelegate>

class CustomItemDelegate : public QStyledItemDelegate {
public:
    CustomItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override {
        QStyledItemDelegate::initStyleOption(option, index);
        option->rect.adjust(0, 5, 0, 0);  // Adjust the top margin
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
        QSize size = QStyledItemDelegate::sizeHint(option, index);
        size.setHeight(size.height() + 10);  // Maintain the row height
        return size;
    }
};

class CustomTableWidget : public QTableWidget {
    Q_OBJECT

public:
    explicit CustomTableWidget(QWidget *parent = nullptr) : QTableWidget(parent), lastHoveredRow(-1) {
        setMouseTracking(true);
        setItemDelegate(new CustomItemDelegate(this));

        setStyleSheet(R"(
        QTableWidget {
            border: none;
            padding: 0;
            margin: 0;
            font-size: 14px;
            background-color: transparent;
        }
        QHeaderView::section{
            margin: 0;
            padding: 0;
            border: 0;
            background-color: transparent;
        }
        QHeaderView{
            margin: 0;
            padding: 0;
            background-color: transparent;
        }
        )");
    }

    void initializeBackgroundColors() {
        setInitialBackgroundColor();
    }

protected:
    void mouseMoveEvent(QMouseEvent *event) override {
        QTableWidget::mouseMoveEvent(event);
        int row = rowAt(event->pos().y());
        if (row != lastHoveredRow) {
            if(lastHoveredRow!= -1) setUnHovered(lastHoveredRow);
            if(row != -1) setHovered(row);

            lastHoveredRow = row;
        }
    }

private:
    QBrush unHoveredBg = QColor(47,47,47, 200);
    QBrush hoveredBg = QColor(255, 0, 102);

    QColor hoveredText = Qt::white;
    QColor unHoveredText = QColor(255,255,255,100);

    int lastHoveredRow = -1;

    void setHovered(int row) {
        for(int col = 0; col < columnCount(); ++col) {
            item(row, col)->setBackground(hoveredBg);
            item(row, col)->setTextColor(hoveredText);
        }
    }

    void setUnHovered(int row) {
        for(int col = 0; col < columnCount(); ++col) {
            item(row, col)->setBackground(unHoveredBg);
            item(row, col)->setTextColor(unHoveredText);
        }
    }

    void setInitialBackgroundColor() {
        for (int row = 0; row < rowCount(); ++row) {
            for (int col = 0; col < columnCount(); ++col) {
                if (item(row, col)) {
                    item(row, col)->setBackground(unHoveredBg);
                    item(row, col)->setTextColor(unHoveredText);

                }
            }
        }
    }
};

#endif // CUSTOMTABLEWIDGET_H