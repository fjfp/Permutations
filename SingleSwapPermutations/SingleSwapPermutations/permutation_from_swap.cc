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
using Number = factorial_base::Number;
using value_type = Number::value_type;

// Returns a tuple of string positions to be swapped.
// The first argument is the permutation state.
// The second argument is a selector indicating a prefix of the string.
inline swap_indices_type number_to_swap_indices( Number const& number
                                               , unsigned prefix_selector) {

    // Return the tuple with the index to the end of the string as the final
    // element and with a first element as the index to
    // - the first string element, if the selector is odd -OR-
    // - some character indexed by the prefix selector into the permutation
    //   state (1-based)
    return { (prefix_selector & 1) ? 0 : number[prefix_selector] - 1
           , prefix_selector + 1 };
}

// Returns a tuple of string positions to be swapped.
// The argument is the permutation state.
// Increments the permutation state from which the swap indices are extracted.
swap_indices_type permute(Number& permutation_counter) {
    auto index = factorial_base::increment(permutation_counter);
    return number_to_swap_indices(permutation_counter, index);
}
