TTL
===

C++11 Tuple Template Library


## Why a tuple algorithms library?

IMHO C++(11) tuples just suck. They are wonderfull to do some usefull tricks, like overloading operators for lexicographical sorting:

    friend bool operator<( const foo& lhs , const foo& rhs )
    {
        return std::tie( lhs.bar , lhs.quux ) < std::tie( rhs.bar , rhs.quux );
    }
    
But when what we need is just a... well, just a tuple; they sucks. Everybody who have worked with C++ tuples know what I mean:

    auto tuple = std::make_tuple( 1 , true , 'a' );

    auto third = std::get<0>( tuple ); //No runtime indexing?
    
    std::cout << tuple << std::endl; // <-- hundreds of template related errors. How horrible and difficult was to overload
                                     //     << to just print "(1,true,a)", isn't?
                                     

## The goal

Some of that issues are inherent to the way C++ tuples work (They are just a library feature based on hard-level template-meta-programming), and others are just lacks on the standard library.  
This library has the purpose of offer some common utilities, workarounds, and features to make the work with C++ tuples easy, avoiding become a "*Reinvent the wheel everyday*" process.  

Many of that features are easy to implement and pretty common. The goal is not to write a so *hot-smarttest C++ tuple library in the world*. The goal is to make the everyday work easy, joining all that tuple tricks and workarounds in one simple and clear library.

## Planned features  

 - **Pretty-printing for tuples**: Happy text-based tuple debugging!
         
         std::cout << std::make_tuple( "hello",23.5f , true ) << std::endl;
         
         > (hello,23.5,true)

 - **`std::tuple_call()` for C++11**: Even if `std::tuple_call()` was added to C++1y, many of us cannot rely on C++1y and still target our projects to C++11. So say goodbye to the indices trick!
 
         int i = ttl::tuple_call( [](int , bool , char){ return 1; } , std::make_tuple(1,true,'a') );
         
    
 - **`<algorithm>`-like algorithms for tuples**: What if we need to transform the elements of a tuple? What if we need to filter some elements of a tuple conditionally? The standard `<algorithm>` library doesn't provide any way. But TTL does!:
 
         auto input = std::make_tuple(1,true,'a');
         std::tuple<std::string,std::string,std::string> output;
         
         ttl::transform( std::begin( input ) , std::end( input ) , std::begin( output ) , std::to_string );
 
   But wait, since C++11 I use lambdas for algorithms always! And C++11 has no polymorphic lambdas support :(. Don't worry, TTL implements `ttl::overloaded_function`, which
   helps a lot:

         ttl::transform( std::begin( input ) , std::end( input ) , std::begin( output ) , ttl::make_overloaded_function(
                         []( int  i ) { return std::string{ "That was an int" }; },
                         []( char c ) { return std::string{ "That was a char" }; },
                         []( bool b ) { return std::string{ "That was a bool" }; } )
                       );

         std::cout << input << " --> " << output << std::endl;


   > (1,true,a) --> (That was an int,That was a char,That was a bool)
   
   Algorithms which take tuples and return tuples, ok. But I don't work with tuples only! What about the classic standard containers?
   Don't worry, TTL takes care of these. The TTL algorithms are dessigned to work with non-tuple iterators too (As input xor output, both non-tuple 
   ranges are not supported. Thats what the STL algorithms are dessigned for, isn't?).  
   So any technique you use with STL algorithms will work with tuples too:

         //Send the contents of a tuple to std::cout!
         ttl::transform( std::begin( tuple ) , std::end( tuple ) , 
                         std::ostream_iterator<std::string>( std::cout , " " ) , 
                         std::to_string 
                       );

         //Copy the contents of a vector to a tuple!
         std::vector<int> v = { 1 , 2 , 3 , 4 };
         std::tuple<int,int,int,int> t;

         ttl::transform( std::begin( v ) , std::end( v ) , std::begin( t ) , []( int i ){ return i*2; } );


Anybody who has more ideas, features, or knows usefull tuple tricks, is free to do suggestions! Please use the issues system.  
