/*
 *<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<    STD_MACROS.h || BIT_MATH.h    >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 *
 * Author  : Mohamed Aldremly
 * Date    : 5/6/2026
 *  Layer  : LIB
 *
 *
 */ 
 
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define REGISTER_SIZE 8
#define SET_BIT(reg,bit)    reg|=(1<<bit)
#define CLR_BIT(reg,bit)    reg&=(~(1<<bit))
#define TOG_BIT(reg,bit)    reg^=(1<<bit)
#define GET_BIT(reg,bit)    (reg&(1<<bit))>>bit
#define IS_BIT_SET(reg,bit)  (reg&(1<<bit))>>bit
#define IS_BIT_CLR(reg,bit)  !((reg&(1<<bit))>>bit)
#define ROR(reg,num)         reg=(reg<<(REGISTER_SIZE-num))|(reg>>(num))
#define ROL(reg,num)        reg= (reg>>(REGISTER_SIZE-num))|(reg<<(num))

#define SET_2BIT(reg,bit)    reg|=(3<<bit*2)
#define SET_4BIT(reg,bit)    reg|=(0b1111<<bit*4)

#define CLR_2BIT(reg,bit)    reg&=(~(0b11<<bit*2))
#define SET_2BIT_VALUE(reg,bit,value)    reg|=  (((value) & 0b11U) << (bit*2))

#define CLR_4BIT(reg,bit)    reg&=(~(0b1111<<bit*4))
#define SET_4BIT_VALUE(reg,bit,value)    reg|=  (((value) & 0b1111U) << (bit*4))

#define CLR_3BIT(reg,bit)    reg&=(~(0b111<<bit*3))
#define SET_3BIT_VALUE(reg,bit,value)    reg |=  (((value) & 0b111U) << (bit*3))

#endif //BIT_MATH_H_
