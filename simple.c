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
  char * args[4];
  int i;
  for (i=0; i < 4;i++)    {
      args[i]="";
    }
  int limitcount=0;
  char c;
  while ((c = getopt (argc, argv, "t:jk:l:m:c:")) != -1)   {
    
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
      // param1
      args[0]=optarg;
      if (argcount < 1) argcount=1;
      break;

    case 'k' : 
      // param2
      args[1]=optarg;
      if (argcount < 2)     argcount=2;
      break;

    case 'l' : 
      // param2
      args[2]=optarg;
      if (argcount < 3) argcount=3;
      break;

    case 'm' : 
      // param2
      args[3]=optarg;
      if (argcount < 4) argcount=4;
      break;     
    }
  }
  printf ("\targcount: %d,\n",argcount); //json attribute
  // now call the function
    switch (argcount) {
    case 1:
      gtmci_orderany1(tablename , limitcount);  
      break;      
    }


  gtm_exit();
  printf ("}}\n"); // json

  // try and reset the terminal
  //  system("stty sane"); 

  return 0;
}
