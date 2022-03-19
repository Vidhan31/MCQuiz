#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// struct score_detail to store and return right, wrong, skipped questions as well as score of a section 
/*
    rws[0]->right answers
    rws[1]->wrong answers
    rws[2]->skipped questions
    rws[3]->calculated score
*/
struct score_detail
{
    int rws[4];  
};

// to store details of a candidate
struct candidate
{
    char name[100],prn[20],class[20];
    int roll;
    struct score_detail score; // to store final score of candidate (including wrong, right, skipped questions)
};


void instructions();
char candidate_instruction(char*);
struct score_detail test();
struct score_detail dms(); 
struct score_detail pic();
struct score_detail sepm();
struct score_detail wt();
struct score_detail ds();
void enterScore(struct candidate temp);


int main()
{
    char choice;
// home page
home:
    system("cls");
    printf("\t\t\tMCQ TEST USING C PROGRAM\n");
    printf("\n\t\t****************************************");
    printf("\n\t\t               WELCOME");
    printf("\n\t\t________________________________________");
    printf("\n\t\t               MCQ TEST   ");
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\t\t > Press A attempt test.");
    printf("\n\t\t > Press I to read instructions");
    printf("\n\t\t > Press Q to quit");
    printf("\n\t\t________________________________________\n\n");
    choice = toupper(getch());
    if (choice == 'I')
    {
        instructions();
        printf("\n\nPress any key to go to home page...");
        getch();
        goto home;
    }
    else if (choice=='A')
    {
        goto details;
    }
    else if (choice=='Q')
    {
        return 0;
    }
    else{
        printf("\n\nWrong choice.\nPress any key to try again...");
        getch();
        goto home;
    }

// Take details
details:
    system("cls");
    struct candidate c1;
    printf("\n\n\n\n\n\t\t\t***************************************************");
    printf("\n\n\t\t\t\t\t Enter your details\n");
    printf("\t\t\t\t\t Name: ");gets(c1.name);
    printf("\t\t\t\t\t Class: ");scanf("\n");gets(c1.class);
    printf("\t\t\t\t\t Roll No.: ");scanf("%d",&c1.roll);
    printf("\t\t\t\t\t PRN No.: ");scanf("\n");gets(c1.prn);
    printf("\n\n\n\t\t\t***************************************************");
    printf("\n\n\t\t\t\t\t Press P to proceed.... ");
    printf("\n\t\t\t\t\t Press any key to go back....");
    if(toupper(getch())=='P')
    {
        choice = candidate_instruction(c1.name);  //display instructions before starting test
        if(choice=='Y')
        {
            c1.score = test(); // run test section wise and return final score including right, wrong, skipped ques
            system("cls");
            printf("\n\n\n\n\n\t\t\t***************************************************************************");
            printf("\n\n\t\t\t\tCongratualations %s, You have completed your test...",c1.name);
            printf("\n\n\t\t\t\tYour Final Score is: ");
            printf("\n\n\t\t\t\tTotal Correct Answers: %d",c1.score.rws[0]);
            printf("\n\t\t\t\tTotal Wrong Answers: %d",c1.score.rws[1]);
            printf("\n\t\t\t\tTotal Unattempted Questions: %d",c1.score.rws[2]);
            printf("\n\t\t\t\tTotal Score out of 100: %d",c1.score.rws[3]);
            printf("\n\n\n\t\t\t***************************************************************************");
            enterScore(c1);
            printf("\n\n\t\t\t\tPress any key to home page...");
            getch();
            goto home;
        }
        else
        {
            goto home;
        }
    }
    else
        goto home;
    
} // main() end

// instructions that will be displayed from home screen
void instructions()
{
    system("cls");
    printf("\n\n                              INSTRUCTIONS");
    printf("\n -----------------------------------------------------------------------------");
    printf("\n ............................ C program MCQ test .............................");
    printf("\n >> This is an multiple choice questions exam");
    printf("\n >> At first you will be asked to enter your name, roll no., class and prn no.");
    printf("\n >> This test will have 5 sections, each section having 5 questions. ");
    printf("\n    After 1st section is completed, immediately 2nd section will be loaded , then 3rd and so on.");
    printf("\n >> You will be given 4 options and you have to press A, B ,C or D for the right option");
    printf("\n    Options are NOT case sensitive");
    printf("\n    If any other key is pressed then the question will be treated as unattempted and hence");
    printf("\n    0 marks will be added for that question.");
    printf("\n >> NEGATIVE MARKING. For every correct answer 4 marks will be added and for every wrong");
    printf("\n    attempt 1/4 of 4 marks will be deducted i.e, 1 mark will be deducted");
    printf("\n >> No marks will be deducted for unattempted questions.");
    printf("\n >> There is not time limit for attempting questions.");
    printf("\n >> Once a question is skipped/attempted, you cannot go back to the question.");
    printf("\n\n**************************** ALL THE BEST ***********************************");
}

// instructions that will display after taking input
char candidate_instruction(char* name)
{
    char choice;
    system("cls");
    printf("\n\n                              INSTRUCTIONS");
    printf("\n                             Welcome %s ",name);
    printf("\n .............................................................................");
    printf("\n >> This is an multiple choice questions exam");
    printf("\n >> This test will have 5 sections, each section having 5 questions. ");
    printf("\n    After 1st section is completed, immediately 2nd section will be loaded , then 3rd and so on.");
    printf("\n >> You will be given 4 options and you have to press A, B ,C or D for the right option");
    printf("\n    Options are NOT case sensitive");
    printf("\n    If any other key is pressed then the question will be treated as unattempted and hence");
    printf("\n    0 marks will be added for that question.");
    printf("\n >> NEGATIVE MARKING. For every correct answer 4 marks will be added and for every wrong");
    printf("\n    attempt 1/4 of 4 marks will be deducted i.e, 1 mark will be deducted");
    printf("\n >> No marks will be deducted for unattempted questions.");
    printf("\n >> There is not time limit for attempting questions.");
    printf("\n >> Once a question is skipped/attempted, you cannot go back to the question.");
    printf("\n\n**************************** ALL THE BEST ********************************");
    printf("\n\n\t Press Y to attempt test.");
    printf("\n\n\t Press any key to go to home page...");
    choice = toupper(getch());
    return choice;
}

// Actual Test of total 25 questions
struct score_detail test()
{
    int i,j,temp[5][4]; // temp[5][4] to store and calculate output of all sections (5 sections * 4 outputs)
    struct score_detail pic_score, dms_score, wt_score, sepm_score, ds_score, record;
    for(i=1;i<=5;i++)
    {
        switch (i)
        {
        case 1:
            pic_score = pic();
            printf("\n\nYour score in Section %d = %d",i,pic_score.rws[3]);
            printf("\nPress any key to proceed to Section %d",i+1);
            for(j=0;j<4;j++)
               temp[i-1][j]=pic_score.rws[j];
            getch();
            break;
        case 2:
            dms_score = dms();
            printf("\n\nYour score in Section %d = %d",i,dms_score.rws[3]);
            printf("\nPress any key to proceed to Section %d",i+1);
            for(j=0;j<4;j++)
                temp[i-1][j]=dms_score.rws[j];
            getch();
            break;
        case 3:
            ds_score = ds();
            printf("\n\nYour score in Section %d = %d",i,ds_score.rws[3]);
            printf("\nPress any key to proceed to Section %d",i+1);
            for(j=0;j<4;j++)
                temp[i-1][j]=ds_score.rws[j];
            getch();
            break;
        case 4:
            wt_score = wt();
            printf("\n\nYour score in Section %d = %d",i,wt_score.rws[3]);
            printf("\nPress any key to proceed to Section %d",i+1);
            for(j=0;j<4;j++)
                temp[i-1][j]=wt_score.rws[j];
            getch();
            break;
        case 5:
            sepm_score = sepm();
            printf("\n\nYour score in Section %d = %d",i,sepm_score.rws[3]);
            printf("\nThis was the last section, Press any key to end test...");
            for(j=0;j<4;j++)
                temp[i-1][j]=sepm_score.rws[j];
            getch();
            break;
        default:
            break;
        }
    }
    for(i=0;i<4;i++)
    {
        record.rws[i]=0;
        for(j=0;j<5;j++)
        {
            record.rws[i]+=temp[j][i]; // add all counters of right answers, wrong ans, skipped and final score.
        }
    }
    return record;
}

// section 1 PIC MCQs
struct score_detail pic()
{
    int i;
    char option;
    struct score_detail pic;
    for(i=0;i<4;i++)
    {
        pic.rws[i]=0;
    }
    for(i=0;i<=5;i++)
    {
        system("cls");
        printf("\n\n\tSection 1: Programming in C ");
        switch (i)
        {
        case 1:
            printf("\n\nC preprocessors can have compiler specific features.");
			printf("\n\nA.True\t\tB.Depends on the Standard\n\nC.False\t\tD.Depends on the Platform");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'A')
			{
				printf("\n\nCorrect answer");
				pic.rws[0]++;
				getch();
				break;
			}
			else if (option == 'C' || option == 'B' || option == 'D')
			{
			    printf("\n\nWrong answer");
				pic.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                pic.rws[2]++;
                getch();
                break;
            }
        case 2:
            printf("\n\nWhich of the following are C preprocessors?");
			printf("\n\nA.#ifdef\t\tB.#define\n\nC.#endif\t\tD.all of the mentioned");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'D')
			{
				printf("\n\nCorrect answer");
				pic.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'C')
			{
			    printf("\n\nWrong answer");
				pic.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                pic.rws[2]++;
                getch();
                break;
            }
        case 3:
            printf("\n\nHow many number of pointer (*) does C have against a pointer variable declaration?");
			printf("\n\nA.7\t\tB.127\n\nC.255\t\tD.No Limits");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'D')
			{
				printf("\n\nCorrect answer");
				pic.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'C')
			{
			    printf("\n\nWrong answer");
				pic.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                pic.rws[2]++;
                getch();
                break;
            }
        case 4:
            printf("\n\nIn C language, FILE is of which data type?");
			printf("\n\nA.int\t\tB.char*\n\nC.struct\t\tD.None of the mentioned");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'C')
			{
				printf("\n\nCorrect answer");
				pic.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'D')
			{
			    printf("\n\nWrong answer");
				pic.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                pic.rws[2]++;
                getch();
                break;
            }
        case 5:
            printf("\n\nWhich of the following is not an operator in C?");
			printf("\n\nA. ,\t\tB.sizeof()\n\nC. ~\t\tD.None of the mentioned");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'D')
			{
				printf("\n\nCorrect answer");
				pic.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'C')
			{
			    printf("\n\nWrong answer");
				pic.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                pic.rws[2]++;
                getch();
                break;
            }
        default:
            break;
        }
    }
    printf("\n\n\t\tCorrect Answers: %d",pic.rws[0]);
    printf("\n\t\tWrong Answers: %d",pic.rws[1]);
    printf("\n\t\tUnattempted: %d",pic.rws[2]);
    pic.rws[3] = (pic.rws[0]*4)-pic.rws[1];
    return pic;
}

// section 2 DMS MCQs
struct score_detail dms()
{
    int i;
    char option;
    struct score_detail dms;
    for(i=0;i<4;i++)
    {
        dms.rws[i]=0;
    }
    for(i=0;i<=5;i++)
    {
        system("cls");
        printf("\n\n\tSection 2: Database Management System ");
        switch (i)
        {
        case 1:
            printf("\n\nWhat is Oracle database used for?");
			printf("\n\nA.Creating backup for data\t\tB.Accessing database servers\n\nC.Store and retrieve relevant data\t\tD.Both a & c");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'C')
			{
				printf("\n\nCorrect answer");
				dms.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'D')
			{
			    printf("\n\nWrong answer");
				dms.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                dms.rws[2]++;
                getch();
                break;
            }
        case 2:
            printf("\n\nWhich of the following components comprise an Oracle architecture?");
			printf("\n\nA.Tablespaces\t\tB.Database related background processes\n\nC.Datafiles\t\tD.All of the Mentioned");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'D')
			{
				printf("\n\nCorrect answer");
				dms.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'C')
			{
			    printf("\n\nWrong answer");
				dms.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                dms.rws[2]++;
                getch();
                break;
            }
        case 3:
            printf("\n\nWhich of the following is another name of Oracle database design?");
			printf("\n\nA.Database Instance\t\tB.Database Schema\n\nC.Database Abstraction\t\tD.None of the Mentioned");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'B')
			{
				printf("\n\nCorrect answer");
				dms.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'C' || option == 'D')
			{
			    printf("\n\nWrong answer");
				dms.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                dms.rws[2]++;
                getch();
                break;
            }
        case 4:
            printf("\n\nWhich of the following is the smallest unit of storage in an Oracle database?");
			printf("\n\nA.Segment\t\tB.Extent\n\nC.Data File\t\tD.Data Block");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'D')
			{
				printf("\n\nCorrect answer");
				dms.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'C')
			{
			    printf("\n\nWrong answer");
				dms.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                dms.rws[2]++;
                getch();
                break;
            }
        case 5:
            printf("\n\nWhich of the following is used to logically group data together?");
			printf("\n\nA.Tablespace\t\tB.Datafiles\n\nC.Object\t\tD.Database");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'A')
			{
				printf("\n\nCorrect answer");
				dms.rws[0]++;
				getch();
				break;
			}
			else if (option == 'C' || option == 'B' || option == 'D')
			{
			    printf("\n\nWrong answer");
				dms.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                dms.rws[2]++;
                getch();
                break;
            }
        default:
            break;
        }
    }
    printf("\n\n\t\tCorrect Answers: %d",dms.rws[0]);
    printf("\n\t\tWrong Answers: %d",dms.rws[1]);
    printf("\n\t\tUnattempted: %d",dms.rws[2]);
    dms.rws[3] = (dms.rws[0]*4)-dms.rws[1];
    return dms;
}

// section 3 DS MCQs
struct score_detail ds()
{
    int i;
    char option;
    struct score_detail ds;
    for(i=0;i<4;i++)
    {
        ds.rws[i]=0;
    }
    for(i=0;i<=5;i++)
    {
        system("cls");
        printf("\n\n\tSection 3: Discrete Structure ");
        switch (i)
        {
        case 1:
            printf("\n\nWhich of the following is a subset of set {1, 2, 3, 4}?");
			printf("\n\nA.{1, 2}\t\tB.{1, 2, 3}\n\nC.{1}\t\tD.All of the mentioned");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'D')
			{
				printf("\n\nCorrect answer");
				ds.rws[0]++;
				getch();
				break;
			}
			else if (option == 'C' || option == 'B' || option == 'A')
			{
			    printf("\n\nWrong answer");
				ds.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                ds.rws[2]++;
                getch();
                break;
            }
        case 2:
            printf("\n\nConvert the set x in roster form if set x contains the positive prime number, which divides 72.");
			printf("\n\nA.{∅}\t\tB.{2, 3}\n\nC.{2, 3, 7}\t\tD.{3, 5, 7}");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'B')
			{
				printf("\n\nCorrect answer");
				ds.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'D' || option == 'C')
			{
			    printf("\n\nWrong answer");
				ds.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                ds.rws[2]++;
                getch();
                break;
            }
        case 3:
            printf("\n\nIf x is a set and the set contains the real number between 1 and 2, then the set is ____.");
			printf("\n\nA.Empty set\t\tB.Finite set\n\nC.Infinite set\t\tD.None of the mentioned");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'C')
			{
				printf("\n\nCorrect answer");
				ds.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'D')
			{
			    printf("\n\nWrong answer");
				ds.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                ds.rws[2]++;
                getch();
                break;
            }
        case 4:
            printf("\n\nPower set of empty or Null set has exactly ___ subset.");
			printf("\n\nA.One\t\tB.Two\n\nC.Zero\t\tD.Three");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'A')
			{
				printf("\n\nCorrect answer");
				ds.rws[0]++;
				getch();
				break;
			}
			else if (option == 'C' || option == 'B' || option == 'D')
			{
			    printf("\n\nWrong answer");
				ds.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                ds.rws[2]++;
                getch();
                break;
            }
        case 5:
            printf("\n\nThe members of the set S = {x | x is the square of an integer and x < 100} is ______");
			printf("\n\nA.{0, 2, 4, 5, 9, 55, 46, 49, 99, 81}\t\tB.{1, 4, 9, 16}\n\nC.{0, 1, 4, 9, 16, 25, 36, 49, 64, 81}\t\tD.{0, 1, 4, 9, 25, 36, 49, 123}");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'C')
			{
				printf("\n\nCorrect answer");
				ds.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'D')
			{
			    printf("\n\nWrong answer");
				ds.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                ds.rws[2]++;
                getch();
                break;
            }
        default:
            break;
        }
    }
    printf("\n\n\t\tCorrect Answers: %d",ds.rws[0]);
    printf("\n\t\tWrong Answers: %d",ds.rws[1]);
    printf("\n\t\tUnattempted: %d",ds.rws[2]);
    ds.rws[3] = (ds.rws[0]*4)-ds.rws[1];
    return ds;
}

// section 4 WT MCQs
struct score_detail wt()
{
    int i;
    char option;
    struct score_detail wt;
    for(i=0;i<4;i++)
    {
        wt.rws[i]=0;
    }
    for(i=0;i<=5;i++)
    {
        system("cls");
        printf("\n\n\tSection 4: Web Technologies ");
        switch (i)
        {
        case 1:
            printf("\n\nThe HTML document contains a root tag called __");
			printf("\n\nA.HEAD\t\tB.Title\n\nC.Body\t\tD.HTML");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'D')
			{
				printf("\n\nCorrect answer");
				wt.rws[0]++;
				getch();
				break;
			}
			else if (option == 'C' || option == 'B' || option == 'A')
			{
			    printf("\n\nWrong answer");
				wt.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                wt.rws[2]++;
                getch();
                break;
            }
        case 2:
            printf("\n\nIf we want to place text around an image, which CSS property should we use?");
			printf("\n\nA.push\t\tB.float\n\nC.align\t\tD.wrap");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'B')
			{
				printf("\n\nCorrect answer");
				wt.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'D' || option == 'C')
			{
			    printf("\n\nWrong answer");
				wt.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                wt.rws[2]++;
                getch();
                break;
            }
        case 3:
            printf("\n\nWhich one of the following also known as Conditional Expression:");
			printf("\n\nA.Alternative to if-else\t\tB.Switch statement\n\nC.If-then-else statement\t\tD.immediate if");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'D')
			{
				printf("\n\nCorrect answer");
				wt.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'C')
			{
			    printf("\n\nWrong answer");
				wt.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                wt.rws[2]++;
                getch();
                break;
            }
        case 4:
            printf("\n\nIn JavaScript, what is a block of statement?");
			printf("\n\nA.Conditional block\nB.block that combines a number of statements into a single compound statement\nC.both conditional block and a single statement\nD.block that contains a single statement");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'B')
			{
				printf("\n\nCorrect answer");
				wt.rws[0]++;
				getch();
				break;
			}
			else if (option == 'C' || option == 'A' || option == 'D')
			{
			    printf("\n\nWrong answer");
				wt.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                wt.rws[2]++;
                getch();
                break;
            }
        case 5:
            printf("\n\nWhich of the following variables takes precedence over the others if the names are the same?");
			printf("\n\nA.Global variable\t\tB.The local element\n\nC.The two of the above\t\tD.None of the above");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'B')
			{
				printf("\n\nCorrect answer");
				wt.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'C' || option == 'D')
			{
			    printf("\n\nWrong answer");
				wt.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                wt.rws[2]++;
                getch();
                break;
            }
        default:
            break;
        }
    }
    printf("\n\n\t\tCorrect Answers: %d",wt.rws[0]);
    printf("\n\t\tWrong Answers: %d",wt.rws[1]);
    printf("\n\t\tUnattempted: %d",wt.rws[2]);
    wt.rws[3] = (wt.rws[0]*4)-wt.rws[1];
    return wt;
}

// section 5 SEPM MCQs
struct score_detail sepm()
{
    int i;
    char option;
    struct score_detail sepm;
    for(i=0;i<4;i++)
    {
        sepm.rws[i]=0;
    }
    for(i=0;i<=5;i++)
    {
        system("cls");
        printf("\n\n\tSection 5: Software Engineering & Project Management");
        switch (i)
        {
        case 1:
            printf("\n\n ____ is a software development activity that is not a part of software processes");
			printf("\n\nA.Validation\t\tB.Specification\n\nC.Development\t\tD.Dependence");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'D')
			{
				printf("\n\nCorrect answer");
				sepm.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'C')
			{
			    printf("\n\nWrong answer");
				sepm.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                sepm.rws[2]++;
                getch();
                break;
            }
        case 2:
            printf("\n\n____ is defined as the process of generating analysis and designing documents?");
			printf("\n\nA.Re-engineering\t\tB.Reverse engineering\n\nC.Software re-engineering\t\tD.Science and engineering");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'B')
			{
				printf("\n\nCorrect answer");
				sepm.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'D' || option == 'C')
			{
			    printf("\n\nWrong answer");
				sepm.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                sepm.rws[2]++;
                getch();
                break;
            }
        case 3:
            printf("\n\nWhich one of the following is a requirement that fits in a developers module ?");
			printf("\n\nA.Availability\t\tB.Testability\n\nC.Usability\t\tD.Flexibility");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'A')
			{
				printf("\n\nCorrect answer");
				sepm.rws[0]++;
				getch();
				break;
			}
			else if (option == 'B' || option == 'C' || option == 'D')
			{
			    printf("\n\nWrong answer");
				sepm.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                sepm.rws[2]++;
                getch();
                break;
            }
        case 4:
            printf("\n\nConsider a system where, a heat sensor detects an intrusion and alerts the security company.” What kind of a requirement the system is providing?");
			printf("\n\nA.Functional\t\tB.Non-Functional\n\nC.Known Requirement\t\tD.None of the mentioned");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'C')
			{
				printf("\n\nCorrect answer");
				sepm.rws[0]++;
				getch();
				break;
			}
			else if (option == 'A' || option == 'B' || option == 'D')
			{
			    printf("\n\nWrong answer");
				sepm.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                sepm.rws[2]++;
                getch();
                break;
            }
        case 5:
            printf("\n\nWhich of the following is not a software risk?");
			printf("\n\nA.Product risk\t\tB.Project risk\n\nC.Business risk\t\tD.Management risk");
            printf("\n\nPress A, B, C or D for answer\nPress any other key to skip the question\n");
            option = toupper(getch());
			if (option == 'B')
			{
				printf("\n\nCorrect answer");
				sepm.rws[0]++;
				getch();
				break;
			}
			else if (option == 'C' || option == 'A' || option == 'D')
			{
			    printf("\n\nWrong answer");
				sepm.rws[1]++;
                getch();
				break;
			}
            else
            {
                printf("\n\nQuestion Skipped");
                sepm.rws[2]++;
                getch();
                break;
            }
        default:
            break;
        }
    }
    printf("\n\n\t\tCorrect Answers: %d",sepm.rws[0]);
    printf("\n\t\tWrong Answers: %d",sepm.rws[1]);
    printf("\n\t\tUnattempted: %d",sepm.rws[2]);
    sepm.rws[3] = (sepm.rws[0]*4)-sepm.rws[1];
    return sepm;
}

// store records into a file
void enterScore(struct candidate temp) 
{
    // creating file pointer to work with files
    FILE *fptr;

    // opening file in writing mode
    fptr = fopen("scores.txt", "a" );
    
    // exiting program 
    if (fptr == NULL) {
        printf("Error!");
    }
    // entering details into file
    fprintf(fptr, "Roll No: %d", temp.roll);
    fprintf(fptr, "\nName: %s", temp.name);
    fprintf(fptr, "\nClass: %s", temp.class);
    fprintf(fptr, "\nPRN No. %s", temp.prn);
    fprintf(fptr, "\nCorrect Answers: %d", temp.score.rws[0]);
    fprintf(fptr, "\nWrong Answers: %d", temp.score.rws[1]);
    fprintf(fptr, "\nUnattempted Questions: %d", temp.score.rws[2]);
    fprintf(fptr, "\nFinal Score: %d/100", temp.score.rws[3]);
    fprintf(fptr, "\n*************************************\n");
    fclose(fptr);
}


