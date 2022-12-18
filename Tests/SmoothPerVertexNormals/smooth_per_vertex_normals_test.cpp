#include <SmoothPerVertexNormals/utils.h>

#include <iostream>

using namespace utils;

int main()
{
    vec3 first(10.0, 12.0, 0.0);
    vec3 second(0.0, 0.0,  13.4);

    vec3 etalon(10.0, 12.0, 13.4);

    vec3 third = first + second;

    std::cout << "Third vector magnitude -> " << third.magnitude() << std::endl;

    if(third == etalon)
    {
        std::cout << "PASSED" << std::endl;
    }


    return 0;
}
