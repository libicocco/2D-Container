#include <iostream>
#include "facade.h"

int main(){
    //typedef Container2D<int, std::vector, std::vector> VVI;
    typedef Container2D<int> VVI;
    VVI lalin;
    lalin.push_back(VVI::InnerContT(1,0)); // VVI::InnerContT is just a vector<int>
    lalin.push_back(VVI::InnerContT(2,1));
    lalin.push_back(VVI::InnerContT(3,2));
    lalin.push_back(VVI::InnerContT(4,3));
    lalin.push_back(VVI::InnerContT(5,4));

    for(VVI::twoD_iterator it = lalin.global_begin(); it != lalin.global_end(); ++it)
        std::cout << *it << std::endl;
}
