#include "slist.hpp"

int main()
{
    MyList<int> list;
    for (int i = 0; i < 10; ++i)
        list.push_front(i % 3);
    
    // std::cout << list << std::endl;
    for (MyList<int>::iterator iter = list.begin(); iter != list.end(); ++iter)
        std::cout << *iter << std::endl;
    
    return 0;
}