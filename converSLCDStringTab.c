#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "converSLCDStringTab.h"
const MCUSegIOToSLCDSeg_t MCUSegIOToSLCDSegTab[]={
{40,"1D 1E 1F 1A"},//slcd seg 0
{41,"1C 1G 1B 7F"},//slcd seg 1
{42,"2D 2E 2F 2A"},//slcd seg 2
{43,"2C 2G 2B 2:"},//slcd seg 3
{33,"3D 3E 3F 3A"},//slcd seg 4
{19,"3C 3G 3B 7E"},//slcd seg 5
{24,"4D 4E 4F 4A"},//slcd seg 6
{25,"4C 4G 4B 4:"},//slcd seg 7
{26,"5D 5E 5F 5A"},//slcd seg 8
{27,"5C 5G 5B 50"},//slcd seg 9
{20,"6D 6E 6F 6A"},//slcd seg 10
{22,"6C 6G 6B 6."},//slcd seg 11
{23,"9B 9G 9C 7D"},//slcd seg 12
{28,"9A 9F 9E 9D"},//slcd seg 13
{29,"8B 8G 8C 8u"},//slcd seg 14
{30,"8A 8F 8E 8D"},//slcd seg 15
{31,"7A 7B 7G 7C"},//slcd seg 16
};
uint8_t SLCDStringTab[][7]= {
{'A', 'B', 'C', 'D', 'E', 'F', ' '},//'0'
{'B', 'C', ' ', ' ', ' ', ' ', ' '},//'1'
{'A', 'B', 'D', 'E', 'G', ' ', ' '},//'2'
{'A', 'B', 'C', 'D', 'G', ' ', ' '},//'3'
{'B', 'C', 'F', 'G', ' ', ' ', ' '},//'4'
{'A', 'C', 'D', 'F', 'G', ' ', ' '},//'5'
{'A', 'C', 'D', 'E', 'F', 'G', ' '},//'6'
{'A', 'B', 'C', ' ', ' ', ' ', ' '},//'7'
{'A', 'B', 'C', 'D', 'E', 'F', 'G'},//'8'
{'A', 'B', 'C', 'D', 'F', 'G', ' '},//'9'
{':', 'u', '.', ' ', ' ', ' ', ' '},//'.'/':'/'u'
{'A', 'D', 'E', 'F', 'G', ' ', ' '},//'E'
{'E', 'G', ' ', ' ', ' ', ' ', ' '},//'r'
{'C', 'D', 'E', 'G', ' ', ' ', ' '},//'o'
};
const uint8_t SegName[]="ABCDEFG:.u";
#define SegNameSUM   (sizeof(SegName)-1)
SLCDFont_t font_seg[9][14];
void get_SeX_IO_maping_table(uint8_t SegX, IOMaping_t * str )
{
    uint8_t i,s;
    char str1 = SegX+'0';
   // printf("%c %c %d\r\n",str1,MCUSegIOToSLCDSegTab[0].seg_name[0], sizeof(MCUSegIOToSLCDSegTab)/sizeof(MCUSegIOToSLCDSeg_t));
    for(i = 0;i<SegNameSUM; i++){
        for(s = 0;s<sizeof(MCUSegIOToSLCDSegTab)/sizeof(MCUSegIOToSLCDSeg_t); s++){
            str->MCUSegX = MCUSegIOToSLCDSegTab[s].MCUSegX;
            if(str1==MCUSegIOToSLCDSegTab[s].seg_name[0] && SegName[i]==MCUSegIOToSLCDSegTab[s].seg_name[1]){ //D C
                str->seg_name = MCUSegIOToSLCDSegTab[s].seg_name[1];
                str->SLCDCom = 4;
                break;
            }else if(str1==MCUSegIOToSLCDSegTab[s].seg_name[3] && SegName[i]==MCUSegIOToSLCDSegTab[s].seg_name[4]){ //E G
                str->seg_name = MCUSegIOToSLCDSegTab[s].seg_name[4];
                str->SLCDCom = 3;
                break;
            }else if(str1==MCUSegIOToSLCDSegTab[s].seg_name[6] && SegName[i]==MCUSegIOToSLCDSegTab[s].seg_name[7]){ //F B
                str->seg_name = MCUSegIOToSLCDSegTab[s].seg_name[7];
                str->SLCDCom = 1;
                break;
            }else if(str1==MCUSegIOToSLCDSegTab[s].seg_name[9] && SegName[i]==MCUSegIOToSLCDSegTab[s].seg_name[10]){ //A
                str->seg_name = MCUSegIOToSLCDSegTab[s].seg_name[10];
                str->SLCDCom = 2;
                break;
            }else{
                str->seg_name = 0;
                str->SLCDCom = 0;
            }
        }
        printf("%d,%d,%c \r\n",str->MCUSegX,str->SLCDCom,str->seg_name);
        str++;
    }

}
void get_SegX_font(uint8_t SegX, SLCDFont_t * pFont)
{
    uint8_t i,s,m;
    IOMaping_t IOMaping[SegNameSUM];
    get_SeX_IO_maping_table(SegX,IOMaping);

    printf("Seg%d\r\n",SegX);
    for(i = 0;i<sizeof(SLCDStringTab)/7;i++){
        for(s=0;s<7;s++){
            for(m = 0; m<SegNameSUM; m++){
                if(SLCDStringTab[i][s]==IOMaping[m].seg_name){
                    switch(IOMaping[m].SLCDCom){
                    case 1:
                        pFont->com0[IOMaping[m].MCUSegX/8] |= 1<<(IOMaping[m].MCUSegX%8);
                        break;
                    case 2:
                        pFont->com1[IOMaping[m].MCUSegX/8] |= 1<<(IOMaping[m].MCUSegX%8);
                        break;
                    case 3:
                        pFont->com2[IOMaping[m].MCUSegX/8] |= 1<<(IOMaping[m].MCUSegX%8);
                        break;
                    case 4:
                        pFont->com3[IOMaping[m].MCUSegX/8] |= 1<<(IOMaping[m].MCUSegX%8);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
               printf("0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\r\n",pFont->com0[0],pFont->com0[1],pFont->com0[2],pFont->com0[3],pFont->com0[4],pFont->com0[5],pFont->com0[6],pFont->com0[7]);
               printf("0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\r\n",pFont->com1[0],pFont->com1[1],pFont->com1[2],pFont->com1[3],pFont->com1[4],pFont->com1[5],pFont->com1[6],pFont->com1[7]);
               printf("0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\r\n",pFont->com2[0],pFont->com2[1],pFont->com2[2],pFont->com2[3],pFont->com2[4],pFont->com2[5],pFont->com2[6],pFont->com2[7]);
               printf("0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\r\n",pFont->com3[0],pFont->com3[1],pFont->com3[2],pFont->com3[3],pFont->com3[4],pFont->com3[5],pFont->com3[6],pFont->com3[7]);
        pFont++;
    }
}
SLCDFont_t Font[14];
void logical_table_conver_encoding(void)
{
    memset(Font,0,sizeof(Font));
    get_SegX_font(3, Font);

}
