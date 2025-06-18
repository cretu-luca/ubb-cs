<!-- Notification Container -->
<div id="notification-container">
    <span id="notification-text"></span>
    <button onclick="document.getElementById('notification-container').style.display='none'">X</button>
</div>

<script src="websocket-client.js"></script>
<script>
    // Create a WebSocket-like connection
    const socket = new PHPWebSocket("websocket-server.php");
    
    // Handle connection open
    socket.onopen = function() {
        console.log("WebSocket connection established");
    };
    
    // Handle incoming messages
    socket.onmessage = function(event) {
        // Show notification
        const notificationContainer = document.getElementById('notification-container');
        const notificationText = document.getElementById('notification-text');
        
        notificationText.textContent = event.data;
        notificationContainer.style.display = 'block';
        
        // Hide after 5 seconds
        setTimeout(() => {
            notificationContainer.style.display = 'none';
        }, 5000);
    };
</script>
