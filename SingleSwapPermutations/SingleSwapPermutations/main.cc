// Copyright 2016 Frank Plochan
//
// This file is part of SingleSwapPermutations.
//
// SingleSwapPermutations is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// SingleSwapPermutations is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SingleSwapPermutations.  If not,
// see <http://www.gnu.org/licenses/>.

#include"permutation_from_swap.h"
using factorial_base::Number;
#include<iostream>
using std::cout;
#include<algorithm>
#include<iterator>
#include<experimental\generator>
#include<string>
using std::string;

// The yielding iterating function.
// Yields the next permutation of a string.
// Completes when the size of the permutation state is less than the
// string size.
auto iterate(string const& in) {
    string result{in};
    auto const string_size = in.size();

    // Initialize the permutation state.
    Number permutation_counter{0};

    for(;;) {

        // Get the string positions to swap.
        auto swap_indices = permute(permutation_counter);

        // Test loop end condition.
        if(permutation_counter.size() >= string_size)
            break;

        std::swap( result[std::get<0>(swap_indices)]
                 , result[std::get<1>(swap_indices)]);

        co_yield result;
    }
}

int main() {

    string to_permute("abcdefg");

    for(auto& permutation : iterate(to_permute)) {

        std::copy(permutation.begin(), permutation.end(),
                  std::ostream_iterator<char>(cout, ""));

        cout << '\n';
    }

    return 0;
}
