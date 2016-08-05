// Copyright 2016 Frank Plochan
//
// This file is part of the Factorial Base Component.
//
// The Factorial Base Component is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// The Factorial Base Component is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with The Factorial Base Component.  If not,
// see <http://www.gnu.org/licenses/>.

#include"../Common_Include/factorial_base_conversions.h"
#include<numeric>
#include<cassert>

namespace factorial_base {

// Transform the binary unsigned argument into a factorial base number
// residing in the Number type argument.
void to_factorial_base(Number& out, unsigned in) {

    out.clear();
    
    // Compute each d_i in
    // d_1 * 1! + d_2 * 2! + d_3 * 3! + ...
    // appending each d_i to the Number type argument supplied.
    for(unsigned i = 2; in; ++i) {

        auto value = in % i;
        in /= i;

        out.push_back(value);
    }
}

// Transform the factorial base number in the argument into a binary
// unsigned value.
unsigned from_factorial_base(Number const& in) {

    unsigned base = unsigned(in.size()) + 1;

    // Evaluate the factorial base number
    // d_1 * 1! + d_2 * 2! + d_3 * 3! + ... + d_k * k!
    // using Horner's Rule.
    unsigned result = std::accumulate( in.rbegin()
                                     , in.rend()
                                     , 0U
                                     , [&base](unsigned sum, unsigned value) {
                                           return sum * base-- + value;
                                       });

    // Return the resulting evaluation.
    return result;
}

}
