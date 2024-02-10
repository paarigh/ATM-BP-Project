#ifndef LOGIN
#define LOGIN  

#include <stdio.h>

struct account
{
	char firstname[30];
	char lastname[30];
	char id[7] ;
	char password[5];
	char accountnumber[10];
	char bankname[6];
	int  money;
};
struct atm
{
	struct account* bank;
	int numofaccounts;
};

void loginpage(struct account*p);
int countlines(FILE* filename);
void menue();
int cinmoney(int* money); //returns 1 succesful
int getmoney(int* money, struct atm* p, int numperson , struct account r); //returns 1 succesful
int everything(FILE* f, int* flage, int* money , int numoflinesinfile, struct atm all);
int checkid(struct account* p ,int *flagrightornot);
int putmoney(int* money, struct atm* p, int numperson , struct account r);
void loginpage2(struct account* p); //for transfering 
int checkid2(struct account* p, int* flagrightornot2); //for transfering
int transfermoney(int* money, struct atm* p, int numperson2 ,int numperson, struct account r);
void updatefile(FILE* f, int numoflines, struct atm *all , char filename , char** words);
void last10();
FILE* openfile(struct account* p);

#endif

