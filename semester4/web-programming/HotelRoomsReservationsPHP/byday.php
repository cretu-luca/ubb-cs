<?php
include "db.php";

$result = null;

if ($_POST) {
    $queryDate = $_REQUEST['queryDate'];

    $stmt = $db->prepare("
        SELECT SUM(NumberOfGuests)
        FROM Reservation
        WHERE CheckInDate < ? AND CheckOutDate > ?");

    $stmt->execute([$queryDate, $queryDate]);
    $result = $stmt->fetch()[0];
}

?>

<html> 

    <head>

    </head>

    <body>
        <form method="post"> 
            <input type='datetime-local' name="queryDate">
            <button type="submit"> find </button>
        </form>
        
        <p> number of people: <?php echo $result != null ? $result : 0; ?>
    <body>

</html>