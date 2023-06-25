#include <iostream>

int main(){
    int a = 0, b = 0 , c = 0;
    for(int i=0;i<1000;i++){
        a = i + 1;
        b = a + 1;
        c = b + 1;
        std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
    }
    return 0;
}