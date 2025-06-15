<?php
include 'db.php';

if ($_POST) {
    $address = $_POST['address'];
    $description = $_POST['description'];
    
    $stmt = $db->prepare("INSERT INTO Property (address, description) VALUES (?, ?)");
    $stmt->execute([$address, $description]);
    $property_id = $db->lastInsertId();
    
    $stmt = $db->prepare("INSERT INTO UserToProperties (idUser, idProperty) VALUES (?, ?)");
    $stmt->execute([$_SESSION['user']['id'], $property_id]);
    
    echo "Property added!";
}
?>

<html>
<head><title>Add Property</title></head>
<body>
    <h1>Add Property</h1>
    
    <form method="POST">
        <p>Address: <input type="text" name="address" required></p>
        <p>Description: <textarea name="description" required></textarea></p>
        <input type="submit" value="Add Property">
    </form>
    
    <p><a href="dashboard.php">Back to Dashboard</a></p>
</body>
</html>