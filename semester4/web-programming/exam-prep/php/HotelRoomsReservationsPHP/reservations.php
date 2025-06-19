<?php 
include "db.php";

if ($_POST) {
    $action = $_REQUEST['action'];

        if (strcmp($action, "reserve") == 0) {
        include "notifications.php";
        
        foreach ($_SESSION['sessionReservations'] as $r) {
            echo $r['NumberOfGuests'];

            $stmt = $db->prepare("INSERT INTO Reservation 
                (UserId, RoomId, CheckInDate, CheckOutDate, NumberOfGuests, TotalPrice)
                VALUES (?, ?, ?, ?, ?, ?)"); 

            $stmt->execute([$r['UserId'], $r['RoomId'], $r['CheckInDate'], $r['CheckOutDate'], $r['NumberOfGuests'], $r['TotalPrice']]);
            
            // Create notification with user info
            $username = $_SESSION['user']['Username'];
            $notification = $username . " reserved room #" . $r['RoomId'] . " for " . $r['NumberOfGuests'] . " guests.";
            
            // This will update the global notification counter
            addNotification($notification);
        }

    } else if (strcmp($action, "cancel") == 0) {
        $_SESSION['sessionReservations'] = [];
    }
}


?>

<html> 
    <head>
        
    </head>

    <body>
        <p> current session reservations: </p>
        
        <?php if (isset($_SESSION['sessionReservations'])): ?>   
            <table>
                <tr> <th> UserId </th> <th> RoomId </th> <th> CheckInDate </th> <th> CheckOutDate </th> <th> NumberOfGuests </th> <th> TotalPrice </th> </tr> 
                <?php foreach($_SESSION['sessionReservations'] as $r): ?>
                    <tr>
                        <td> <?php echo $r['UserId']; ?> </td>
                        <td> <?php echo $r['RoomId']; ?> </td>
                        <td> <?php echo $r['CheckInDate']; ?> </td>
                        <td> <?php echo $r['CheckOutDate']; ?> </td>
                        <td> <?php echo $r['NumberOfGuests']; ?> </td>
                        <td> <?php echo $r['TotalPrice']; ?> </td>
                    </tr> 
                <?php endforeach; ?>

                <form method="post"> 
                    <input type="hidden" name="action" value="reserve"/>
                    <button type="submit"> reserve </button>
                </form>

                <form method="post">
                    <input type="hidden" name="action" value="cancel"/>
                    <button type="submit"> cancel </button>
                </form>
            </table>
        <?php endif; ?>

    </body>

</html>