#!/bin/bash

sudo /sbin/losetup /dev/loop17 floppy.img
sudo mount /dev/loop17 /media/mnt2
sudo cp kernel.elf /media/mnt2/kernel
sudo cp initrd.img /media/mnt2/initrd
sudo umount /dev/loop17
sudo /sbin/losetup -d /dev/loop17
