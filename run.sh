#! /bin/bash

qemu-system-x86_64 -kernel images/5.19/bzImage -initrd images/rootfs/rootfs.ext3 -append "root=/dev/ram session_id=1 node_id=1"

