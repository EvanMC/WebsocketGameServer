var ws;

connect();

function connect() {
	if("WebSocket" in window) {
		ws = new WebSocket("ws://127.0.0.1:9554");
		
		ws.onopen = function() {
			alert("Connection established");
		};
		
		ws.onmessage = function(evt) {
			var received_msg = evt.data;
			alert("Message is received: " + received_msg);
		};
		
		ws.onerror = function(evt) {
			alert("Error");
			var received_msg = evt.data;
			alert("Error: " + received_msg);
		};
		
		ws.onclose = function() {
			// websocket is closed.
			alert("Connection closed");
		};
	} else {
		alert("WebSocket NOT supported by your browser!");
	}
}

function disconnect() {
	ws.close();
}

function send(message) {
	ws.send(message);
	alert("Sent: " + message);
}