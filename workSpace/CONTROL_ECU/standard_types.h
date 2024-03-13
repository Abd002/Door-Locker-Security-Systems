/*
 * StandardTypes.h
 *
 *  Created on: Jan 29, 2024
 *      Author: AbdElRahman Khalifa
 */

#ifndef STANDARD_TYPES_H_
#define STANDARD_TYPES_H_

#define LOGIC_LOW (0u)
#define LOGIC_HIGH (1u)

#define NULL (void*)0

typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned long uint32;
typedef signed long sint32;
typedef unsigned long long uint64;
typedef signed long long sint64;
typedef float float32;
typedef double float64;

typedef enum{
	INTERRUPT_DISABLE,INTERRUPT_ENABLE
}InterruptMode;

#endif /* STANDARD_TYPES_H_ */
