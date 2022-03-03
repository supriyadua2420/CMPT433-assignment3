"use strict";

// Run when webpage fully loaded
$(document).ready(function() {
	// Register a callback function for the changeBtn button:
	//$('#changeBtn').click(function() {
		// Log a message and call other function.
//		console.log("Clicked button!");
//		changeBoxStyles();
//	});
	//var name = $('#status').val();
	$('#status').html("Hello changing the message!");	
	window.setInterval(function() {updateTime()}, 1000);
});
