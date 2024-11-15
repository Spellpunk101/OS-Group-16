# OS-Group-16
Run `make` to build the code; run `chash` to test it.

```sh
prompt> make
prompt> ./chash
```

notes:  the main function prints out the number of lock aquisitions/releases accounting
        for the 1 anticipated grab/release from the ensuing print call that happens after it.
        Our delete only makes one lock grab/release.
