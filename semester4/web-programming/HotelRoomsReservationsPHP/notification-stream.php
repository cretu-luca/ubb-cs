<?php
// Simple SSE implementation - check once and respond
include "db.php";
include "notifications.php";

header('Content-Type: text/event-stream');
header('Cache-Control: no-cache');
header('Connection: keep-alive');

// Get the system notification counter
$systemTimestamp = getNotificationTimestamp();

// Send the current timestamp regardless
echo "id: " . $systemTimestamp . "\n";
echo "data: heartbeat\n\n";
flush();
?> 