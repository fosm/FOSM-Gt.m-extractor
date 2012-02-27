LD_LIBRARY_PATH=/iscsidata/pine02/gtm/

# first we 
test : simple2 
	#bash ./runtest.sh 
	./simple2 -t nodex -j
	stty sane

simple2 : /pine02/scripts/FOSM.ci  /pine02/scripts/FOSM.m simple.c
	gcc -save-temps  -I/pine02/gtm  -O0 -g -L/usr/local/lib -fstack-protector  -L/pine02/gtm -lgtmshr simple.c -o simple2

/pine02/scripts/FOSM.ci : FOSM.ci
	cp  FOSM.ci /pine02/scripts/FOSM.ci

/pine02/scripts/FOSM.m : FOSM.m
	cp  FOSM.m /pine02/scripts/FOSM.m


deploy : simple
	./simple2 -t nodex -j -c10
	stty sane

install : /pine02/scripts/FOSM.ci  /pine02/scripts/FOSM.m simple.c
	echo test

simple : /pine02/scripts/FOSM.ci  /pine02/scripts/FOSM.m simple.c
	gcc -save-temps  -I/pine02/gtm  -O0 -g -L/usr/local/lib -fstack-protector  -L/pine02/gtm -lgtmshr simple.c -o simple


