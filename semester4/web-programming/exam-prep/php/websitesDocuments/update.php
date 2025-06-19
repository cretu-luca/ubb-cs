<?php
include "db.php";

if ($_POST) {
    $name = $_REQUEST['name'];
    $message = "";
    $id = -1;

    $stmt = $db->prepare("SELECT * FROM Documents WHERE Name = ?");
    $stmt->execute([$name]);

    $result = $stmt->fetch();
    if ($result != null) {
        $id = $result['Id'];

        $stmt = $db->prepare("UPDATE Documents SET Keyword1 = ?, Keyword2 = ?, 
            Keyword3 = ?, Keyword4 = ?, Keyword5 = ? WHERE Id = ?");
        $stmt->execute([$_REQUEST['k1'], $_REQUEST['k2'], $_REQUEST['k3'], $_REQUEST['k4'], $_REQUEST['k5'], $id]);
    } else {
        $message = "document not found";
    }
}

?>

<html> 
    <head>
        <title> update document </title>
    </head>

    <body>
        <form method="post">
            <p> name: <input type="text" name="name" /> </p> 
            <p> k1: <input type="text" name="k1" /> </p>
            <p> k2: <input type="text" name="k2" /> </p>
            <p> k3: <input type="text" name="k3" /> </p>
            <p> k4: <input type="text" name="k4" /> </p>
            <p> k5: <input type="text" name="k5" /> </p>
            <button type="submit"> submit </button>

            <?php $message ?>
        </form>

        <a href="home.php"> back <a> 
    </body>

<html> 