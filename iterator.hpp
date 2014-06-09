/* 
 * File:   iterator.hpp
 * Author: manu343726
 *
 * Created on 9 de junio de 2014, 14:18
 */

#ifndef ITERATOR_HPP
#define	ITERATOR_HPP

#include <tuple>
#include <functional>
#include <iterator>

namespace ttl
{
    namespace impl
    {
        template<std::size_t INDEX , typename... ARGS , bool END = INDEX == sizeof...(ARGS)>
        class tuple_iterator;

        template<std::size_t INDEX , typename... ARGS>
        class tuple_iterator<INDEX,ARGS...,false>
        {
        public:
            static_assert( INDEX < sizeof...(ARGS) , "ERROR: Index out of bounds" );


            using tuple_type = std::tuple<ARGS...>;
            using value_type = typename std::tuple_element<INDEX,tuple_type>::type;
            using index      = std::integral_constant<std::size_t,INDEX>;

            tuple_iterator( tuple_type& tuple ) :
                _tuple_ref{ tuple }
            {}

            tuple_iterator<INDEX+1,ARGS...> operator++(int)
            {
                return tuple_iterator<INDEX+1,ARGS...>{ _tuple_ref };
            }

            tuple_iterator<INDEX-1,ARGS...> operator--(int)
            {
                return tuple_iterator<INDEX-1,ARGS...>{ _tuple_ref };
            }

            template<std::size_t I = INDEX , typename = typename std::enable_if<(I<sizeof...(ARGS))>::type>
            value_type& operator*()
            {
                return std::get<INDEX>( _tuple_ref );
            }

            template<std::size_t LHS_I , typename... LHS_ARGS , std::size_t RHS_I , typename... RHS_ARGS>
            friend bool operator==( const tuple_iterator<LHS_I,LHS_ARGS...>& lhs , const tuple_iterator<RHS_I,RHS_ARGS...>& rhs )
            {
                return sizeof...(LHS_ARGS) == sizeof...(RHS_ARGS) && LHS_I == RHS_I && lhs == rhs;
            }

            template<std::size_t LHS_I , typename... LHS_ARGS , std::size_t RHS_I , typename... RHS_ARGS>
            friend bool operator<( const tuple_iterator<LHS_I,LHS_ARGS...>& lhs , const tuple_iterator<RHS_I,RHS_ARGS...>& rhs )
            {
                return sizeof...(LHS_ARGS) == sizeof...(RHS_ARGS) && LHS_I < RHS_I && lhs == rhs;
            }

        private:
            std::reference_wrapper<tuple_type> _tuple_ref;
        };

        template<std::size_t INDEX , typename... ARGS>
        class tuple_iterator<INDEX,ARGS...,true>
        {

        };
    }
}

namespace std
{
    template<typename... ARGS>
    ttl::tuple_iterator<0,ARGS...> begin( std::tuple<ARGS...>& tuple )
    {
        ttl::tuple_iterator<0,ARGS...>{ tuple };
    }
    
    template<typename... ARGS>
    ttl::tuple_iterator<sizeof...(ARGS),ARGS...> end( std::tuple<ARGS...>& tuple )
    {
        ttl::tuple_iterator<sizeof...(ARGS)-1,ARGS...>{ tuple };
    }
}

#endif	/* ITERATOR_HPP */

