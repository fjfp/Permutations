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
#include<memory>
#include<string>

// Enumerates the spellings of the phone number supplied.
class PhoneNumberEnumerator {
public:
    PhoneNumberEnumerator(std::string const& phoneNumber);
    ~PhoneNumberEnumerator();

    // Disallow copy and move
    PhoneNumberEnumerator(PhoneNumberEnumerator const&) = delete;
    PhoneNumberEnumerator(PhoneNumberEnumerator&&) = delete;
    PhoneNumberEnumerator& operator=(PhoneNumberEnumerator const&) = delete;
    PhoneNumberEnumerator& operator=(PhoneNumberEnumerator&&) = delete;

    std::string next();
private:

    // Forward declaration of the implementation of this class found in the
    // corresponding source file.
    struct Impl;
    using Impl_ptr = std::unique_ptr<Impl>;
    Impl_ptr impl_;
};

