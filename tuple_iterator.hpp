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
#include <stdexcept>
#include <type_traits>
#include <iostream>

#include "Turbo/iterator.hpp"
#include "Turbo/list.hpp"
#include "Turbo/utility.hpp"

namespace ttl
{
    namespace impl
    {
        template<std::size_t INDEX , typename ARGS , bool END = INDEX == ARGS::length>
        class tuple_iterator;
    }
    
    template<std::size_t INDEX , typename... ARGS>
    using tuple_iterator = ttl::impl::tuple_iterator<INDEX,tml::list<ARGS...>>;
    
    namespace impl
    {
        template<std::size_t INDEX , typename... ARGS>
        class tuple_iterator<INDEX,tml::list<ARGS...>,false>
        {
        public:
            static_assert( INDEX < sizeof...(ARGS) , "ERROR: Index out of bounds" );


            using tuple_type = std::tuple<ARGS...>;
            using value_type = typename std::tuple_element<INDEX,tuple_type>::type;
            using index      = std::integral_constant<std::size_t,INDEX>;
            
            static constexpr const bool is_end = false;

            tuple_iterator( tuple_type& tuple ) :
                _tuple_ref{ tuple }
            {}

            ttl::tuple_iterator<INDEX+1,ARGS...> operator++(int)
            {
                return ttl::tuple_iterator<INDEX+1,ARGS...>{ _tuple_ref };
            }

            ttl::tuple_iterator<INDEX-1,ARGS...> operator--(int)
            {
                return ttl::tuple_iterator<INDEX-1,ARGS...>{ _tuple_ref };
            }

            value_type& operator*()
            {
                return std::get<INDEX>( _tuple_ref.get() );
            }

            template<std::size_t LHS_I , typename... LHS_ARGS , std::size_t RHS_I , typename... RHS_ARGS , 
                     typename = typename std::enable_if<!ttl::tuple_iterator<LHS_I,LHS_ARGS...>::is_end &&
                                                        !ttl::tuple_iterator<RHS_I,RHS_ARGS...>::is_end
                                                       >::type
                    >
            friend bool operator==( const ttl::tuple_iterator<LHS_I,LHS_ARGS...>& lhs , const ttl::tuple_iterator<RHS_I,RHS_ARGS...>& rhs )
            {
                return sizeof...(LHS_ARGS) == sizeof...(RHS_ARGS) && LHS_I == RHS_I && lhs._tuple_ref.get() == rhs._tuple_ref.get();
            }
            
            template<std::size_t LHS_I , typename... LHS_ARGS , std::size_t RHS_I , typename... RHS_ARGS , 
                     typename = typename std::enable_if<!ttl::tuple_iterator<LHS_I,LHS_ARGS...>::is_end &&
                                                        !ttl::tuple_iterator<RHS_I,RHS_ARGS...>::is_end
                                                       >::type
                    >
            friend bool operator!=( const ttl::tuple_iterator<LHS_I,LHS_ARGS...>& lhs , const ttl::tuple_iterator<RHS_I,RHS_ARGS...>& rhs )
            {
                return !( lhs == rhs );
            }

        private:
            std::reference_wrapper<tuple_type> _tuple_ref;
        };

        template<std::size_t INDEX , typename... ARGS>
        class tuple_iterator<INDEX,tml::list<ARGS...>,true>
        {
        public:
            
            struct tuple_end_value
            {
                template<typename T>
                tuple_end_value& operator=( const T& )
                {
                    return *this;
                }
                
                friend std::ostream& operator<<( std::ostream& os , const tuple_end_value& )
                {
                    return os;
                }
                
                friend std::istream& operator>>( std::istream& is , tuple_end_value& )
                {
                    return is;
                }
            };
            
            static constexpr const bool is_end = true;
            
            template<typename T>
            tuple_iterator( const T& = tuple_end_value{} )
            {}
            
            
            tuple_iterator operator++(int)
            {
                throw std::out_of_range{""};
            }

            tuple_iterator operator--(int)
            {
                throw std::out_of_range{""};
            }

            tuple_end_value& operator*()
            {
                static tuple_end_value holder;
                
                return holder;
            }

            template<typename IT>
            friend bool operator==( const IT& lhs , const tuple_iterator& rhs )
            {
                return false;
            }
            
            template<typename IT>
            friend bool operator==( const tuple_iterator& lhs , const IT& rhs )
            {
                return false;
            }
            
            friend bool operator==( const tuple_iterator& lhs , const tuple_iterator& rhs )
            {
                return true;
            }
            
            template<typename IT>
            friend bool operator!=( const IT& lhs , const tuple_iterator& rhs )
            {
                return !(lhs == rhs);
            }
            
            template<typename IT>
            friend bool operator!=( const tuple_iterator& lhs , const IT& rhs )
            {
                return !(lhs == rhs);
            }
            
            friend bool operator!=( const tuple_iterator& lhs , const tuple_iterator& rhs )
            {
                return !(lhs == rhs);
            }
        };
    }
    
    
    template<std::size_t INDEX , typename... ARGS>
    ttl::tuple_iterator<INDEX,ARGS...> iterator( std::tuple<ARGS...>& tuple )
    {
        return ttl::tuple_iterator<INDEX,ARGS...>{ tuple };
    }
}

namespace std
{
    template<typename... ARGS>
    ttl::tuple_iterator<0,ARGS...> begin( std::tuple<ARGS...>& tuple )
    {
        return ttl::tuple_iterator<0,ARGS...>{ tuple };
    }
    
    template<typename... ARGS>
    ttl::tuple_iterator<sizeof...(ARGS),ARGS...> end( std::tuple<ARGS...>& tuple )
    {
        return ttl::tuple_iterator<sizeof...(ARGS),ARGS...>{ tuple };
    }
}

#endif	/* ITERATOR_HPP */

