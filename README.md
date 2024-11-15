# OS-Group-16
Run `make` to build the code; run `chash` to test it.

```sh
prompt> make
prompt> ./chash
```

notes:  the main function prints out the number of lock acquisitions/releases accounting
        for the 1 anticipated grab/release from the ensuing print call that happens after it.
        
Our delete only makes one lock grab/release.

Deletes are not guaranteed to execute after searches, or after any particular insert.
You get it whenever it happens, good luck.

The names should be at most 70 characters long in the commands file.
        
AI was used to generate the code used to parse input from the input file. 
