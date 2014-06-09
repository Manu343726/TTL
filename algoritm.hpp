/* 
 * File:   algoritm.hpp
 * Author: manu343726
 *
 * Created on 9 de junio de 2014, 14:34
 */

#ifndef ALGORITM_HPP
#define	ALGORITM_HPP

namespace ttl
{
    template<typename F , typename BEGIN , typename END , typename DBEGIN>
    void transform( BEGIN begin , END end , DBEGIN d_begin , F f )
    {
        if( begin != end )
        {
            *d_begin = f( *begin );
            
            transform( begin++ , end , d_begin++ );
        }
    }
}

#endif	/* ALGORITM_HPP */

