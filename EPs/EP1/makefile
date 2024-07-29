# Makefile

# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = simulador
SRCS = driverEP1.c EP1.c
OBJS = $(SRCS:.c=.o)

# Regra padrão: compilar tudo e gerar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar cada arquivo .c em um arquivo .o
%.o: %.c driverEP1.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)

# Regra de "phony" para que `make clean` sempre seja executado
.PHONY: clean


# gcc driverEP1.c EP1.c -o simulador