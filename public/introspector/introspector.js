
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

function table_data(tablename,count,output) {

    $("#stdout").append("<p>tablename " + tablename);
    $("#stdout").append("<p>count " + count);
    $("#stdout").append("<p>output " + output);

}

function load_dbjavascript(url) {

    $("#stdout").append("<p>loading " + url);

    $.ajax({
	url: url,
//	data: data,
	success: function (data) {
	    $("#stdout").append("<p>output " + data);
		},
//	dataType: dataType
    });

}
