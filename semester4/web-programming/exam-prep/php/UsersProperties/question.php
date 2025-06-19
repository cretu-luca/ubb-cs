<?php
include "db.php";

if ($_POST) {
    $answer = $_REQUEST['answer'];

    if (strcmp($answer, $_SESSION['user']['SecretAnswer']) == 0) {
        $_SESSION['loggedIn'] = true;
        Header ('Location: home.php');
    } else {
        echo 'login fail';
    }
}

?>

<html>
    <head> question </head>

    <body>
        <p> <?php echo $_SESSION['user']['SecretQuestion']; ?>

        <form method="post"> 
            <p> answer: <input type="text" name="answer"> </p>
            <button type="submit"> check </button>
        </form>
    </body>

</html> 