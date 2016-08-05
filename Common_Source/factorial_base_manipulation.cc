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

#include"../Common_Include/factorial_base_manipulation.h"
#include<cassert>

namespace factorial_base {

// Increment the factorial base number by 1.
// Returns the index of the last digit altered.
unsigned increment(Number& inout) {

    unsigned i = 0;

    for(auto& value : inout) {

        assert(value <= i + 1);

        // Test limits.
        // If exceeded, adjust the digit value and continue.
        if(++value > i + 1) {
            value = 0;
            ++i;
            continue;
        }

        // Return the last altered digit.
        return i;
    }

    // Convert final carry to a most significant digit.
    inout.push_back(1);

    // Return the last altered digit.
    return unsigned(inout.size()) - 1;
}

}
