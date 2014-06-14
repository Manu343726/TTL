#include <bandit/bandit.h>

#include <algorithm>
#include <vector>
#include <array>
#include <utility>

#include "algoritm.hpp"
#include "tuple_iterator.hpp"
#include ""

using namespace bandit;

go_bandit([](){

    describe("Tuple -> Tuple transformations", []()
    {
        auto input = std::make_tuple( 1 , true , 2.0f , "Hello" );
        
    });

});

int main(int argc, char* argv[])
{
  return bandit::run(argc, argv);
}

