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

# Explicit compile target (produces the target program)
compile: $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
