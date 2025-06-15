<?php
include "db.php";

if (!isset($_SESSION['searchCounts'])) {
    $_SESSION['searchCounts'] = [];
}

$results = [];
$most_popular = null;

if ($_GET) {
    $searchKey = $_GET['searchKey'];

    $stmt = $db->prepare("
        SELECT p.*, COUNT(up.idUser) as owners 
        FROM Property p
        LEFT JOIN UserToProperties up ON p.id = up.idProperty
        WHERE p.description LIKE ?
        GROUP BY p.id
    ");

    $stmt->execute(["%$search%"]);
    $results = $stmt->fetchAll();
    
    foreach ($properties as $property) {
        $prop_id = $property['id'];
        if (!isset($_SESSION['search_counts'][$prop_id])) {
            $_SESSION['search_counts'][$prop_id] = 0;
        }
        $_SESSION['search_counts'][$prop_id]++;
    }

    if (!empty($_SESSION['search_counts'])) {
        $max_count = max($_SESSION['search_counts']);
        $most_popular_id = array_search($max_count, $_SESSION['search_counts']);
        
        $stmt = $db->prepare("SELECT * FROM Property WHERE id = ?");
        $stmt->execute([$most_popular_id]);
        $most_popular = $stmt->fetch();
        $most_popular['search_count'] = $max_count;
    }
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
        
        <?php if ($most_popular): ?>
            <p><strong>Most popular in your searches this session:</strong> 
               <?php echo $most_popular['address']; ?> 
               (appeared <?php echo $most_popular['search_count']; ?> times)
            </p>
        <?php endif; ?>
    <?php endif; ?>
    
    <p><a href="dashboard.php">Back to Dashboard</a></p>
</body>
</html>