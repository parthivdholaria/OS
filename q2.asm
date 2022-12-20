segment .data
	msginp db "Enter the number:", 0x0a, 0x00
	msgout db "The number entered is:", 0x0a, 0x00
	formatinint db "%d", 0x00
	formatoutint db "%d", 0x0a, 0x00

	msginpstr db "Enter the string:", 0x0a, 0x00
	msgoutstr db "The string entered is:", 0x0a, 0x00
	formatstrinp db "%s", 0x00
	formatstrout db "%s", 0x0a, 0x00
	
	


segment .bss
	num resd 100
	string resd 100

segment .text
	global main
	extern printf
	extern scanf

main:
	push rbp
	mov rbp, rsp
	sub rsp, 16

	xor eax, eax
	lea rdi, [msginp]
	call printf


	mov eax, 0
	lea rdi, [formatinint]
	lea rsi, [num]
	call scanf

	xor eax, eax
	lea rdi, [msginpstr]
	call printf

	mov eax, 0
	lea rdi, [formatstrinp]
	lea rsi, [string]
	call scanf


	mov eax, 0
	lea rdi, [msgout]
	call printf


	mov eax, 0
	lea rdi, [formatoutint]
	mov rsi, [num]
	call printf



	mov eax, 0
	lea rdi, [msgoutstr]
	call printf


	mov eax, 0
	lea rdi, [formatstrout]
	lea rsi, [string]
	call printf

	
	add rsp, 16
	leave
	ret

