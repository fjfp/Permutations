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

#pragma once

#include<vector>
#include"factorial_base_common.h"

namespace factorial_base {

    // Transform the binary unsigned argument into a factorial base number
    // residing in the Number type argument.
    void to_factorial_base(Number& out, unsigned in);

    // Transform the factorial base number in the argument into a binary
    // unsigned value.
    unsigned from_factorial_base(Number const& in);

}
