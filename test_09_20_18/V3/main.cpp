#include "slist.hpp"

int main()
{
    MyList<int> list;
    for (int i = 0; i < 10; ++i)
        list.push_front(i % 3);
    
    // std::cout << list << std::endl;
    // for (MyList<int>::iterator iter = list.begin(); iter != list.end(); ++iter)
        // std::cout << *iter << std::endl;
    
    MyList<int> l2(list);
    l2.push_front(12);
    list.push_front(14);
    
    std::cout << "list" << std::endl << list << std::endl;
    std::cout << "l2" << std::endl << l2 << std::endl;
    
    MyList<int> l3(l2);
    std::cout << "l3" << std::endl << l3 << std::endl;
    
    l3 = list;
    std::cout << "l3" << std::endl << l3 << std::endl;
    return 0;
}