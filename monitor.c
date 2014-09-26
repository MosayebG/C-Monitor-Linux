#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>

void  clearScreen()
{
  const char* CLEAR_SCREE_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO,CLEAR_SCREE_ANSI,12);
}


int main( int argc, char *argv[] )
{
  FILE *fp;
  FILE *fp2;
  FILE *fp3;
  FILE *fp4;
  FILE *fp5;
  FILE *fp6;
  FILE *fp7;
  FILE *fp8;
  char file_type[1000];
  int flag = 1;
  char *ram_line;
  int read_time;
  int write_time;
  int choose;
  int i=0; 
  int j=0;
  int k=0; 
  int l=0;
  int m=0;
  int n=0;
  int o=0;
  int last_proc=0;
  
  if (argc != 3)
  {
    fprintf(stderr, "usage:  ./monitor <read_time> <write_time>\n\n");
    exit(1);
  }
  
 read_time = atoi(argv[1]);
 write_time = atoi(argv[2]);
 printf("choose what you want:\n\nSee the statistic of your system: 1\n\nRun the monitoring system: 2\n\nEnter Your Answer: ");
 scanf("%i",&choose);

 //initialling the Procces Number
 
 fp7 = popen("ps -aux | awk \'END{print $2 }\'", "r");
  if (fp7 == NULL) {
    printf("Failed to run command\n" );
    exit -1;
  }
  fgets(file_type, sizeof(file_type), fp7);
  last_proc = atoi(file_type);
  switch(choose)
  {
    case 1:
    
      // Getting CPU information
      
      clearScreen();
      fp2 = popen("lscpu", "r");
      if (fp2 == NULL) {
        printf("Failed to run command\n" );
        exit -1;
      }
      printf("\n");
      for(i; i<50; i++)
        printf("#");
      printf("\n\nCPU information of this system:\n\n");
      while(fgets(file_type, sizeof(file_type), fp2) != NULL)
        printf("%s", file_type);
      pclose(fp2);
      
      printf("\n");
      for(k; k<50; k++)
        printf("#");
        
      // Getting Kernel Version
      
      fp3 = popen("uname -r", "r");
      if (fp3 == NULL) {
        printf("Failed to run command\n" );
        exit -1;
      }
      printf("\n\nKernel Version of this system:\n\n");
      while(fgets(file_type, sizeof(file_type), fp3) != NULL)
        printf("%s", file_type);
      pclose(fp3);
      
      //printf("\n");
      
      for(i; i<50; i++)
        printf("#");
      
      //Getting ram information
      
      fp = popen("free -h -o", "r");
      if (fp == NULL) {
        printf("Failed to run command\n" );
        exit -1;
      }
      printf("\n");
      for(j; j<50; j++)
        printf("#");
      printf("\n\nRam information of this system:\n\n");
      fgets(file_type, sizeof(file_type), fp);
      printf("%s", file_type);
      fgets(file_type, sizeof(file_type), fp);
      printf("%s\n", file_type);
      pclose(fp);
      
      //Time elapsed since last system reboot
      
      fp4 = popen("awk \'{print int($1/3600)\":\"int(($1%3600)/60)\":\"int($1%60)}\' /proc/uptime", "r");
      if (fp4 == NULL) {
        printf("Failed to run command\n" );
        exit -1;
      }
      printf("\n");
      for(l; l<50; l++)
      printf("#");
      printf("\nTime elapsed since last system reboot:\n\n");
      while(fgets(file_type, sizeof(file_type), fp4) != NULL)
        printf("%s\n", file_type);
      pclose(fp4);
      exit(1);
      break;
    
    case 2:
      for(;;)
      {
      clearScreen();
      
      //CPU Utilization
      
      fp5 = popen("mpstat | awk \'FNR>2 {print $3,\"  \", $5,\"   \", $12}\'", "r");
      if (fp5 == NULL) {
        printf("Failed to run command\n" );
        exit -1;
      }
      printf("\n");
      printf("\nCPU Utilization:\n");
      while(fgets(file_type, sizeof(file_type), fp5) != NULL)
      printf("%s", file_type);
      printf("\n");
      
      //Getting ram information
      
      fp = popen("free -h -o", "r");
      if (fp == NULL) {
        printf("Failed to run command\n" );
        exit -1;
      }
      printf("\n");
      printf("\nRam information of this system:\n");
      fgets(file_type, sizeof(file_type), fp);
      printf("%s", file_type);
      fgets(file_type, sizeof(file_type), fp);
      printf("%s\n", file_type);
      
      //Hard Disk Staistics
      
      fp6 = popen("iostat -d | awk \'FNR>2{print $3,\"         \", $4}\'","r");
      if (fp6 == NULL) {
        printf("Failed to run command\n" );
        exit -1;
      }
      printf("\n");
      printf("\nHard Disk Satistics:\n");
      while(fgets(file_type, sizeof(file_type), fp6) != NULL)
        printf("%s", file_type);
      
      //Number of new Process
      
      fp8 = popen("ps -aux | awk \'END{print $2 }\'", "r");
      if (fp8 == NULL) {
        printf("Failed to run command\n" );
        exit -1;
      }
      printf("\nNumber of new Process:\n");
      fgets(file_type, sizeof(file_type), fp8);
      printf("\n%d\n", (atoi(file_type)) - (last_proc));
      last_proc = atoi(file_type);
      sleep(read_time);
      }
      break;
  }
  clearScreen();
  return 0;
}
