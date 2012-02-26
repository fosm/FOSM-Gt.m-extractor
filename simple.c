#include "gtmxc_types.h"   // For GTM call-in function prototypes
#include "string.h"        // strlen(), memcpy(), strncmp()
#include "stdlib.h"        // setenv

#include "stdio.h"        // setenv
#include "unistd.h"
#define BUFLEN 512

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

int 	gtmci_orderany4( gtm_char_t * tablename, gtm_char_t * firstparam,gtm_char_t * secondparam,gtm_char_t * thirdparam) // add param
{
  
  gtm_status_t status;
  gtm_char_t hdrval2 [BUFLEN]; // the changing parameter, set from the return value
  strcpy (hdrval2, ""); 
  gtm_char_t retval [BUFLEN]; // the return value, passed to hdrval2
  memset (retval, 0, sizeof (retval));
    int loopstatus=1;
  while (loopstatus) {
    status = gtm_ci ("ORDERANY4",&retval,tablename,firstparam,secondparam,thirdparam,hdrval2 ); // the ci
    if (check_status (status) != 1) {
      printf("FOSM/ORDEANY3 Internal error!\n");
      char  msgbuf[BUFLEN]; 
      gtm_zstatus(msgbuf, BUFLEN); 
      fprintf(stderr, "%s\n",msgbuf); 
      loopstatus=0;
    }
    else {
      strcpy(hdrval2,retval); // cp the return value
    }

    if (strcmp(hdrval2, "")==0)  {
      loopstatus=0;;		
    } else {
      printf ("Found Key in table '%s', key1 '%s',key2 '%s',key3 '%s' newkey '%s'\n", tablename, firstparam, secondparam,thirdparam,hdrval2 );
    }    
  }
  return 1;
}

int 	gtmci_orderany3( gtm_char_t * tablename, gtm_char_t * firstparam,gtm_char_t * secondparam) // add param
{
  
  gtm_status_t status;

  gtm_char_t hdrval2 [BUFLEN]; // the changing parameter, set from the return value
  strcpy (hdrval2, "");
  
  gtm_char_t retval [BUFLEN]; // the return value, passed to hdrval2
  memset (retval, 0, sizeof (retval));
  
  int loopstatus=1;
  while (loopstatus) {
    status = gtm_ci ("ORDERANY3",&retval,tablename,firstparam,secondparam,hdrval2 ); // the ci

    if (check_status (status) != 1) {
      printf("FOSM/ORDEANY Internal error!\n");
      char  msgbuf[BUFLEN]; 
      gtm_zstatus(msgbuf, BUFLEN); 
      fprintf(stderr, "%s\n",msgbuf); 
      loopstatus=0;
    }
    else {
      strcpy(hdrval2,retval); // cp the return value
    }

    if (strcmp(hdrval2, "")==0)  {
      loopstatus=0;;		
    } else {
      printf ("Found Key in table '%s', key1 '%s',key2 '%s' newkey '%s'\n", tablename, firstparam, secondparam, hdrval2 );
    }    
  }
  return 1;
}

int 	gtmci_orderany2( gtm_char_t * tablename, gtm_char_t * firstparam)
{
  
  gtm_status_t status;

  gtm_char_t hdrval2 [BUFLEN]; // the second parameter, tag value
  strcpy (hdrval2, "");
  
  gtm_char_t retval [BUFLEN]; // the return value
  memset (retval, 0, sizeof (retval));
  
  int loopstatus=1;
  while (loopstatus) {
    //    printf("going to call\n");
    status = gtm_ci ("ORDERANY2",&retval,tablename,firstparam,hdrval2 );

    //        fprintf(stderr, "retval: %s\n",retval); 
    //  fprintf(stderr, "status:%d\n",status); 

    if (check_status (status) != 1) {
      printf("FOSM/nodex_children2 Internal error!\n");
      char  msgbuf[BUFLEN]; 
      gtm_zstatus(msgbuf, BUFLEN); 
      fprintf(stderr, "%s\n",msgbuf); 
      loopstatus=0;
      //    continue;
    }
    else {

      strcpy(hdrval2,retval);
    }

    if (strcmp(hdrval2, "")==0)  {
      //      printf("hdrval2 is empty %s!",hdrval2);
      loopstatus=0;;		
    } else {
      //      printf ("Found Key '%s'\n",hdrval2);
      printf ("Found Key in table '%s', key1 '%s' newkey '%s'\n", tablename, firstparam, hdrval2 );
    }    
  }

  return 1;
}

int 	gtmci_any_2(const char * routine, gtm_char_t * tablename, int limitcount, char * argv1, char * argv2 )
{
  char * argv[] = { argv1, argv2 };
  printf ("argv%d:\"%s\" %s,\n ",0,argv[0],argv1);
  printf ("argv%d:\"%s\" %s,\n ",1,argv[1],argv2);
  return gtmci_any(routine, tablename, limitcount, 2, argv );
}

int 	gtmci_any_3(const char * routine, gtm_char_t * tablename, int limitcount, char * argv1, char * argv2, char * argv3 )
{
  char * argv[] = { argv1, argv2, argv3 };
  printf ("argv%d:\"%s\", 2argv1:%s,\n ",0,argv[0],argv1);
  printf ("argv%d:\"%s\" 2argv2 %s,\n ",1,argv[1],argv2);
  printf ("argv%d:\"%s\" 2argv3 %s,\n ",2,argv[2],argv3);
  return gtmci_any(routine, tablename, limitcount, 3, argv );
}

int 	gtmci_any_4(const char * routine, gtm_char_t * tablename, int limitcount, char * argv1, char * argv2, char * argv3 , char * argv4)
{
  char * argv[] = { argv1, argv2, argv3, argv4 };
  printf ("argv%d:\"%s\", 2argv1:%s,\n ",0,argv[0],argv1);
  printf ("argv%d:\"%s\" 2argv2 %s,\n ",1,argv[1],argv2);
  printf ("argv%d:\"%s\" 2argv3 %s,\n ",2,argv[2],argv3);
  printf ("argv%d:\"%s\" 2argv4 %s,\n ",3,argv[3],argv4);
  return gtmci_any(routine, tablename, limitcount, 4, argv );
}

int 	gtmci_any_1(const char * routine, gtm_char_t * tablename, int limitcount, char * argv1 )
{
  char * argv[] = { argv1};
  return gtmci_any(routine, tablename, limitcount, 1, argv );
}

// 

// the last it
int 	gtmci_any(const char * routine, gtm_char_t * tablename, int limitcount, int argc, char ** argv )
{
  
  gtm_status_t status;

  //  gtm_char_t hdrval [4][BUFLEN]; // the reset parameter, tag value
  //  strcpy (hdrval2, "");
  
  gtm_char_t retval [BUFLEN]; // the return value
  memset (retval, 0, sizeof (retval));
  
  gtm_char_t value[4] [BUFLEN]; // the return value
  memset (value[0], 0, sizeof (retval));

  int loopstatus=1;
  printf ("routine:\"%s\",\n ",routine);

  if (argc < 1)
    {
        printf ("error needs arguments\n ");
      return ;
    }
  printf ("lastarg:\"%d\",\n ",argc-1);
  printf ("argc:\"%d\",\n ",argc);
  int i;
  for (i =0; i < argc; i++) {
    strcpy(value[i],argv[i]); // we want to pass our own value int
    printf ("argv%d:\"%s\",\n ",i,argv[i]);

  } 

  printf ("tablename:\"%s\",\n keys : {",tablename);

  while (loopstatus) {
    
    switch(argc){

      // no with 0
    case 1 :
      status = gtm_ci (routine,&retval,tablename, value[0]);
	break;
    case 2 :
      printf ("value%d:\"%s\",\n ",0,value[0]);
      printf ("value%d:\"%s\",\n ",1,value[1]);
      status = gtm_ci (routine,&retval,tablename, value[0],value[1]);
      break;
      
	// case 3:
    case 3 :
      printf ("value%d:\"%s\",\n ",0,value[0]);
      printf ("value%d:\"%s\",\n ",1,value[1]);
      printf ("value%d:\"%s\",\n ",1,value[2]);
      status = gtm_ci (routine,&retval,tablename, value[0],value[1],value[2]);
      break;

	// case 4
    case 4 :
      printf ("value%d:\"%s\",\n ",0,value[0]);
      printf ("value%d:\"%s\",\n ",1,value[1]);
      printf ("value%d:\"%s\",\n ",1,value[2]);
      printf ("value%d:\"%s\",\n ",3,value[3]);
      status = gtm_ci (routine,&retval,tablename, value[0],value[1],value[2],value[3]);
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


int 	gtmci_orderany1( gtm_char_t * tablename, int limitcount)
{
  
  gtm_status_t status;

  gtm_char_t hdrval2 [BUFLEN]; // the second parameter, tag value
  strcpy (hdrval2, "");
  
  gtm_char_t retval [BUFLEN]; // the return value
  memset (retval, 0, sizeof (retval));
  
  int loopstatus=1;

  printf ("tablename:\"%s\",\n keys : {",tablename);

  while (loopstatus) {
  status = gtm_ci ("ORDERANY1",&retval,tablename,hdrval2);
    if (check_status (status) != 1) {
      printf("FOSM/nodex_children2 Internal error!\n");
      char  msgbuf[BUFLEN]; 
      gtm_zstatus(msgbuf, BUFLEN); 
      fprintf(stderr, "%s\n",msgbuf); 
      loopstatus=0;
    }
    else {
      strcpy(hdrval2,retval);
    }

    if (strcmp(hdrval2, "")==0)  {
      loopstatus=0;;		
    } else {
      printf ("\t \"%s\" : 1, \n", hdrval2 ); //json
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



int test()
{
  gtmci_orderany4( "nodex","addr:city","Berlin","baccbcadadbbbab");
  gtmci_orderany3( "nodex","addr:city","Berlin");
  gtmci_orderany2( "nodex","addr:city");
  gtmci_orderany1( "nodex",100);  
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
  char * args[5];
  int i;
  for (i=0; i < 4;i++)    {
      args[i]="";
    }
  int limitcount=0;
  int value=0;
  char c;
  while ((c = getopt (argc, argv, "t:jk:l:m:n:c:v")) != -1)   {
    
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
      if (argcount < 4) argcount=5;
      break;     

    case 'v' : 
      // get the value. does not call order
      value=1;
      break;     

    }
  }
  printf ("\targcount: %d,\n",argcount); //json attribute
  for (i=0; i < 4;i++)    {
    printf ("iargv%d:\"%s\",\n ",i,args[i]);
    }

  // now call the function
    switch (argcount) {
    case 1:
      gtmci_orderany1(tablename , limitcount);  
      break;      
    case 2:
      //gtmci_orderany2(tablename , args[0], limitcount);  
      gtmci_any_2("ORDERANY2", tablename, limitcount, args[0],args[1]);
      break;      

    case 3:
      gtmci_any_3("ORDERANY3", tablename, limitcount, args[0],args[1],args[2]);
      break;      

    case 4:
      if (value)
	{
	  gtmci_any_4("VALUEANY4", tablename, 1, args[0],args[1],args[2],args[3]);
	}
      else
	{
	  gtmci_any_4("ORDERANY4", tablename, limitcount, args[0],args[1],args[2],args[3]);
	}
      break;      
    

    }



  gtm_exit();
  printf ("}}\n"); // json

  // try and reset the terminal
  //  system("stty sane"); 

  return 0;
}
