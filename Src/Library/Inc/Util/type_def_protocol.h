#ifndef __TYPE_DEF_PROTOCOL_H__
#define __TYPE_DEF_PROTOCOL_H__

// defined for non-stm32 project

#define PI 3.1415926;

#ifdef NON_STM32
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned long long uint64_t;
typedef long long int64_t;
typedef long int32_t;
typedef short int16_t;
typedef signed char int8_t;
#endif

#endif // DEBUG
