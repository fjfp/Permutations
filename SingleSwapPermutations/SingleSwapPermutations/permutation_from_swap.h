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

#pragma once

#include"../../Common_Include/factorial_base_manipulation.h"
#include<tuple>
using swap_indices_type = std::tuple< factorial_base::Number::value_type
                                    , factorial_base::Number::value_type >;

// Return a tuple containing the indices of a string to swap with the argument
// being the current state of the permutations of the string.
swap_indices_type permute(factorial_base::Number& permutation_counter);
