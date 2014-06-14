/* 
 * File:   utility_functions.hpp
 * Author: manu343726
 *
 * Created on 12 de junio de 2014, 11:05
 */

#ifndef UTILITY_FUNCTIONS_HPP
#define	UTILITY_FUNCTIONS_HPP

namespace ttl
{
    struct identity
    {
        template<typename T>
        T operator()( const T& v )
        {
            return v;
        }
    };
    
    struct to_string
    {
        template<typename T>
        std::string operator()( const T& val )
        {
            return std::to_string( val );
        }
        
        std::string operator()( const char* str )
        {
            return { str };
        }
    };
}

#endif	/* UTILITY_FUNCTIONS_HPP */

