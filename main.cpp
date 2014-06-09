/* 
 * File:   main.cpp
 * Author: manu343726
 *
 * Created on 9 de junio de 2014, 14:17
 */

#include <iostream>
#include <tuple>
#include <string>
#include <sstream>

#include "algoritm.hpp"
#include "tuple_iterator.hpp"

struct to_string
{
    template<typename T>
    std::string operator()( const T& v ) const
    {
        std::stringstream ss;
        
        ss << std::boolalpha << v;
        
        return ss.str();
    }
};

int main() 
{
    auto tuple = std::make_tuple( 1 , 'a' , true );
    std::tuple<std::string,std::string,std::string> dest;
    
    ttl::transform( std::begin(tuple) , std::end(tuple) , std::begin(dest) , to_string{} );
    
    std::cout << "(" << std::boolalpha
              << std::get<0>( dest ) << "," 
              << std::get<1>( dest ) << "," 
              << std::get<2>( dest ) << ")" << std::endl;
}

