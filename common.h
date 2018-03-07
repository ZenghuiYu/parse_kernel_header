#ifndef __COMMON_H__
#define __COMMON_H__

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

#define __packed __attribute((packed))
#define LINUX_MAGIC ('H' + ('d' << 8) + ('r' << 16) + ('S' << 24))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif /* __COMMON_H__ */
