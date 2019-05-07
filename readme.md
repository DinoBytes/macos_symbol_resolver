# Symbol Resolver for macOS

If you've ever tried and failed to load a non-publicly exported symbol in macOS via `dlsym()` or similar only to have it epically fail, this code is meant to help with that.

## Acknowledgements and Licensing

The code in this repo is largely a mashup of works by [Jonathan Levin](http://newosxbook.com) and various StackOverflow posts. While not intentionally copied, the code in this repo is extremely similar to the aforementioned resources. All credit for the discovery and publication of these methods belongs to them.

Additionally, this code makes use of the CoreSymbolication Private Framework provided by Apple that is built into macOS.

This framework was long ago reversed by [Mountain Storm](https://github.com/mountainstorm). The [headers](https://github.com/mountainstorm/CoreSymbolication) they reversed are used in this repo.

## Example Usage

An example use case has been provided via example.c. This example finds the symbol for `LSServerMain()` -- the main routine for the LaunchServices framework -- and runs it. While this isn't the most robust or functionally complete test case, it should accurately demonstrate usage.

I personally have a habit of copying necessary frameworks to my working directory. For this example, copy `/System/Library/PrivateFrameworks/CoreSymbolication.framework/CoreSymbolication` to your working directory. Compile via `clang example.c symbol_resolver.c CoreSymbolication -o test_me`.

The example output will load the `LaunchServices` framework via `dlopen()`, find the symbol for `LSServerMain()`, and then run the function.

Output:
```
dinobytes at hostname in ~/dev/macos_symbol_resolver
$ ls
CoreSymbolication   CoreSymbolication.h example.c           readme.md           symbol_resolver.c   symbol_resolver.h

dinobytes at hostname in ~/dev/macos_symbol_resolver
$ clang example.c symbol_resolver.c CoreSymbolication -o test_me

dinobytes at hostname in ~/dev/macos_symbol_resolver
$ ./test_me
[+] Resolving symbols... Done
Symbol resides at:  0x7fff4778098d

^C
```

If you'd rather not copy and manage frameworks yourself, you're free to copy `CoreSymbolication.h` for the `CoreSymbolication.framework` directory, though you may need to disable SIP. To compile this way, you'll want to use something like `clang -F/System/Library/PrivateFrameworks/ -framework CoreSymbolication example.c symbol_resolver.c -o test_me`.
