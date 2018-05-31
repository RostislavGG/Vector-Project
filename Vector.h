#include <iostream>
#include <cassert>
#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector
{
public:
    Vector();
    Vector(int _size, T& type);
    Vector(const Vector<T>& other);
    Vector& operator=(const Vector<T>& other);

    void push_back(const T&);
    void pop_back();
    size_t size() const;
    void resize(int);
    void resize(int, T);
    bool empty() const;
    T back() const;
    void clear();
    void increaseSize();
    bool condition(bool(*condition)()) const;
    void remove(int);

    T& operator[](const int) const;
    T& operator[](const int);

    ~Vector();
private:
    std::size_t current_size;
    std::size_t max_size;
    T* elements;

    void copyMembers(const Vector<T>& other)
    {
        current_size = other.current_size;
        max_size = other.max_size;
        elements = new T[max_size];
        for (int i = 0; i < current_size; i++)
        {
            elements[i] = other.elements[i];
        }
    }

};

template <class T>
Vector<T>::Vector()
{
    max_size = 127;
    elements = new T[max_size];
    current_size = 0;
}

template <class T>
Vector<T>::Vector(int _size, T& type)
{
    assert(_size > 0);
    current_size = _size;
    max_size *= 2;
    elements = new T[current_size];
    for (unsigned i = 0; i < current_size; i++)
    {
        elements[i] = type;
    }
}

template <class T>
Vector<T>::Vector(const Vector<T>& other)
{
    copyMembers(other);
}

template <class T>
Vector<T>& Vector<T>::operator = (const Vector<T>& other)
{
    if (this != &other)
    {
        delete[] elements;
        copyMembers(other);
    }
    return *this;
}

template <class T>
Vector<T>::~Vector()
{
    delete[] elements;
}

template <class T>
void Vector<T>::push_back(const T& x)
{
    if (current_size == max_size)
    {
        increaseSize();
    }
    elements[current_size] = x;
    current_size++;
}

template <class T>
void Vector<T>::pop_back()
{
    if (current_size != 0)
    {
        current_size--;
    }
}

template <class T>
std::size_t Vector<T>::size() const
{
    return current_size;
}

template <class T>
void Vector<T>::resize(int newSize)
{
    if (newSize > current_size)
    {
        this->resize(newSize, 0);
    }
    else
    {
        for (int i = 0; i < newSize - current_size; i++)
        {
            this->pop_back();
        }
    }
}

template <class T>
void Vector<T>::resize(int newSize, T with)
{
    if (newSize < current_size)
    {
        this->resize(newSize);
    }
    else
    {
        for (unsigned int i = current_size; i < newSize; i++)
        {
            this->push_back(with);
        }
    }
}

template <class T>
bool Vector<T>::empty() const
{
    if (current_size == 0)
    {
        return true;
    }
    return false;
}

template <class T>
T Vector<T>::back() const
{
    assert(this->size() >= 0);
    return elements[current_size];
}

template <class T>
void Vector<T>::clear()
{
    delete[] elements;
    max_size = 127;
    current_size = 0;
    elements = new T[max_size];
}

template <class T>
void Vector<T>::increaseSize()
{
    T* new_elements = new T[max_size*2];
    max_size *= 2;
    for (int i = 0; i < current_size; i++)
    {
        new_elements[i] = elements[i];
    }
    delete[] elements;
    elements = new_elements;
}

template <class T>
T& Vector<T>::operator[](const int index) const
{
    return elements[index];
}

template <class T>
T& Vector<T>::operator[](const int index)
{
    assert(index > 0 && index < this->size());
    return elements[index];
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& vec)
{
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        out << vec[i] << " ";
    }
    return out;
}

template <class T>
bool Vector<T>::condition(bool(*cond)()) const
{
    if (this->empty())
    {
        return false;
    }
    for (unsigned i = 0; i < current_size; i++)
    {
        if (cond(this[i]))
        {
            return true;
        }
    }
    return false;
}

template <class T>
void Vector<T>::remove(int at)
{
    assert(at > 0 && at <= current_size);
    for (unsigned i = at-1; i < current_size-1; i++)
    {
        elements[i] = elements[i+1];
    }
    pop_back();
}


#endif // VECTOR_H
