obj-m := chdev.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o *.ko *.order *.symvers *.mod.c *.mod.o
