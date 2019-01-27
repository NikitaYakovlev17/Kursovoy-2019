.586
	.model flat, stdcall
	includelib libucrt.lib
	includelib kernel32.lib
	includelib ..\Debug\Lib.lib
	ExitProcess PROTO :DWORD

	readw PROTO: DWORD
	readr PROTO: DWORD
	strln PROTO: DWORD
	power PROTO: DWORD, :DWORD

.stack 4096
.const
	L0 DWORD 4
	L1 DWORD 2
	L2 DWORD 3
	L3 DWORD 100
	L4 BYTE "Hello world", 0
	L5 BYTE "Завершение программы.", 0
.data
	onex DWORD ?
	twox DWORD ?
	entrya DWORD ?
	entryb DWORD ?
	entryc DWORD ?
	entryd DWORD ?
	entrye DWORD ?
	entryf DWORD ?
	entryg DWORD ?

.code

one PROC onea : SDWORD, oneb : SDWORD
	push onea
	push oneb
	pop eax
	pop ebx
	add eax, ebx
	push eax
	push L0
	pop eax
	pop ebx
	mul ebx
	push eax
	pop onex
	push onex
	ret
one ENDP

two PROC twostr : DWORD
	push twostr
	pop edx
	push twostr
		call strln
	push eax
	pop twox
	push twox
	ret
two ENDP

main PROC
	push L1
	pop entrya
	push L2
	pop entryb
	push entrya
	push entryb
	pop edx
	pop edx
	push entryb
	push entrya
		call one
	push eax
	push L3
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop entryc
	push entryc
		call readr
	push offset L4
	pop entryg
	push entryg
	pop edx
	push entryg
		call two
	push eax
	pop entryd
	push entrya
	push L2
	pop edx
	pop edx
	push L2
	push entrya
		call power
	push eax
	pop entryf
	push entryd
		call readr
	push entryf
		call readr
	push offset L5
		call readw
	push 0
	call ExitProcess
main ENDP
end main