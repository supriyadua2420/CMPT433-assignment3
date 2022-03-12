"use strict";


var socket = io.connect();
// Run when webpage fully loaded
$(document).ready(function() {

	
	$('#modeNone').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("None");
		$('#modeid').html("None");
	});
	
	$('#modeRock1').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("Rock1");
		$('#modeid').html("Rock1");
	});

	$('#modeRock2').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("Rock2");
		$('#modeid').html("Rock2");
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

	$('#volumeUp').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("volumeUp");
		$('#volumeid').html("this");
	});

	$('#volumeDown').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("volumeDown");
		//$('#modeid').html("Base");
	});
	$('#tempoUp').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("tempoUp");
		//$('#modeid').html("Base");
	});
	$('#tempoDown').click(function() {
		// Log a message and call other function.
		console.log("Clicked button!");
		sendBeatsCommand("tempoDown");
		//$('#modeid').html("Base");
	});

	//change
	console.log("Document loaded");
	
	// Send message to request some (one-shot) updates:
	sendRequest('cpuinfo');
	sendRequest('version');
	sendRequest('cmdline');

	// Setup a repeating function (every 1s)
	window.setInterval(function() {sendRequest('uptime')}, 1000);


	// Handle data coming back from the server
	socket.on('fileContents', function(result) {
		var fileName = result.fileName;
		var contents = result.contents;
//		console.log("fileContenst callback: fileName " + fileName 
//				+ ", contents: " + contents);
		
		var domObj;
		switch(fileName) {
		case 'version':
			domObj = $('#versionId');
			break;
		case 'uptime':
			domObj = $('#uptimeId');
			break;
		case 'cpuinfo':
			domObj = $('#cpuinfoId');
			break;
		case 'cmdline':
			domObj = $('#cmdlineId');
			break;
		default:
			console.log("Unknown DOM object: " + fileName);
			return;
		}
		// Make linefeeds into <br> tag.
		contents = replaceAll(contents, "\n", "<br/>");
		domObj.html(contents);
	});


	/*socket.on('daError', function(result) {
		var msg = divMessage('SERVER ERROR: ' + result);
		$('#messages').append(msg);
	});*/
	
	socket.on('commandReply', function(result) {
		console.log("Got result!");
		var newDiv = $('<div></div>').text(result);
		$('#messages').append(newDiv);
		$('#messages').scrollTop($('#messages').prop('scrollHeight'));
		$('#status').html(result);
	});

	
});


function sendBeatsCommand(message) {
	socket.emit('beats', message);
};

function sendRequest(file) {
	console.log("Requesting '" + file + "'");
	socket.emit('proc', file);
}

function replaceAll(str, find, replace) {
	return str.replace(new RegExp(find, 'g'), replace);
}
