
// Mostra como usar chamadas de sistema diretamente em C.
// compilar ---- gcc hello_syscall.c -o hello
// executar ----- ./hello

#include <unistd.h>   // para write e _exit

int main() {
    write(1, "Hello World!\n", 13);  // escreve na saída padrão
    _exit(0);                        // encerra o programa
}
