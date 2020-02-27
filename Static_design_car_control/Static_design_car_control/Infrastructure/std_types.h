/*
 * Complier.h
 *
 * Created: 2/15/2020 10:47:30 PM
 *  Author: Reem el-Areeny
 */ 


#ifndef COMPLIER_H_
#define COMPLIER_H_


/************************************************************************/
/*				      		DEFINING BOOLEAN VALUES                         */
/************************************************************************/
#define FALSE 	0	// defines boolean false
#define TRUE 	1	// defines boolean true


/************************************************************************/
/*						      DEFINING LOW/HIGH VALUES                        */
/************************************************************************/
#define LOW  0		// defines LOW value for a bit
#define HIGH 0xFF	// defines HIGH value for a bit


/************************************************************************/
/*						     DEFINING SET/CLEAR VALUES                        */
/************************************************************************/
#define CLEAR_VALUE  0x00 // defines clear
#define SET_VALUE    0xFF //define set
/************************************************************************/
/*			   			 NULL POINTER DIFINITION                           */
/************************************************************************/
#define NULL   ((void *)0)   //defines the Null pointer


/************************************************************************/
/*                   TYPEDEFS FOR STANDARD TYPES                        */
/************************************************************************/
typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char sint8_t;
typedef signed short int sint16_t;
typedef signed long int sint32_t;
typedef signed long long sint64_t;
typedef volatile uint8_t* const reg_type8_t;
typedef volatile uint16_t* const reg_type16_t;

typedef float float_32_t;
typedef double float_64_t;


/************************************************************************/
/*                   TYPEDEF FOR ERROR MESSAGES                         */
/************************************************************************/

#define ERROR_STATUS_t		uint8_t 
#define E_Ok					0
#define E_Nok					1

#endif /* COMPLIER_H_ */