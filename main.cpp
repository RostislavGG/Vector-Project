#include <iostream>
#include <Vector.h>

bool modulo(int &x)
{
    if (x % 999 == 0)
        return true;
    return false;
}

int main()
{

    Vector<int> v;
    for (int i = 0; i < 20; i++)
    {
        v.push_back(i);
    }
    for(Vector<int>::RandomAccessIterator it = v.begin(); it != v.end(); it++)
    {
        std::cout<<*it<<" ";
    }
    std::cout << std::endl;
    for(Vector<int>::RandomAccessIterator it = v.begin(); it != v.end(); ++it)
    {
        std::cout<<*it<<" ";
    }
    std::cout << std::endl;
    for(Vector<int>::RandomAccessIterator it = v.begin(); it != v.end(); it+=2)
    {
        std::cout<<*it<<" ";
    }
    std::cout << std::endl;
    for(Vector<int>::RandomAccessIterator it = v.begin(); it < v.end(); it = it + 3)
    {
        std::cout<<*it<<" ";
    }
    std::cout << std::endl;
    for(Vector<int>::RandomAccessIterator it = v.end()-1; it != v.begin()-1; it--)
    {
        std::cout<<*it<<" ";
    }
    std::cout << std::endl;
    for(Vector<int>::RandomAccessIterator it = v.end()-1; it != v.begin()-1; --it)
    {
        std::cout<<*it<<" ";
    }
    std::cout << std::endl;
    for(Vector<int>::RandomAccessIterator it = v.end()-1; it > v.begin()-1; it-=3)
    {
        std::cout<<*it<<" ";
    }
    std::cout << std::endl;
    for(Vector<int>::RandomAccessIterator it = v.end()-1; it > v.begin()-1; it = it - 2)
    {
        std::cout<<*it<<" ";
    }
    std::cout << std::endl;


    Vector<int> v2(5, 100);
    std::cout << v2 << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < 1000; i++)
    {
        v2.push_back(i);
    }
    std::cout << v2 << std::endl;
    std::cout << std::endl;

    std::cout << v2.condition(modulo) << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < 5; i++)
    {
        v2.remove(0);
    }
    std::cout << v2 << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < 500; i++)
    {
        v2.pop_back();
    }

    std::cout << v2 << std::endl;
    std::cout << std::endl;

    v2.resize(10);
    std::cout << v2 << std::endl;
    std::cout << std::endl;

    v2.resize(15, 5);
    std::cout << v2 << std::endl;
    std::cout << std::endl;

    std::cout << v2.size() << std::endl;
    std::cout << std::endl;

    for (unsigned i = 0; i < v2.size(); i++)
    {
        v2[i] = i;
    }

    std::cout << v2 << std::endl;
    std::cout << std::endl;

    std::cout << v2.size() << " - " << v2.capacity() << std::endl << std::endl;

    v2.shrink_to_fit();
    std::cout << v2 << std::endl;
    std::cout << std::endl;

    std::cout << v2.size() << " - " << v2.capacity() << std::endl << std::endl;


    Vector<int>::RandomAccessIterator it = v2.begin();
    Vector<int>::RandomAccessIterator it2 = v2.end();

    if (it < it2)
    {
        std::cout << "OK1" << std::endl;
    }
    if (it2 > it)
    {
        std::cout << "OK2" << std::endl;
    }
    if (it != it2)
    {
        std::cout << "OK3" << std::endl;
    }
    if (it == v2.begin())
    {
        std::cout << "OK4" << std::endl;
    }
    if (it <= it2)
    {
        std::cout << "OK5" << std::endl;
    }
    if (it2 >= it)
    {
        std::cout << "OK6" << std::endl;
    }


    return 0;
}
