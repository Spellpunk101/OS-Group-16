# OS-Group-16
Run `make` to build the code; run `chash` to test it.

```sh
prompt> make
prompt> ./chash
```
Notes:

The main function prints out the number of lock acquisitions/releases accounting
for the 1 anticipated grab/release from the ensuing print call that happens after it.
        
Our delete only makes one lock grab/release.

Deletes are not guaranteed to execute after searches, or after any particular insert.
You get it whenever it happens, good luck.

The names should be at most 50 characters long in the commands file, with total instruction command not exceeding 70 characters.
        
AI was used to generate the code used to parse input from the input file.
This code was modified from static array allocation to dynamic array allocation by us humans.

AI was also used for the Makefile but is was Google's new AI Overview tool.
I just searched how to properly structure a Makefile and that was one of the results.
I decided to just try it out and compare it to other Makefile structures I found.
It worked decently and required less changes than other Makefile formats that I found so I decided to use it.
