#include <bandit/bandit.h>

#include <algorithm>
#include <vector>
#include <array>
#include <utility>

#include "algoritm.hpp"
#include "tuple_iterator.hpp"
#include "utility_functions.hpp"
#include "overloaded_function.hpp"

using namespace bandit;

go_bandit([](){

    describe("Tuple -> Tuple transformations", []()
    {
        auto input = std::make_tuple( 1u , true , -1 , "Hello" );
        
        it("Identity tuple -> tuple transformation (ttl::copy())" , [&]()
        {
            decltype(input) output;
            
            ttl::copy( std::begin( input ) , std::end( input ) , std::begin( output ) );
            AssertThat(output,Equals(input)); 
        });
        
        it("Monomorphic tuple -> tuple transformation (ttl::transform() using ttl::to_string functor)" , [&]()
        {
            ttl::transform_result<decltype(input),ttl::to_string> output;
            
            ttl::transform( std::begin( input ) , std::end( input ) , std::begin( output ) , ttl::to_string{} );
            AssertThat(output,Equals(std::make_tuple(std::string{"1"},
                                                     std::string{"1"},
                                                     std::string{"-1"},
                                                     std::string{"Hello"}
                                                    )
                                    )
                      ); 
        });
        
        it("Polymorphic tuple -> tuple transformation (ttl::transform() using custom overloaded functor)" , [&]()
        {
            auto transform = ttl::make_overloaded_function( []( unsigned int i ){ return i % 2 == 0; }  ,
                                                            []( bool i ){ return static_cast<int>(i); } ,
                                                            []( int i ){ return std::to_string(i); }    ,
                                                            []( const char* i ){ return std::strlen( i ); } );
                                                            
            ttl::transform_result<decltype(input),decltype(transform)> output;
            AssertThat( (std::is_same<std::tuple<bool,int,std::string,std::size_t>,decltype(output)>::value) , Equals(true) );
            
            ttl::transform( std::begin( input ) , std::end( input ) , std::begin( output ) , transform );
            AssertThat(output,Equals(std::make_tuple(false,
                                                     1,
                                                     std::string{"-1"},
                                                     5
                                                    )
                                    )
                      ); 
        });
    });
    
    
    describe("Tuple -> STL transformations", []()
    {
        auto input = std::make_tuple( 1u , true , -1 , "Hello" );
        
        it("Monomorphic tuple -> STL transformation (ttl::transform() using ttl::to_string functor with std::vector as output)" , [&]()
        {
            std::vector<std::string> output;
            
            ttl::transform( std::begin( input ) , std::end( input ) , std::back_inserter( output ) , ttl::to_string{} );
            
            AssertThat( output , Equals(std::vector<std::string>{ { "1" , "1" , "-1" , "Hello" } }) );
        });
    });
    
    
    describe("STL -> tuple transformations", []()
    {
        std::istringstream input{ "1 2 3 4" };
        std::tuple<int,int,int,int> output;
        
        it("Monomorphic STL -> tuple transformation (ttl::copy() using std::istream_iterator as input" , [&]()
        {
            ttl::copy( std::istream_iterator<int>( input ) , std::istream_iterator<int>() , std::begin( output ) );
            
            AssertThat( output , Equals( std::make_tuple( 1 , 2 , 3 , 4 ) ) );
        });
    });
});

int main(int argc, char* argv[])
{
  return bandit::run(argc, argv);
}

