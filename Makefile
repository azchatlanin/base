PROJECT_NAME=otus
BUILD_VERSION=0.9.$(shell date +%s)

DECORATOR_BEGIN=@echo "\033[0;32m [OK] \033[0m\033[0;33m 
DECORATOR_END=\033[0m" $<

all: start build_meson run

start:
	$(DECORATOR_BEGIN) START BUILD $(BUILD_VERSION) $(DECORATOR_END)

build_meson:
	$(DECORATOR_BEGIN) Compiling ... $(DECORATOR_END)
	meson compile -C build 

run:
	$(DECORATOR_BEGIN) Run ... $(DECORATOR_END)
	./build/$(PROJECT_NAME) 

