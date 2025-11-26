# nice_demo.py
# Aqui usamos os.nice() para mudar a prioridade dinâmica. 
# O filho com nice alto (+15) ganha menos CPU que o filho com nice baixo (−5).
# sudo python3 nice_demo.py
# nice_demo.py

import os, time

def loop_contador(name, nice_value):
    try:
        os.nice(nice_value)  # ajusta prioridade dinâmica
    except PermissionError:
        print(f"Sem permissão para nice={nice_value}, continuando...")
    c = 0
    for i in range(20):
        time.sleep(0.2)
        print(f"{name}: {c}")
        for _ in range(50_000_00):
            c += 1

pid1 = os.fork()
if pid1 == 0:
    loop_contador("nice=+15", 15)
    os._exit(0)

pid2 = os.fork()
if pid2 == 0:
    loop_contador("nice=-5", -5)  # precisa de sudo
    os._exit(0)

# Pai espera os filhos
os.wait()
os.wait()
