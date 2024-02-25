#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int vise_reci(const char *str) {
    while (*str) {
        if (*str == ' ') {
            return 1;
        }
        str++;
    }
    return 0;
}

int i_strstr(const char* linija, const char* pattern) {
   
    while (*linija) {
        const char* l = linija;
        const char* p = pattern;

        while (*l && *p && tolower((unsigned char)*l) == tolower((unsigned char)*p)) {
            l++;
            p++;
        }
        
        if (*p == '\0') {
            return 1;  
        }

        linija++;
    }

    return 0;  
}




int grep(FILE *file, const char *pattern, int inverzija, int ignorisi_velicinu, int samo_broj, int zaustavi_posle, int ispisi_broj_linije, int cela_rec, int cela_linija){

    
    char linija[250];
    int broj_linija=0;
    int br_matchova=0;


	while (fgets(linija, sizeof(linija), file)!=NULL){
    
        broj_linija++;          
        char *kopija_linije = strdup(linija);
        char *token = strtok(kopija_linije, " \t\n");
      
      if(vise_reci(pattern)){
                int matchl=0;
                
                if(ignorisi_velicinu){
                   
                  matchl=i_strstr(linija,pattern);
                }else {
                   if(strstr(linija,pattern)!=NULL){
                    matchl=1;
                   }
                    
                }


              if(matchl && !cela_rec && (!cela_linija || (cela_linija && strlen(pattern)==strlen(linija)-1))){  

                    
                    if(zaustavi_posle>0){
                        if(inverzija){
                           free(kopija_linije);
                            continue;
                        }
                        if(samo_broj){
                            br_matchova++;
                            free(kopija_linije);
                            continue;
                        }
                        if (ispisi_broj_linije) {
                            printf("%d:", broj_linija);
                        }
                        printf("%s", linija);
                        br_matchova++;
                        zaustavi_posle--;
                        if (zaustavi_posle == 0) {
                         free(kopija_linije);
                            return br_matchova; 
                        }
                        free(kopija_linije);
                        continue;
                        
                    }
                   
                    br_matchova++;
                   
                    if (inverzija) {
                        free(kopija_linije);
                        continue;
                        
                    } 
                    if (ispisi_broj_linije) {
                        printf("%d:", broj_linija);
                    }
                    if(samo_broj){
                       free(kopija_linije);
                        continue;;
                    }
                    else {
                        printf("%s", linija);
                        free(kopija_linije);
                        continue;
                    }
                    
                }  
             
            }

        int match=0;
        
        while (token != NULL) {
            

            if (ignorisi_velicinu) {
                match = (strcasecmp(token, pattern) == 0 ) || ( i_strstr(token,pattern)==1 );
            } else {
                match = (strcmp(token, pattern) == 0) || (strstr(token, pattern) != NULL);
            }
        
            
           
            if (match && !cela_linija) {

                if(zaustavi_posle>0){
                   if ((!cela_rec || (cela_rec && strlen(token) == strlen(pattern))) ) {
                        if(inverzija){
                            
                            break;
                        }
                        if(samo_broj){
                            br_matchova++;
                            break;
                        }
                        if (ispisi_broj_linije) {
                            printf("%d:", broj_linija);
                        }
                        printf("%s", linija);
                        br_matchova++;
                        zaustavi_posle--;
                        if (zaustavi_posle == 0) {
                            return br_matchova; 
                        }
                        break;
                   }
                }

                
                if ((!cela_rec || (cela_rec && strlen(token) == strlen(pattern))) ) {
                    br_matchova++;
                    if (inverzija) {
                        break;
                        
                    } 
                    if (ispisi_broj_linije) {
                        printf("%d:", broj_linija);
                    }
                    if(samo_broj){
                        break;
                    }
                    else {
                        printf("%s", linija);
                        break;
                    }
                }
            }

            token = strtok(NULL, " \t\n");
        }
        
        if(inverzija && !match && !samo_broj){
                 
                
                if(zaustavi_posle>0){
                        
                        if (ispisi_broj_linije) {
                            printf("%d:", broj_linija);
                        }
                        printf("%s", linija);
                        
                        zaustavi_posle--;
                        if (zaustavi_posle == 0) {
                            return br_matchova; 
                        }
                    free(kopija_linije);
                    continue;
             }      
             if (ispisi_broj_linije) {
                            printf("%d:", broj_linija);
                        }
             printf("%s", linija);
        }

        free(kopija_linije);
    
        
    }

    if (samo_broj) {
        if(inverzija){
            printf("   Broj linija: %d\n", broj_linija-br_matchova);
        }
        
        else printf("   Broj linija: %d\n", br_matchova);

    }

    return br_matchova;
    fclose(file);



}



void print_h() {
    printf("Upotreba: ./grep [opcije] obrazac [fajl...]\n");
    printf("Opcije:\n");
    printf("  -h     Prikazuje ovu pomoćnu poruku\n");
    printf("  -v     Invertuje rezultate podudaranja\n");
    printf("  -i     Ignoriše razlike između velikih i malih slova\n");
    printf("  -c     Ispisuje samo broj odabranih linija po FAJLU\n");
    printf("  -m NUM Zaustavi se posle NUM odabranih linija\n");
    printf("  -n     Ispisuje broj linije uz izlazne linije\n");
    printf("  -w     Podudara samo cele reči\n");
    printf("  -x     Podudara samo cele linije\n");
    exit(EXIT_FAILURE);
}




int main(int argc, char *argv[]){
	if (argc < 3) {
        print_h();
    }

	int inverzija = 0;          
	int ignorisi_velicinu = 0;  
	int samo_broj = 0;          
	int zaustavi_posle = 0;      
	int ispisi_broj_linije = 0;  
	int cela_rec = 0;         
	int cela_linija = 0;         
	char *pattern = NULL;  
    int brojac_opcija=1;

	  for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' ) {
                int flag=0;
                brojac_opcija++;
            for (int j = 1; argv[i][j] != '\0'; j++) {
                switch (argv[i][j]) {
                    case 'h':
                        print_h();
                        break;
                    case 'v':
                        inverzija= 1;
                        
                        break;
                    case 'i':
                        ignorisi_velicinu = 1;
                        
                        break;
                    case 'c':
                        samo_broj = 1;
                        
                        break;
                    case 'm':
                        
                            zaustavi_posle = atoi(argv[i + 1]);
                            flag++;
                            brojac_opcija++;
                            break;
                        
                 
                    case 'n':
                        ispisi_broj_linije = 1;
                       
                        break;
                    case 'w':
                        cela_rec = 1;
                        
                        break;
                    case 'x':
                        cela_linija = 1;
                        
                        break;

                    default:
                        print_h();
                        break;
                }
            }
                if(flag>0){
                i++;   
                }
        } else {

            pattern = argv[i];
            break;
            }
            
    }
	
     if (pattern == NULL) {
        print_h();
    }

    int ukupno_mecing = 0;

    
    for (int i = brojac_opcija+1; i < argc; i++) {
        
        FILE *file = fopen(argv[i], "r");

        if (file == NULL) {
            perror("Neuspelo otvaranje datoteke");
            continue;
        }
        printf("FAJL: %s\n\n",argv[i]);
        int mecing = grep(file, pattern, inverzija, ignorisi_velicinu, samo_broj, zaustavi_posle, ispisi_broj_linije, cela_rec, cela_linija);
        ukupno_mecing += mecing;
            if(ukupno_mecing>0 || samo_broj==1){
            for(int i=0;i<50;i++){
                printf("-");
            }
            }
            printf("\n");
        
        fclose(file);
    }

    if (!samo_broj) {
        if (ukupno_mecing > 0) {
            return EXIT_SUCCESS;
        } else {
            
            return EXIT_FAILURE;
        }
    }

    
	return 0;
	
}