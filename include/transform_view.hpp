/* 
 * File:   transform_view.hpp
 * Author: manu343726
 *
 * Created on 15 de junio de 2014, 16:10
 */

#ifndef TRANSFORM_VIEW_HPP
#define	TRANSFORM_VIEW_HPP

namespace ttl
{
    template<typename ITERATOR , typename TRANSFORM>
    struct transform_view
    {
    public:
        transform_view( const ITERATOR& it  , TRANSFORM t ) :
            _it{ it }
        {}
            
        auto operator*() -> const decltype( _t( *_it ) )&
        {
            return _t( *_it );
        }
        
        auto operator++() -> decltype( ++_it )
        {
            return ++_it;
        }
        
        auto operator--() -> decltype( --_it )
        {
            return --_it;
        }
    private:
        ITERATOR _it;
        std::function<TRANSFORM> _t;
    };
}

#endif	/* TRANSFORM_VIEW_HPP */

