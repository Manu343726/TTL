/* 
 * File:   algoritm.hpp
 * Author: manu343726
 *
 * Created on 9 de junio de 2014, 14:34
 */

#ifndef ALGORITM_HPP
#define	ALGORITM_HPP

#include "Turbo/enable_if.hpp"


namespace ttl
{
    template<typename F , typename BEGIN , typename END , typename DBEGIN>
    void transform( BEGIN begin , END end , DBEGIN d_begin , F f )
    {
        if( begin != end )
        {
            *d_begin = f( *begin );
            
            ttl::transform( begin++ , end , d_begin++ , f );
        }
    }
    
    template<typename F , typename BEGIN , typename END , typename DBEGIN>
    void copy_if( BEGIN begin , END end , DBEGIN d_begin , F f )
    {
        if( begin != end )
        {
            if( f( *begin ) )
            {
                *d_begin = *begin;
                
                copy_if( begin++ , end , d_begin++ , f );
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
    
    
}

#endif	/* ALGORITM_HPP */

