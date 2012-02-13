#include "gtmxc_types.h"   // For GTM call-in function prototypes
#include "string.h"        // strlen(), memcpy(), strncmp()
#include "stdlib.h"        // setenv

#include "stdio.h"        // setenv
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


int process_nodex () {

  gtm_status_t status;
  gtm_char_t hdrval [BUFLEN];
  gtm_char_t retval [BUFLEN];

  int nullcount=10; // count down null items

  memset (hdrval, 0, sizeof (hdrval));

    status = gtm_ci ("nodexorder", retval, &hdrval);
    if (check_status (status) != 1) {
      printf("FOSM/nodexorder Internal error!\n");
      //    continue;
    }
    printf ("Check '%s' \n", hdrval);

    while (hdrval)
      {
	status = gtm_ci ("nodexorder", &hdrval , &hdrval);

	if (check_status (status) != 1) {
	  printf("FOSM/nodexorder Internal error!\n");
	  return;
	}

	if (strcmp(hdrval, "")==0)
	  {
	    printf("hdrval is empty %s!",hdrval);
	    return;		
	  }
	printf ("Found Key '%s'\n",hdrval);
	
      }


  return 1;
}


int main()
{

  setenv("GTMCI","/pine02/scripts/FOSM.ci",0);  // where to find the call in routine 
  setenv("gtmroutines","/pine02/scripts/o(/pine02/scripts /pine02/serenji /pine02/gtmx /pine02/gtm)",0); // where to find the FOSM.m routine
  setenv("gtmgbldir","/pine02/data/xapi_big.gld",0); // where is the database located? well this script looks for data relative, so needs to be run there as well


  int err=  gtm_init(); // init 
  printf ("init returned %d\n",err);

  process_nodex();
  
  gtm_exit();
  return 0;
}
