<?php
include 'db.php';

if ($_POST) {
    $answer = $_POST['answer'];
    if ($answer == $_SESSION['user']['secretAnswer']) {
        $_SESSION['logged_in'] = true;
        header('Location: dashboard.php');
    } else {
        echo "Wrong answer";
    }
}
?>

<html>
    <head>
        <title> question </title>
    </head>

    <body>
        <p> Question: <?php echo $_SESSION['user']['secretQuestion']; ?> </p>
        <form method="POST">
            <input type="text" name="answer" required>
            <button type="submit"> Submit </button>
        </form>
    </body>
</html>