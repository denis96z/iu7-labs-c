# Файлы исходных кодов.
SOURCES := main.c

# Исполняемый файл.
EXECUTABLE := task02.exe

# Вид сборки.
MODE := debug

# Компилятор.
COMPILER := gcc

#Компоновщик.
LINKER := gcc

# Флаги компиляции.
C_FLAGS := -std=c99 -Wall -Werror -pedantic

# Флаги компоновки.
L_FLAGS :=

ifeq ($(MODE), debug)
	# Отладочная сборка.
	C_FLAGS += -ggdb -g3 -O0
	L_FLAGS += -ggdb
endif

ifeq ($(MODE), release)
	# Финальная сборка.
	C_FLAGS += -DNDEBUG -g0
endif

# Объектные файлы.
OBJECTS = $(SOURCES:.c=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LINKER) $(L_FLAGS) $^ -o $@

.c.o :
	$(COMPILER) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf *.o *.exe