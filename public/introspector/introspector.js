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

function load_details_data(newlevel, count, id, table, key)
{
//  alert(id);
  $("#" + id).append("<li>Loading</li>");

    // now how many keys?
    switch(newlevel){
	case 1:
	break;
	case 2:
	var url = "http://pine02.fosm.org:5000/tables/listk2db/" + table +"/" + key +"/" + count;	
	load_dbjavascript(url);
	break;
	case 3:
	break;
	case 4:
	break;
	default :
	break;
    }
}

//gtm_fosminvoke: { init_returned:0, argcount: 1, tablename:"changeset", keys : { "1" : 1, "8701754" : 1, "8701971" : 1, "8702046" : 1, "8702267" : 1, "8702317" : 1, "8702351" : 1, "8702442" : 1, "8702554" : 1, "8702625" : 1, } }} );]
function gtm_fosminvoke(output,count) {

    var tbl=output.gtm_fosminvoke.tablename;
    $("#stdout").append("<p>tablename " + tbl);
    var keycount=output.gtm_fosminvoke.argcount;
    var keycount2=keycount+1; // the key count for the children

    $("#stdout").append("<p>key count " + keycount);
    $("#stdout").append("<ul id=\"tbl_\"" + tbl + ">");

    var keys=output.gtm_fosminvoke.keys;
    var idclean= 1;

    for (k in keys) {
	//var v= keys[k];
	var id=tbl + "_" + idclean;
	idclean++;
	var style="style=\"border:1px solid red; background-color:yellow;\"";
	var code = "onclick=\'load_details_data(" + keycount2 +"," + count +",\"" + id +"\",\"" + tbl +"\",\"" + k +"\");\'";
	$("#stdout").append("<li  "+ style + " " + code + " id=\"" + id+ "\"> " +k + "</li>");
	//var x = document.getElementById(id);
	//alert (x);
//	jQuery("#" + id).click(function(event) {

//	    return false;
//	})
    }
    $("#stdout").append("</ul>");
}

function table_data(tablename,count,output) {

    $("#stdout").append("<p>tablename " + tablename);
    $("#stdout").append("<p>count " + count);
    $("#stdout").append("<p>output " + output);
    gtm_fosminvoke(output,count);
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
