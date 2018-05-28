#include <iostream>
#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector
{
public:
    Vector();
    Vector(const Vector<T>& other);
    Vector& operator=(const Vector<T>& other);

    void push_back(const T&);
    void pop_back();
    size_t size() const;
    void resize(int newSize);
    bool empty() const;
    T back() const;
    void clear();
    void increaseSize();

    T operator[](const int) const;


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
        elements[current_size] = nullptr;
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
    if (current_size == 0)
    {
        std::cerr << "The vector is empty" << std::endl;
    }
    return elements[current_size-1];
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
    max_size = max_size*2 + 1;
}

template <class T>
T Vector<T>::operator[](const int index) const ///Needs errors
{
    if (index > current_size || index < 0)
    {
        std::cerr << "Index out of range of the vector size";
    }
    else
    {
        return elements[index];
    }
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


#endif // VECTOR_H
