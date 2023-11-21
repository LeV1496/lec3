

#include <stdio.h>
#include <string.h>
int main()
{
    FILE *file = fopen("passwd","rt");
    
    char temp[10000];
    char username[100];
    printf("Vvedite username \n");
    scanf ("%s", username);
       
    int status=0;
    
       while (!feof(file)) {
           fscanf(file,"%s",temp);
           if (strcmp(username,temp)==0) { puts(temp); status=1; break; }
       }
       
       if (!status) {
           puts("takogo logina net\n");
       }
    
    
}
