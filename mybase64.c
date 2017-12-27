
#include <stdlib.h>
#include <stdio.h> /* A supprimer ??*/
#include <unistd.h>

#define STD_IN	0
#define NB_MAX_BUFF	3


int main(void){
	
	char buff[NB_MAX_BUFF];
	ssize_t nbCaracStdin;
	int  temp, inc;
	const char tabconv64[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	
	
	while((nbCaracStdin = read(STD_IN, buff, NB_MAX_BUFF)) != 0){
	
//	printf("read : %d\n", (int)nbCaracStdin);
		
		if(nbCaracStdin != -1){
		
	
			/* the firt entry in the buffer will be the first displayed
			 * ie for "abc" 'a' will be in buf[0] */
	
			if(nbCaracStdin == NB_MAX_BUFF){
				temp = (buff[0]<<16) + (buff[1]<<8) + (buff[2]);
	
				for(inc=3; inc>=0; inc--){
				/* inc will first use equal to 3 => the most significant 6-bit will be read first
				 * The most high 6-bit are the ones of buff[0] ('a' character in the example) */
					printf("%c", tabconv64[((temp>>(inc*6))&(0x3F))]);
		
				}	
			}else if(nbCaracStdin == (NB_MAX_BUFF-1)){
				/* 1 standard character is missed
				 * 2 characters where read through standard input
				 * It means that the 2 first base64 characters will be displayed normally, the third 
				 * one will be completed with 2 '0' bit and the last one will be directly displayed as '="
				 * without using the conversion table */
				
				
				/* get the 6 most significant bit of buff[2] for the first base64 character */
				temp = (buff[0]>>2) & (0x3F);
				printf("%c",tabconv64[temp]);
				
				/* merge the 2 least significant bits of buff[0] (as 2 most significant bits in base64 6-bit)
				 * with the four most significant of buff[1] (as 2 least significant bit in base 64) */
				temp = ((buff[0] & 0x03) << 4) | ((buff[1]>>4) & (0x0F));
				printf("%c",tabconv64[temp]);
				
				temp = ((buff[1] & 0x0F) << 2); /*<<2 for '0' bit stuffing */
				printf("%c",tabconv64[temp]);
				
				/* last character will be '=' */
				printf("=");
				
			}else if(nbCaracStdin == (NB_MAX_BUFF-2)){
				/* 2 characters are missed from standard output
				 * Only the first base64 character can be displayed normally, the second one will be stuffed
				 * with 4 '0' bit */
				
				 
				/* get the 6 most significant bit of buff[2] for the first base64 character */
				temp = (buff[0]>>2) & (0x3F);
				printf("%c",tabconv64[temp]);
				
				/* get the 2 least significant bit of buff[2] and complete with 4 '0b0' stuffing */
				temp = (buff[0] & 0x03) << 4 ;
				printf("%c",tabconv64[temp]);
				
				/* 2 last characters will be '=' */
				printf("==");
				
			}
			
		}else{
			printf("error");
		}
	
	}/* end of while */
	printf("\n");
	
	return 0;
	
}
