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

    class ForwardIterator;

    ///Returns a Forward Iterator to
    ///the beginning of our vector
    ///Time - O(1)
    ForwardIterator fbegin()
    {
        return elements;
    }

    ///Returns a Forward Iterator to
    ///the end of our vector
    ///Time - O(1)
    ForwardIterator fend()
    {
        return elements+size();
    }

    class RandomAccessIterator;

    ///Returns a RandomAccessIterator to
    ///the beginning of our vector
    ///Time - O(1)
    RandomAccessIterator begin()
    {
        return elements;
    }

    ///Returns a RandomAccessIterator to
    ///the end of our vector
    ///Time - O(1)
    RandomAccessIterator end()
    {
        return elements+size();
    }


private:
    std::size_t current_size;
    std::size_t max_size;
    T* elements;

    ///Copies the properties of the given vector
    ///onto our own
    ///Time - O(n)
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

public:
    class ForwardIterator
    {
    public:
        ForwardIterator();
        ForwardIterator(T*);
        ForwardIterator(const ForwardIterator&);
        ForwardIterator& operator = (const ForwardIterator&);

        bool operator == (const ForwardIterator&) const;
        bool operator != (const ForwardIterator&) const;
        T& operator * () const;
        ForwardIterator& operator ++ ();
        ForwardIterator operator ++ (int);

        ~ForwardIterator();

    protected:
        T* it;
    };

    class RandomAccessIterator
    {
    public:
        RandomAccessIterator();
        RandomAccessIterator(T*);
        RandomAccessIterator(const RandomAccessIterator&);
        RandomAccessIterator& operator = (const RandomAccessIterator&);

        bool operator == (const RandomAccessIterator&) const;
        bool operator != (const RandomAccessIterator&) const;
        T& operator * () const;
        RandomAccessIterator& operator ++ ();
        RandomAccessIterator operator ++ (int);

        bool operator > (const RandomAccessIterator&) const;
        bool operator < (const RandomAccessIterator&) const;
        bool operator >= (const RandomAccessIterator&) const;
        bool operator <= (const RandomAccessIterator&) const;

        RandomAccessIterator& operator -- ();
        RandomAccessIterator operator -- (int);

        RandomAccessIterator operator + (int);
        RandomAccessIterator operator - (int);

        RandomAccessIterator operator += (int);
        RandomAccessIterator operator -= (int);

        ~RandomAccessIterator();

    private:
        T* it;
    };

};

///Default Constructor for the vector
///Initializes the vector with a max_size
///of 127 and current size of 0
template <class T>
inline Vector<T>::Vector()
{
    max_size = 127;
    elements = new T[max_size];
    current_size = 0;
}

///Constructor with arguments for the vector
///_size - The size of the vector
///type - All elements in the vector have this value
template <class T>
inline Vector<T>::Vector(int _size, T& type)
{
    assert(_size > 0);
    current_size = _size;
    max_size = current_size + 1;
    elements = new T[current_size];
    for (unsigned i = 0; i < current_size; i++)
    {
        elements[i] = type;
    }
}

///Copy Constructor of the vector
template <class T>
inline Vector<T>::Vector(const Vector<T>& other)
{
    copyMembers(other);
}

///Operator = of the vector
///Deletes all the current elements and
///Creates a new vector with current_size and max_size of other
///Copies all the elements of other onto our newly created vector
///O(n) time complexity
template <class T>
inline Vector<T>& Vector<T>::operator = (const Vector<T>& other)
{
    if (this != &other)
    {
        delete[] elements;
        copyMembers(other);
    }
    return *this;
}

///Destructor for the vector
///deletes our elements
template <class T>
inline Vector<T>::~Vector()
{
    delete[] elements;
}

///Adds an element named x to the back of our vector
///If there is no more space we allocate more as seen in lines 192-195
///Average time O(1), Worst case time O(n) where n = max_size+1
template <class T>
inline void Vector<T>::push_back(const T& x)
{
    if (current_size == max_size)
    {
        increaseSize();
    }
    elements[current_size] = x;
    current_size++;
}

///Deletes the last element in our vector if the vector is NOT empty
///Time - O(1)
template <class T>
inline void Vector<T>::pop_back()
{
    if (current_size != 0)
    {
        current_size--;
    }
}

///Returns the current size of our vector
///Time - O(1)
template <class T>
inline std::size_t Vector<T>::size() const
{
    return current_size;
}

///Resizes our vector by a given value if the new size is non negative
///If the new size is bigger than the current size go to 241
///Else pops back the number of elements we want
///Time - O(n)
template <class T>
inline void Vector<T>::resize(int newSize)
{
    assert(newSize >= 0);
    if (newSize > current_size)
    {
        this->resize(newSize, T());
    }
    else
    {
        for (int i = 0; i < current_size - newSize; i++)
        {
            this->pop_back();
        }
    }
}

///Resizes our vector by a given value
///if the new size is bigger than our current one
///adds "newSize" - "current_size" times "with"
///If "newSize" is smaller than "current_size" go to 220
///Time - O(n)
template <class T>
inline void Vector<T>::resize(int newSize, T with)
{
    assert(newSize >= 0);
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

///Checks if our vector is empty
///Returns true if it is
///Returns false if it's not
///Time - O(1)
template <class T>
inline bool Vector<T>::empty() const
{
    if (current_size == 0)
    {
        return true;
    }
    return false;
}

///Returns the last element in our vector if
///the size of our vector is bigger than zero
///Time - O(1)
template <class T>
inline T Vector<T>::back() const
{
    assert(this->size() > 0);
    return elements[current_size];
}

///Deletes all the elements in our vector
///Makes our vector the same as a defaultly constructed vector
///Time - O(1)
template <class T>
inline void Vector<T>::clear()
{
    delete[] elements;
    max_size = 127;
    current_size = 0;
    elements = new T[max_size];
}

///Allocates more memory for our vector
///Creates a new array with a two times bigger capacity
///Copies the content of our old array into our new one
///Deletes the old array
///Our new array is now the one used in the vector
///Time - O(n)
template <class T>
inline void Vector<T>::increaseSize()
{
    T* new_elements = new T[max_size*2];
    max_size *= 2;
    for (unsigned i = 0; i < current_size; i++)
    {
        new_elements[i] = elements[i];
    }
    delete[] elements;
    elements = new_elements;
}

///Returns a constant reference to an element by a given index
///Does that if the index is a valid one
///Time - O(1)
template <class T>
inline T& Vector<T>::operator[](const int index) const
{
    assert(index >= 0 && index < (int)this->size());
    return elements[index];
}

///Returns a reference to an element by a given index
///Does that if the index is a valid one
///Time - O(1)
template <class T>
inline T& Vector<T>::operator[](const int index)
{
    assert(index > 0 && index < (int)this->size());
    return elements[index];
}

///Operator << prints the contents of our vector
///Time - O(n)
template <class T>
inline std::ostream& operator<<(std::ostream& out, const Vector<T>& vec)
{
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        out << vec[i] << " ";
    }
    return out;
}

///Searches the elements of our vector for an element that
///satisfies a given bool function
///Returns true if such an element exists
///false otherwise
///Time - O(n)
template <class T>
inline bool Vector<T>::condition(bool(*cond)()) const
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

///Removes an element by a given index if
///the index is a valid one
///Time - O(n)
template <class T>
inline void Vector<T>::remove(int at)
{
    assert(at > 0 && at <= (int)current_size);
    for (unsigned i = at-1; i < current_size-1; i++)
    {
        elements[i] = elements[i+1];
    }
    pop_back();
}

///Default Constructor for Forward Iterator
///Creates a Forward Iterator pointing to
///the beginning of the arrays "elements"
///Time - O(1)
template <class T>
Vector<T>::ForwardIterator::ForwardIterator()
{
    it = elements;
}

///Constructor with arguments for Forward Iterator
///Creates a Forward Iterator by a given pointer
///Time - O(1)
template <class T>
Vector<T>::ForwardIterator::ForwardIterator(T* _it)
{
    it = _it;
}

///Copy Constructor for Forward Iterator
///Copies a Forward Iterator
///Time - O(1)
template <class T>
Vector<T>::ForwardIterator::ForwardIterator(const ForwardIterator& other)
{
    this->it = other.it;
}

///Operator = for a Forward Iterator
///Time - O(1)
template <class T>
typename Vector<T>::ForwardIterator& Vector<T>::ForwardIterator::operator =(const ForwardIterator& other)
{
    this->it = other.it;
    return *this;
}

///Compares two Forward Iterators and
///returns true if they are equal
///false otherwise
///Time - O(1)
template <class T>
inline bool Vector<T>::ForwardIterator::operator == (const ForwardIterator& other) const
{
    return it == other.it;
}

///Compares two Forward Iterators and
///returns true if they are not equal
///false otherwise
///Time - O(1)
template <class T>
inline bool Vector<T>::ForwardIterator::operator != (const ForwardIterator& other) const
{
    return it != other.it;
}

///Derefernces a Forward Iterator and
///returns the value that the Forward Iterator
///is pointing to
///Time - O(1)
template <class T>
inline T& Vector<T>::ForwardIterator::operator *() const
{
    assert(it != nullptr);
    return *it;
}

///Prefix operator ++
///'Moves' the Forward Iterator to the
///right of our arrays
///Time - O(1)
template <class T>
inline typename Vector<T>::ForwardIterator& Vector<T>::ForwardIterator::operator ++()
{
    it++;
    return *this;
}

///Postfix operator ++
///'Moves' the Forward Iterator to the
///right of our arrays
///Time - O(1)
template <class T>
inline typename Vector<T>::ForwardIterator Vector<T>::ForwardIterator::operator ++(int x)
{
    ForwardIterator f = *this;
    f++;
    return f;
}

///Destructor
///Deletes our pointer
template <class T>
inline Vector<T>::ForwardIterator::~ForwardIterator()
{
    delete it;
}

///Default Constructor
///Creates a pointer to the beginning of the vector
///Time - O(1)
template <class T>
Vector<T>::RandomAccessIterator::RandomAccessIterator()
{
    it = elements;
}

template <class T>
Vector<T>::RandomAccessIterator::RandomAccessIterator(T* _it)
{
    it = _it;
}

template <class T>
Vector<T>::RandomAccessIterator::RandomAccessIterator(const RandomAccessIterator& other)
{
    it = other.it;
}

template <class T>
typename Vector<T>::RandomAccessIterator& Vector<T>::RandomAccessIterator::operator =(const RandomAccessIterator& other)
{
    it = other.it;
    return *this;
}

template <class T>
inline bool Vector<T>::RandomAccessIterator::operator == (const RandomAccessIterator& other) const
{
    return it == other.it;
}

template <class T>
inline bool Vector<T>::RandomAccessIterator::operator != (const RandomAccessIterator& other) const
{
    return it != other.it;
}

template <class T>
inline T& Vector<T>::RandomAccessIterator::operator *() const
{
    assert(it != nullptr);
    return *it;
}

template <class T>
inline typename Vector<T>::RandomAccessIterator& Vector<T>::RandomAccessIterator::operator ++()
{
    it++;
    return *this;
}

template <class T>
inline typename Vector<T>::RandomAccessIterator Vector<T>::RandomAccessIterator::operator ++(int x)
{
    RandomAccessIterator r = *this;
    r+=1;
    return r;
}

template <class T>
inline Vector<T>::RandomAccessIterator::~RandomAccessIterator()
{
    delete it;
}

template <class T>
inline bool Vector<T>::RandomAccessIterator::operator > (const RandomAccessIterator& other) const
{
    return it > other.it;
}

template <class T>
inline bool Vector<T>::RandomAccessIterator::operator < (const RandomAccessIterator& other) const
{
    return it < other.it;
}

template <class T>
inline bool Vector<T>::RandomAccessIterator::operator >= (const RandomAccessIterator& other) const
{
    return it >= other.it;
}

template <class T>
inline bool Vector<T>::RandomAccessIterator::operator <= (const RandomAccessIterator& other) const
{
    return it <= other.it;
}

template <class T>
inline typename Vector<T>::RandomAccessIterator& Vector<T>::RandomAccessIterator::operator --()
{
    it--;
    return *this;
}

template <class T>
inline typename Vector<T>::RandomAccessIterator Vector<T>::RandomAccessIterator::operator --(int x) ///
{
    RandomAccessIterator r = *this;
    r--;
    return r;
}

template <class T>
inline typename Vector<T>::RandomAccessIterator Vector<T>::RandomAccessIterator::operator + (int x)
{
    it += x;
    return it;
}

template <class T>
inline typename Vector<T>::RandomAccessIterator Vector<T>::RandomAccessIterator::operator - (int x)
{
    it -= x;
    return it;
}

template <class T>
inline typename Vector<T>::RandomAccessIterator Vector<T>::RandomAccessIterator::operator += (int x)
{
    it += x;
    return it;
}

template <class T>
inline typename Vector<T>::RandomAccessIterator Vector<T>::RandomAccessIterator::operator -= (int x)
{
    it -= x;
    return it;
}

#endif // VECTOR_H
