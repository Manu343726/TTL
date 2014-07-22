/* 
 * File:   algoritm.hpp
 * Author: manu343726
 *
 * Created on 9 de junio de 2014, 14:34
 */

#ifndef ALGORITM_HPP
#define	ALGORITM_HPP

#include "assign.hpp"
#include "utility_functions.hpp"

#include "../Turbo/enable_if.hpp"
#include "../Turbo/function.hpp"
#include "../Turbo/eval.hpp"
#include "../Turbo/utils/assert.hpp"
#include "tuple_iterator.hpp"
#include "zip_iterator.hpp"

#include <tuple>
#include <type_traits>

namespace ttl
{
    namespace impl
    {
        template<typename BEGIN , typename DBEGIN , typename is_end = tml::eval<tml::logical_or<ttl::is_tuple_end_iterator<BEGIN>,
                                                                                                ttl::is_tuple_end_iterator<DBEGIN>
                                                                                               >
                                                                               >
                >
        struct transform_algorithm
        {
            template<typename F , typename END>
            static void execute( BEGIN begin , END end , DBEGIN d_begin , F f )
            {
                if( begin != end )
                {
                    auto next = ttl::assign( d_begin , f(*begin) );

                    ttl::impl::transform_algorithm<decltype(++begin),decltype(++next)>::execute( ++begin , end , ++next , f );
                }
            }
        };
        
        template<typename BEGIN , typename DBEGIN>
        struct transform_algorithm<BEGIN,DBEGIN,tml::true_type>
        {
            template<typename F , typename END>
            static void execute( BEGIN begin , END end , DBEGIN d_begin , F f )
            {}
        };
    }
    
    
    
    
    
    template<typename F , typename BEGIN , typename END , typename DBEGIN>
    void transform( BEGIN begin , END end , DBEGIN d_begin , F f )
    {
        ttl::impl::transform_algorithm<BEGIN,DBEGIN>::execute( begin , end , d_begin , f );
    }
    
    template<typename BEGIN , typename END , typename DBEGIN>
    void copy( BEGIN begin , END end , DBEGIN d_begin )
    {
        ttl::impl::transform_algorithm<BEGIN,DBEGIN>::execute( begin , end , d_begin , ttl::identity{} );
    }
    
    template<typename F , typename BEGIN , typename END , typename DBEGIN>
    void copy_if( BEGIN begin , END end , DBEGIN d_begin , F f )
    {
        if( begin != end )
        {
            if( f( *begin ) )
            {
                auto next = ttl::assign( d_begin , *begin );
                
                copy_if( ++begin , end , ++next , f );
            }
            else
                copy_if( ++begin , end , d_begin , f );
        }
    }
    
    template<typename F , typename END>
    void for_each( END begin , END end , F f )
    {}
    
    template<typename F , typename BEGIN , typename END , TURBO_DISABLE_FUNCTION_IF( ttl::is_tuple_end_iterator<BEGIN> )>
    void for_each( BEGIN begin , END end , F f )
    {
        if( begin != end )
        {
            f( *begin );
            
            ttl::for_each( ++begin , end , f );
        }
    }
    
    template<typename F , typename END , typename E>
    E foldl( END begin , END end , F f , const E& state )
    {
        return state;
    }
    
    template<typename F , typename E , typename BEGIN , typename END , TURBO_DISABLE_FUNCTION_IF( ttl::is_tuple_end_iterator<BEGIN> )>
    E foldl( BEGIN begin , END end , F f , const E& state )
    {
        if( begin != end )
        {
            return ttl::foldl( ++begin , end , f , f(state,*begin) );
        }
        else
            return state;
    }
    
    template<typename F , typename END , typename E>
    E foldr( END begin , END end , F f , const E& state )
    {
        return state;
    }
    
    template<typename F , typename E , typename BEGIN , typename END , TURBO_DISABLE_FUNCTION_IF( ttl::is_tuple_end_iterator<BEGIN> )>
    E foldr( BEGIN begin , END end , F f , const E& state )
    {
        if( begin != end )
        {
            return f( *begin , ttl::foldr( ++begin , end , f , state ) );
        }
        else
            return state;
    }
    
#if __cplusplus > 201103L //If C++14
    template<typename BEGIN , typename END , typename P>
    bool all_of( BEGIN begin , END end , P predicate )
    {
        return ttl::foldl( begin , end , [=]( bool state , const auto& value )
        {
            return state && predicate( value );
        },
        true);
    }
    
    template<typename BEGIN , typename END , typename P>
    bool any_of( BEGIN begin , END end , P predicate )
    {
        return ttl::foldl( begin , end , [=]( bool state , const auto& value )
        {
            return state || predicate( value );
        },
        false);
    }
    
    template<typename BEGIN , typename END , typename P>
    bool none_of( BEGIN begin , END end , P predicate )
    {
        return ttl::foldl( begin , end , [=]( bool state , const auto& value )
        {
            return state && !predicate( value );
        },
        true);
    }
    
    template<typename FIRST1 , typename LAST1 , typename FIRST2 , typename LAST2 , typename E = ttl::equal>
    bool equal( FIRST1 first1 , LAST1 last1 , FIRST2 first2 , LAST2 last2 , E equal = ttl::equal{} )
    {
        return ttl::foldl( ttl::zip( first1 , first2 ) , ttl::zip( last1 , last2 ) , [=]( bool state , const auto& zip )
        {
            return state && equal( std::get<0>( zip ) , std::get<1>( zip ) );
        },
        true);
    }
    
#endif /* C++14 */
    
    namespace impl
    {
        template<typename T , typename F>
        struct transform_result;
        
        template<typename... ARGS , typename F>
        struct transform_result<std::tuple<ARGS...>,F> : 
            public tml::function<std::tuple<decltype( std::declval<F>()( std::declval<ARGS>() ) )...>>
        {};
    }
    
    template<typename TUPLE , typename TRANSFORM>
    using transform_result = tml::eval<ttl::impl::transform_result<TUPLE,TRANSFORM>>;
}

#endif	/* ALGORITM_HPP */

