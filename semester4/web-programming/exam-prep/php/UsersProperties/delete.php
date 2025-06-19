<?php 
include "db.php";

$address = null;

if ($_POST) {
    $address = $_REQUEST['address'];

    $stmt = $db->prepare("SELECT * FROM Property WHERE Address LIKE ?");
    $stmt->execute(['%' . $address . '%']);
    $result = $stmt->fetch();

    $propId = $result['Id'];
    $userId = $_SESSION['user']['Id'];

    echo $propId;
    echo $userId;

    $stmt = $db->prepare("SELECT * FROM UserToProperties WHERE UserId = ? AND PropertyId = ?");
    $stmt->execute([$userId, $propId]);

    if (empty($stmt->fetchAll())) {
        echo 'not your property';
        return;
    }

    $stmt = $db->prepare("SELECT * FROM UserToProperties WHERE UserId <> ? AND PropertyId = ?");
    $stmt->execute([$userId, $propId]);

    $result = $stmt->fetchAll();

    if ($result) {
        echo 'cannot delete property, will only remove ownership';
        
        $stmt = $db->prepare("DELETE FROM UserToProperties WHERE UserId = ? AND PropertyId = ?");
        $stmt->execute([$userId, $propId]);
    } else {
        $stmt = $db->prepare("DELETE FROM UserToProperties WHERE UserId = ? AND PropertyId = ?");
        $stmt->execute([$userId, $propId]);

        $stmt = $db->prepare("DELETE FROM Property WHERE Id = ?");
        $stmt->execute([$propId]);
    }
}

?>

<html>
    <head> 
        <title> delete property by name </title>
    </head>

    <body>
        <form method="post">
            <p> address: <input type="text" name="address"> </p>
            <button type="submit"> delete </button>
        </form>
    </body>
<html>