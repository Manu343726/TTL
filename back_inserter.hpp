/* 
 * File:   back_inserter.hpp
 * Author: manu343726
 *
 * Created on 10 de junio de 2014, 13:21
 */

#ifndef BACK_INSERTER_HPP
#define	BACK_INSERTER_HPP

#include <tuple>

#include "tuple_iterator.hpp"

namespace ttl
{
    template<typename... ARGS>
    class back_inserter_iterator
    {
    public:
        using tuple_type = std::tuple<ARGS...>;
        
        back_inserter_iterator() = default;
        
        back_inserter_iterator( const tuple_type& tuple ) :
            _data{ tuple }
        {}
        
        tuple_type& tuple() 
        {
            return _data;
        }
    private:
        tuple_type _data;
    };
    
    template<typename... ARGS , typename T>
    back_inserter_iterator<ARGS...,T> assign( back_inserter_iterator<ARGS...>& lhs , const T& rhs )
    {
        return { std::tuple_cat( lhs.tuple() , std::make_tuple( rhs ) ) };
    }
    
    template<typename... ARGS>
    back_inserter_iterator<ARGS...> back_inserter( const std::tuple<ARGS...>& tuple )
    {
        return { tuple };
    }
    
    back_inserter_iterator<> back_inserter()
    {
        return { std::make_tuple() };
    }
}

#endif	/* BACK_INSERTER_HPP */

