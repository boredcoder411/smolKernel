extern start
call start
times 510-($-$$) db 0
dw 0xaa55