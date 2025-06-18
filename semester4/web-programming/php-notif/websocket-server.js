<?php
include "db.php"; // This includes session handling

// Set headers for AJAX
header('Content-Type: application/json');
header('Cache-Control: no-cache, must-revalidate');
header('Expires: Mon, 26 Jul 1997 05:00:00 GMT');

// Handle different WebSocket actions
$action = isset($_REQUEST['action']) ? $_REQUEST['action'] : '';
$response = ['success' => false];

// Message storage file - we'll use this to share messages between all clients
$messageFile = sys_get_temp_dir() . '/php_websocket_message.txt';

switch ($action) {
    case 'connect':
        // Just acknowledge the connection
        $response = ['success' => true, 'status' => 'connected'];
        break;
        
    case 'poll':
        // Check for new messages
        if (file_exists($messageFile)) {
            $messageData = file_get_contents($messageFile);
            $messageObj = json_decode($messageData, true);
            
            // Check if the message is newer than what the client has seen
            $lastSeen = isset($_SESSION['last_message_time']) ? $_SESSION['last_message_time'] : 0;
            
            if ($messageObj && isset($messageObj['timestamp']) && $messageObj['timestamp'] > $lastSeen) {
                // Update the client's last seen time
                $_SESSION['last_message_time'] = $messageObj['timestamp'];
                
                $response = [
                    'success' => true,
                    'hasMessage' => true,
                    'message' => $messageObj['message']
                ];
            } else {
                $response = ['success' => true, 'hasMessage' => false];
            }
        } else {
            $response = ['success' => true, 'hasMessage' => false];
        }
        break;
        
    case 'send':
        // Process a new message
        $message = isset($_POST['message']) ? $_POST['message'] : '';
        
        if (!empty($message)) {
            // Store the message with a timestamp
            $messageObj = [
                'message' => $message,
                'timestamp' => time()
            ];
            
            file_put_contents($messageFile, json_encode($messageObj));
            $response = ['success' => true];
        } else {
            $response = ['success' => false, 'error' => 'No message provided'];
        }
        break;
        
    default:
        $response = ['success' => false, 'error' => 'Unknown action'];
        break;
}

// Return the response as JSON
echo json_encode($response);
?>
