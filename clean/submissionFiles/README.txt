I was having issues with trailing spaces causing label lookup in my label store to cause it to fail. Also some of my regex's were acting wonky when labels would have names like L4_x because it wasn't flexible/rigid enough to match it or make it fail (POSIX RegExp's arent that good :/) but in any case I think I ironed out all those bugs. adder, allops, and bit_masks all worked for this version. Didn't have time to test the rest.

Feel free to email me with any questions or concerns about my implementation:
lipfordc@vt.edu