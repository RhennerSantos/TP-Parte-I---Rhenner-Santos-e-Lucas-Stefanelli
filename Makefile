# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall

# Arquivos de origem
SRCS = main.c menu.c bd.c

# Arquivo objeto
OBJS = $(SRCS:.c=.o)

# Nome do executável
TARGET = sistema_times

# Desassocia comandos a nomes de arquivos
.PHONY: all compile run clean

# Alvo padrão 
all: compile run

# Alvo de compilação explícito
compile: $(TARGET)

# Roda o executável
run: $(TARGET)
	./$(TARGET)

# Remove arquivos criados temporariamente
clean:
	rm -f $(OBJS) $(TARGET)

# Compila arquivos de origem em arquivos objeto 
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# liga arquivos objeto para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
