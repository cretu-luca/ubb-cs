<?php
include "db.php";

if (isset($_SESSION['loggedInUser'])) {
    $user = $_SESSION['loggedInUser'];

    $stmt = $db->prepare("SELECT * FROM Channels WHERE OwnerId = ?");
    $stmt->execute([$user['Id']]);

    $channels = $stmt->fetchAll();
}

?>

<html> 
    <head> 
        <title> owned </title>
    </head>

    <body>
        <?php if (isset($_SESSION['loggedInUser'])): ?>
            <table border='1'>
                    <tr> <th> ownerId </th> <th> name </th> <th> description </th> <th> subscribers </th> </tr> 
                    <?php foreach ($channels as $chan): ?>
                        <tr> 
                            <td> <?php echo $chan['Id']; ?> </td>
                            <td> <?php echo $chan['Name']; ?> </td>
                            <td> <?php echo $chan['Description']; ?> </td>
                            <td> <?php echo $chan['Subscribers']; ?> </td>
                        </tr> 
                    <?php endforeach ?>
                </table>
        <?php endif; ?>

        <a href='index.php'> home </a>
    </body>

</html> 
