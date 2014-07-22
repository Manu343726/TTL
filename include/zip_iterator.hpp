/* 
 * File:   zip_iterator.hpp
 * Author: manu343726
 *
 * Created on 22 de julio de 2014, 14:14
 */

#ifndef ZIP_ITERATOR_HPP
#define	ZIP_ITERATOR_HPP

#include <tuple>
#include <functional>

#include "tuple_call.hpp"

#include "Turbo/algorithm.hpp"

namespace ttl
{
    namespace impl
    {
        template<typename ITs , typename VALUE_TYPES , typename is_end>
        struct zip_iterator;
    }
    
    template<typename... ITs>
    using zip_iterator = ttl::impl::zip_iterator<tml::list<ITs...>,tml::list<typename ITs::value_type...>,tml::any<tml::lazy<ttl::is_tuple_end_iterator>,tml::list<ITs...>>>;
    
    namespace impl
    {   
        template<typename... ITs , typename... VALUE_TYPES>
        struct zip_iterator<tml::list<ITs...>,tml::list<VALUE_TYPES...>,tml::false_type>
        {
            template<typename T>
            using vt = typename T::value_type;
            using value_type = std::tuple<VALUE_TYPES...>;
            using reference  = std::tuple<std::reference_wrapper<VALUE_TYPES>...>;

        private:
            std::tuple<ITs...> _its;

            template<std::size_t... indices>
            ttl::zip_iterator<decltype(++(std::declval<ITs>()))...> 
            increment( tml::size_t_list<indices...> )
            {
                return { (++(std::get<indices>( _its )))... };
            }

            template<std::size_t... indices>
            reference deref( tml::size_t_list<indices...> )
            {
                return std::make_tuple( std::ref(*std::get<indices>(_its))... );
            }

            template<std::size_t... indices>
            value_type deref( tml::size_t_list<indices...> ) const
            {
                return std::make_tuple( (*std::get<indices>(_its))... );
            }     

        public:        
            template<typename... ARGS>
            zip_iterator( ARGS&&... iterators ) :
                _its{ std::forward<ARGS>( iterators )... }
            {}

            auto operator++() -> decltype( increment( tml::size_t_range<0,sizeof...(ITs)>{} ) )
            {
                return increment( tml::size_t_range<0,sizeof...(ITs)>{} );
            }

            reference operator*()
            {
                return deref( tml::size_t_range<0,sizeof...(ITs)>{} );
            }

            value_type operator*() const
            {
                return deref( tml::size_t_range<0,sizeof...(ITs)>{} );
            } 
            
            template<typename... LHS_ITs , typename... RHS_ITs , 
                     TURBO_SFINAE_ANY( DISABLE_IF( ttl::impl::is_tuple_end_iterator<ttl::zip_iterator<LHS_ITs...>> ),
                                       DISABLE_IF( ttl::impl::is_tuple_end_iterator<ttl::zip_iterator<RHS_ITs...>> )
                                     )
                    >
            friend bool operator==( const ttl::zip_iterator<LHS_ITs...>& lhs , const ttl::zip_iterator<RHS_ITs...>& rhs )
            {
                return lhs._its == rhs._its;
            }
            
            template<typename... LHS_ITs , typename... RHS_ITs ,
                     TURBO_SFINAE_ANY( DISABLE_IF( ttl::impl::is_tuple_end_iterator<ttl::zip_iterator<LHS_ITs...>> ),
                                       DISABLE_IF( ttl::impl::is_tuple_end_iterator<ttl::zip_iterator<RHS_ITs...>> )
                                     )
                    >
            friend bool operator!=( const ttl::zip_iterator<LHS_ITs...>& lhs , const ttl::zip_iterator<RHS_ITs...>& rhs )
            {
                return !(lhs == rhs);
            }
        };
        
        template<typename... ITs , typename... VALUE_TYPES>
        class zip_iterator<tml::list<ITs...>,tml::list<VALUE_TYPES...>,tml::true_type>
        {
        public:
            struct value_type{};
            struct reference{};
            
            struct tuple_end_value
            {
                template<typename T>
                tuple_end_value& operator=( const T& )
                {
                    return *this;
                }
                
                friend std::ostream& operator<<( std::ostream& os , const tuple_end_value& )
                {
                    return os;
                }
                
                friend std::istream& operator>>( std::istream& is , tuple_end_value& )
                {
                    return is;
                }
            };
            
            static constexpr const bool is_end = true;
            
            template<typename... ARGS>
            zip_iterator( ARGS&&... )
            {}
            
            
            zip_iterator operator++()
            {
                return *this;
            }

            zip_iterator operator--()
            {
                return *this;
            }

            tuple_end_value& operator*() const
            {
                static tuple_end_value holder;
                
                return holder;
            }
            
            tuple_end_value& operator*()
            {
                static tuple_end_value holder;
                
                return holder;
            }

            template<typename IT>
            friend bool operator==( const IT& lhs , const zip_iterator& rhs )
            {
                return false;
            }
            
            template<typename IT>
            friend bool operator==( const zip_iterator& lhs , const IT& rhs )
            {
                return false;
            }
            
            friend bool operator==( const zip_iterator& lhs , const zip_iterator& rhs )
            {
                return true;
            }
            
            template<typename IT>
            friend bool operator!=( const IT& lhs , const zip_iterator& rhs )
            {
                return !(lhs == rhs);
            }
            
            template<typename IT>
            friend bool operator!=( const zip_iterator& lhs , const IT& rhs )
            {
                return !(lhs == rhs);
            }
            
            friend bool operator!=( const zip_iterator& lhs , const zip_iterator& rhs )
            {
                return !(lhs == rhs);
            }
        };
        
        template<typename... ITs>
        struct is_tuple_end_iterator<ttl::zip_iterator<ITs...>> : public tml::function<tml::any_of<tml::lazy<ttl::impl::is_tuple_end_iterator>,tml::list<ITs...>>>
        {};
    }
    
    
    template<typename... ITs>
    ttl::zip_iterator<typename std::decay<ITs>::type...> zip( ITs&&... iterators )
    {
        return { std::forward<ITs>( iterators )... };
    }
}

#endif	/* ZIP_ITERATOR_HPP */

