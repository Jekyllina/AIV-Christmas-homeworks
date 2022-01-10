MD bin
clang.exe -Iinclude -o bin\linkedlist.lib src\LinkedLists_refactored.c -fuse-ld=llvm-lib
clang.exe -Iinclude -o bin\Lists.exe src\LinkedLists_refactored.c -Lbin -l linkedlist