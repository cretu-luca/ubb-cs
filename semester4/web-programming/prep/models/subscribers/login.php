<?php
include "db.php";

if ($_POST) {
    $username = $_POST['username'];

    $stmt = $db->prepare("SELECT * FROM Persons WHERE Name = ?");
    $stmt->execute([$username]);
    $user = $stmt->fetch();

    if ($user) {
        $_SESSION['loggedInUser'] = $user;
        header("Location: index.php");
    } else {
        echo 'user not found';
    }
}

?>

<html>
    <head>
        <title> login </title>
    </head>

    <body>
        <form method="post">
            <p> Username: <input type="text" name="username" required> </p>
            <button type="submit"> Submit </button> 
        </form>

        <a href='index.php'> home </a>
    </body>
</html>