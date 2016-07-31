/*
exemplo de como juntar strings em c
*/

char b[4]="aic\0";
char c[4]="nir\0";
printf("%s \n", b);
char grunge[10]="";
strcat(grunge,b);
printf("%s \n", grunge);
strcat(grunge,c);
printf("%s \n", grunge);