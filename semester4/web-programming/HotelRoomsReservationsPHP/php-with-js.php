<?php
// simple_server.php

// Example 1: Handle single name
if (isset($_POST['userName'])) {
    $nameFromClient = $_POST['userName'];
    echo "Hello " . $nameFromClient . "! Message received at " . date('H:i:s');
}

// Example 2: Handle calculation
if (isset($_POST['action']) && $_POST['action'] == 'calculate') {
    $firstNumberFromClient = $_POST['firstNumber'];
    $secondNumberFromClient = $_POST['secondNumber'];
    $calculationResult = $firstNumberFromClient + $secondNumberFromClient;
    echo "Sum is: " . $calculationResult;
}

// Example 3: Handle form data
if (isset($_POST['action']) && $_POST['action'] == 'processForm') {
    $userAgeFromClient = $_POST['userAge'];
    $userCityFromClient = $_POST['userCity'];
    echo "You are " . $userAgeFromClient . " years old from " . $userCityFromClient;
}
?>