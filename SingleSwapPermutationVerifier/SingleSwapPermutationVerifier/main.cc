// Copyright 2016 Frank Plochan
//
// This file is part of SingleSwapPermutationVerifier.
//
// SingleSwapPermutationVerifier is free software: you can redistribute it
// and/or modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// SingleSwapPermutationVerifier is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with SingleSwapPermutationVerifier.  If not,
// see <http://www.gnu.org/licenses/>.

#include"verifier.h"
using permutation_type = permutation_verifier::permutation_type;
#include<iostream>
using std::cout;

// Attempts to verify that strings up to and including a specified length will
// have their permutations correctly enumerated.
// NOTE: Verification is successful for all strings of length up to and
//       including 1000.
bool loop_to_size(unsigned size) {

    size_t length = size_t(size);

    // This is the index set of the final permutation of a string of size one
    // less than the current size.  It is initialized to the index list of the
    // final permutation of a three item string.
    permutation_type previous{2, 1, 0};

    while(previous.size() <= length) {

        // Create the verifier object with the index list of the previous
        // length string.
        permutation_verifier verifier(std::move(previous));

        // Invoke the verifier returning false if the verification fails.
        if(verifier())
            previous = std::move(verifier.result_);
        else {
            cout << "Verification failed for length "
                 << (previous.size() + 1) << '\n';
            return false;
        }
    }

    // Return successful verification of correct permutation enueration of all
    // strings to a given size.
    return true;
}

// Program Entry Point
// Invoke the verification loop reporting success when appropriate.
int main() {

    static int unsigned const top = 10000;

    if(loop_to_size(top))
        cout << "Verified thru permutation of " << top << " elements.\n";
    return 0;
}
