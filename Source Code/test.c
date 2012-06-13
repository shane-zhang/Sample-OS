#include <stdio.h>
#include <linux/unistd.h>

int main(void)
{
	printf("%ld\n",syscall(347,10));
	return 0;
}
