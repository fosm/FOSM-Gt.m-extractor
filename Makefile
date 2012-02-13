LD_LIBRARY_PATH=/iscsidata/pine02/gtm/

test : simple 
	bash ./runtest.sh 


simple : /pine02/scripts/FOSM.ci  /pine02/scripts/FOSM.m simple.c
	gcc -save-temps  -I/pine02/gtm  -O0 -g -L/usr/local/lib -fstack-protector  -L/pine02/gtm -lgtmshr simple.c -o simple

/pine02/scripts/FOSM.ci : FOSM.ci
	cp  FOSM.ci /pine02/scripts/FOSM.ci

/pine02/scripts/FOSM.m : FOSM.m
	cp  FOSM.m /pine02/scripts/FOSM.m


