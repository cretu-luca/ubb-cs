<?php 
include "db.php";

$keywords = "";
$keywordsArray = [];

$documentsResult = [];
$documents = [];

if ($_POST) {
    $documentsResult = [];
    $documents = [];

    $keywordsReq = $_REQUEST['keywords'];
    $keywordsArray = explode(', ', $keywordsReq);

    $stmt = $db->prepare("SELECT * FROM Documents");
    $stmt->execute();
    $documents = $stmt->fetchAll(); 

    foreach ($documents as $doc) {

        $count = 0;
        
        foreach ($keywordsArray as $kw) {
            if (strcmp($doc["Keyword1"], $kw) == 0) {
                $count += 1;
            }

            if (strcmp($doc["Keyword2"], $kw) == 0) {
                $count += 1;
            }

            if (strcmp($doc["Keyword3"], $kw) == 0) {
                $count += 1;
            }

            if (strcmp($doc["Keyword4"], $kw) == 0) {
                $count += 1;
            }

            if (strcmp($doc["KeyWord5"], $kw) == 0) {
                $count += 1;
            }
        }

        echo $count;
        echo "<br>";

        if ($count == 3) {
            array_push($documentsResult, $doc);
        }
    }
}
?>

<html> 
    <head> 
        <title> search: </title>
    </head>

    <body>
        <form method="post"> 
            <p> keywords (comma-separated): <input type="text" name="keywords" /> </p>
            <button type="submit"> submit </button> 
        </form>

        <?php if ($documents != null): ?>

            <table>
                <tr><th>Name</th><th>k1</th><th>k2</th><th>k3</th><th>k4</th><th>k5</th></tr>
                    <?php foreach ($documentsResult as $r): ?>
                        <tr>
                            <td><?php echo $r['Name']; ?></td>
                            <td><?php echo $r['Keyword1'] ?></td>
                            <td><?php echo $r['Keyword2'] ?></td>
                            <td><?php echo $r['Keyword3'] ?></td>
                            <td><?php echo $r['Keyword4'] ?></td>
                            <td><?php echo $r['KeyWord5'] ?></td>
                        </tr>
                    <?php endforeach; ?>
            </table?>

        <?php endif ?>
        
        <a href="home.php"> back </a> 
    </body>
</html>