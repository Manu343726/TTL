/* 
 * File:   static_if.hpp
 * Author: manu343726
 *
 * Created on 15 de junio de 2014, 18:40
 */

#ifndef STATIC_IF_HPP
#define	STATIC_IF_HPP

#define STATIC_IF( cond , true_ , false_ )

template<typename COND>
struct static_if
{
    void operator()() const
    {
        true_();
    }
};

template<>
struct static_if<tml::false_type>
{
    void operator()() const
    {
        false_();
    }
};

#endif	/* STATIC_IF_HPP */

