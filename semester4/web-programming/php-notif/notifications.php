// Inside reserve action
if (strcmp($action, "reserve") == 0) {
    include "notifications.php";
    
    foreach ($_SESSION['sessionReservations'] as $r) {
        // Process reservation...
        
        // Create notification with user info
        $username = $_SESSION['user']['Username'];
        $notification = $username . " reserved room #" . $r['RoomId'] . " for " . $r['NumberOfGuests'] . " guests.";
        
        // This will update the global notification counter
        addNotification($notification);
    }
}<?php
include "db.php";

// Track the last notification timestamp in the session
if (!isset($_SESSION['last_notification_check'])) {
    $_SESSION['last_notification_check'] = 0;
}

// Special system-wide notification counter
$notificationCounterFile = sys_get_temp_dir() . '/php_notification_counter.txt';

function addNotification($message) {
    global $notificationCounterFile;
    
    // Update the notification counter
    file_put_contents($notificationCounterFile, time());
    
    // Send notification via our WebSocket-like system
    $messageObj = [
        'message' => $message,
        'timestamp' => time()
    ];
    
    // Store message for WebSocket server to pick up
    $wsMessageFile = sys_get_temp_dir() . '/php_websocket_message.txt';
    file_put_contents($wsMessageFile, json_encode($messageObj));
}

function getNotificationTimestamp() {
    global $notificationCounterFile;
    
    if (file_exists($notificationCounterFile)) {
        return (int)file_get_contents($notificationCounterFile);
    }
    
    return 0;
}
?>
