/* 
 * File:   algorithm_policies.hpp
 * Author: manu343726
 *
 * Created on 15 de junio de 2014, 18:03
 */

#ifndef ALGORITHM_POLICIES_HPP
#define	ALGORITHM_POLICIES_HPP

#include "Turbo/eval.hpp"
#include "Turbo/enable_if.hpp"
#include "Turbo/function.hpp"
#include "Turbo/type_traits.hpp"

#include <utility>
#include <type_traits>
#include <functional>

namespace ttl
{
    template<typename F , typename D>
    struct illformed_call
    {
        illformed_call( F f , const D& default_value ) :
            _f{ f } ,
            _default{ default_value }
        {}
            
        template<typename... ARGS , typename FF = F , typename = TURBO_ENABLE_IF( tml::is_valid_call<FF,ARGS...> )>
        tml::function_return_type<F> operator()( ARGS&&... args ) const
        {
            return _f( std::forward<ARGS>( args )... );
        }
        
        template<typename... ARGS , typename FF = F , typename = TURBO_DISABLE_IF( tml::is_valid_call<FF,ARGS...> )>
        D operator()( ARGS&&... args ) const
        {
            return _default;
        }
        
    private:
        F _f;
        D _default;
    };
    
    template<typename F , typename D>
    ttl::illformed_call<F,D> make_illformed_call( F f , const D& def )
    {
        return { f , def };
    }
}

#endif	/* ALGORITHM_POLICIES_HPP */

