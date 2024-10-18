//
// Created by Сергей Перлин on 04.10.2024.
//

#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QVector>

template<typename T>
class IController {
public:
    virtual ~IController() = default;
    virtual QVector<T> all() = 0;

};

#endif //ICONTROLLER_H
