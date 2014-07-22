/* 
 * File:   overloaded_function.hpp
 * Author: manu343726
 *
 * Created on 10 de junio de 2014, 1:29
 */

#ifndef OVERLOADED_FUNCTION_HPP
#define	OVERLOADED_FUNCTION_HPP

#include <functional>
#include <type_traits>

#include "../Turbo/eval.hpp"
#include "../Turbo/type_traits.hpp"

namespace ttl
{   
    template<typename F , typename... Fs>
    struct overloaded_function : public F , public Fs...
    {
        overloaded_function( F f , Fs... fs ) :
            F{ f },
            Fs{ fs }...
        {}
    };
    
    namespace impl
    {
        template<typename T>
        struct deduce_type;
        
        //Non-const operator():
        template<typename C , typename R , typename... ARGS>
        struct deduce_type<R(C::*)(ARGS...)> 
        {
            using result = std::function<R(ARGS...)>;
        };

        //Const operator()
        template<typename C , typename R , typename... ARGS>
        struct deduce_type<R(C::*)(ARGS...) const>
        {
            using result = std::function<R(ARGS...)>;
        };
       
        //For function pointers
        template<typename R , typename... ARGS>
        std::function<R(ARGS...)> function_signature( R(*)(ARGS...) );
        
        //For functors (Lambdas included)
        template<typename F>
        tml::eval<deduce_type<decltype(&F::operator())>> function_signature( F );
    }
    
    template<typename F , typename... Fs>
    auto make_overloaded_function( F f , Fs... fs ) -> ttl::overloaded_function<decltype( ttl::impl::function_signature( f ) ) , decltype( ttl::impl::function_signature( fs ) )...>
    {
        return { f , fs... };
    }
}

namespace tml
{
    namespace impl
    {
        template<typename F , typename... Fs>
        struct is_functor<ttl::overloaded_function<F,Fs...>> : public tml::function<tml::true_type>
        {};
    }
}

#endif	/* OVERLOADED_FUNCTION_HPP */
