MD bin
clang.exe -Iinclude -o bin\doublylinkedlist.lib src\DoublyLinkedLists.c -fuse-ld=llvm-lib
clang.exe -Iinclude -o bin\DoublyLists.exe src\DoublyLinkedLists.c -Lbin -l dynarray