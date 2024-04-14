
/* ******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: STD_TYPES.h
 *
 * Description: Types for STM32F401CC blackpill
 * 
 * Author: Fady
 * 
 *******************************************************************************/




#ifndef _STD_TYPES_H
#define _STD_TYPES_H

#define __IO		volatile

typedef enum 
{
	FALSE,
	TRUE
}bool;


/* Boolean Data Type */
typedef unsigned char bool_t;

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

/* NULL Value */
#define NULL_PTR	(void*)0
#define NULL_t		(void*)0
#define NULL		(void*)0

typedef unsigned char* 			pu8_t;
typedef unsigned char* 			pu16_t;
typedef unsigned char* 			pu32_t;

typedef unsigned char 			uint8_t;			/*       0 .. 255             		*/
typedef unsigned short int 		uint16_t;			/*       0 .. 65535           		*/
typedef unsigned long int  		uint32_t;			/*       0 .. 4294967295      		*/
typedef unsigned long long    	uint64_t;			/*       0 .. 18446744073709551615  */

typedef signed char 			sint8_t;			/*        -128 .. +127            	*/
typedef signed short int 		sint16_t;			/*      -32768 .. +32767         	*/
typedef signed long int  		sint32_t;			/*	 -2147483648 .. +2147483647     */
typedef signed long long      	sint64_t;

typedef float  					f32_t;
typedef double					f64_t;


#endif /* STD_TYPES_H_ */
