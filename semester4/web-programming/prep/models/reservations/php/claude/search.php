<?php
include 'db.php';

$results = [];
if ($_POST) {
    $search = $_POST['search'];
    $stmt = $db->prepare("
        SELECT p.*, COUNT(up.idUser) as owners 
        FROM Property p 
        LEFT JOIN UserToProperties up ON p.id = up.idProperty 
        WHERE p.description LIKE ? 
        GROUP BY p.id 
        ORDER BY owners DESC
    ");
    $stmt->execute(["%$search%"]);
    $results = $stmt->fetchAll();
}
?>

<html>
<head><title>Search</title></head>
<body>
    <h1>Search Properties</h1>
    
    <form method="POST">
        <input type="text" name="search" placeholder="Search description">
        <input type="submit" value="Search">
    </form>
    
    <?php if ($results): ?>
        <h2>Results</h2>
        <table border="1">
            <tr><th>Address</th><th>Description</th><th>Owners</th></tr>
            <?php foreach ($results as $r): ?>
            <tr>
                <td><?php echo $r['address']; ?></td>
                <td><?php echo $r['description']; ?></td>
                <td><?php echo $r['owners']; ?></td>
            </tr>
            <?php endforeach; ?>
        </table>
        <p>Most popular: <?php echo $results[0]['address']; ?></p>
    <?php endif; ?>
    
    <p><a href="dashboard.php">Back to Dashboard</a></p>
</body>
</html>