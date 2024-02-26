PROGNAME := blinky

CC     = arm-none-eabi-gcc
LD     = arm-none-eabi-gcc
CP     = arm-none-eabi-objcopy
RM     = rm -rf

OBJDIR = build
DEPDIR = .deps

SRCS = startup.c main.c

CFLAGS   = -g -mcpu=cortex-m4 -mthumb -O0 -Wall
DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$*.d
LFLAGS   = -nostdlib -T stm32f411-rom.ld -Wl,-Map=blinky.map


OBJS = $(patsubst %, $(OBJDIR)/%.o, $(basename $(SRCS)))
$(shell mkdir -p $(dir $(OBJS)) > /dev/null)

DEPS = $(patsubst %, $(DEPDIR)/%.d, $(basename $(SRCS)))
$(shell mkdir -p $(dir $(DEPS)) > /dev/null)


# Avisa ao make que esse target (all) não gera arquivos
.PHONY: all
all: $(OBJS) $(PROGNAME).elf $(PROGNAME).bin

$(PROGNAME).elf: $(OBJS)
	$(LD) $(LFLAGS) -o $@ $^

$(PROGNAME).bin: $(PROGNAME).elf
	$(CP) -O binary $^ $@

$(OBJDIR)/%.o: %.c $(DEPDIR)/%.d
	$(CC) -c $(CFLAGS) $(DEPFLAGS) $< -o $@

$(DEPS):

-include $(DEPS)

# Avisa ao make que esse target (clean) não gera arquivos
.PHONY: clean
clean:
	$(RM) $(OBJDIR) $(DEPDIR)
	$(RM) $(PROGNAME).elf $(PROGNAME).bin $(PROGNAME).map