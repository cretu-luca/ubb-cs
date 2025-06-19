<?php 
include "db.php";

if ($_POST) {
    $name = $_REQUEST['name'];

    $stmt = $db->prepare("SELECT * FROM User WHERE Name = ?");
    $stmt->execute([$name]);

    $user = $stmt->fetch();
    
    if ($user) {
        $_SESSION['user'] = $user;
        header('Location: question.php');
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
            <button type="submit"> login </button>
        </form>
    </body>
</html>