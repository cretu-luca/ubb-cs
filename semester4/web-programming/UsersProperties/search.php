<?php
include "db.php";

$result = null;
$properties = null;

$maxSearch = -1;
$maxSearchKey = -1;

if (!isset($_SESSION['property_searches'])) {
    $_SESSION['property_searches'] = array();
}

if ($_POST) {
    $query = $_REQUEST['query'];

    $stmt = $db->prepare("SELECT * FROM Property WHERE Description LIKE ?");
    $stmt->execute(['%' . $query . '%']);
    $result = $stmt->fetchAll();

    foreach ($result as $r) {
        $propId = $r['Id'];
        if (isset($_SESSION['property_searches'][$propId])) {
            $_SESSION['property_searches'][$propId] = $_SESSION['property_searches'][$propId] + 1; 
        } else { 
            $_SESSION['property_searches'][$propId] = 1;
        }
    }

    $stmt = $db->prepare("SELECT * FROM Property");
    $stmt->execute();

    $properties = $stmt->fetchAll();
    foreach ($properties as $prop) {
        $propId = $prop['Id'];
        if (isset($_SESSION['property_searches'][$propId])) {
            
            if ($_SESSION['property_searches'][$propId] > $maxSearch) {
                $maxSearch = $_SESSION['property_searches'][$propId];
                $maxSearchKey = $prop;
            }
        }
    }
}

?>

<html>
    <head>
        <title>Property Search</title>
    </head>

    <body>

        <?php if ($maxSearchKey != -1): ?>
            <p>Most searched property: <?php echo $maxSearchKey['Address']; ?> </p>
        <?php endif; ?>

        <form method="post">
            <p> desc: <input type="text" name="query"> </p>
            <button type="submit"> search </button>
        </form>

        <?php if ($result): ?>
            <table>
                <tr> <th> Address </th> <th> Description </th> </tr> 
                <?php foreach($result as $r): ?>
                    <tr>
                        <td> <?php echo $r['Address']; ?> </td> 
                        <td> <?php echo $r['Description']; ?> </td>
                    </tr> 
                <?php endforeach; ?>
            </table>
        <?php endif; ?>
    </body>
</html>

