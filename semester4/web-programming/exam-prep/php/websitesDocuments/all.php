<?php
include "db.php";

$stmt = $db->prepare ("SELECT URL, COUNT(d.Id) AS Documents
    FROM Websites w
    LEFT JOIN Documents d
    ON w.Id = d.WebsiteId
    GROUP BY URL");
$stmt->execute();

$result = $stmt->fetchAll();
?>

<html>
    <title>
        <p> get all websites </p> 
    </title>

    <body>
        <table>
            <tr><th></th><th>URL</th><th>Documents</th></tr>
            <tr>
                <?php foreach ($result as $r): ?>
                <td><?php echo $r['URL']; ?></td>
                <td><?php echo $r['Documents']; ?></td>
            </tr>
            <?php endforeach; ?>
        </table?>

        <a href="home.php"> back </a>
    </body>
</html> 