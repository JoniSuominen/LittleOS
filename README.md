# LittleOS
A small project to educate myself on how an operating system works on a low level.
The basis for this project is the LittleOS book.

## Building the kernel
You can use the accompanied Makefile or compile the files with GCC/Nasm yourself.
I have used QEMU as the virtual machine for my kernel, as I dont wanna necessarily run it
on real hardware at this point

```
make
qemu-system-i386 -kernel kernel
```


## Materials used
* https://ordoflammae.github.io/littleosbook/
* https://arjunsreedharan.org/post/82710718100/kernels-101-lets-write-a-kernel
* http://os-book.com/OS10/index.html
