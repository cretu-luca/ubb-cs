<?php
include 'db.php';

$stmt = $db->prepare("
    SELECT p.*, COUNT(up.idUser) as owners 
    FROM Property p 
    JOIN UserToProperties up ON p.id = up.idProperty 
    GROUP BY p.id 
    HAVING COUNT(up.idUser) > 1
");
$stmt->execute();
$shared = $stmt->fetchAll();
?>

<html>
<head><title>Shared Properties</title></head>
<body>
    <h1>Properties with Multiple Owners</h1>
    
    <table border="1">
        <tr><th>Address</th><th>Description</th><th>Number of Owners</th></tr>
        <?php foreach ($shared as $s): ?>
        <tr>
            <td><?php echo $s['address']; ?></td>
            <td><?php echo $s['description']; ?></td>
            <td><?php echo $s['owners']; ?></td>
        </tr>
        <?php endforeach; ?>
    </table>
    
    <p><a href="dashboard.php">Back to Dashboard</a></p>
</body>
</html>