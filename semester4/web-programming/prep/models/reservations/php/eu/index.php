<?php
include "db.php";

if ($_POST) {
    $name = $_POST['name'];

    $stmt = $db->prepare("SELECT * FROM User WHERE name = ?");
    $stmt->execute([$name]);
    $user = $stmt->fetch();


    if ($user) {
        $_SESSION['user'] = $user;
        header('Location: question.php');
    } else {
        echo "user not found";
    }
}
?>

<html>
<head> 
    <title> login </title>
</head>
<body>
    <h1> login </h1>
    <form method="POST">
        <p> name: </p>
        <input type="text" name="name" required>
        <button type="submit"> Next </button>
    </form>
</body>
</html>