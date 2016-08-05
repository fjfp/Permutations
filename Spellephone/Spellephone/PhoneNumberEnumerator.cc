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

#include"Spellephone.h"
#include "PhoneNumberEnumerator.h"
using std::string;
using std::vector;
using std::unique_ptr;
#include<cctype>
using std::isdigit;
#include<iterator>
#include<type_traits>

// Copy the digits from argument in to argument out.  Non-digit characters in
// argument in are ignored
inline void stripNondigits(string& out, string const& in) {
    std::copy_if(in.begin(), in.end(), std::back_inserter(out),
                 [](string::value_type ch) {
                     return isdigit(ch);
                 });
}

// Implementation of the phone number enumerator.  A separate implementation
// relieves the consumer of having to carry along the baggage in Spellephone.h
// and of even knowing about the coroutines being used.
struct PhoneNumberEnumerator::Impl {

    // Each string indexed by i (0 <= i <= 9) holds the letters found on a phone
    // button numbered i.
    static string const button_letters[];

    // Type name helpers
    using Counters_type = Spellephone::Counters<int>;
    using Counters_ptr = unique_ptr<Counters_type>;

    // C++ likes an instantiation to which it applies decltype.  So, use the age
    // old trick of casting 0 to a pointer of the desired type and...
    // PRESTO - an instantiation of said type (with severe limitations).
#   define decltype_hack ((Counters_type*)0)
    using permutation_generator = decltype(decltype_hack->next_permutation());
#   undef decltype_hack

    // The permuter of indices (into button_letters)
    Counters_ptr counters_{nullptr};

    // The std::experimental::generator bound to counters_
    permutation_generator generator_;

    // The std::experimental::generator::iterator over the generator, above
    permutation_generator::iterator iterator_{nullptr};

    string const& phone_number_;        // the incoming phone number

    Impl(string const& phoneNumber);    // the constructor
    string next();                      // the enumerating method
};

string const PhoneNumberEnumerator::Impl::button_letters[] =
{          "0"
,  "1",   "abc", "def"
,  "ghi", "jkl", "mno"
, "pqrs", "tuv", "wxyz" };

// Convert a character digit to binary
template<typename T>
inline int t2index(T ch) {
    return int(ch - T('0'));
}

// Construct the implementation
PhoneNumberEnumerator::Impl::Impl(string const& phoneNumber)
: phone_number_(phoneNumber) {

    // Strip the non-digits from the phone number.
    string all_digits;
    stripNondigits(all_digits, phone_number_);

    // Create a vector of sizes, one for each digit.  Each size is the count
    // of characters found on the phone button for the specified digit.
    // Buttons with no characters use the respective digit as it's only
    // character.
    vector<size_t> sizes;
    std::transform( all_digits.begin(), all_digits.end()
                  , std::back_inserter(sizes)
                  , [this](decltype(all_digits)::value_type ch) {
                        return button_letters[t2index(ch)].size();
                    });

    // Create the counters from the sizes for each digit.
    // Get the coroutine generator and it's associated iterator.
    counters_ = Counters_ptr(new Counters_type(sizes.begin(), sizes.end()));
    generator_ = std::move(counters_->next_permutation());
    iterator_ = generator_.begin();
}

// Genereate the next permutation.
string PhoneNumberEnumerator::Impl::next() {

    // Return an empty string once enumeration is completed.
    if(iterator_ == generator_.end())
        return string();

    // Transformation aid to convert digits to the current permutation's value
    // for a digit's position within the phone number.
    struct transformer {
        // The button definitions from the containing class.
        string const*          buttons;

        // The current permutation (based on the phone number with non-digits
        // removed).
        decltype((*iterator_)) permutation;

        // The index into permutation corresponding to the character being
        // transformed by operator().
        int                    i { 0 };

        // Return the character for the current index into the phone number.
        // Non-digits return themselves.
        // Digits index the button definitions which are indexed by the
        // corresponding permutation element indexed by i.
        char operator()(string::value_type ch) {
            return isdigit(ch) ? buttons[t2index(ch)][permutation[i++]]
                               : ch;
        }

        // Constructor
        transformer(string const* buttons, decltype((permutation)) perm)
        : buttons(buttons), permutation(perm)
        { }
    };

    // Transform the phone number to an alphabetization of itself as defined by
    // the current permutation.
    string result;
    std::transform( phone_number_.begin(), phone_number_.end()
                  , std::back_inserter(result)
                  , transformer(button_letters, *iterator_) );

    // Access the next permutation or end-of-permutations.
    ++iterator_;

    // Return the permutation just transformed.
    return result;
}

// Implementation wrapper class definitions.
PhoneNumberEnumerator::PhoneNumberEnumerator(string const& phoneNumber):
impl_{Impl_ptr{new Impl(phoneNumber)}}
{ }

PhoneNumberEnumerator::~PhoneNumberEnumerator() { }

string PhoneNumberEnumerator::next() {
    return impl_->next();
}
