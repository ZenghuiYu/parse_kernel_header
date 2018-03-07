/*
 * parse_header.c
 *
 * This program is used to parse Linux kernel's header, which contains
 *      version
 *      header
 *      loadflags
 *      ...
 * Maybe helpful when you looking intothe Linux booting process.
 *
 * Some of codes in header files are just copied from Linux kernel and
 * syslinux. For more information:
 *      linux/arch/i386/boot/setup.S
 *
 *
 * Yu Zenghui
 * zenghuiyu96@gmail.com
 *
 */

#include "common.h"
#include "linux.h"

int main(int argc, char **argv)
{
/*
    printf("%d\n", sizeof(uint8_t));
    printf("%d\n", sizeof(uint16_t));
    printf("%d\n", sizeof(uint32_t));
    printf("%d\n", sizeof(uint64_t));

    printf("%d\n", sizeof(struct linux_header));
*/

    FILE *f_linux;
    struct linux_header *kernel_data;
    int rv;

    if (argc != 2) {
	fprintf(stderr, "Usage: a.out [file-name]\n");
	exit(-1);
    }

    if (!(f_linux = fopen(argv[1], "r"))) {
	fprintf(stderr, "Can not open file: linux\n");
	exit(-1);
    }

    kernel_data = (struct linux_header *)malloc(sizeof(struct linux_header));
    if (!kernel_data) {
	fprintf(stderr, "malloc() failed!\n");
	exit(-1);
    }
    
    rv = fread(kernel_data, sizeof(struct linux_header), 1, f_linux);
    if (!rv) {
	fprintf(stderr, "fread() failed!\n");
	exit(-1);
    }

    /* Print useful content of kernel image */
    printf("Boot sector signature: %4x\n", kernel_data->boot_flag);
    printf("jump: %4x\n", kernel_data->jump);
    printf("Kernel version pointer: %4x\n", kernel_data->kernel_version);
    printf("Load high flag: %2x\n\n", kernel_data->loadflags);

    /* for load_linux.c */
    printf("boot_flag: %4x\n", kernel_data->boot_flag);
    printf("LINUX_MAGIC: %8x\n", LINUX_MAGIC);
    printf("header: %8x\n", kernel_data->header);
    printf("\n[1] %c\n[2] %c\n[3] %c\n[4] %c\n\n", *((char *)kernel_data + 0x202),
           *((char *)kernel_data + 0x203), *((char *)kernel_data + 0x204),
	   *((char *)kernel_data + 0x205));
    printf("setup_sects: %2x\n", kernel_data->setup_sects);
    printf("version: %4x\n", kernel_data->version);
    printf("initrd_addr_max: %8x\n", kernel_data->initrd_addr_max);
    printf("cmdline_max_len: %8x\n", kernel_data->cmdline_max_len);

    free(kernel_data);
    return 0;
}
