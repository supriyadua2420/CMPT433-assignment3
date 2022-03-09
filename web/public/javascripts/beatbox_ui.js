"use strict";


var socket = io.connect();
// Run when webpage fully loaded
$(document).ready(function() {
	
	//var name = $('#status').val();
	$('#status').html("Hello changing the message!");	
	
	$('#modeNone').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("None");
		$('#modeid').html("None");
	});
	
	$('#modeRock1').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("Rock #1");
		$('#modeid').html("Rock #1");
	});

	$('#modeRock2').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("Rock #2");
		$('#modeid').html("Rock #2");
	});

	$('#modeHiHat').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("HiHat");
		$('#modeid').html("Hi-Hat");
	});

	$('#modeSnare').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("Snare");
		$('#modeid').html("Snare");
	});

	$('#modeBase').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("Base");
		$('#modeid').html("Base");
	});

	
	
	socket.on('commandReply', function(result) {
		console.log("Got result!");
		//var newDiv = $('<div></div>').text(result);
		//$('#messages').append(newDiv);
		//$('#messages').scrollTop($('#messages').prop('scrollHeight'));
	});
	
});


function sendBeatsCommand(message) {
	socket.emit('beats', message);
};
