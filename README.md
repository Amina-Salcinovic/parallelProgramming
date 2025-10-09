# parallel-programming
(base) student@itcenter-lab128:~/Desktop/parallel-programing-amina$ make valgrind
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./memory_demo
==7770== Memcheck, a memory error detector
==7770== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==7770== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==7770== Command: ./memory_demo
==7770== 
==7770== Invalid write of size 4
==7770==    at 0x1091C6: main (main.c:7)
==7770==  Address 0x4a9e068 is 0 bytes after a block of size 40 alloc'd
==7770==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7770==    by 0x109185: main (main.c:5)
==7770== 
==7770== Conditional jump or move depends on uninitialised value(s)
==7770==    at 0x1091F4: main (main.c:9)
==7770==  Uninitialised value was created by a stack allocation
==7770==    at 0x109169: main (main.c:3)
==7770== 
==7770== Invalid read of size 4
==7770==    at 0x1091EF: main (main.c:9)
==7770==  Address 0x4a9e068 is 0 bytes after a block of size 40 alloc'd
==7770==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7770==    by 0x109185: main (main.c:5)
==7770== 
==7770== 
==7770== HEAP SUMMARY:
==7770==     in use at exit: 40 bytes in 1 blocks
==7770==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
==7770== 
==7770== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==7770==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==7770==    by 0x109185: main (main.c:5)
==7770== 
==7770== LEAK SUMMARY:
==7770==    definitely lost: 40 bytes in 1 blocks
==7770==    indirectly lost: 0 bytes in 0 blocks
==7770==      possibly lost: 0 bytes in 0 blocks
==7770==    still reachable: 0 bytes in 0 blocks
==7770==         suppressed: 0 bytes in 0 blocks
==7770== 
==7770== For lists of detected and suppressed errors, rerun with: -s
==7770== ERROR SUMMARY: 14 errors from 4 contexts (suppressed: 0 from 0)


I changed the loop condition from (int i = 0; i<=10; i++) to (int i = 0; i<10; i++) because we tried to access the elemnt with index which does not exist
Also the variable ipos is used before assigninf it a value, so I initialize the variable the right way. 





(base) student@itcenter-lab128:~/Desktop/parallel-programing-amina/parallel-programming$ make valgrind
gcc -Wall -Wextra -g -std=c99 -o memory_demo main.c 2
main.c: In function ‘main’:
main.c:8:7: warning: implicit declaration of function ‘printf’ [-Wimplicit-function-declaration]
    8 |       printf("Memory allocation failed!\n");
      |       ^~~~~~
main.c:2:1: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
    1 |  #include <stdlib.h>
  +++ |+#include <stdio.h>
    2 | 
main.c:8:7: warning: incompatible implicit declaration of built-in function ‘printf’ [-Wbuiltin-declaration-mismatch]
    8 |       printf("Memory allocation failed!\n");
      |       ^~~~~~
main.c:8:7: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
main.c:16:12: warning: comparison of constant ‘-1’ with boolean expression is always true [-Wbool-compare]
   16 |   if(!ipos != -1)
      |            ^~
main.c:16:12: warning: logical not is only applied to the left hand side of comparison [-Wlogical-not-parentheses]
main.c:16:6: note: add parentheses around left hand side expression to silence this warning
   16 |   if(!ipos != -1)
      |      ^~~~~
      |      (    )
main.c:17:7: warning: incompatible implicit declaration of built-in function ‘printf’ [-Wbuiltin-declaration-mismatch]
   17 |       printf("Value %d found at position", ival, ipos);
      |       ^~~~~~
main.c:17:7: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
main.c:17:14: warning: too many arguments for format [-Wformat-extra-args]
   17 |       printf("Value %d found at position", ival, ipos);
      |              ^~~~~~~~~~~~~~~~~~~~~~~~~~~~
main.c:19:4: warning: incompatible implicit declaration of built-in function ‘printf’ [-Wbuiltin-declaration-mismatch]
   19 |    printf("Value %d not found.\n", ival);
      |    ^~~~~~
main.c:19:4: note: include ‘<stdio.h>’ or provide a declaration of ‘printf’
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./memory_demo
==9646== Memcheck, a memory error detector
==9646== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==9646== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==9646== Command: ./memory_demo
==9646== 
Value 0 found at position==9646== 
==9646== HEAP SUMMARY:
==9646==     in use at exit: 0 bytes in 0 blocks
==9646==   total heap usage: 2 allocs, 2 frees, 1,064 bytes allocated
==9646== 
==9646== All heap blocks were freed -- no leaks are possible
==9646== 
==9646== For lists of detected and suppressed errors, rerun with: -s
==9646== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)