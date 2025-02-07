#include <stdio.h>
#include <string.h>


int main(){
  char str[100];
  int i = 0; 
  int maiusculas = 0 ;

  scanf("%[^\n]", str);

  while(strcmp(str, "FIM") != 0){
    printf("%s\n", str);
    scanf(" %[^\n]", str);


    for(i = 0; str[i]!= '\0'; i++){

      if(str[i] >= 'A' && str['Z'])
      {
        maiusculas += 1; 
      } 
    }
      printf(maiusculas)
  }


}