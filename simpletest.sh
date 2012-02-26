
export gtmgbldir=/pine02/data/xapi.gl
export GTMCI=/pine02/scripts/FOSM.ci
export LD_LIBRARY_PATH=/iscsidata/pine02/gtm/
#echo LD_LIBRARY_PATH is  :$LD_LIBRARY_PATH
#ldd -v /home/h4ck3rm1k3/experiments/simpletest/simple
#bash ./simpletest2.sh
echo firstarg $1
echo second arg $2
# now just invoke the script to get the data
/home/h4ck3rm1k3/experiments/simpletest/simple  -t$1 -c$2
