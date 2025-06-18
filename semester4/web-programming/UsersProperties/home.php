<?php
include "db.php";


?>

<?php if (isset($_SESSION['user']['Name'])): ?>
    <p> hei, <?php echo $_SESSION['user']['Name']; ?> . </p>
    <a href="search.php"> search </a>
    <a href="delete.php"> delete </a>
    <a href="owners.php"> delete </a>
<?php endif; ?>
