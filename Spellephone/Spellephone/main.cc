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

#include"PhoneNumberEnumerator.h"
#include<iostream>
using std::cout;
#include<string>
using std::string;

// Program entry point.
int main(int argc, char** argv) {

    if(2 != argc) {
        std::cerr << "Must supply one argument\n";
        return -1;
    }

    string const phone_number = argv[1];

    cout << phone_number << '\n';

    // Construct the enumerator for the various "spellings" of the phone
    // number provided.
    PhoneNumberEnumerator enumerator(phone_number);

    // Iterate over the "spellings" and send them to cout.
    for(string perm = enumerator.next(); perm.size(); perm = enumerator.next())
        cout << perm << '\n';

    return 0;
}
