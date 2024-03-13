/*
 * commonmacros.h
 *
 *  Created on: Feb 10, 2024
 *      Author: AbdElRahman Khalifa
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SET_BIT(X,NUM) ((X)|=(1<<(NUM)))

#define CLEAR_BIT(X,NUM) ((X)&=~(1<<(NUM)))

#define GET_BIT(X,NUM) !!((X)&(1<<(NUM)))

#define MAKE_BIT(X,NUM,VAL)((X)=((X)&~(1<<(NUM)))|((VAL)*(1<<(NUM))))

#define BIT_IS_CLEAR(X,NUM) (!GET_BIT(X,NUM))

#define BIT_IS_SET(X,NUM) (GET_BIT(X,NUM))

#endif /* COMMON_MACROS_H_ */
