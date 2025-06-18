<?php
include "db.php";

$rooms = null;
$action = null;
$price = null;
$percentage = 0;

if ($_POST) {
    $action = $_REQUEST['action'];
    if (strcmp($action, "getRooms") == 0) {
        
        $checkintime = $_REQUEST['checkintime'];
        $checkouttime = $_REQUEST['checkouttime'];
        $persons = $_REQUEST['persons'];

        $_SESSION['checkintime'] = $checkintime;
        $_SESSION['checkouttime'] = $checkouttime;
        $_SESSION['persons'] = $persons;

        $stmt = $db->prepare ("SELECT * FROM HotelRoom WHERE Capacity >= ?");
        $stmt->execute([$persons]);

        $rooms = $stmt->fetchAll();
        $numberOfRooms = sizeof($rooms);

        $stmt = $db->prepare("
            SELECT RoomId 
            FROM Reservation 
            WHERE (CheckOutDate > ? OR CheckInDate < ?) AND UserID = ?
        "); 
        $stmt->execute([$checkintime, $checkouttime, $_SESSION['user']['Id']]);

        $reservations = $stmt->fetchAll();
        $numberOfReservations = sizeof($reservations);

        foreach ($reservations as $reservation) {
            $roomId = $reservation['RoomId'];
            $roomToRemove = null;

            foreach ($rooms as $room) {
                if ($room['Id'] == $roomId) {
                    $roomToRemove = $room;
                }
            }

            $key = array_search($roomToRemove, $rooms);
            unset($rooms[$key]);
        }

        $percentage = floatval($numberOfReservations / $numberOfRooms);
        echo $percentage;

    } else if (strcmp($action, "reserve") == 0) {
        $roomId = $_REQUEST['reserveId'];
        $price = $_REQUEST['myPrice'];

        if (!isset($_SESSION["sessionReservations"])) {
            $_SESSION["sessionReservations"] = array();
        }

        $reservation = [
            "UserId" => $_SESSION['user']['Id'],
            "RoomId" => $roomId,
            "CheckInDate" => $_SESSION['checkintime'], 
            "CheckOutDate" => $_SESSION['checkouttime'],
            "NumberOfGuests" => $_SESSION['persons'],
            "TotalPrice" => $price
        ];
        
        array_push($_SESSION["sessionReservations"], $reservation);
    }
}

?>

<html>

    <head>

    </head>

    <body>
        <form method="post">
            <input type="hidden" value="getRooms" name="action"/>  
            <input type='datetime-local' name="checkintime">
            <input type='datetime-local' name="checkouttime">
            <p> persons: <input type="text" name="persons"/> </p>
            <button type="submit"> search </button>
        </form>

        <?php if ($rooms): ?>   
            <table>
                <tr> <th> RoomNumber </th> <th> Capacity </th> <th> BasePrice </tr> 
                <?php foreach($rooms as $r): ?>
                    <form method="post"> 
                    <tr>
                        <input type="hidden" value="reserve" name="action"/>
                        <input type="hidden" value="<?php echo $r['Id']; ?>" name="reserveId" />
                        <input type="hidden" value="<?php echo (int)($r['BasePrice'] * $percentage); ?>" name="myPrice" />
                        <td> <?php echo $r['RoomNumber']; ?> </td>
                        <td> <?php echo $r['Capacity']; ?> </td>
                        <td> <?php echo (int)($r['BasePrice'] * $percentage); ?> </td>   
                        <td> <button type="submit"> reserve </button> </td>
                    </tr> 
                <?php endforeach; ?>
            </table>
        <?php endif; ?>

    </body>

</html>