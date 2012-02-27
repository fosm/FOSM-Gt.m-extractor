#! /usr/bin/perl
use lib "/home/h4ck3rm1k3/perl5/lib/perl5";
#eval $(perl -I$HOME/perl5/lib/perl5 -Mlocal::lib)
use Dancer;
use Plack::Runner;

sub basicpage {

    my $code =shift;

    q[
<html><head><script src="http://code.jquery.com/jquery-latest.js"></script>
<script src="/introspector/introspector.js"></script></head><body>
<div id="stdout"><!-- output will land here--></div>
<script>
$(document).ready(function(){] 
."\n$code\n" .
q[}); // ready\n  
</script></body></html>];
};

# details about a dat file
get '/tables/details/:datfile' => sub {

    my $tablename = params->{datfile};
    basicpage ("look_at_table(\"$tablename\");");
};

get '/tables' => sub {
    basicpage ("loot_at_tables()");
};

sub runprogram
{
    my $program=shift;
    warn "going to run $program";
    open PROC, "$program |";
    my $output="";
    while (<PROC>)
    {
	$output .= $_;
    }
    close PROC;
    return $output;
}

get '/tables/listk1/:datfile/:rowcount' => sub {

    my $count = params->{rowcount};
    my $tablename = params->{datfile};
    my $output="";
    $output=  "load_dbjavascript(\"/proxy/tables/listk1db/${tablename}/${count}\")";
    basicpage ($output);
};

sub rungtm
{
    my $args=shift;
# now setup the paths :
    $ENV{gtmgbldir}="/pine02/data/xapi.gld";
    $ENV{GTMCI}="/pine02/scripts/FOSM.ci";
    $ENV{LD_LIBRARY_PATH}='/iscsidata/pine02/gtm/';
    return  runprogram("/home/h4ck3rm1k3/experiments/simpletest/simple " . $args);    
}

get '/tables/listk3db/:datfile/:key1/:key2/:rowcount' => sub {

    my $count = params->{rowcount};
    my $tablename = params->{datfile};
    my $firstkey = params->{key1};
    my $secondkey = params->{key2};
    my $output=rungtm("-t$tablename -c$count -k$firstkey -l$secondkey");
    "table_data(\"$tablename\",\"$count\",$output);";
};

get '/tables/listk4db/:datfile/:key1/:key2/:key3/:rowcount' => sub {

    my $count = params->{rowcount};
    my $tablename = params->{datfile};
    my $firstkey = params->{key1};
    my $secondkey = params->{key2};
    my $thirdkey = params->{key3};
    my $output=rungtm("-t$tablename -c$count -k$firstkey -l$secondkey -m$thirdkey");
    "table_data(\"$tablename\",\"$count\",$output);";
};

get '/tables/listk5db/:datfile/:key1/:key2/:key3/:key4/:rowcount' => sub {

    my $count = params->{rowcount};
    my $tablename = params->{datfile};
    my $firstkey = params->{key1};
    my $secondkey = params->{key2};
    my $thirdkey = params->{key3};
    my $key4 = params->{key4};
    my $output=rungtm("-t$tablename -c$count -k$firstkey -l$secondkey -m$thirdkey  -n$key4");
    "table_data(\"$tablename\",\"$count\",$output);";
};


#http://pine02.fosm.org:5000/tables/value4db/relation/2284/seq/1/type
get '/tables/value4db/:datfile/:key1/:key2/:key3/:key4' => sub {

    my $count = params->{rowcount};
    my $tablename = params->{datfile};
    my $firstkey = params->{key1};
    my $secondkey = params->{key2};
    my $thirdkey = params->{key3};
    my $key4 = params->{key4};
    my $output=rungtm("-t$tablename -c1 -k$firstkey -l$secondkey -m$thirdkey  -n$key4 -v ");
    "table_data(\"$tablename\",\"$count\",$output);";
};

get '/tables/listk6db/:datfile/:key1/:key2/:key3/:key4/:key5/:rowcount' => sub {

    my $count = params->{rowcount};
    my $tablename = params->{datfile};
    my $firstkey = params->{key1};
    my $secondkey = params->{key2};
    my $thirdkey = params->{key3};
    my $key4 = params->{key4};
    my $key5 = params->{key6};
    my $output=rungtm("-t$tablename -c$count -k$firstkey -l$secondkey -m$thirdkey  -n$key4 -o$key5");
    "table_data(\"$tablename\",\"$count\",$output);";
};



get '/tables/listk2db/:datfile/:key1/:rowcount' => sub {

    my $count = params->{rowcount};
    my $tablename = params->{datfile};
    my $firstkey = params->{key1};
    my $output=rungtm("-t$tablename -c$count -k$firstkey");
    #warn $output;    
    "table_data_k1(\"$tablename\",\"$count\",\"$firstkey\",$output);";
};

get '/tables/listk1db/:datfile/:rowcount' => sub {

    my $count = params->{rowcount};
    my $tablename = params->{datfile};
    my $output="";
# now setup the paths :
    $ENV{gtmgbldir}="/pine02/data/xapi.gld";
    $ENV{GTMCI}="/pine02/scripts/FOSM.ci";
    $ENV{LD_LIBRARY_PATH}='/iscsidata/pine02/gtm/';
    $output=  runprogram("/home/h4ck3rm1k3/experiments/simpletest/simple -t$tablename -c$count -j");
    #warn $output;
    "table_data(\"$tablename\",\"$count\",$output);";
};

get '/' => sub {
        "Hello World!"
};

#use JSON;

sub listdir
{
    my $dirname=shift;
    #listdir("/pine02/data/")
    opendir D,$dirname or die "cannot open $dirname";
    warn $dirname;
    my @dats = map { s/\.dat$//; $_ } grep { /\.dat$/ } readdir(D);
    closedir D;
    #join ""
 #   $json->encode( \@dats );
    warn join ",",@dats;
    to_json(\@dats);
}


get '/tables/list' => sub {

q[
<html>
<head>
<script src="http://code.jquery.com/jquery-latest.js"></script>
<script src="/introspector/introspector.js"></script>
</head>
<body>
list of tables, just the dat files! <div id="tables"></div>
<script>

  $(document).ready(function(){
   var list=
]
		    . 
		    listdir("/pine02/data/") .
q[
process_tablelist(list);
     }); // ready
  </script>
</body>
</html>
];

};




## proxy interface 
use LWP::UserAgent;

#use LWP::Simple qw
get qr '/proxy/(.*)' => sub {
    # proxy the request to some server
    my $url = request->path ;
    my $source = config->{gtm_data_source};
    $url =~ s/(.+proxy)/$source/; # replace the proxy with the real server
    warn "Going to get $url";
    my $ua = new LWP::UserAgent;
    my $req = new HTTP::Request 'GET' => $url;
    # send request
    my $res = $ua->request($req);

    # check the outcome
    if ($res->is_success) {
	return $res->content;
    } else {
	print "Error: " . $res->status_line . "\n";
    }    
};

#dance;

my $app = sub {
    my $env = shift ;
    my $request = Dancer::Request->new ( env => $env ) ;
    Dancer->dance($request);
};
Plack::Runner->run($app);
