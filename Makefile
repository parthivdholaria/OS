all: shell
	./shell


shell: myshell.c
	gcc usingcat.c -o cat
	gcc usingclr.c -o clear
	gcc usingdate.c -o date
	gcc usingls.c -o ls
	gcc usingmkdir.c -o mkdir
	gcc usingrm.c -o rm
	gcc myshell.c -o shell
