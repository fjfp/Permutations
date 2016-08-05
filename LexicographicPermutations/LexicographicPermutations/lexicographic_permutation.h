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

#pragma once
#include<string>
#include<experimental\generator>

// Return a yield generator enumerating the permutations of the
// string provided.
std::experimental::generator<std::string>
lexicographic_permutation(std::string const& in);
