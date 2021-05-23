#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void leftrotate(int length,int c[],int rotation){
    for(int i=0;i<rotation%length;i++){
        int temp = c[0];
        for(int j=0;j<length-1;j++){
            c[j] = c[j+1];
        }
        c[length-1] = temp;
    }
}
void encryption(int length,char plaintext[],char key[16]){
    char h[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};

    for(int i=0;i<16;i++){
        h[i] = (key[i] ^ h[i])%128;
    }
    unsigned int total = 0;
    for(int i=0;i<16;i++){
        total = total+h[i];
    }
    total = total%128;

    int ciphertext[length];

    for(int i=0;i<length;i++){
        plaintext[i] -= 33;
        ciphertext[i] = (int)(plaintext[i]+((h[(i+1)%16]&h[(i+7)%16])^(total|h[15-(i%16)])));
        ciphertext[i] = ciphertext[i] %94 + 33;
    }
    printf("\n");

    leftrotate(length,ciphertext,total);
    for(int i=0;i<length;i++){
        printf("%c",ciphertext[i]);
    }
    printf("\n");
}

void inputIntostr(int *count,char *str){
    while(1){
        char c;
        scanf("%c",&c);
        if(c!='\n'){
            str[*count] = c;
            *count = *count+1;
        }else{
            break;
        }
    }
}
int main()
{
    while(1){
        char str[100000] = {'\0'};
        char key[17] = {'\0'};
        int count = 0;
        printf("Input your data:");
        gets(str);
        count = strlen(str);
        printf("\n");

        while(1){
            int countKey = 0;
            char keyvalue[16] = {'\0'};
            printf("Input your key:");
            inputIntostr(&countKey,keyvalue);
            if(countKey!=16){
                printf("Your key must be 16 words!!!\n");
            }else{
                for(int i=0;i<16;i++){
                    key[i] = keyvalue[i];
                }
                break;
            }
        }
        printf("%s\n",str);
        printf("%s\n",key);
        encryption(count,str,key);
        break;
    }
    return 0;
}
