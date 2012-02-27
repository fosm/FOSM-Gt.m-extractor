#include "gtmxc_types.h"   // For GTM call-in function prototypes
#include "string.h"        // strlen(), memcpy(), strncmp()
#include "stdlib.h"        // setenv

#include "stdio.h"        // setenv
#include "unistd.h"
#define BUFLEN 512
#define MAXARGS 8

// parts of code taken from http://fooboo.org/~tmr/public/mod_mgirpc/mod_mgirpc.c

int check_status (gtm_status_t status) {

  if (status != 0) {
    gtm_char_t msgbuf [BUFLEN];
    gtm_zstatus (msgbuf, BUFLEN);
    printf ((const char *) msgbuf);
    printf ("\nError%d\n",status);
    return 0;
  }

  return 1;
}

int callin_void_void(const char * name)
{
  gtm_status_t status;
  status = gtm_ci (name );
    if (check_status (status) != 1) {
      printf("FOSM/nodexorder2 Internal error!\n");

      char msgbuf[BUFLEN]; 
      gtm_zstatus(msgbuf, BUFLEN); 
      fprintf(stderr, "%s\n",msgbuf); 

      //    continue;
    }

}

// a generic routine 
int 	gtmci_any(const char * routine, gtm_char_t * tablename, int limitcount, int argc, char ** argv )
{
  if (argc < 1)
    {
        printf ("error needs arguments\n ");
      return ;
    }
  
  gtm_status_t status;

 
  gtm_char_t retval [BUFLEN]; // the return value
  memset (retval, 0, sizeof (retval));
  
  gtm_char_t value[MAXARGS] [BUFLEN]; // the parmeter values are all copied here
  memset (value[0], 0, sizeof (retval));

  int loopstatus=1;
  printf ("routine:\"%s\",\n ",routine);

  printf ("lastarg:\"%d\",\n ",argc-1);
  printf ("argc:\"%d\",\n ",argc);
  int i;
  for (i =0; i < argc; i++) {
    strcpy(value[i],argv[i]); // we want to pass our own value int
    //printf ("argv%d:\"%s\",\n ",i,argv[i]);

  } 
  printf ("tablename:\"%s\",\n keys : {",tablename);
  while (loopstatus) {
    
    switch(argc){
    case 1 :
      status = gtm_ci (routine,&retval,tablename, value[0]);
	break;
    case 2 :
      status = gtm_ci (routine,&retval,tablename, value[0],value[1]);
      break;
    case 3 :
      status = gtm_ci (routine,&retval,tablename, value[0],value[1],value[2]);
      break;
    case 4 :
      status = gtm_ci (routine,&retval,tablename, value[0],value[1],value[2],value[3]);
      break;
    case 5 :
      status = gtm_ci (routine,&retval,tablename, value[0],value[1],value[2],value[3], value[4]);
      break;
    case 6 :
      status = gtm_ci (routine,&retval,tablename, value[0],value[1],value[2],value[3], value[4], value[5]);
      break;
    case 7 :
      status = gtm_ci (routine,&retval,tablename, value[0],value[1],value[2],value[3], value[4], value[5],value[6]);
      break;
    case 8 :
      status = gtm_ci (routine,&retval,tablename, value[0],value[1],value[2],value[3], value[4], value[5],value[6],value[7]);
      break;
    };

    if (check_status (status) != 1) {
      printf("FOSM/gtm_ci Internal error!\n");
      char  msgbuf[BUFLEN]; 
      gtm_zstatus(msgbuf, BUFLEN); 
      fprintf(stderr, "%s\n",msgbuf); 
      loopstatus=0;
    }
    else {
      strcpy(value[argc-1],retval);
    }
    if (strcmp(value[argc-1], "")==0)  {
      loopstatus=0;;		
	} else {
	  printf ("\t \"%s\" : 1, \n", value[argc-1] ); //json
	}    
	if (limitcount >0){
	  if (limitcount==1) {
	    printf ("}\n" ); //json
	    return;   }
	  limitcount --;
	}
  }

  printf ("}\n" ); // json

  return 1;
}



int main(int argc, char ** argv)
{

  setenv("GTMCI","/pine02/scripts/FOSM.ci",0);  // where to find the call in routine 
  setenv("gtmroutines","/pine02/scripts/o(/pine02/scripts /pine02/serenji /pine02/gtmx /pine02/gtm)",0); // where to find the FOSM.m routine
  chdir("/pine02/data");
  setenv("gtm_dist","/pine02/gtm",0);
  int err=  gtm_init(); // init 
  printf ("{ gtm_fosminvoke: {\n"); // start of the json
  printf ("\tinit_returned:%d,\n",err); // json attr

  // setenv("gtmgbldir","/pine02/data/xapi_big.gld",0); // where is the database located? well this script looks for data relative, so needs to be run there $as well
  // t table
  // j first param
  // k second param
  // l third param
  // m fourth param
  char * tablename=0;
  int argcount = 0;
  char * args[MAXARGS];
  int i;
  for (i=0; i < MAXARGS-1;i++)    {
      args[i]="";
    }
  int limitcount=0;
  int value=0;
  char c;
  while ((c = getopt (argc, argv, "t:jk:l:m:n:o:p:q:c:v")) != -1)   {
    
    switch (c) {
    case 't' : 
      // table
      tablename = optarg;
      break;
    case 'c' : 
      // limit  count to 
      limitcount = atoi(optarg);
      break;
    case 'j' : 
      if (argcount < 1) argcount=1;
      break;

    case 'k' :    // param2
      args[0]=optarg;
      if (argcount < 2)     argcount=2;
      break;

    case 'l' :  // param 3
      args[1]=optarg;
      if (argcount < 3) argcount=3;
      break;

    case 'm' : 
      // param2
      args[2]=optarg;
      if (argcount < 4) argcount=4;
      break;     

    case 'n' : 
      // param2
      args[3]=optarg;
      if (argcount < 5) argcount=5;
      break;     

    case 'o' : 
      args[4]=optarg;
      if (argcount < 6) argcount=6;
      break;     

    case 'p' : 
      args[5]=optarg;
      if (argcount < 7) argcount=7;
      break;     

    case 'q' : 
      args[6]=optarg;
      if (argcount < 8) argcount=8;
      break;     

    case 'v' : 
      // get the value. does not call order
      value=1;
      break;     

    }
  }
  printf ("\targcount: %d,\n",argcount); //json attribute
  for (i=0; i < MAXARGS-1;i++)    {
    printf ("inargv%d:\"%s\",\n ",i,args[i]);
    }

  char FNAME[25];
  char FNAMEV[25];
  sprintf(FNAME,"ORDERANY%d",argcount);
  sprintf(FNAMEV,"VALUEANY%d",argcount-1);

  // now call the function
    switch (argcount) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      if (value)
	{
	  gtmci_any(FNAMEV, tablename, 1, argcount-1, args); // for the value, we need all params to be filled in
	}
      else
	{
	  gtmci_any(FNAME, tablename, limitcount, argcount, args);// for the order we need to leave the last param empty
	}
      break;      
    default :
      printf("Unknown args\n");
    }
  gtm_exit();
  printf ("}}\n"); // json

  // try and reset the terminal
  //  system("stty sane"); 

  return 0;
}
