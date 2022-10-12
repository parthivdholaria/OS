# OS
This is for the assignment 2

Arguments handled in ls are 
1) -1
2) -a
ls: is used to print contents of the current directory
On the terminal just type ls -1 or ls -a respectively to see them working
error handled: prompts "Entered unhandled argument"


Arguments handled in cat
1) -n
2) >
3) -E
On the terminal you can just type cat -n filename to see the contents or type cat > filename.txt to create a new file named filename or cat -E filename
Errors: No errors thrown

Arguments handled in date
1) +%Y
2) +%B
On the terminal you can just type date +%Y to see which year or type date +%B to see which month is it
Errors: No erros thrown


Arguments handled in echo 
1) -E
2) -n
On the terminal you can just type echo message or echo -e message1\nmessage2 or type echo -n message1\nmessage2

Arguments handled for mkdir 
1) -v
2) --help
On the terminal type mkdir name or mkdir -v name or mkdir --help
Errors: None

Arguments handled for pwd
1) --version
2) --help
on the terminal type pwd to view the path
Errors: thrown none

Arguments handled for cd
1) ..
2) .
3) --help
4) --version
on the terminal type cd name or cd .. or cd . or cd --help or cd --version
Erros: throws error occured when it fails to change the given directory



Arguments handled for rm
1) --version
2) -v
3) --help
4_ -f
on the terminal type rm file or rm -v file or rm --version or rm -f file name
Errors: No errors


clear:
use to clear the screen


Error Handling
For more or less parameters passed the terminal will show a message respectively
For file  creation if program fails to create a new file a message will be displayed.


C functions used:

1) fork()
2) execl()
3) chdir()
4) readdir()
5) opendir()
6) wait
7) pthread_create()
8) pthread_join()
9) unlink()
10) remove()
11) getcwd()
12) exit()
13) localtime()
14) strftime()
15) fopen()
16) fclose()
17) fgets()
18) fgetc()
19) strcmp()
20) strncat()
21) getline()
22) mkdir()
23) system()
24) strtok()



headers file used:

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <assert.h>
#include <pthread.h>
#include <dirent.h>
#include <ftw.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>













