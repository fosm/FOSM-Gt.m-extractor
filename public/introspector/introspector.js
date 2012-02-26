
function process_tablelist(list) {
//    alert(list);
//    $("#tables")
    $("#tables").append("<p>This is a list of tables found in system</p>");
    for (t in list  )  {
	
	$("#tables").append("<ul><a href='details/" + list[t] + "'>"+ list[t] +"</a></ul>");
	
    }
//   alert(list);
}

function look_at_table(tablename) {

    $("#stdout").append("<p>This is what you can do </p>");
    $("#stdout").append("<ul><a href='../listk1/" + tablename + "/10'>"+ "List the first 10 keys</a></ul>");	

}

function look_at_tables() {

    $("#stdout").append("<p>This is what you can do </p>");
    $("#stdout").append("<ul><a href='list'>List the Tables</a></ul>");	

}

//gtm_fosminvoke: { init_returned:0, argcount: 1, tablename:"changeset", keys : { "1" : 1, "8701754" : 1, "8701971" : 1, "8702046" : 1, "8702267" : 1, "8702317" : 1, "8702351" : 1, "8702442" : 1, "8702554" : 1, "8702625" : 1, } }} );]
function gtm_fosminvoke(output) {
    var tbl=output.gtm_fosminvoke.tablename;
    $("#stdout").append("<p>tablename " + tbl);
       $("#stdout").append("<ul id=\"tbl_\"" + tbl + ">");
    var keys=output.gtm_fosminvoke.keys;
    for (k in keys) {
	//var v= keys[k];
	var id=tbl + "_" + k;
	$("#stdout").append("<li id=\"" + id+ "\"> " +k + "</li>");
    }
    $("#stdout").append("</ul>");
}

function table_data(tablename,count,output) {

    $("#stdout").append("<p>tablename " + tablename);
    $("#stdout").append("<p>count " + count);
    $("#stdout").append("<p>output " + output);
    gtm_fosminvoke(output);
}

function eval_output_table_data(data) {
    
    $("#stdout").append("<p>going to eval " + data);
     jQuery.globalEval(data);
}
function load_dbjavascript(url) {

    $("#stdout").append("<p>loading " + url);

    $.ajax({
	url: url,
//	data: data,
	success: function (data) {
	    $("#stdout").append("<p>output " + eval_output_table_data(data));
		},
//	dataType: dataType
    });

}
