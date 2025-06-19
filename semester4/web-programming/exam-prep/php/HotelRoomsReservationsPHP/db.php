<?php
$db = new PDO("mysql:host=localhost;dbname=RoomsReservations", "root", "");
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}
?>