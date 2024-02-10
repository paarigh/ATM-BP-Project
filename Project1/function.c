#include "function.h"
#include <string.h>
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 100

void loginpage(struct account *p)
{   
    char tmp;
    char id[7], password[5];

    printf("Enter your ID: ");
    scanf_s("%6s", id ,7);
    do
    {   //momkene karbar bishtar az 6 ta bede 
        //in mige oonghadr begir ta be /n beresi
        tmp = getchar(); //ye char migire mindaze door 
    } while (tmp != '\n');
    printf("Enter your password: ");
    fgets(password, 5, stdin);
    do
    {
        tmp = getchar();
    } while (tmp != '\n');
    memcpy(p[0].id, id, 6);
    p[0].id[6] = NULL;
    memcpy(p[0].password, password, 4);
    p[0].password[4] = NULL;


}
void loginpage2(struct account* p)
{
    
        char accountnumber[11], bankname[9];

        printf("Enter your destination bank: ");
        getchar();
        fgets(bankname, 6, stdin);
        getchar();
        printf("Enter the account number: ");
     
        //too vorodi espac migereft
        scanf_s("%10s", accountnumber, 10);
        memcpy(p[0].accountnumber, accountnumber, 9);
        memcpy(p[0].bankname, bankname, 5);
    

}
int countlines(FILE* fp)
{
    // count the number of lines in the file called filename                                    
    int ch = 0;
    int lines = 0;

    if (fp == NULL)
    return 0;

    lines++;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
            lines++;
    }
    return lines;
}

void menue() {
    printf("enter 1 for getting money from wallet:\n");
    printf("enter 2 for putting money in the wallet:\n");
    printf("enter 3 for transferring money:\n");
    printf("enter 4 to go to the previous page:\n");
    printf("enter 5 for checking money:\n");
    printf("enter 6 for seeing last 10 proc:\n");
}
int cinmoney(int* money )
{
    scanf_s("%d", money, 1);
    if (*money >= 0)
    {
        //movafagh
        return 1;

    }
    else
    {
        printf("wrong number\n");
        return 0;
       
    }
}
int getmoney(int* money, struct atm p, int numperson , struct account r)
{
    if (p.bank[numperson].money >= *money)    //chek koni ke onghadr pool dare ya na 
    {  
        FILE* x;
        p.bank[numperson].money = p.bank[numperson].money - *money;
        printf("%d was geted from the wallet: \n" , *money);
        x = openfile(&r);
        fprintf(x, "%d%s", *money, ".geted ");   // update file
        fclose(x);
        return 1; //movafagh
   
    }

    return 0;

}
int putmoney(int* money, struct atm p, int numperson , struct account r)
{
    
    
    FILE* x;
    p.bank[numperson].money = p.bank[numperson].money + *money;
    printf("%d was puted in the wallet: \n", *money);
    x = openfile(&r);
    fprintf(x, "%d%s", *money, ".puted ");
    fclose(x);      // update file
    return 1; //movafagh

  
}
int checkid(struct account* p, int* flagrightornot , int numoflinesinfile , struct atm all)
{
    int i;
    char x[6], y[4] , z[6] , k[4];
    while (p[0].id < 0 || p[0].password < 0)
  {
        *flagrightornot = 0;
  }
    memcpy(z, p[0].id, 6);
    memcpy(k, p[0].password, 4);
  for (i = 0; i < numoflinesinfile; i++)
  {
      memcpy(x, all.bank[i].id, 6);
      memcpy(y, all.bank[i].password, 4);
      if (x[0]==z[0] && x[1] == z[1] && x[2] == z[2] && x[3] == z[3] && x[4] == z[4] && x[5] == z[5] &&y[0]==k[0] && y[1] == k[1] && y[2] == k[2])
      { 
          *flagrightornot = 1;
          return i;
          
      }
    
  }
}int checkid2(struct account* p, int* flagrightornot2, int numoflinesinfile, struct atm all)
{
    int i, flag = 1;
    char x[9], y[5], z[9], k[5];
    while (p[0].accountnumber < 0)
    {
        *flagrightornot2 = 0;
    }
    memcpy(z, p[0].accountnumber, 9);
    memcpy(k, p[0].bankname, 5);
    for (i = 0; i < numoflinesinfile; i++)
    {
        memcpy(x, all.bank[i].accountnumber, 9);
        memcpy(y, all.bank[i].bankname, 5);
        if (x[0] == z[0] && x[1] == z[1] && x[2] == z[2] && x[3] == z[3] && x[4] == z[4] && x[5] == z[5] && x[6] == z[6] && x[7] == z[7] && x[8] == z[8]  &&  y[0] == k[0] && y[1] == k[1] && y[2] == k[2] && y[3] == k[3] && y[4] == k[4])
        {

            *flagrightornot2 = 1;
            flag = 0;
            return i;

        }
       
    }
    if (flag == 1)
    {    
        printf("wrong number!:\n");
        *flagrightornot2 = 0;
    }
}
int transfermoney(int* money, struct atm p, int numperson2 , int numperson , struct account r)
{
    if (p.bank[numperson].money >= *money)    //chek koni ke onghadr pool dare ya na 
    {
        FILE* x;
        p.bank[numperson].money = p.bank[numperson].money - *money;
        p.bank[numperson2].money = p.bank[numperson2].money + *money;
        printf("%d was transfered from the wallet: \n", *money);
        x = openfile(&r);
        fprintf(x, "%d%s", *money, ".transfered ");
        fclose(x);
        return 1; //movafagh

    }
}
void updatefile(FILE* f, int numoflines, struct atm* all, char filename, char* words)
{
    int j = 0, i = 0;
    for (j = 0; j < numoflines; j++)
    {
        fprintf(f, "%s ", all->bank[j].firstname);
        i++;
        fprintf(f, "%s ", all->bank[j].lastname);
        i++;
        fprintf(f, "%6s ", all->bank[j].id);
        i++;
        fprintf(f, "%4s ", all->bank[j].password);
        i++;
        fprintf(f, "%9s ", all->bank[j].accountnumber);
        i++;
        fprintf(f, "%5s ", all->bank[j].bankname);
        i++;
        fprintf(f, "%d", all->bank[j].money); // Removed the space after %d
        if (j != numoflines - 1) // Add a newline only if it's not the last line
            fprintf(f, "\n");
    }
    fclose(f);
}

void last10( struct account p)
{

        char filename[20];
        int u = atoi(p.id);
        int i = 0 , j , n;
        char words[MAX_WORDS][MAX_WORD_LENGTH];
        // Create the filename by concatenating the value of 'u' with ".txt"
        snprintf(filename, sizeof(filename), "%d.txt", u);
        FILE* file;
        fopen_s(&file, filename, "r");

       // fseek(file, 0, SEEK_SET);
        while (fscanf_s(file, "%s", words[i], MAX_WORD_LENGTH) == 1) {
            i++;  // i is important
        }
        fclose(file);
        i--;
        j = i - 10;
        n = i;
        if (i >= 10)
        {    
            fopen_s(&file, filename, "w");
            for (i = i; i >j; i--)
            {
                printf(words[i]);
                printf("\n");    //show
            }
            for (j = j+1; j<=n; j++)
            {
                fprintf(file, "%s ", words[j]); // update file
            }
            fclose(file);
        }
        else
        {
            for (i = i; i >=0; i--)
            {
                printf(words[i]);
                printf("\n");    //show
            }
        }
        

  

       
  

}

FILE* openfile(struct account *p)
{
    char filename[20];
    int u = atoi(p[0].id);
    int i = 0, j, n;
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    // Create the filename by concatenating the value of 'u' with ".txt"
    snprintf(filename, sizeof(filename), "%d.txt", u);
    FILE* file;
    fopen_s(&file, filename, "a+");
    return file;
}