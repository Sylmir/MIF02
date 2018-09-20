#include "slist.hpp"

#include <iterator>

int main()
{
    MyList<int> list;
    for (int i = 0; i < 10; ++i)
        list.push_front(i % 3);
    
    std::cout << "list" << std::endl << list << std::endl;
    
    MyList<int> l2(list);
    l2.push_front(12);
    list.push_front(14);
    
    std::cout << "list (14 en plus)" << std::endl << list << std::endl;
    std::cout << "l2 (12 + copie de list sans le 14)" << std::endl << l2 << std::endl;
    
    MyList<int> l3(l2);
    std::cout << "l3 (copie de l2)" << std::endl << l3 << std::endl;
    
    l3 = list;
    std::cout << "l3 (copie de list)" << std::endl << l3 << std::endl;
    
    MyList<int>::iterator it = l3.begin();
    l3.insert(it, 12);
    l3.insert(it, -11);
    it = l3.begin();
    for (int i = 0; i < 5; i++)
        it++;
    l3.insert(it, -1234);
    std::cout << "l3 après insert (12, -11 list[0], list[1], list[2], -1234, reste de list)" << std::endl << l3 << std::endl;
    
    std::cout << "list à la fin" << std::endl << list << std::endl;
    std::cout << "l2 à la fin" << std::endl << l2 << std::endl;
    std::cout << "l3 à la fin" << std::endl << l3 << std::endl;
    return 0;
}