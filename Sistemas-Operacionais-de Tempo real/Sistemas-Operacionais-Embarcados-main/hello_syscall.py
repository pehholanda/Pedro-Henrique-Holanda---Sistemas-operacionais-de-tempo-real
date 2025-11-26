# hello_syscall.py
import os

msg = b"Hello World!\n"
os.write(1, msg)   # 1 = STDOUT
os._exit(0)        # encerra sem chamar cleanup (equivalente a _exit em C)

