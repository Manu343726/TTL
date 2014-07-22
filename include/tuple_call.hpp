/* 
 * File:   tuple_call.hpp
 * Author: manu343726
 *
 * Created on 9 de junio de 2014, 17:22
 */

#ifndef TUPLE_CALL_HPP
#define	TUPLE_CALL_HPP

#include "../Turbo/integral_lists.hpp"
#include "../Turbo/basic_types.hpp"

#include <tuple>
#include <utility>

namespace ttl
{
    namespace impl
    {
        template<typename F , typename... ARGS , typename... INDICES>
        auto tuple_call( F f , const std::tuple<ARGS...>& tuple , tml::list<INDICES...> ) -> decltype( f( std::get<INDICES::value>( tuple )... ) )
        {
            return f( std::get<INDICES::value>( tuple )... );
        }
    }
    
    
    template<typename F , typename... ARGS>
    auto tuple_call( F f , const std::tuple<ARGS...>& tuple ) -> decltype( ttl::impl::tuple_call( f , tuple , tml::size_t_range<0,sizeof...(ARGS)>{} ) )
    {
        return ttl::impl::tuple_call( f , tuple , tml::size_t_range<0,sizeof...(ARGS)>{} );
    }
}

#endif	/* TUPLE_CALL_HPP */

