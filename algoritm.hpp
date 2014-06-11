/* 
 * File:   algoritm.hpp
 * Author: manu343726
 *
 * Created on 9 de junio de 2014, 14:34
 */

#ifndef ALGORITM_HPP
#define	ALGORITM_HPP

#include "assign.hpp"

#include "Turbo/enable_if.hpp"
#include "Turbo/function.hpp"
#include "Turbo/eval.hpp"
#include "Turbo/utils/assert.hpp"

#include <tuple>
#include <type_traits>

namespace ttl
{
    namespace impl
    {
        template<typename BEGIN , typename is_end = tml::Bool<BEGIN::is_end>>
        struct transform_algorithm
        {
            template<typename F , typename END , typename DBEGIN>
            static void execute( BEGIN begin , END end , DBEGIN d_begin , F f )
            {
                if( begin != end )
                {
                    auto next = ttl::assign( d_begin , f(*begin) );

                    ttl::impl::transform_algorithm<decltype(begin++)>::execute( begin++ , end , next++ , f );
                }
            }
        };
        
        template<typename BEGIN>
        struct transform_algorithm<BEGIN,tml::true_type>
        {
            template<typename F , typename END , typename DBEGIN>
            static void execute( BEGIN begin , END end , DBEGIN d_begin , F f )
            {}
        };
    }
    
    template<typename F , typename BEGIN , typename END , typename DBEGIN>
    void transform( BEGIN begin , END end , DBEGIN d_begin , F f )
    {
        ttl::impl::transform_algorithm<BEGIN>::execute( begin , end , d_begin , f );
    }
    
    
    
    template<typename F , typename BEGIN , typename END , typename DBEGIN>
    void copy_if( BEGIN begin , END end , DBEGIN d_begin , F f )
    {
        if( begin != end )
        {
            if( f( *begin ) )
            {
                auto next = ttl::assign( d_begin , *begin );
                
                copy_if( begin++ , end , next++ , f );
            }
            else
                copy_if( begin++ , end , d_begin , f );
        }
    }
    
    template<typename F , typename END>
    void for_each( END begin , END end , F f )
    {}
    
    template<typename F , typename BEGIN , typename END , TURBO_DISABLE_FUNCTION_IF( tml::Bool<BEGIN::is_end> )>
    void for_each( BEGIN begin , END end , F f )
    {
        if( begin != end )
        {
            f( *begin );
            
            ttl::for_each( begin++ , end , f );
        }
    }
    
    template<typename F , typename END , typename E>
    E foldl( END begin , END end , F f , const E& state )
    {
        return state;
    }
    
    template<typename F , typename E , typename BEGIN , typename END , TURBO_DISABLE_FUNCTION_IF( tml::Bool<BEGIN::is_end> )>
    E foldl( BEGIN begin , END end , F f , const E& state )
    {
        if( begin != end )
        {
            return ttl::foldl( begin++ , end , f , f(state,*begin) );
        }
        else
            return state;
    }
    
    template<typename F , typename END , typename E>
    E foldr( END begin , END end , F f , const E& state )
    {
        return state;
    }
    
    template<typename F , typename E , typename BEGIN , typename END , TURBO_DISABLE_FUNCTION_IF( tml::Bool<BEGIN::is_end> )>
    E foldr( BEGIN begin , END end , F f , const E& state )
    {
        if( begin != end )
        {
            return f( *begin , ttl::foldr( begin++ , end , f , state ) );
        }
        else
            return state;
    }
    
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

