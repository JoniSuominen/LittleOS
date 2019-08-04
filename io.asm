global outb

outb:
    mov al, [esp + 8] ; move data to be sent into the al register
    mov dx, [esp + 4] ; move the address of I/O port into the dx register
    out dx, al        ; send the data to the I/O port
    ret               ; return to the calling function