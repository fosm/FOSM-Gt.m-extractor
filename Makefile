
simple : /pine02/scripts/FOSM.ci  /pine02/scripts/FOSM.m
	gcc -save-temps  -I/pine02/gtm  -O0 -g -L/usr/local/lib -fstack-protector  -L/pine02/gtm -lgtmshr simple.c

/pine02/scripts/FOSM.ci : FOSM.ci
	cp  FOSM.ci /pine02/scripts/FOSM.ci

/pine02/scripts/FOSM.m : FOSM.m
	cp  FOSM.ci /pine02/scripts/FOSM.m

