<?php
include 'db.php';

if ($_POST) {
    $name = $_POST['name'];
    $stmt = $db->prepare("SELECT * FROM User WHERE name = ?");
    $stmt->execute([$name]);
    $user = $stmt->fetch();
    
    if ($user) {
        $_SESSION['user'] = $user;
        header('Location: question.php');
    } else {
        echo "User not found";
    }
}
?>

<html>
<head><title>Login</title></head>
<body>
    <h1>Property System</h1>
    <form method="POST">
        <p>Enter your name:</p>
        <input type="text" name="name" required>
        <input type="submit" value="Next">
    </form>
</body>
</html>