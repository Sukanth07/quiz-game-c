#include <stdio.h>
#include <stdlib.h>
#include <time.h>   //for time()
#include <conio.h>
#include <string.h> //for string operations

//Variables are declared in global scope to access all over the program
int i, j, temp, score, opt, count, mark, catMark1, catMark2, catMark3, sno;
char f_sno[3], f_category[25], f_ques[100], f_opA[30], f_opB[30], f_opC[30], f_opD[30], f_opCorrect[2];
char ch, line[100], ans[11][5], user_name[25], correctAns[30], yourAns[30];
int a[10] = {1,2,3,4,5,6,7,8,9,10};

void mainmenu();        //mainmenu
void start_game();      //starting game
void result();          //printing final results
void store_score();     //to store high score data in another file
void high_score();      //to view high score
void instructions();    //to view instructions
void random();          //to randomize the array "a" for each execution

/*---------------------------------------------------------------------------------*/
void mainmenu(){
    system("cls");
    printf("\n\t\t\t\t QUIZ GAME");
    printf("\n\t\t\t\t `````````\n");
    printf("\n\t\t 1. Start Game");
    printf("\n\t\t 2. View High Score");
    printf("\n\t\t 3. Instructions");
    printf("\n\t\t 4. Exit Game");
    printf("\n\n\t\t Your Option  :  "); scanf("%d", &opt);

    switch (opt)
    {
    case 1:
        start_game();
        break;
    case 2:
        high_score();
        break;
    case 3:
        instructions();
        break;
    case 4:
        break;
    default:
        printf("\n\t\t ---Invalid Option---");
    }
}
/*---------------------------------------------------------------------------------*/
void start_game(){
    system("cls");
    FILE *fp;
    fp = fopen("q_bank.txt","r");
    if(fp == NULL)
        printf("\n ERROR WHILE OPENING \"q_bank.txt\" FILE!");
    if(fp){
        printf("\n\n\t Your Name : "); fflush(stdin); gets(user_name);
        printf("\n\n\t Hello %s !", user_name);
        printf("\n\t Hope you'll be enjoying this game.");
        printf("\n\n\t Press any key to start the game...");
        ch = getch();

        random();
        i = 0, sno = 1, score = 0, count = 0, catMark1 = 0, catMark2 = 0, catMark3 = 0;
        
        //read line by line from q_bank.txt file using fscanf()
        while (fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",f_sno,f_category,f_ques,f_opA,f_opB,f_opC,f_opD,f_opCorrect) != EOF && sno <= 10)
        {
            if(a[i] == atoi(f_sno)){     //atoi() used to convert f_sno into int type
                system("cls");
                printf("\n\n\n\t Category : %s", f_category);
                printf("\n\n\t Q.no.%d : %s", sno, f_ques);
                printf("\n\n\t %s", f_opA);
                printf("\n\t %s", f_opB);
                printf("\n\t %s", f_opC);
                printf("\n\t %s", f_opD);
                printf("\n\n\t Your Option  :  "); fflush(stdin); gets(ans[i]);

                if(strcmp(ans[i],f_opCorrect)==0){      //if entered option is correct
                    printf("\n\n\t Correct Answer !  You are rewarded with 10 points");
                    score += 10;
                    count += 1;
                    printf("\n\t Score = %d", score);
                    if(strcmp(f_category,"Programming")==0) catMark1 += 10;
                    if(strcmp(f_category,"Information Technology")==0) catMark2 += 10;
                    if(strcmp(f_category,"General Knowledge")==0) catMark3 += 10;
                }
                if(strcmp(ans[i],f_opCorrect)!=0){      //if entered option is wrong
                    printf("\n\n\t Wrong Answer... You are rewarded with 0 point");
                    printf("\n\t The correct option is (%s)", f_opCorrect);
                    score += 0;
                    printf("\n\t Score = %d", score);
                }
                printf("\n\n\t Press any key for next...");
                printf("\n\t Press \'q\' to quit the game...");
                ch = getch();
                if(ch == 'q' || ch == 'Q'){
                    fseek(fp,0,SEEK_SET);
                    mainmenu();
                    break;
                }
                sno++;
                i++;
                fseek(fp, 0, SEEK_SET);
            }
        }
        
    }
    fclose(fp);
    result();
}
/*---------------------------------------------------------------------------------*/
void result(){
    system("cls");
    FILE *fp;
    fp = fopen("q_bank.txt", "r");
    if(fp == NULL)
        printf("\n ERROR WHILE OPENING \"q_bank.txt\" FILE!");
    if(fp){
        printf("\n\n\t Congratulations %s. You have completed the quiz game.",user_name);
        printf("\n\t You have got %d correct out of 10 questions.", count);
        printf("\n\n\t Here are your answers :-");
        printf("\n\t ************************");
        i = 0;
        sno = 1;
        while (fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",f_sno,f_category,f_ques,f_opA,f_opB,f_opC,f_opD,f_opCorrect) != EOF && sno <= 10)
        {
            if(a[i] == atoi(f_sno)){
                char x1[2]="a", x2[2]="b", x3[2]="c", x4[2]="d";
                //for correctAns variable
                if(strcmp(f_opCorrect,x1)==0)   strcpy(correctAns,f_opA);
                if(strcmp(f_opCorrect,x2)==0)   strcpy(correctAns,f_opB);
                if(strcmp(f_opCorrect,x3)==0)   strcpy(correctAns,f_opC);
                if(strcmp(f_opCorrect,x4)==0)   strcpy(correctAns,f_opD);
                //for yourAns variable
                if(strcmp(ans[i],x1)==0)    strcpy(yourAns,f_opA);
                if(strcmp(ans[i],x2)==0)    strcpy(yourAns,f_opB);
                if(strcmp(ans[i],x3)==0)    strcpy(yourAns,f_opC);
                if(strcmp(ans[i],x4)==0)    strcpy(yourAns,f_opD);

                printf("\n\t Category        : %s", f_category);
                printf("\n\t Q.no            : %d", sno);
                printf("\n\t Question        : %s", f_ques);
                printf("\n\t Correct Answer  : %s", correctAns);
                printf("\n\t Your Answer     : %s", yourAns);
                if(strcmp(ans[i],f_opCorrect)==0) mark = 10;
                else mark = 0;
                printf("\n\t Marks Awarded   : %d", mark);
                printf("\n\t -------------------------------------------------------------------");
                sno++;
                i++;
                fseek(fp,0,SEEK_SET);
            }
        }
        fclose(fp);
        printf("\n\n\t Press any key for next...");
        ch = getch();

        system("cls");

        printf("\n\n\t Category Wise Marks :-");
        printf("\n\t **********************");
        printf("\n\t Programming             :  %d", catMark1);
        printf("\n\t Information Technology  :  %d", catMark2);
        printf("\n\t General Knowledge       :  %d", catMark3);
        printf("\n\n\t Press any key for next...");
        ch = getch();

        printf("\n\n\t Your Final Score  :  %d out of 100", score);
        printf("\n\n\t Press any key to go mainmenu...");
        ch = getch();
        store_score();  //calling store_score() to store the highest score data
        mainmenu();
    }
}
/*---------------------------------------------------------------------------------*/
void store_score(){
    FILE *temp, *myfile;
    temp = fopen("temp.txt", "w");
    myfile = fopen("score.txt", "r");  //initially score.txt contains [0,name] -> 0-score, name-Name
    if(temp == NULL || myfile == NULL)
        printf("\n\n\t ERROR WHILE OPENING \"score.txt\" OR \"temp.txt\" FILE!");
    if(myfile && temp){
        int totScore;
        char name[25];
        char delim = ',';
        fscanf(myfile,"%d,%[^,],%s",&totScore,name);
        if(score >= totScore){
            fprintf(temp,"%d,%s",score,user_name);
        }
    }
    fclose(myfile);
    fclose(temp);
    remove("score.txt");
    rename("temp.txt","score.txt");
}
/*---------------------------------------------------------------------------------*/
void high_score(){
    system("cls");
    FILE *fp;
    fp = fopen("score.txt", "r");
    if(fp == NULL)
        printf("\n\n\t ERROR WHILE OPENING \"score.txt\" FILE!");
    if(fp){
        int totScore;
        char name[25];
        fscanf(fp,"%d,%[^,],%s",&totScore,name);
        printf("\n\n");
		printf("\n\t  _       _   _   ________    _       _        ________   ________   ________   ________   ________                    ");
		printf("\n\t | |     | | | | |  ______|  | |     | |      |  ______| |  ______| |  ____  | |   ___  | |  ______|                   ");
		printf("\n\t | |     | | | | | |         | |     | |      | |        | |        | |    | | |  |   | | | |                          ");
		printf("\n\t | |_____| | | | | |  _____  | |_____| |      | |______  | |        | |    | | |  |___| | | |______                    ");
		printf("\n\t | |_____| | | | | | |___  | | |_____| |      |______  | | |        | |    | | |  __  __| |  ______|                   ");
		printf("\n\t | |     | | | | | |     | | | |     | |             | | | |        | |    | | | |  \\ \\   | |                          ");
		printf("\n\t | |     | | | | | |_____| | | |     | |       ______| | | |______  | |____| | | |   \\ \\  | |______                    ");
		printf("\n\t |_|     |_| |_| |_________| |_|     |_|      |________| |________| |________| |_|    \\_\\ |________|                   ");
		
		
		printf("\n\n\n\t Name   :  %s", name);
		printf("\n\t Score  :  %d", totScore);
    }
    fclose(fp);
    printf("\n\n\t Press any key to go mainmenu...");
    ch = getch();
    mainmenu();
}
/*---------------------------------------------------------------------------------*/
void instructions(){
    system("cls");
	
	printf("\n\n\t\t\t\t WELCOME TO QUIZ GAME");
	printf("\n\t\t\t\t ********************");
	printf("\n\n\t NOTE: Please note these instrucions before you start to play.");
	printf("\n\n\t 1. You will be given with 10 questions to complete this quiz game");
	printf("\n\t 2. Each question has 10 points");
	printf("\n\t 3. Each question is based on 3 different categories");
	printf("\n\t 4. Enter the option letter to answer the question [ Eg: a (or) c ]");
	printf("\n\t 5. The option letters you enter are case sensitive (only lowercase)");
	printf("\n\t 6. Your final results will be displayed in the end");
	printf("\n\n");
	
	printf("\n\t                       **                                                          ");
	printf("\n\t *      ****** ******* **  ******       ****** *******   **   ******  *******      ");
	printf("\n\t *      *         *    *  *            *          *    *    * *     *    *         ");
	printf("\n\t *      ******    *        ******       ******    *    ****** ******     *         ");
	printf("\n\t *      *         *              *            *   *    *    * *    *     *         ");
	printf("\n\t ****** ******    *        ******       ******    *    *    * *     *    *         ");
	
	printf("\n\n\t Press any key to go mainmenu...");
	if(ch=getch())
	    mainmenu();
}
/*---------------------------------------------------------------------------------*/
void random(){
    srand(time(NULL));
    for(i = 0; i<10; i++){
        j = (rand()%9) + 1;
        temp = a[i]; 
        a[i] = a[j];
        a[j] = temp;
    }
}
/*---------------------------------------------------------------------------------*/
int main(){
    system("cls");
    mainmenu();
    printf("\n\n\n----------------------------------------\n");
    system("pause");
    return 0;
}