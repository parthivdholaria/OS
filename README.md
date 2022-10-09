# OS
This is for the assignment 2


I have implimented ls cd pwd echo mkdir rm date cat commands in C. The shell  written in C forks everytime it loads the binary of these commands.

Arguments handled in ls are 
1) -l
2) -a
On the terminal just type ls -l and ls -a respectively to see them working

Arguments handled in cat
1) -n
2) >
On the terminal you can just type cat -n filename to see the contents or type cat > filename.txt to create a new file named filename

Arguments handled in date
1) +%Y
2) +%B
On the terminal you can just type date +%Y to see which year or type date +%B to see which month is it


Arguments handled in echo 
1) -e
2) -n
On the terminal you can just type echo message or echo -e message1\nmessage2 or type echo -n message1\nmessage2

Arguments handled for mkdir 
1) -v
2) -p
On the terminal type mkdir name or mkdir -v name or mkdir -p name

Arguments handled for pwd
none
on the terminal type pwd to view the path

Arguments handled for cd
1) ..
2) .
on the terminal type cd name or cd .. or cd .

Arguments handled for rm
1) --version
2) -v
on the terminal type rm file or rm -v file or rm --version


Note:
I have also included clear function to clear screen.


Error Handling
For more or less parameters passed the terminal will show a message respectively
For file  creation if program fails to create a new file a message will be displayed.







