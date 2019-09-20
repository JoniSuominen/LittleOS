global outb
global inb
global load_segment_registers
global load_gdt

outb:
  mov al, [esp + 8] ; move data to be sent into the al register
  mov dx, [esp + 4] ; move the address of I/O port into the dx register
  out dx, al        ; send the data to the I/O port
  ret               ; return to the calling function

inb:
  mov dx, [esp + 4] ; read I/O port into register dx
  in al, dx ; al is the destination port, dx is the source port
  ret ; return the found value

load_gdt:
  lgdt[esp + 4]
  ret


load_segment_registers:
  mov dx, 0x10
  mov ds, dx
  mov ss, dx
  mov es, dx
  mov fs, dx
  mov gs, dx
  jmp 0x08:flush_cs
  

flush_cs:
  ret

