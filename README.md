## Aula 04 - Sistemas Embarcados
---
### Arquivo Makefile

Compila automaticamente programas e bibliotecas utilizando instruções contidas em um arquivo **Makefile** - documentação [GNU make](https://www.gnu.org/software/make/manual/html_node/index.html). 

- **Regras Explícitas**
- **Regras Implícitas**
- **Definição de Variáveis**
- **Diretivas**
- **Comentários (#)**

Uma **regra** informa ao make duas coisas:
>(1) Quando um **target** está desatualizado;\
(2) Como fazer para atualizá-lo.


Um **target** está desatualizado se ele não existir **ou** se é mais antigo que qualquer um dos **pré-requisitos**. O modo de atualizá-lo é ditado pela **receita**.

```
targets: pre-requisitos
    receita
```

Por exemplo, para **compilarmos** o arquivo **main.c**, temos a seguinte regra:
```
main.o: main.c
    arm-none-eabi-gcc -c -g -mcpu=cortex-m4 -mthumb -O0 -Wall main.c -o main.o
```

Execute no terminal o comando **make**, tenha certeza de que o arquivo objeto do programa **main** esteja desatualizado.
---
### Melhorando o nosso Makefile

O arquivo ainda não está, necessariamente, facilitando as coisas para nós, **ainda**.\
Para isso, vamos melhorá-lo adicionando **variáveis**, **variáveis automáticas** e um **target** para remover os arquvios que geramos a cada make.

```
    # Variáveis para a compilação
    CC      = arm-none-eabi-gcc
    CFLAGS  = -g -mcpu=cortex-m4 -mthumb -O0 -Wall

    # Variáveis automáticas
    # (1) $<: representa o primeiro elemento da lista de pré-requisitos;
    # (2) $@: representa o alvo (target) da regra
    main.o: main.c
        $(CC) -c $(CFLAGS) $< -o $@

    startup.o: startup.c:
        $(CC) -c $(CFLAGS) $< -o $@

    clean:
        rm -f *.o
```

**Obs.:** Nessa configuração atual, apenas a primeira regra de compilação é executada, a saber a do **main**. Para resolvermos esse problema adicionamos o target **all**:

```
    # Variáveis para a compilação
    CC      = arm-none-eabi-gcc
    CFLAGS  = -g -mcpu=cortex-m4 -mthumb -O0 -Wall

    all: main.o startup.o

    main.o: main.c
        $(CC) -c $(CFLAGS) $< -o $@

    startup.o: startup.c:
        $(CC) -c $(CFLAGS) $< -o $@

    clean:
        rm -f *.o
```
**Obs.:** Executamos agora com `make all`.


Podemos deixar a regra ainda mais flexível, uma vez que a regra para os dois arquivos é a mesma. Vamos utilizar os **wildcards** para criarmos padrões de alvos e pré-requisitos.
```
    # Variáveis para a compilação
    CC      = arm-none-eabi-gcc
    CFLAGS  = -g -mcpu=cortex-m4 -mthumb -O0 -Wall

    all: main.o startup.o

    %.o: %.c
        $(CC) -c $(CFLAGS) $< -o $@


    clean:
        rm -f *.o
```

Ainda adicionaremos processamento de texto para criarmos regras para a compilação de arquivos genéricos, adicionaremos uma pasta para salvar esses arquivos objetos criados, uma pasta para armazenar as dependências que nossos arquivos fonte possuem.

```
CC = arm-none-eabi-gcc
RM = rm -rf

# Diretórios dos arquivos objetos e das listas de dependências
OBJDIR = build
DEPDIR = .deps

# Arquivos a serem compilados
SRCS = startup.c main.c

# Flags do compilador e linkes
CFLAGS   = -g -mcpu=cortex-m4 -mthumb -Wall -O0
DEPFLAGS = -MMD -MF $(DEPDIR)/$*.d


# Gera a lista de arquivos objetos e cria o diretório aonde esses arquivos serão armazenados
OBJS = $(patsubst %, $(OBJDIR)/%.o, $(basename $(SRCS)))
$(shell mkdir -p $(dir $(OBJS)) > /dev/null)

#Gera a lista de arquivos de dependências e cria o diretório onde esses arquivos serão salvos
DEPS = $(patsubst %, $(DEPDIR)/%.d, $(basename $(SRCS)))
(shell mkdir -p $(dir $(DEPS)) > /dev/null)

all: $(OBJS)

$(OBJDIR)/%.o: %c $(DEPDIR)/%.d
    $(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

# Cria um novo target para cada arquivo de dependência possível. Para a primeira compilação.
$(DEPS):

# Inclui o oconteúdo dos arquivos de dependência
- include $(DEPS)

# Avisa ao make que o target não gerará arquvios.
# .PHONY
.PHONY: clean
clean:
    $(RM) $(OBJDIR) $(DEPDIR)

```

---
> Autor: Gustavo Alves de Oliveira\
Matrícula: 12311ECP026\
Universidade Federal de Uberlândia


