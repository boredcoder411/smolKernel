bits 32
org 0x7c00
section .text
	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 0x00)

global start
extern k_main

start:
	cli
	call k_main
	hlt
times 510-($-$$) db 0
dw 0xaa55
