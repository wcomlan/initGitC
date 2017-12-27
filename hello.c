

#include <stdio.h>
#include <string.h>

#define NB_ARG	3

int main(int argc, char **argv){

	printf("hello World.... et puis c'est toutzz!\n");

//int inc = 0;

char str_cmd_arg[13] ="";
char * filename = 0;
FILE *filestream, *dest_stream;
int tmp_char;

	printf("%d arguments\n", argc);

	
	if(argc == NB_ARG){
		/* la commande a deux paramètres => argc==4 => OK */
		strncpy(str_cmd_arg, argv[1], 12);
		
		if(strcmp(str_cmd_arg, "--unix_file") == 0){
		
			puts("unix file \n");
			filename = argv[2];
			puts(filename);
			puts("\n");
			
			filestream = fopen(filename, "r+");
			
			if(filestream != NULL){
			
				if( (dest_stream = fopen("fichier_dos", "w+")) != NULL){
					
					while( (tmp_char = fgetc(filestream)) != EOF){
					
					if(tmp_char == '\n'){
						//fseek(filestream, -1, SEEK_CUR);
						fputc('\r', dest_stream);
						fputc(tmp_char, dest_stream);
					}else{
						fputc(tmp_char, dest_stream);
					}
		
				}
					
					fclose(dest_stream);
				}else{
					fclose(dest_stream);
				}
			
				while( (tmp_char = fgetc(filestream)) != EOF){
					if(tmp_char == 'n'){
						//fseek(filestream, -1, SEEK_CUR);
						putchar('r');
						putchar('n');
					}
		
				}
	
				fclose(filestream);
				
			}else{
				fclose(filestream);
			}
			
			
		}else if(strcmp(str_cmd_arg, "--dos_file") == 0){
			puts("--dos file \n");
			filename = argv[2];
			puts(filename);
			puts("\n");
			
			
			
		}else{
			puts("bad command's parameter. Expected argument is \"--unix_file\" or \"--dos file\"\n");
		}
	}else{
		/* la commande devrait avoir deux paramètres => argc==4 */
		puts("\nUnrecognized command line option \n");
	}

	printf("\nFin\n");


	return 0;

}
