MD bin
clang.exe -Iinclude -o bin\dynarray.lib src\dynarray_refactored.c -fuse-ld=llvm-lib
clang.exe -Iinclude -o bin\dynarray02.exe src\dynarray_refactored.c -Lbin -l dynarray