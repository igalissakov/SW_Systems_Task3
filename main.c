#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TXT 1024
#define WORD 30

int SumGem(char c)
{
    if('a'<=c && c<='z') return (c-'a'+1);
    if('A'<=c && c<='Z') return (c-'A'+1);
    return 0;
}
void print_sub(char* match, int flag){
    if(flag) printf("~");
    printf("%s",match);
}
void Gematria(char* word, char* txt)
{
    int flag=0;
    int k=0;
    char match[WORD];
    int sum=0;
    int sub_sum=0;
    for(int i=0; i<strlen(word);i++)
    {
        sum+=SumGem(word[i]);
    }
    for(int i=0;i<strlen(txt);i++)
    {
        for (int j=i;j<strlen(txt);j++)
        {
            sub_sum+=SumGem(txt[j]);
            if(sub_sum==0 && SumGem(txt[j])==0) break;
            if(sub_sum<sum)
            {
                match[k++]=txt[j];
            }
            else if(sub_sum>sum){
                memset(match,'\0',WORD);
                sub_sum=0;
                k=0;
                break;
            }
            else{
                match[k++]=txt[j];
                print_sub(match,flag);
                flag=1;
                memset(match,'\0',WORD);
                sub_sum=0;
                k=0;
                break;
            }
            
        }
        memset(match,'\0',WORD);
        sub_sum=0;
        k=0;
        
    }
}
void getString(char* word,char* txt){
    int i = 0;
	char c = 0;
	while ((c = getchar()) != ' ' && (c != '\t') && (c != '\n')) word[i++] = c;
	word[i] = '\0';
	i = 0;
    c = 0;
	while ((c = getchar()) != '~') txt[i++] = c;
	txt[i] = '\0';  
}
char convertlettrToAtbash(char c){
    if('a'<=c && c<='z') return ('z'-(c-'a'));
    if('A'<=c && c<='Z') return ('Z'-(c-'A'));
    return c;
}
int check(char* reversed,char* converted,char* solution){
    int ConCounter=0;
    int RevCounter=0;
    for(int i=0;i<strlen(converted);++i){
        if(solution[i]==converted[i]) ConCounter++;
        if(solution[i]==reversed[i]) RevCounter++;
    }
    if(ConCounter==strlen(converted)||RevCounter==strlen(converted)) return 1;
    return 0;
}
void convertAtbash(char* word, char* converted){
    int i;
    strcpy(converted,word);
    for(i=0;i<strlen(word);++i){
        converted[i]=convertlettrToAtbash(word[i]);
    }
}
void reverseAtbash(char* atbash, char* reversed){
    int j=0;
    for(int i=strlen(atbash)-1;i>=0;--i){
        reversed[j++]=atbash[i];
    }
}
void Atbash(char* word,char* txt){
    char converted[WORD];
    char reversed[WORD];
    char result[WORD];
    int flag=0;
    convertAtbash(word,converted);
    reverseAtbash(converted,reversed);
    for(int i=0;i<strlen(txt)-strlen(converted);i++){
        if(txt[i]==' ') continue;
        int tmp=i;
        int j=0;
        for(;j<strlen(converted);j++)
        {
            while (txt[tmp+j]==' ')
            {
                tmp++;
            }
            result[j]=txt[tmp+j];
        }
        if(check(reversed,converted,result)){
            result[j]='\0';
            print_sub(result,flag);
            flag=1;
        }
        memset(result,0,WORD);
    }
}

int isClear(char* left){
    for(int i=0;i<strlen(left);i++){
        if(left[i]!=' '){
            return 0;
        }
    }
    return 1;
}
int match(char* left,char c){
    if(c==' ') return 1;
    for(int i=0;i<strlen(left);i++){
        if(c==left[i]){
            left[i]=' ';
            return 1;
        }
    }
    return 0;
}
void resetLeft(char* l, char* word)
{
    l[0]=' ';
    for (int i = 1; i <= strlen(word); i++)
    {
        l[i]=word[i-1];
    }
    
}
void Anagram(char* word, char* txt)
{
    char left[WORD];
    int flag=0;
    resetLeft(left,word);
    char solution[TXT];
    int sol_counter=0;
    int flag_2=1;
    for(int i=0;i<strlen(txt);i++){
        if(flag_2&& txt[i]==' ') continue;
        if(match(left,txt[i])){
            flag_2=0;
            solution[sol_counter++]=txt[i];
            if(isClear(left)){
                flag_2=1;
                solution[sol_counter]='\0';
                print_sub(solution,flag);
                flag=1;
                resetLeft(left,word);
                sol_counter=0;
                memset(solution,0,TXT);
            }
        }
        else{
            flag_2=1;
            i=i-sol_counter;
            sol_counter=0;
            memset(solution,0,TXT);
            resetLeft(left,word);
        }
    }
}

int main()
{
    char word[WORD];
    char txt[TXT];
    getString(word,txt);
    printf("Gematria Sequences: ");
    Gematria(word,txt);
    printf("\n");
    printf("Atbash Sequences: ");
    Atbash(word,txt);
    printf("\n");
    printf("Anagram Sequences: ");
    Anagram(word,txt);
    return 0;
}