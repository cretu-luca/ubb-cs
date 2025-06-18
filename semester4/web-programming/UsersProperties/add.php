<?php
include "db.php";

if ($_POST) {
    $address = $_SESSION['address'];
    $description = $_SESSION['description'];

    
}

?>

<html>
    <form method="post">
        <p> address: <input type="text" name="address"> </p>
        <p> description: <input type="text" name="description"> </p>
        <button type="submit"> add </button>
    </form> 
</html>