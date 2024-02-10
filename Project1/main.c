#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 100
int main() {
    int numoflinesinfile, menuenum, flage = 0, numofperson = 0, x, proc2 = 0, menueproc = 0, num = 0;
    int i = 0, j = 0, y, flagrightornot = 0, k, * money, numofperson2 = 0, flagrightornot2 = 0;
    int moneyproc = 0, num2 = 0, num3 = 0, num4 = 0, num6=0;
    struct atm* all;
    char filename[] = "test.txt";
    char filename2[] = "tesr.txt";
    char filename3[11];
    char words[MAX_WORDS][MAX_WORD_LENGTH];
    char t[3];
    struct account p[2];
    for (i = 0; i < MAX_WORDS; i++) {
        for (j = 0; j < MAX_WORD_LENGTH; j++) {
            words[i][j] = '\0'; // NULL all blanks of matrix
        }
    }
    i = 0;
    j = 0;
    struct account acc;
    memset(&acc, NULL, sizeof(acc)); // NULL all blanks of struct
    money = (int*)malloc(2 * sizeof(int));
    FILE* f;
    fopen_s(&f, filename, "r");
    fseek(f, 0, SEEK_SET);
    while (fscanf_s(f, "%s", words[i], MAX_WORD_LENGTH) == 1) {
        i++;
    }
    fseek(f, 0, SEEK_SET);

    numoflinesinfile = countlines(f);
    all = (struct atm*)malloc(sizeof(struct atm));
    all->bank = (struct account*)malloc(numoflinesinfile * sizeof(struct account));
    i = 0;

    for (j = 0; j < numoflinesinfile; j++)
    {
        strcpy_s(all->bank[j].firstname, 30, words[i]);
        i++;
        strcpy_s(all->bank[j].lastname, 30, words[i]);
        i++;
        memcpy(all->bank[j].id, words[i], 7);
        i++;
        memcpy(all->bank[j].password, words[i], 5);
        i++;
        memcpy(all->bank[j].accountnumber, words[i], 10);
        i++;
        memcpy(all->bank[j].bankname, words[i], 6);
        i++;
        all->bank[j].money = atoi(words[i]); //exeption mikhord
        i++;
    }

    i = 0;
    j = 0;
    
    all->numofaccounts = numoflinesinfile;
    loginpage(&p[0]);
    fclose(f);
    numofperson = checkid(&p, &flagrightornot, numoflinesinfile, all);
    system("CLS");
    while (proc2 == 0) // in halghe roye menue micharkhe vase proc 2 
    {   
        num = 0;
        menueproc = 0;
        menuenum = 0;
        num2 = 0;
        num3 = 0;
        moneyproc = 0;
        num4 = 0;
        num6 = 0;

        while (menueproc == 0)
        {
            while (flagrightornot == 0)
            {
                printf(" WRONG NUMBER ,please enter again : \n");
                loginpage(&p[0]);
                checkid(&p, &flagrightornot, numoflinesinfile, all);
            }

            if (flagrightornot == 1)
            {
                system("CLS");
                menue();
                scanf_s("%d", &menuenum, 1);
                if (menuenum == 4)
                {
                    flagrightornot = 0; // bere vard loop bala beshe 
                    continue;
                }
                else
                    break;
            }
        }
        system("CLS");
        if (menuenum == 1)
        {
            while (moneyproc == 0)
            {
                printf("enter 1 to go to the previous page or 5 to enter money :\n");
                scanf_s("%d", &num4, 1);
                system("CLS");
                if (num4 == 1)
                {
                    proc2 = 0;
                    break;
                }
                printf("enter the money:\n");
                y = cinmoney(&money);
                system("CLS");
                if (y == 0)
                {
                    printf("enter 1 to go to the previous page or 5 for the next page :\n");
                    scanf_s("%d", &menuenum, 1);
                    system("CLS");
                    if (menuenum == 1)
                        continue;
                    else
                    {
                        fopen_s(&f, filename, "w");
                        updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                        break;
                    }
                    printf("Do you want another process?\n");
                    printf("Enter 1 for yes.\n");
                    printf("Enter 2 for no.\n");
                    scanf_s("%d", &k, 4);
                    system("CLS");
                    if (k == 1)
                        break;
                    else
                    {
                        fopen_s(&f, filename, "w");
                        updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                        proc2 = 1;
                        break;
                    }
                }
                if (y == 1)
                {


                    printf("enter 1 to go to the previous page and 5 for not:\n");
                    scanf_s("%d", &num, 1);
                    system("CLS");
                    if (num == 1)
                        continue;

                    x = getmoney(&money, all, numofperson , p[0]);
                   
                    if (x == 1)
                    {
                        printf("Do you want another process?\n");
                        printf("Enter 1 for yes.\n");
                        printf("Enter 2 for no.\n");
                        scanf_s("%d", &k, 4);
                        system("CLS");
                        if (k == 1)
                        {
                            break;

                        }
                        else
                        {
                            fopen_s(&f, filename, "w");
                            updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                            proc2 = 1;
                            break;

                        }
                    }

                    if (x == 0)
                    {
                        printf("You don't have enough money.\n");
                        printf("Do you want another process?\n");
                        printf("Enter 1 for yes.\n");
                        printf("Enter 2 for no.\n");
                        scanf_s("%d", &k, 4);
                        system("CLS");
                        if (k == 1)
                            continue;
                        else
                        {
                            fopen_s(&f, filename, "w");
                            updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                            return 0;
                        }
                    }
                }
            }
        }
        if (menuenum == 2)
        {
            while (moneyproc == 0)
            {
                printf("enter 1 to go to the previous page or 5 to enter money:\n");
                scanf_s("%d", &num4, 1);
                system("CLS");
                if (num4 == 1)
                {
                    proc2 = 0;
                    break;
                }
                printf("enter the money:\n");
                y = cinmoney(&money);
                system("CLS");
                if (y == 0)
                {
                    printf("enter 1 to go to the previous page or 5 for the next page :\n");
                    scanf_s("%d", &menuenum, 1);
                    system("CLS");
                    if (menuenum == 1)
                        continue;
                    else
                    {
                        fopen_s(&f, filename, "w");
                        updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                        break;
                    }
                    printf("Do you want another process?\n");
                    printf("Enter 1 for yes.\n");
                    printf("Enter 2 for no.\n");
                    scanf_s("%d", &k, 4);
                    system("CLS");
                    if (k == 1)
                        break;
                    else
                    {
                        fopen_s(&f, filename, "w");
                        updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                        proc2 = 1;
                        break;
                    }

                }

                if (y == 1)
                {
                    printf("enter 1 to go to the previous page or 5 for the next page :\n");
                    scanf_s("%d", &num, 1);
                    system("CLS");
                    if (num == 1)
                        continue;
                    x = putmoney(&money, all, numofperson ,p[0]);
                   
                    if (x == 1)
                    {
                        printf("Do you want another process?\n");
                        printf("Enter 1 for yes.\n");
                        printf("Enter 2 for no.\n");
                        scanf_s("%d", &k, 4);
                        system("CLS");
                        if (k == 1)
                            break;
                        else
                        {
                            fopen_s(&f, filename, "w");
                            updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                            proc2 = 1;
                            break;
                        }
                    }

                }
            }
        }

        if (menuenum == 3)
        {
            while (num3 == 0)
            {
                printf("enter 1 to go to the previous page or 5 to login::\n");
                scanf_s("%d", &num4, 1);
                system("CLS");
                if (num4 == 1)
                {
                    proc2 = 0;
                    break;
                }
                loginpage2(&p[0]);
                numofperson2 = checkid2(&p, &flagrightornot2, numoflinesinfile, all);
                printf("enter 1 to go to the previous page or 5 for the next page:\n");
                scanf_s("%d", &num, 1);
                system("CLS");
                if (num == 1)
                    continue;

                while (flagrightornot2 == 0)
                {

                    loginpage2(&p[0]);
                    numofperson2 = checkid2(&p, &flagrightornot2, numoflinesinfile, all);
                }
                if (flagrightornot == 1)
                {
                    while (num2 == 0) {
                        printf("enter money:\n");
                        y = cinmoney(&money);
                        system("CLS");
                        while (y != 1)
                        {
                            printf("wrong number ! enter again\n");
                            y = cinmoney(&money);
                            system("CLS");
                        }

                        if (y == 1) // adad mosbat
                        {
                            printf("enter 1 to go to the previous page or 5 for the next page:\n");
                            scanf_s("%d", &num, 1);
                            system("CLS");
                            if (num == 1)
                                continue;
                            x = transfermoney(&money, all, numofperson2, numofperson , p[0]);
                           
                            if (x == 1) // movafagh
                            {
                                printf("Do you want another process?\n");
                                printf("Enter 1 for yes.\n");
                                printf("Enter 2 for no.\n");
                                scanf_s("%d", &k, 4);
                                system("CLS");
                                if (k == 1)
                                {
                                    num3 = 1;
                                    num2 = 1;
                                    continue;
                                }
                                else
                                {
                                    fopen_s(&f, filename, "w");
                                    updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                                    num3 = 1;
                                    num2 = 1;
                                    proc2 = 1;
                                    return 0;
                                }
                            }
                            else
                            {
                                printf("you don't have enough money.\n ");
                                system("CLS");
                                printf("Do you want another process?\n");
                                printf("Enter 1 for yes.\n");
                                printf("Enter 2 for no.\n");
                                scanf_s("%d", &k, 4);
                                system("CLS");
                                if (k == 1)
                                {
                                    num3 = 1;
                                    num2 = 1;
                                    continue;
                                }
                                else
                                {
                                    fopen_s(&f, filename, "w");
                                    updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                                    num3 = 1;
                                    num2 = 1;
                                    proc2 = 1;
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (menuenum == 5)
        {
            printf("enter 1 to go to the previous page or 5 for the next page:\n");
            scanf_s("%d", &num, 1);
            system("CLS");
            if (num == 1)
                continue;
            money = all->bank[numofperson].money;
            printf("you have %d dollars in the wallet:\n", money);
            system("CLS");
            printf("Do you want another process?\n");
            printf("Enter 1 for yes.\n");
            printf("Enter 2 for no.\n");
            scanf_s("%d", &k, 4);
            system("CLS");

            if (k == 1)

                continue;
            else
            {
                fopen_s(&f, filename, "w");
                updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                return 0;
            }
        }
        if (menuenum == 6)
        {
            printf("enter 1 to go to the previous page or 5 to see last 10 proc :\n");
            scanf_s("%d", &num6, 1);
            system("CLS");
            if (num6 == 1)
            {
                continue;
            }
            last10(p);
            printf("Do you want another process?\n");
            printf("Enter 1 for yes.\n");
            printf("Enter 2 for no.\n");
            scanf_s("%d", &k, 4);
            system("CLS");
            if (k == 1)
                continue;
            else
            {
                fopen_s(&f, filename, "w");
                updatefile(f, numoflinesinfile, all, "test.txt", &words[0]);
                break;
            }
        }
    }
}
