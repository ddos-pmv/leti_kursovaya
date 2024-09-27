//
// Created by Сергей Перлин on 27.09.2024.
//

#ifndef MODEL_H
#define MODEL_H
template<typename T>
class IModel {
public:
    virtual ~IModel() = default;
    virtual bool add(const T &a) = 0;
    virtual T* getById(int id) = 0;
    virtual bool remove(int id) = 0;
};



#endif //MODEL_H
