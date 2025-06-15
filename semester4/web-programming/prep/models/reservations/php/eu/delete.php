<?php
include "db.php";

$stmt = $db->prepare("SELECT id, address, description FROM Property");
$stmt->execute();
$properties = $stmt->fetchAll();

if ($_POST) {
    if(isset($_POST['property_id'])) {
        $id = $_POST['property_id'];
        
        $stmt = $db->prepare("DELETE FROM Property WHERE id = ?");
        $stmt->execute([$id]);
        
        header("Location: delete.php");
        exit();
    }
}

?>

<html> 
    
    <head>
        <p> delete </p>
    </head>

    <body>
        <table>
            <tr> <th> addr </th> <th> desc </th> <th>action</th> </tr> 
            <?php foreach ($properties as $prop): ?>
                <tr> 
                    <td> <?php echo $prop['description']; ?> </td>
                    <td> <?php echo $prop['address']; ?> </td>
                    <td>
                        <form method="post">
                            <input type="hidden" name="property_id" value="<?php echo $prop['id']; ?>">
                            <button type="submit"> delete </button>
                        </form>
                    </td>
                </tr> 
            <?php endforeach ?>
        </table>
    </body>

</html>