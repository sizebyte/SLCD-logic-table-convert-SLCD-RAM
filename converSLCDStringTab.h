#ifndef CONVERSLCDSTRING_H
#define CONVERSLCDSTRING_H


typedef struct{
    uint8_t MCUSegX; //mcu segmented gpio index  X=1-> MCU SEG1
    char * seg_name; //slcd segmented name
}MCUSegIOToSLCDSeg_t;
typedef struct{
    uint8_t MCUSegX; //mcu segmented gpio index
    uint8_t SLCDCom;//com index
    char seg_name; //slcd segmented name
}IOMaping_t;
typedef struct{
    uint8_t com0[8];
    uint8_t com1[8];
    uint8_t com2[8];
    uint8_t com3[8];
}SLCDFont_t;











extern void logical_table_conver_encoding(void);

#endif // CONVERSLCDSTRING_H




