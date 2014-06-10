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
#include "tuple_call.hpp"
#include "runtime_tuple_indexer.hpp"
#include "overloaded_function.hpp"

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

struct hey
{
    void operator()( int i ) const
    {
        std::cout << "Hey, an int! " << i << std::endl;
    }
    
    void operator()( char i ) const
    {
        std::cout << "Hey, a char! " << i << std::endl;
    }
    
    void operator()( bool i ) const
    {
        std::cout << "Hey, a bool! " << std::boolalpha << i << std::endl;
    }
};


void f( const std::string& a , const std::string& b , const std::string& c )
{
    std::cout << a + b + c << std::endl;
}


auto hey2 = ttl::make_overloaded_function( [&](int  i){ std::cout << "Hey, an int! " << i << std::endl; } ,
                                           [&](char i){ std::cout << "Hey, a char! " << i << std::endl; } ,
                                           [&](bool i){ std::cout << "Hey, a bool! " << std::boolalpha << i << std::endl; } );
int main() 
{
    auto tuple = std::make_tuple( 1 , 'a' , true );
    std::tuple<std::string,std::string,std::string> dest;
    auto numbers = std::make_tuple( 1,2,3,4,5,6,7,8,9 );
    
    auto indexer = ttl::make_indexer( numbers );
    
    ttl::transform( std::begin(tuple) , std::end(tuple) , std::begin(dest) , to_string{} );
    
    std::cout << "(" << std::boolalpha
              << std::get<0>( dest ) << "," 
              << std::get<1>( dest ) << "," 
              << std::get<2>( dest ) << ")" << std::endl;
    
    ttl::tuple_call( f , dest );
    
    ttl::for_each( std::begin( tuple ) , std::end( tuple ) , hey2 );
    
    std::cout << ttl::foldl( ttl::iterator<2>( numbers ) , ttl::iterator<7>( numbers ) ,
                             []( int e , int x )
                             {
                                 return e + x;
                             } ,
                             0
                           ) << std::endl;
                             
    std::cout << indexer(0,int{}) << std::endl;
}

