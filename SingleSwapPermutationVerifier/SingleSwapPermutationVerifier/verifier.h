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

#pragma once
#include<vector>
#include<set>
#include<algorithm>
#include<iterator>
#include<cassert>

// Permutation is recursive.  That is, given a final permutation index list for
// a string of length k-1, one stage of permuting a string of length k can be
// accomplished by permuting the prefix of length k-1.
inline void apply_permutation( std::vector<unsigned>&       inout
                             , std::vector<unsigned> const& in) {

    std::vector<unsigned> work;

    // Permute the prefix of the k-length index list with the contents of the
    // k-1-length index list.
    std::transform( in.begin(), in.end()
                  , std::back_inserter(work)
                  , [&inout](unsigned i) {
                        return inout[i];
                    });

    // The last index of the k-length index list remains unchanged, so copy to
    // the output.
    work.push_back(inout.back());

    inout = std::move(work);
}

// Class to permute an odd length index list.
template<bool ISODD_ = true>
struct verifier {

    // The index list of the permuted k-1-length string (input)
    // The index list of the permuted k-length string (output)
    std::vector<unsigned> previous_permutation_,
                          current_permutation_;

    // Constructor
    verifier(std::vector<unsigned>&& previous)
        : previous_permutation_(std::move(previous)) {
        assert(*std::max_element( previous_permutation_.begin()
                                , previous_permutation_.end())
               < unsigned(previous_permutation_.size()));
    }

    // Create the index list of a permuted k-length string.
    // This accomplished by applying the following steps k times,
    // 1) Swap the first and last indices of the k-length index list.
    //    This is ignored on the first pass.
    // 2) Apply the k-1-length permutation to the prefix of the k-length
    //    index list.
    bool operator()() {

        std::copy( previous_permutation_.begin()
                  , previous_permutation_.end()
                  , std::back_inserter(current_permutation_) );

        current_permutation_.push_back(int(previous_permutation_.size()));

        // At this point the first iteration of the loop described above is
        // effectively completed.

        // Structure to track unique k-length index list suffix.  At the end of
        // this method the cardinality of this object must be k for a verified
        // permutation.
        // NOTE: This might be better served by a bit set. The memory complexity
        //       differs by a constant factor, but the runtime complexity may be
        //       reduced to O(n) from, probably, O(n log n).

        std::set<unsigned> endings;
        unsigned const iterations = unsigned(previous_permutation_.size());
        endings.insert(current_permutation_.back());

        // Apply the remainder of the loop described above.
        for(unsigned i = 0; i < iterations; ++i) {

            std::swap( current_permutation_.front()
                     , current_permutation_.back());

            endings.insert(current_permutation_.back());

            apply_permutation(current_permutation_, previous_permutation_);
        }

        return current_permutation_.size() == endings.size();
    }
};

// Class to permute an even length index list.
template<>
struct verifier<false> {

    // The index list of the permuted k-1-length string (input)
    // The index list of the permuted k-length string (output)
    std::vector<unsigned> previous_permutation_,
                          current_permutation_;

    // Constructor
    verifier(std::vector<unsigned>&& previous)
        : previous_permutation_(std::move(previous)) {
        assert(*std::max_element( previous_permutation_.begin()
                                , previous_permutation_.end())
               < unsigned(previous_permutation_.size()));
    }

    // Create the index list of a permuted k-length string.
    // This accomplished by applying the following steps k times,
    // 1) Swap the i-th and last indices of the k-length index list,
    //    for the i-th invocation of this step.
    //    This is ignored on the first pass.
    // 2) Apply the k-1-length permutation to the prefix of the k-length
    //    index list.
    bool operator()() {

        std::copy( previous_permutation_.begin()
                  , previous_permutation_.end()
                  , std::back_inserter(current_permutation_) );

        current_permutation_.push_back(int(previous_permutation_.size()));

        // At this point the first iteration of the loop described above is
        // effectively completed.

        // Structure to track unique k-length index list suffix.  At the end of
        // this method the cardinality of this object must be k for a verified
        // permutation.
        // NOTE: This might be better served by a bit set. The memory complexity
        //       differs by a constant factor, but the runtime complexity may be
        //       reduced to O(n) from, probably, O(n log n).

        std::set<unsigned> endings;
        unsigned const iterations = unsigned(previous_permutation_.size());
        endings.insert(current_permutation_.back());

        // Apply the remainder of the loop described above.
        for(unsigned i = 0; i < iterations; ++i) {
            std::swap( current_permutation_[i]
                      , current_permutation_.back());
            endings.insert(current_permutation_.back());
            apply_permutation(current_permutation_, previous_permutation_);
        }

        return current_permutation_.size() == endings.size();
    }
};

// Wrapper to select and invoke either of the above structures.
struct permutation_verifier {

    using odd_verifier = verifier<true>;
    using even_verifier = verifier<false>;
    using permutation_type = std::vector<unsigned>;

    permutation_type data_;
    permutation_type result_;

    permutation_verifier(permutation_type&& data): data_(data)
    { }

    bool operator()() {

        bool rc;

        if(data_.size() & 1ULL) {

            auto verifier = even_verifier(std::move(data_));
            if(rc = verifier())
                result_ = std::move(verifier.current_permutation_);

        } else {

            auto verifier = odd_verifier(std::move(data_));
            if(rc = verifier())
                result_ = std::move(verifier.current_permutation_);
        }

        return rc;
    }
};
