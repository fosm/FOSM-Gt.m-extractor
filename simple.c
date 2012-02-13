

#include "gtmxc_types.h"   // For GTM call-in function prototypes
#include "string.h"        // strlen(), memcpy(), strncmp()
#include "stdlib.h"        // setenv

#include "stdio.h"        // setenv
#define MGIRPCBUFLEN 256

// parts of code taken from http://fooboo.org/~tmr/public/mod_mgirpc/mod_mgirpc.c

int check_status (gtm_status_t status) {

  if (status != 0) {
    gtm_char_t msgbuf [MGIRPCBUFLEN];
    gtm_zstatus (msgbuf, MGIRPCBUFLEN);
    printf ((const char *) msgbuf);
    return 0;
  }

  return 1;
}

int process_nodex () {

  gtm_status_t status;
  gtm_char_t hdrval [MGIRPCBUFLEN];
  gtm_char_t retval [MGIRPCBUFLEN];
  //  while (1) 
  {
    memset (hdrval, 0, sizeof (hdrval));

    status = gtm_ci ("nodexorder", &retval, &hdrval);
    if (check_status (status) != 1) {
      printf("FOSM/nodexorder Internal error!");
      //    continue;
    }
    printf ("Check '%s' \n", hdrval);

    while (hdrval)
      {
	if (strcmp(hdrval, ""))
	  {
	    return;
	  }
	status = gtm_ci ("nodexorder", &retval , &hdrval);
	if (check_status (status) != 1) {
	  printf("FOSM/nodexorder Internal error!");
	}
	printf ("Check '%s'\n",hdrval);
	
      }


  }

  return 1;
}

int main()
{

  setenv("GTMCI","/pine02/scripts/FOSM.ci",0);
  setenv("gtmroutines","/pine02/scripts/",0);
  /*

	 "/pine02/scripts/ewd/mdb",
	 "/pine02/scripts/ewd/EWD",
	 "/pine02/scripts/serenji",
	 "/pine02/scripts/ewd/EWD/m_apache",
	 "/pine02/scripts/gtm",
	 "/pine02/scripts/gtmx", 0);
  */
  setenv("gtmgbldir","/pine02/data/xapi_big.gld",0);
  
  int err=  gtm_init();
  printf ("init returned %d\n",err);


  process_nodex();

  
  gtm_exit();
  return 0;
}
