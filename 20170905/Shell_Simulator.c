#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define LINE_LENGTH 1024 //length for the input
#define ARGV_LENGTH 64 //length for tokens division out of the input

//ANSI codes for text colors use: printf("%smessage\n", KRED); to print in red
#define KNRM  "\x1B[0m" //RESET COLOR
#define KBLK  "\x1B[30m" //BLACK COLOR
#define KRED  "\x1B[31m" //RED COLOR
#define KGRN  "\x1B[32m" //GREEN COLOR
#define KYEL  "\x1B[33m" //YELLOW COLOR
#define KBLU  "\x1B[34m" //BLUE COLOR
#define KMAG  "\x1B[35m" //MAGENTA COLOR
#define KCYN  "\x1B[36m" //CYAN COLOR
#define KWHT  "\x1B[37m" //WHITE COLOR

//ANSI codes for Background colors
#define BBLK  "\x1B[40m" //BLACK COLOR
#define BRED  "\x1B[41m" //RED COLOR
#define BGRN  "\x1B[42m" //GREEN COLOR
#define BYEL  "\x1B[43m" //YELLOW COLOR
#define BBLU  "\x1B[44m" //BLUE COLOR
#define BMAG  "\x1B[45m" //MAGENTA COLOR
#define BCYN  "\x1B[46m" //CYAN COLOR
#define BWHT  "\x1B[47m" //WHITE COLOR

//ANSI codes for other Text Attributes
#define TEXT_ATTR_OFF "\x1B[0m"	//All attributes off
#define TEXT_BOLD "\x1B[1m" //Bold on
#define TEXT_DIM "\x1B[2m" //Dim on
#define TEXT_ITALIC "\x1B[3m" //ITALIC on
#define TEXT_UNDERLINE "\x1B[4m" //Underline (on monochrome display adapter only)
#define TEXT_REV_VID "\x1B[7m" //Reverse video on  (FG becomes BG and BG becomes FG)
#define TEXT_CONCEALED_ON "\x1B[8m" //Concealed on (Covers all with the Background color)

int history_mode; //to keep track to not store command getting executed from history
char input[LINE_LENGTH]; //to keep a copy of input for storing in history as it is
FILE *COMMAND_LOG; //file pointer to manage the history records
char *file_name="CMD_LOG.dat"; //file name in which history is stored

struct command_log //structure for each command record in the history log
{
	int id; //index of each command
	char command[LINE_LENGTH]; //complete command as one single string
}cmd_log;

void parse(char *line,char **argv) //function definition to parse the command input and turn it into argument vector so that execvp ...
{
	while(*line!='\0') //if not the end of line
	{
		while(*line==' '||*line=='\t'||*line=='\n') //word breaks
			*line++='\0'; //replace word breaks with \0
		*argv++=line; //save the argument position
		while(*line!='\0'&&*line!=' '&&*line!='\t'&&*line!='\n')
			line++; //skip the argument until such break is found.
	}
	*argv='\0'; //mark the end of the argument list
}

void record_command(char c_line[]) //function definition to record a command in history
{
	COMMAND_LOG=fopen(file_name,"a+"); //opening the History file in append+ mode
	fseek(COMMAND_LOG,0,SEEK_END); //setting the read pointer to the end
	if(ftell(COMMAND_LOG)!=0) //if the file is NOT empty...
	{
		fseek(COMMAND_LOG,-sizeof(cmd_log),SEEK_END); //set the read-write pointer to starting of last record
		if(fread(&cmd_log,sizeof(cmd_log),1,COMMAND_LOG)==1); //successful read of last record
		cmd_log.id++; //for new record ID must be last ID+1
	}
	else //else if file is empty
		cmd_log.id=0; //new records ID = 0
	strcpy(cmd_log.command,c_line); //new records command = the input by user
	fwrite(&cmd_log,sizeof(cmd_log),1,COMMAND_LOG); //writing the new record to the file
	fclose(COMMAND_LOG); //closing the file
}

void execute(char **argv) //function definition to execute the given command as a new child process
{
	pid_t pid;
	int status;
	if((pid=fork())<0) //fork a child process & if failed...
	{
		printf("\t\t\t" BRED KWHT " ERROR: forking child process failed " KNRM "\n"); //failed fork message
		exit(1); //exit out that process
	}
	else //else if successful...
		if(pid==0) //for the child process...
		{
			if(execvp(*argv,argv)<0) //execute the command
			{
				printf("\t\t\t" BRED KWHT " ERROR: exec failed " KNRM "\n"); //if failed show the error
				exit(1); //exit out of that forked process
			}
		}
		else //and for the parent process...
		{
			while(wait(&status)!=pid); //wait for completion
			if(status==0 && history_mode==0) //only if the command is successful or valid && not run from history...
				record_command(input); //record it in history.
		}
}

void create_history_file() //function definition to create the file...
{
	COMMAND_LOG=fopen(file_name,"a+"); //but if already present just not disturb it
	fclose(COMMAND_LOG); //close the file
}

void welcome() //function definition to display the welcome message of this shell
{
	//welcome message
	printf("\t\t\t\t" BBLK KGRN " Hi BOSS " KNRM "\n");
	printf("\t\t" BBLK KYEL " This Shell has some limited commands support!! " KNRM "\n");
	printf("\t" BBLK KYEL " Some good features implemented can be used as follows: \t" KNRM "\n");
	printf("\t" BBLK KYEL " 1. history :" KWHT "to see all commands in history\t\t\t"KNRM"\n");
	printf("\t" BBLK KYEL " 2. last [n] :" KWHT "to execute last 'n' commands from history\t\t"KNRM"\n");
	printf("\t" BBLK KYEL " 3. ! [n] :" KWHT "to execute last 'n-th' command from history\t\t"KNRM"\n");
	printf("\t" BBLK KYEL " 4. !! :" KWHT "to execute last command from history\t\t\t"KNRM"\n");
}

void prompt() //function definition to display a prompt
{
	printf(" " TEXT_BOLD KCYN "@ UR SERVICE :" KNRM TEXT_ATTR_OFF " "); //the prompt message
}

int history(char c_line[],char *argv[]) //function definition to implement history feature
{
	int return_flag=0; //return flag by default 0
	COMMAND_LOG=fopen(file_name,"r"); //opening the History file in read mode
	if(c_line[0]=='!') //if the input starts with !...
	{
		history_mode=1; //enable the history mode flag so that this command doesn't get stored in history again
		int n=0,i=1; //n for the number and i for the position
		while(c_line[i]==' ') //if the current character is ' ' ...
			i++; //skip the position
		while(isdigit(c_line[i])) //till it reads digits...
		{
			n=n*10+(int)(c_line[i]-'0'); //convert it to a number
			i++;
		}
		if(c_line[i]!='\0') //if its not the end of string
			n=0; //not a valid number
		if(c_line[1]=='!') //if second character is !...
			n=1; //set n as 1
		if(n) //if n is not 0...
		{
			fseek(COMMAND_LOG,0,SEEK_END); //setting the read pointer to the end
			if(ftell(COMMAND_LOG)<(n*sizeof(cmd_log))) //if there are less than n records...
				printf("\t\t\t" BRED KWHT " Not that much records in History " KNRM "\n"); //show this error
			else //else execute the n-th last command from history ...
			{
				fseek(COMMAND_LOG,-n*sizeof(cmd_log),SEEK_END); //set the read-write pointer to starting of n-th last record
				if(fread(&cmd_log,sizeof(cmd_log),1,COMMAND_LOG)==1) //if a record is successfully read...
				{
					printf(KGRN TEXT_BOLD "%s" KNRM TEXT_ATTR_OFF "\n",cmd_log.command); //print the line of command read
					parse(cmd_log.command,argv); //parse the line of command
					execute(argv); //execute the line of command
				}
			}
		}
		else //if n is 0...
			printf("\t\t\t" BRED KWHT " Not a valid History Access " KNRM "\n"); //Not correct form to access History feature
		return_flag=1; //set return flag as 1
	}
	else
		if(strcmp(c_line,"history")==0) //else if the input is history...
		{
			fseek(COMMAND_LOG,0,SEEK_END); //setting the read pointer to the end
			if(ftell(COMMAND_LOG)==0) //if the History file is empty
				printf("\t\t\t" BRED KWHT " NO RECORD OF COMMANDS IN THE HISTORY " KNRM "\n"); //give this error message
			else
			{
				printf(TEXT_BOLD BWHT KBLK " ID " KNRM "    " TEXT_BOLD BWHT KBLK " COMMAND " TEXT_ATTR_OFF KNRM "\n"); //title for understanding the output
				fseek(COMMAND_LOG,0,SEEK_SET); //setting the read pointer to the start of the file
				while(fread(&cmd_log,sizeof(cmd_log),1,COMMAND_LOG)==1) //till the records are successfully read or end of file...
					printf(KCYN "%d\t" KYEL "%s" KNRM "\n",cmd_log.id,cmd_log.command); //print the id of command read and the command from history
			}
			return_flag=1; //set return flag as 1
		}
		else
			if(strncmp(c_line,"last",4)==0) //if the command is for last n commands
			{
				history_mode=1; //enable the history mode flag so that this command doesn't get stored in history again
				int n=0,i=4; //n for the number and i for the position
				while(c_line[i]==' ') //if the current character is ' ' ...
					i++; //skip the position
				while(isdigit(c_line[i])) //till it reads digits...
				{
					n=n*10+(int)(c_line[i]-'0'); //convert it to a number
					i++;
				}
				if(c_line[i]!='\0') //if its not the end of string
					n=0; //not a valid number
				if(c_line[4]=='\0') //if its only 'last'...
					n=1; //set n as 1
				if(n) //if n is not 0...
				{
					fseek(COMMAND_LOG,0,SEEK_END); //setting the read pointer to the end
					if(ftell(COMMAND_LOG)<(n*sizeof(cmd_log))) //if there are less than n records...
						printf("\t\t\t" BRED KWHT " Not that much records in History " KNRM "\n"); //show this error
					else //else execute the last n commands from history ...
					{
						fseek(COMMAND_LOG,-n*sizeof(cmd_log),SEEK_END); //set the read-write pointer to starting of n-th last record
						while(fread(&cmd_log,sizeof(cmd_log),1,COMMAND_LOG)==1) //while a records are successfully being read or not end of file...
						{
							printf(KGRN TEXT_BOLD "%s" KNRM TEXT_ATTR_OFF "\n",cmd_log.command); //print the line of command read
							parse(cmd_log.command,argv); //parse the line of command
							execute(argv); //execute the line of command
						}
					}
				}
				else //if n is 0...
					printf("\t\t\t" BRED KWHT " Not a valid History Access You might have missed the number " KNRM "\n"); //Not correct form to access History feature
				return_flag=1; //set return flag as 1
			}
	fclose(COMMAND_LOG); //closing the history file
	return return_flag; //returning the flag
}

void main(void) //main module
{
	char line[LINE_LENGTH]; //the input line
	char *argv[ARGV_LENGTH]; //the command line argument

	welcome(); //displaying the welcome message

	create_history_file(); //in case it doesn't exist to avoid errors

	while(1) //repeat until done ....
	{
		prompt(); //display a prompt
		gets(line); //read in the command line
		history_mode=0; //by default everytime its a non history mode
		strcpy(input,line); //copying the entered command line into input string for usage at history record time
		if(history(line,argv)) //checking if the user is in history mode
			continue; //continue the loop

		parse(line,argv); //if not in history mode, parse the line of command
		if(strcmp(argv[0],"exit")==0) //is it and "exit"??
		{
			printf("\t\t\t\t" BBLK KGRN " See Ya Soon " KNRM "\n"); //termination message
			exit(0); //exit if it is
		}
		execute(argv); //otherwise, execute the command
		if(strcmp(input,"reset")==0) //if the reset command is given by the user but not history...
			welcome(); //the welcome message is displayed again
	}
}