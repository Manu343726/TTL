/* 
 * File:   assign.hpp
 * Author: manu343726
 *
 * Created on 11 de junio de 2014, 21:08
 */

#ifndef ASSIGN_HPP
#define	ASSIGN_HPP

namespace ttl
{
    template<typename ITERATOR , typename VALUE>
    ITERATOR& assign( ITERATOR& i , const VALUE& value )
    {
        *i = value;
        
        return i;
    }
}

#endif	/* ASSIGN_HPP */

