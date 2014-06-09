/* 
 * File:   main.cpp
 * Author: manu343726
 *
 * Created on 9 de junio de 2014, 14:17
 */

#include <iostream>
#include <tuple>
#include <string>

#include "algoritm.hpp"
#include "iterator.hpp"


int main() 
{
    auto tuple = std::make_tuple( 1 , 'a' , true );
    std::tuple<std::string,std::string,std::string> dest;
    
    ttl::transform( std::begin(tuple) , std::end(tuple) , std::begin(dest) , std::to_string );
}

