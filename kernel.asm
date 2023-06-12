bits 32
section .text
	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 0x00)

global start
global disable_cursor
extern k_main

disable_cursor:
	pushf
	push eax
	push edx
 
	mov dx, 0x3D4
	mov al, 0xA
	out dx, al
 
	inc dx
	mov al, 0x20
	out dx, al
 
	pop edx
	pop eax
	popf
	ret

start:
	cli
	call k_main
	hlt
times 510-($-$$) db 0
dw 0xaa55
