CC := gcc
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

obj-m += file_monitor.o
obj-m += exec_control.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean