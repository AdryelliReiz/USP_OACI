#include <stdio.h>

int processa(short int *M, int memSize) {
  	unsigned short int ri, pc, a, b, c, d, r, psw;

    pc = 0; // inicializa o contador de programa
    a = 0; // inicializa o acumulador
    b = 0; // inicializa o registrador B
    c = 0; // inicializa o registrador C
    d = 0; // inicializa o registrador D
    r = 0; // inicializa o registrador R (retorno)
    psw = 0; // inicializa o PSW

    do {
      	ri = M[pc]; // busca a próxima instrução na memória

      	unsigned short int opcode = (ri & 0xF000) >> 12; // extrai os 4 bits mais significativos (opcode)
      	c = ri & 0x0FFF; // extrai os 12 bits menos significativos (endereço ou valor imediato)

        switch (opcode) {
            case 0x0: // NOP - Não faz nada
                break;

            case 0x1: // LDA(X)
                a = M[c]; // carrega o acumulador com o conteúdo no endereço c
                break;

            case 0x2: // STA(X)
                M[c] = a; // armazena o conteúdo do acumulador no endereço c
                break;

            case 0x3: // JMP(X)
                r = pc + 1; // armazena o próximo endereço sequencial no registrador R
				pc = c - 1; // define o próximo endereço sequencial como o valor armazenado no endereço c da memória
				break;

            case 0x4: // JNZ(X)
                if (a != 0) {
                    r = pc + 1; // armazena o próximo endereço sequencial no registrador R
					pc = c - 1; // define o próximo endereço sequencial como o valor armazenado no endereço c da memória
                }
                break;

            case 0x5: // RET
                pc = r; // Define o contador de programa para o endereço armazenado em r
				break;

            case 0x6: // ARIT
				{
					unsigned short int arit_op = (ri & 0x0E00) >> 9;   // Bits 11-9: arit_op
					unsigned short int res_reg = (ri & 0x01C0) >> 6;  // Bits 8-6: res_reg
					unsigned short int op1_reg = (ri & 0x0038) >> 3;  // Bits 5-3: op1_reg
					unsigned short int op2_val = (ri & 0x0007);       // Bits 2-0: op2_val
					unsigned short int op1_val = 0;
					unsigned short int result = 0;

					// Obter valor de op1_reg
					switch (op1_reg) {
						case 0: op1_val = a; break;
						case 1: op1_val = b; break;
						case 2: op1_val = c; break;
						case 3: op1_val = d; break;
						case 6: op1_val = r; break;
						case 7: op1_val = psw; break;
						default: op1_val = 0; break;
					}

					// Verificar se o bit mais significativo de op2_val está definido
					if ((op2_val & 0x0004) != 0) {
						// Bits 2-1 representam o registrador a ser utilizado
						op2_val &= 0x0003; // Máscara para obter os bits 2-1 de op2_val
						switch (op2_val) {
							case 0: op2_val = a; break;
							case 1: op2_val = b; break;
							case 2: op2_val = c; break;
							case 3: op2_val = d; break;
							case 6: op2_val = r; break;
							default: op2_val = 0; break; // Tratamento padrão caso algo inesperado aconteça
						}
					} else {
						// Caso contrário, op2_val deve ser 0
						op2_val = 0;
					}

					// Executar operação aritmética
					switch (arit_op) {
						case 0: result = 0x0000; break; // Põe como resultado (FFFF)h
						case 1: result = 0xFFFF; break; // Põe como resultado (0000)h
						case 2: result = ~op1_val; break; // NOT
						case 3: result = op1_val & op2_val; break; // AND
						case 4: result = op1_val | op2_val; break; // OR
						case 5: result = op1_val ^ op2_val; break; // XOR
						case 6: result = op1_val + op2_val; break; // ADD
						case 7: result = op1_val - op2_val; break; // SUB
					}

					// Armazena o resultado no registrador especificado
					switch (res_reg) {
						case 0: a = result; break;
						case 1: b = result; break;
						case 2: c = result; break;
						case 3: d = result; break;
						case 6: r = result; break;
						case 7: psw = result; break;
						default: break; // PSW and other cases are not handled here
					}

					// Atualiza o PSW (exemplo simples para overflow e zero)
					
					psw = 0;
					// Atualizar os bits do PSW
					// Bit 8: Overflow na soma
					if (arit_op == 6 && (op1_val + op2_val > 0xFFFF)) {
						psw |= 256; // 0x0100 em decimal
					}

					// Bit 7: Underflow na subtração
					if (arit_op == 7 && (op1_val < op2_val)) {
						psw |= 128; // 0x0080 em decimal
					}

					// Bit 6: Op1 > Op2
					if (op1_val > op2_val) {
						psw |= 64; // 0x0040 em decimal
					}

					// Bit 5: Op1 == Op2
					if (op1_val == op2_val) {
						psw |= 32; // 0x0020 em decimal
					}

					// Bit 4: Op1 < Op2
					if (op1_val < op2_val) {
						psw |= 16; // 0x0010 em decimal
					}

				}
				break;

            case 0xF: // HALT
                return 0; // para o processador
                break;

            default:
                break;
        }

        pc++; // incrementa o contador de programa
        if (pc >= memSize) break; // verifica se o contador de programa ultrapassou o tamanho da memória

	} while (1); // loop infinito para execução contínua

    return 0;
}
