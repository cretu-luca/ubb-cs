<?php 
include "db.php";

$stmt = $db->prepare("
    SELECT p.Id, p.Address, p.Description, COUNT(p.Id) as ownerNumber
    FROM Property p
    INNER JOIN UserToProperties UTP
    ON p.Id = UTP.PropertyId
    GROUP BY p.Id
    HAVING ownerNumber > 1
");

$stmt->execute();
$result = $stmt->fetchAll();

?>

<html>
    <head>
        <p> properties with more than one owner </p>
    <head>

    <body>

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