// Copyright 2016 Frank Plochan
//
// This file is part of Spellephone.
//
// Spellephone is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Spellephone is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Spellephone.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include<experimental/generator>
#include<initializer_list>
#include<vector>
#include<cassert>
#include<algorithm>
#include<memory>

namespace Spellephone {

// Generates an infinite sequences of consecutive numbers in the range [0..n).
template<typename Base_>
struct Counter {
    using value_type = Base_;
    using generator_type = std::experimental::generator<int>;

    Base_ maximum_;             // The sequence modulus
    bool  wrapped_ { false };   // Indicator that the sequence has wrapped to 0

    Counter(Base_ max): maximum_(max) { }

    // Disallow copy and move
    Counter(Counter const&) = delete;
    Counter(Counter&&) = delete;
    Counter& operator=(Counter const&) = delete;
    Counter& operator=(Counter&&) = delete;

    // Uses Microsoft Visual Studio 2015 "resumable" function, co_yield to
    // enumerate this counter's values.
    generator_type get_generator() {

        // This counter's current value
        value_type i = 0;

        for(;;) {

            // Yield the current value and wait to resume
            co_yield i;

            // On resume, increment current value (mod maximum_) and
            // set flag to true if wrapped to 0, else false.
            if(++i >= maximum_)
                i -= maximum_;
            wrapped_ = i == 0;
        }
    }

    // Test if enumerator wrapped to 0.
    bool didWrap() const { return wrapped_; }
};

// Collection of counters where a permutation is a particular setting of each
// counter in the collection.
template<typename Base_>
struct Counters {
    using counter_type       = Counter<Base_>;
    using counter_type_ptr   = std::unique_ptr<counter_type>;
    using generator_type     = typename counter_type::generator_type;
    using generator_iterator = typename generator_type::iterator;
    using index_coll_type    = std::vector<Base_>;
    using initializer_list   = std::initializer_list<size_t>;

    // Instantiation particular traits.
    // Holds a 3-tuple of dependent types,
    // a Counter<Base_> type with a dependent std::experimental::generator<int>
    // type with a dependent iterator.
    // The generator is moveable and not copyable while it's iterator is
    // copyable.  To maintain the binding between counter and generator, this
    // class maintains a unique pointer to counter.  In order to maintain the
    // consistency of the permutations generated, this class only allows for
    // move construction and move assignment.
    struct Counting_Traits {

        counter_type_ptr       counter_;
        generator_type         generator_;
        generator_iterator     iterator_;

        Counting_Traits(Base_ max)
        : counter_   { new counter_type(max) }
        , generator_ { std::move(counter_->get_generator()) }
        , iterator_  { generator_.begin() }
        { }

        Counting_Traits(Counting_Traits const&) = delete;
        Counting_Traits& operator=(Counting_Traits const&) = delete;

        Counting_Traits(Counting_Traits&& other)
        : counter_   { std::move(other.counter_) }
        , generator_ { std::move(other.generator_) }
        , iterator_  { other.iterator_ }
        {
            other.iterator_ = generator_iterator { nullptr };
        }

        Counting_Traits& operator=(Counting_Traits&& other) {
            if(this != &other) {
                counter_   = std::move(other.counter_);
                generator_ = std::move(other.generator_);
                iterator_  = other.iterator_;
                other.iterator_ = generator_iterator { nullptr };
            }
        }
    };

    using generator_coll_type = std::vector<Counting_Traits>;

    // The collection of counters making up a permutation.
    generator_coll_type counters_;
    index_coll_type     permutation_;   // a specific permutation

    bool                last_permutation_not_reached { true };

    // Constructor
    Counters(initializer_list list);

    // Constructor
    template<typename Iter_>
    Counters(Iter_ first, Iter_ last);

    // Disallow copies and moves.
    // This class is moveable, but not copyable.  For this illustration
    // neither is necessary.
    Counters(Counters const&) = delete;
    Counters(Counters&&) = delete;
    Counters& operator=(Counters const&) = delete;
    Counters& operator=(Counters&&) = delete;

    // Returns a generator of index_coll_type whose iterator yields permutations
    auto next_permutation();
};

// Initialize the counters and first permutation.
template<typename Base_>
Counters<Base_>::Counters(initializer_list list) {
    if(!list.size())
        return;

    counters_.reserve(list.size());
    permutation_.reserve(list.size());

    for(auto len : list) {
        assert(len > 0);
        counters_.emplace_back(Counting_Traits(int(len)));
        permutation_.push_back(0);
    }
}

// Initialize the counters and first permutation.
template<typename Base_> template<typename Iter_>
Counters<Base_>::Counters(Iter_ first, Iter_ last) {
    if(first == last)
        return;

    std::for_each(first, last,
                  [this](auto& item) {
                    auto len = int(item);
                    assert(len > 0);
                    this->counters_.emplace_back(Counting_Traits(len));
                    this->permutation_.push_back(0);
                  });
}

// Returns a generator of index_coll_type whose iterator yields permutations
template<typename Base_>
auto Counters<Base_>::next_permutation() {

    do {

        // return the first permutation already initialized in the constructor.
        co_yield permutation_;

        auto end = counters_.rend();
        auto digit = permutation_.rbegin();

        // Count by adding 1 to the least significant counter and propagating
        // the carry.  Counter<Base_>::didWrap() == true implies the carry.
        for( auto counter = counters_.rbegin()
           ; counter != end
           ; ++counter, ++digit) {

            ++(*counter).iterator_;
            *digit = *(*counter).iterator_;

            if((*counter).counter_->didWrap())
                continue;
            break;
        }

        // Set the do loop's stopping condition when the most significant
        // counter wraps.
        last_permutation_not_reached = !counters_.front().counter_->didWrap();

    } while(last_permutation_not_reached);
}

}
