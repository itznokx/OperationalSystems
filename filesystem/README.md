## Part 1

 - First execute a CMD (terminal) command: dd if=/dev/zero of=vdrive.img bs=1M count=100 (This command will create a "zero" file with 102400 block of 1kb )
 - Next you need to execute: sudo mkfs.ext2 vdrive.img (This command will create a filesystem on the file mkfs.filesystem_type. In that case, we are using ext2 fs type)
 - After this 2 commands execute this: sudo losetup /dev/loop15 vdrive.img (This will mount a filesystem of vdrive.img file);
 - Check the OS volumes. If everything worked fine, should be a new volume. You'll probably need sudo permissions to write files in that volume.

## Part 2

