<?php
include 'db.php';

$stmt = $db->prepare("
    SELECT p.*, COUNT(up.id) as owner_count
    FROM Property p
    LEFT JOIN UserToProperties up
    ON p.id = up.idProperty
    GROUP BY p.id
    HAVING COUNT(up.id) > 1
");
$stmt->execute();
$properties = $stmt->fetchAll();

?>

<html>
    <head>
        <p> more than 1 owner </p>
    </head>

    <body>
        <table>
        
            <tr> <th> addr </th> <th> desc </th> </tr>

            <?php foreach ($properties as $prop): ?>
                
                <tr> 

                    <td> <?php echo $prop['address']; ?> </td>
                    <td> <?php echo $prop['description']; ?> </td>

                </tr>

            <?php endforeach; ?> 

        </table>
    </body>

</html> 