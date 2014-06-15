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
#include <vector>

#include "algoritm.hpp"
#include "tuple_iterator.hpp"
#include "tuple_call.hpp"
#include "runtime_tuple_indexer.hpp"
#include "overloaded_function.hpp"
//#include "back_inserter.hpp"

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
                             
                  
    std::vector<std::string> output_vector;
    std::vector<int> vector = { 11 , 22 , 33 , 44 };
    
    ttl::transform( std::begin( vector ) , std::end( vector ) , std::begin( numbers ) , []( int i ){ return 2*i;  } ); 
    ttl::transform( std::begin( tuple ) , std::end( tuple ) , std::back_inserter( output_vector ) , to_string{} );
    ttl::transform( std::begin( tuple ) , std::end( tuple ) , std::ostream_iterator<std::string>( std::cout , "|" ) , to_string{} );
    
    
    for( const auto& str : output_vector )
        std::cout << std::endl << str;
    
        std::cout << std::endl << "(" << std::boolalpha
              << std::get<0>( numbers ) << "," 
              << std::get<1>( numbers ) << "," 
              << std::get<2>( numbers ) << ")" << std::endl;
}

