<?php
include 'db.php';

if (!$_SESSION['logged_in']) {
    header('Location: index.php');
    exit;
}

$stmt = $db->prepare("
    SELECT p.* FROM Property p 
    JOIN UserToProperties up ON p.id = up.idProperty 
    WHERE up.idUser = ?
");
$stmt->execute([$_SESSION['user']['id']]);
$properties = $stmt->fetchAll();
?>

<html>
<head><title>Dashboard</title></head>
<body>
    <h1>Welcome <?php echo $_SESSION['user']['name']; ?></h1>
    
    <p>
        <a href="add.php">Add Property</a> | 
        <a href="search.php">Search</a> | 
        <a href="shared.php">Shared Properties</a> |
        <a href="logout.php">Logout</a>
    </p>
    
    <h2>Your Properties</h2>
    <table border="1">
        <tr><th>Address</th><th>Description</th><th>Delete</th></tr>
        <?php foreach ($properties as $p): ?>
        <tr>
            <td><?php echo $p['address']; ?></td>
            <td><?php echo $p['description']; ?></td>
            <td><a href="delete.php?id=<?php echo $p['id']; ?>">Delete</a></td>
        </tr>
        <?php endforeach; ?>
    </table>
</body>
</html>