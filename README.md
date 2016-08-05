# What's This

This is the root directory for some expolorations into permutations.  While this
may not be an exciting topic in general, it becomes a bit more so when
enumerating permutations by use of the [Factorial Number System]
(https://en.wikipedia.org/wiki/Factorial_number_system),

![Factorial Numbers](/imgs/factorial_summation.png)

# What's Here

Visual Studio 2015 C++ projects in,

- [LexicographicPermutations](https://github.com/fjfp/Permutations/tree/master/LexicographicPermutations)

Generates permutations of a given string lexicographically.  This is
accomplished with help of the Factorial Number System.  Permutations are
returned using VC++ 2015's experimental (as of this date) `co_yield`
instruction.

- [SingleSwapPermutations](https://github.com/fjfp/Permutations/tree/master/SingleSwapPermutations)

Generates permutations of a given string non-lexicographically.  This is
accomplished with help of the Factorial Number System.  Permutations are
returned using VC++ 2015's experimental (as of this date) `co_yield`
instruction.

- [SingleSwapPermutationVerifier](https://github.com/fjfp/Permutations/tree/master/SingleSwapPermutationVerifier)

Verifies that a string can have its permutations successfully enumerated by
exchanging the position of only two positions within the string for each
permutation.

- [Spellephone](https://github.com/fjfp/Permutations/tree/master/Spellephone)

An implementation of a interview question to "spell" out a given phone number by
enumerating all permutations of the phone number with digits replaced by letters
found on the phone buttons, where applicable.  Uses nested `co_yield`
instructions from VC++ 2015's experimental library.

# What License

All projects and files fall under the GNU General Public License version 3.0 or
above.  A copy of this license is found in each project's root folder.
