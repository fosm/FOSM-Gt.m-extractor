
export GTMCI=/pine02/gtmx/bin/gtm.ci
export gtmgbldir=/pine02/data/xapi_small.gld

zappy='/pine02' ; export zappy
gtm_dist="$zappy/gtm"; export gtm_dist
gtmx="$zappy/gtmx"; export gtmx
gtmroutines="$zappy/scripts/o($zappy/scripts $zappy/serenji $gtmx $gtm_dist)"; export gtmroutines
gtm="$gtmx/gtmrun ^direct gtm"; export gtm
gtmrun="$gtmx/gtmrun" ; export gtmrun
mupip="$gtm_dist/mupip"; export mupip
lke="$gtm_dist/lke"; export lke
gde="$gtmx/gtmrun ^GDE"; export gde
dse="$gtm_dist/dse"; export dse
PATH=$PATH:$zappy/scripts:$zappy/gtmx:$zappy/gtm
gtm_repl_instance="fosm01";export gtm_repl_instance

cd /pine02/data
/pine02/gtmx/bin/gtm
