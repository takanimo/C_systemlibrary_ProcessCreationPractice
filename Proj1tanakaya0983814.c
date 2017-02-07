/*OS Project 1  Takamasa Nakayama (0983814)*/
#include<stdio.h>//basic library
#include<stdlib.h>// needs for calling exit.
#include<unistd.h>//for pid_t
#include <sys/types.h>//for pid_t type
#include<string.h>//string library
#include<time.h>//used for random
#include<signal.h>//to kill the child process

int main(int argc, char *argv[]){
	//initialization
	pid_t pid1,pid2,pid3;	//pid
	//int pipefd0[2],pipefd1[2],pipefd2[2],pipefd3[2],pipefd4[2],pipefd5[2],pipefd6[2];	//pipe.[0]read [1] write
	
	int ret,i,j,input,z;		//convert
	//char buf[30];
	char qtion[7][30];//set default questions from each students
	strcpy(qtion[0],"Student#0: What is 1+1?");
	strcpy(qtion[1],"Student#1: What is CS?");
	strcpy(qtion[2],"Student#2: What year is this?");
	strcpy(qtion[3],"Student#3: Who is Obama?");
	strcpy(qtion[4],"Student#4: What is ass?");
	strcpy(qtion[5],"Student#5: Where is Tokyo?");
	strcpy(qtion[6],"Student#6: What is candy?");
	strcpy(qtion[7],"Student#7: What is Xmas?");

	char aswer2[10][30];//set for students answers
	strcpy(aswer2[0],": 2");
	strcpy(aswer2[1],": Computer Science");
	strcpy(aswer2[2],": 2016");
	strcpy(aswer2[3],": US President");
	strcpy(aswer2[4],": butt in slang");
	strcpy(aswer2[5],": Capital of Japan");
	strcpy(aswer2[6],": sugar");
	strcpy(aswer2[7],": Santa day");

	char aswer1[10][40];//used when students answer other student's questions 
	strcpy(aswer1[0],"Question#0: (What is 1+1?)->");
	strcpy(aswer1[1],"Question#1: (What is CS?)->");
	strcpy(aswer1[2],"Question#2: (What year is this?)->");
	strcpy(aswer1[3],"Question#3: (Who is Obama)?->");
	strcpy(aswer1[4],"Question#4: (What is ass?)->");
	strcpy(aswer1[5],"Question#5: (Where is Tokyo?)->");
	strcpy(aswer1[6],"Question#6: (What is candy?)->");
	strcpy(aswer1[7],"Question#7: (What is X'mas?)->");


	srand((unsigned int)time(NULL));//rand set.
	//1.start message of program.
	printf("\n----Taka's Project1 is started----\n\n");
	//2. Display PID of Manager process
	printf("PID of Manager process is: (%d)\n",pid1=getpid());

	//3. Input the number of students.
	printf("How many child process do you want??: ");
	scanf("%d",&input);
	if(input <3){//needs to be more than 3. requirement.
	printf("Number of child process needs to be equal/greater than 	3\n\n");
	exit(-1);
	}else if(input>8){//since I've set all answers in array, 8 is maximum
	printf("Number of child process needs to be equal/less than 8\n\n");
	exit(-1);
	}else{
	printf("You want %d number of child processes\n",input);
	}
	
	pid_t pids[input];//creates array of typed # of children process.
	printf("\n");


	//4.create children process as students
	for(i=0;i<input;++i){
		//prepare pipe for communication.//pipe.[][0]read [][1] write
		int pipefd[i][2];
		int pipefd2[i][2];//used for answers
		if(pipe(pipefd[i])==-1){//in case failed creating pipe.
		perror("failed pipe");
		exit(1);	
		}
		if(pipe(pipefd2[i])==-1){//in case failed creating pipe.
		perror("failed pipe");
		exit(1);	
		}

		if((pids[i]=fork())<0){//failed forking
			perror("fork is failed.\n");
			exit(-1);
		}else if(pids[i]==0){//child process
			printf("#%d st student's PID is (%d)\n",i, getpid());//5.Display PIDs of children processes
			close(pipefd[i][0]);//child doesnt need to read. just write.
			switch(i){
				case 0:	
					
					write(pipefd[i][1],qtion[0],30);//write its question to parent
					break;
				case 1: 
					write(pipefd[i][1],qtion[1],30);
					break;

				case 2:
					
					write(pipefd[i][1],qtion[2],30);
					break;
				case 3:	
					write(pipefd[i][1],qtion[3],30);
					break;
				case 4:
					
					write(pipefd[i][1],qtion[4],30);
					break;

				case 5:	
					write(pipefd[i][1],qtion[5],30);
					break;
				case 6:	
					write(pipefd[i][1],qtion[6],30);
					break;

				case 7:	
					write(pipefd[i][1],qtion[7],30);
					break;
				default:
					
					printf("No question\n");
					break;

			}
				switch(i){//switch for answer. students answer for other student's questions.
				case 0:	
					
					write(pipefd2[i][1],aswer2[0],30);
					break;
				case 1: 
					write(pipefd2[i][1],aswer2[1],30);
					break;

				case 2:
					write(pipefd2[i][1],aswer2[2],30);
					break;
				case 3:	
					write(pipefd2[i][1],aswer2[3],30);
					break;
				case 4:
					write(pipefd2[i][1],aswer2[4],30);
					break;
				case 5:	
					write(pipefd2[i][1],aswer2[5],30);
					break;
				case 6:	
					write(pipefd2[i][1],aswer2[6],30);
					break;

				case 7:	
					write(pipefd2[i][1],aswer2[7],30);
					break;
				default:
					
					printf("No answer\n");
					break;

			}
			
			
			exit(0);
		}else{//Parent process
			sleep(1);	//sleep every 1 sec
			close(pipefd[i][1]);//parent doesn't need to write. just read.
			close(pipefd2[i][1]);
			read(pipefd[i][0],qtion[i],35);//read questions from children
			sleep(1);
			read(pipefd2[i][0],aswer2[i],30);//read answers from children
			if(i==(input-1)){	//it starts showing Q&A after all children process are displayed
				printf("<Start Q and A>\n");
				for(j=0;j<input;++j){//Students ask their questions
					printf("Question: %s\n",qtion[j]);
				}
				printf("-----------------------------\n");
				int numst[input];	
				int p,q;			
					for(p=0;p<input;p++){//for random answers. first fill array
						numst[p]=p;
						printf("%d,",numst[p]);
					}printf("\n");
				for(z=0;z<input;++z){//answers each others quesitons.
				char aswer3[40];
					if(z!=(input-1)){//sorting for randomizing "which student answer which student's question"
						int randnumst=rand()%(input-z);
						int temp=numst[0];
						numst[0]=numst[randnumst];
						numst[randnumst]=temp;
						int temp2=numst[input-1-z];
						numst[input-1-z]=numst[randnumst];
						numst[randnumst]=temp2;
					}else{
						int temp3=numst[0];
						numst[0]=numst[input-1];
						numst[input-1]=temp3;			
	
						}
						int t;
						printf("[");//showing inside array. Left most is always chosen as randomized answer
						for(t=0;t<input;t++){
							printf("%d,",numst[t]);						
						}printf("]\n");
						
					
				int numstalt=numst[0];
				strcpy(aswer3,aswer1[numstalt]);//Question the student gonna answer

				int numaswer=rand()%input;//randomizing student's answer.
							
					char aswer4[30];
					printf("Student#%d answerd %s\n",z,aswer3);
					while(numstalt!=numaswer){//student answers the question until it gets to the correct answer.
						sleep(1);
					strcpy(aswer4,aswer2[numaswer]);
					printf("	%s",aswer4);
							printf("<wrong>\n");				
						
					numaswer=rand()%input;					
					}
					sleep(1);
					strcpy(aswer4,aswer2[numaswer]);
						printf("	%s",aswer4);
						printf("<correct>\n");
					
				}
			}
			wait(NULL);//wait for children process to finish.
		
		}
	}printf("\n<All process is done.Exit Manager Process>\n------program end-------\n\n");




return 0;
}
