ordena:
    movq    %rdi, -24(%rbp)      # Salva o ponteiro para o array na pilha
    movl    %esi, -28(%rbp)      # Salva o tamanho do array na pilha
    movl    $0, -12(%rbp)        # Inicializa o contador externo (i) com 0
    jmp     .L2                  # Salta para o início do loop externo

.L6:
    movl    -12(%rbp), %eax      # Carrega i em eax
    addl    $1, %eax             # Incrementa i
    movl    %eax, -8(%rbp)       # Salva i de volta na pilha
    jmp     .L3                  # Salta para o início do loop interno

.L5:
    movl    -12(%rbp), %eax      # Carrega i em eax
    cltq                         # Estende para 64 bits
    leaq    0(,%rax,4), %rdx    # Calcula o deslocamento para o elemento atual do array
    movq    -24(%rbp), %rax      # Carrega o ponteiro para o array em rax
    addq    %rdx, %rax           # Calcula o endereço do elemento atual do array
    movl    (%rax), %edx         # Carrega o valor do elemento atual em edx
    movl    -8(%rbp), %eax       # Carrega j em eax
    cltq                         # Estende para 64 bits
    leaq    0(,%rax,4), %rcx    # Calcula o deslocamento para o elemento seguinte do array
    movq    -24(%rbp), %rax      # Carrega o ponteiro para o array em rax
    addq    %rcx, %rax           # Calcula o endereço do elemento seguinte do array
    movl    (%rax), %eax         # Carrega o valor do elemento seguinte em eax
    cmpl    %eax, %edx           # Compara os dois elementos
    jle     .L4                  # Salta se o elemento atual for menor ou igual ao seguinte
    movl    -12(%rbp), %eax      # Carrega i em eax
    cltq                         # Estende para 64 bits
    leaq    0(,%rax,4), %rdx    # Calcula o deslocamento para o elemento atual do array
    movq    -24(%rbp), %rax      # Carrega o ponteiro para o array em rax
    addq    %rdx, %rax           # Calcula o endereço do elemento atual do array
    movl    (%rax), %eax         # Carrega o valor do elemento atual em eax
    movl    %eax, -4(%rbp)       # Salva o valor do elemento atual temporariamente
    movl    -8(%rbp), %eax       # Carrega j em eax
    cltq                         # Estende para 64 bits
    leaq    0(,%rax,4), %rdx    # Calcula o deslocamento para o elemento seguinte do array
    movq    -24(%rbp), %rax      # Carrega o ponteiro para o array em rax
    addq    %rdx, %rax           # Calcula o endereço do elemento seguinte do array
    movl    -12(%rbp), %edx      # Carrega i em edx
    movslq  %edx, %rdx           # Estende para 64 bits
    leaq    0(,%rdx,4), %rcx    # Calcula o deslocamento para o elemento atual do array
    movq    -24(%rbp), %rdx      # Carrega o ponteiro para o array em rdx
    addq    %rcx, %rdx           # Calcula o endereço do elemento atual do array
    movl    (%rax), %eax         # Carrega o valor do elemento seguinte em eax
    movl    %eax, (%rdx)         # Salva o valor do elemento seguinte no lugar do atual
    movl    -8(%rbp), %eax       # Carrega j em eax
    cltq                         # Estende para 64 bits
    leaq    0(,%rax,4), %rdx    # Calcula o deslocamento para o elemento seguinte do array
    movq    -24(%rbp), %rax      # Carrega o ponteiro para o array em rax
    addq    %rax, %rdx           # Calcula o endereço do elemento seguinte do array
    movl    -4(%rbp), %eax       # Carrega o valor temporário do elemento atual em eax
    movl    %eax, (%rdx)         # Restaura o valor temporário para o lugar do elemento seguinte

.L4:
    addl    $1, -8(%rbp)         # Incrementa j

.L3:
    movl    -8(%rbp), %eax       # Carrega j em eax
    cmpl    -28(%rbp), %eax      # Compara j com o tamanho do array
    jl      .L5                  # Salta se j < n
    addl    $1, -12(%rbp)        # Incrementa i

.L2:
    movl    -12(%rbp), %eax      # Carrega i em eax
    cmpl    -28(%rbp), %eax      # Compara i com o tamanho do array
    jl      .L6                  # Salta se i < n
    ret                           # Retorna
