<?php
include 'db.php';

$property_id = $_GET['id'];

// Check how many owners
$stmt = $db->prepare("SELECT COUNT(*) FROM UserToProperties WHERE idProperty = ?");
$stmt->execute([$property_id]);
$owner_count = $stmt->fetchColumn();

if ($owner_count > 1) {
    // Just remove from this user
    $stmt = $db->prepare("DELETE FROM UserToProperties WHERE idUser = ? AND idProperty = ?");
    $stmt->execute([$_SESSION['user']['id'], $property_id]);
} else {
    // Delete property completely
    $stmt = $db->prepare("DELETE FROM UserToProperties WHERE idProperty = ?");
    $stmt->execute([$property_id]);
    $stmt = $db->prepare("DELETE FROM Property WHERE id = ?");
    $stmt->execute([$property_id]);
}

header('Location: dashboard.php');
?>