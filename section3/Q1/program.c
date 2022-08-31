//Amirreza Hosseini 9820363
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>

int main(int argc, char *argv[])
{
if (strcmp (argv[1], "-c")==0)  //craet
{
	open(argv[3],O_CREAT|O_RDWR,strtol(argv[2],NULL,8));
}
if (strcmp(argv[1],"-w")==0) //write
{
	char str[200];
       	fgets(str,200,stdin); 
	int file= open(argv[2],O_CREAT|O_WRONLY,00755);
	write(file,str, strlen(str));
}
if (strcmp(argv[1],"-r")==0) //read
{
	char readBuffer[256];
	int readFile=open(argv[2],O_RDONLY,00755);
	read(readFile,readBuffer,255);
	fprintf(stdout,"%s\n",readBuffer);
}
if (strcmp(argv[1],"-m")==0) //make
{
	char dirName[256];
	sprintf(dirName,"%s",argv[2]);
//	fgets(dirName,200,stdin);
	mkdir(dirName,00755);
	
//	char fileName[256];
//        strcat(fileName, argv[2]);
//	strcat(fileName, "/");
  //      strcat(fileName, argv[3]);

	int i=0;
	int v5=atoi(argv[5]);
	int v6=atoi(argv[6]);

	for(i=v5;i<=v6;i++)
	{	
		char fileNameTemp[256];
		sprintf(fileNameTemp,"%s/%s%d.%s",dirName,argv[3],i,argv[4]);
	
		open(fileNameTemp,O_CREAT|O_WRONLY,00755);

		memset(fileNameTemp, 0, sizeof fileNameTemp);
	}
//	char tst[240];
//	sprintf(tst,"%s/%d.%s",dirName,2,"txt");
//	open(tst,O_CREAT|O_WRONLY,00755);

}

return 0;
}
