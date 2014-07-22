/* 
 * File:   runtime_tuple_indexer.hpp
 * Author: manu343726
 *
 * Created on 9 de junio de 2014, 21:02
 */

#ifndef RUNTIME_TUPLE_INDEXER_HPP
#define	RUNTIME_TUPLE_INDEXER_HPP

#include <tuple>
#include <array>
#include <numeric>
#include <iterator>

#include "../Turbo/list.hpp"
#include "../Turbo/list_algorithms.hpp"
#include "../Turbo/algorithm.hpp"
#include "../Turbo/utility.hpp"
#include "../Turbo/placeholders.hpp"

using namespace tml::placeholders;

namespace ttl
{
    template<typename... ARGS>
    class runtime_tuple_indexer
    {
    public:
        using tuple_type = std::tuple<ARGS...>;
        using tuple_args = tml::list<ARGS...>;
        using elements_size = tml::transform<tml::lambda<_1 , tml::util::size_of<_1>> , tuple_args>;
        
        runtime_tuple_indexer( const std::tuple<ARGS...>& tuple ) :
            _data{ tuple }
        {}
            
        char* operator[]( std::size_t element_index )
        {
            return &_data.bytes[compute_offset( element_index )];
        }
        
        template<typename T>
        T& operator()( std::size_t element_index , const T& = T{} )
        {
            return *reinterpret_cast<T*>( (*this)[element_index] );
        }
        
    private:
        std::size_t compute_offset( std::size_t element_index ) const
        {
            return std::accumulate( std::begin( tml::to_runtime<elements_size>() ) , 
                                    std::end( tml::to_runtime<elements_size>() ) ,
                                    0
                                  );
        }
        
        union 
        {
            tuple_type tuple;
            std::array<char,sizeof(tuple_type)> bytes;
        } _data;
    };
    
    template<typename... ARGS>
    ttl::runtime_tuple_indexer<ARGS...> make_indexer( const std::tuple<ARGS...>& tuple )
    {
        return { tuple };
    }
}

#endif	/* RUNTIME_TUPLE_INDEXER_HPP */

