// Copyright 2016 Frank Plochan
//
// This file is part of LexicographicPermutations.
//
// LexicographicPermutations is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// LexicographicPermutations is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LexicographicPermutations.  If not,
// see <http://www.gnu.org/licenses/>.

#include"../../Common_Include/factorial_base_manipulation.h"
using factorial_base::Number;
#include"lexicographic_permutation.h"
using std::experimental::generator;
using std::string;
#include<algorithm>
#include<iterator>

// Generate a permutation of the first argument dictated by the second
// argument.
string generate_permutation(string const& str, Number const& state) {

    string chars{str},              // Copy of the string to be permuted
           result;                  // The permuted string to be returned

    // Convert the factorial base number in argument two into a permutation
    // of argument one.
    std::transform( state.rbegin()
                  , state.rend()
                  , std::back_inserter(result)
                  , [&](unsigned i) {

                      auto value = chars[i];

                      chars.erase(chars.begin() + i);

                      return value;
                    });


    return result + chars;
}

// Return a yield generator enumerating the permutations of the
// string provided.
generator<string> lexicographic_permutation(string const& in) {

    size_t const string_size{in.size()};

    // Initialize a permutation state.
    Number state;
    std::fill_n(std::back_inserter(state), string_size - 1, 0U);

    for(;;) {

        // Set state to the next permutation.
        factorial_base::increment(state);

        // The loop ends when this is true.
        if(state.size() >= string_size)
            break;

        // Yield the permutation corresponding to the current permutation state.
        co_yield generate_permutation(in, state);
    }
}
