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
}

#endif	/* UTILITY_FUNCTIONS_HPP */

