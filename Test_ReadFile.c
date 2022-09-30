#include <stdio.h>
sdf
int main(){
    FILE *fp = NULL;
    char get;

    fp = fopen("Product.txt", "r");
    
    get = fgetc(fp);
    get = fgetc(fp);
    
    printf("get=%c\n",get);

    return 0;
}
