<html>
    <head> 
        <title> home </title>
    <head>

    <?php if (isset($_SESSION['loggedInUser'])): ?>
        <p> Hi, <?php $_SESSION['loggedInUser']['Name'] ?> </p>
    <?php endif; ?>

    <body>
        <a href='login.php'> login </a> <br> 
        <a href='owned.php'> owned </a> <br>
        <a href='subscriptions.php'> subscriptions </a> <br> 
    </body>
</html> 