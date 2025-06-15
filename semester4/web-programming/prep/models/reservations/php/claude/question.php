<?php
include 'db.php';

if ($_POST) {
    $answer = $_POST['answer'];
    if (strtolower($answer) == strtolower($_SESSION['user']['secretAnswer'])) {
        $_SESSION['logged_in'] = true;
        header('Location: dashboard.php');
    } else {
        echo "Wrong answer";
    }
}
?>

<html>
<head><title>Security Question</title></head>
<body>
    <h1>Security Question</h1>
    <p>Question: <?php echo $_SESSION['user']['secretQuestion']; ?></p>
    <form method="POST">
        <input type="text" name="answer" required>
        <input type="submit" value="Login">
    </form>
</body>
</html>