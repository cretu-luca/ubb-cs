<?php 
include "db.php";

if ($_POST) {
    $name = $_REQUEST['name'];
    $password = $_REQUEST['password'];

    $stmt = $db->prepare("SELECT * FROM User WHERE Username = ?");
    $stmt->execute([$name]);

    $user = $stmt->fetch();
    
    if ($user) {
        if (strcmp($user['Password'], $password) == 0) {
            $_SESSION['user'] = $user;
            header('Location: home.php');
        } else {
            echo 'invalid password';
        }

    } else {
        echo 'login failed';
    }
}

?>

<html> 
    <head> 
        <title> login </title>
    </head>

    <p> login </p>

    <body>
        <form method="post">
            <p> name: <input type="text" name="name" /> <p>
            <p> password: <input type="text" name="password" /> <p>
            <button type="submit"> login </button>
        </form>
    </body>
</html>