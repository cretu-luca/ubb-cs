<?php
include "db.php";

if ($_POST) {

    if (!isset($_SESSION['user'])) {
        echo 'not logged in';
    } else {
        $address = $_POST['address'];
        $description = $_POST['description'];

        $stmt = $db->prepare("
            INSERT INTO Property (address, description)
            VALUES (?, ?);
        "); 
        
        $stmt->execute([$address, $description]);
    }
}
?>

<html>
    <head> 
        <title> add property </title>
    </head>

    <body>
        <form method="POST">
            <p> address: <input type="text" name="address" required> </p>
            <p> description: <input type="text" name="description" required> </p>

            <button type="submit"> add </button>
        </form>
    </body>
</html>