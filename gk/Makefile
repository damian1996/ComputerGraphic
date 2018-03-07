
CC:=g++
LD:=g++
CFLAGS=-std=c++14
LDFLAGS=-lpng
debug : CFLAGS+=-g
release : CFLAGS+=-O3 -flto
release : LDFLAGS+=-O3 -flto
srcdir := src
builddir := build
outdir := bin
SOURCES := $(shell find src -name *.cpp)
SRCDIRS := $(shell find src -type d)
DIRS := $(SRCDIRS:$(srcdir)%=$(builddir)%)
DIRS += $(outdir)
OBJS := $(SOURCES:$(srcdir)/%.cpp=$(builddir)/%.o)
DEPS := $(SOURCES:$(srcdir)/%.cpp=$(builddir)/%.d)
TARGET := $(outdir)/gk

all: release
.PHONY: clean all release debug 
release: $(TARGET)
debug: $(TARGET)

$(TARGET): $(OBJS) | $(DIRS)
	$(LD) $+ $(LDFLAGS) -o $@
build/%.o: src/%.cpp build/%.d | $(DIRS)
	$(CC) $< $(CFLAGS) -c -o $@
build/%.d: src/%.cpp | $(DIRS)
	@$(CC) $< -MM -MP |\
		sed 's=\($(*F)\)\.o[ :]*=$(@D)/\1.o $@ : =g;'\
		> $@

$(DIRS) :
	@mkdir -p $@

clean:
	@rm -rf $(OBJS) $(DEPS) $(TARGET)
	-@rmdir -p bin $(DIRS) 2> /dev/null || true

.SECONDARY: $(OBJS) $(DEPS)

-include $(DEPS)
