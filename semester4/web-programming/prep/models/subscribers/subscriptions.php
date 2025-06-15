<?php 
include 'db.php';

$user_id = $_SESSION['loggedInUser']['Id'];

$stmt = $db->prepare("SELECT * FROM Channels");
$stmt->execute();

$channels = $stmt->fetchAll();

$subscriptions = [];

foreach ($channels as $chan) {
    $subscribersList = preg_split("/\,/", $chan['Subscribers']);

    foreach ($subscribersList as $subscr) {
        $subscriberId = preg_split("/\-/", $subscr)[0];
        $subscriberId = trim($subscriberId);

        if (strcmp($user_id, $subscriberId) === 0) {
            array_push($subscriptions, $chan);
            break;
        }
    }
}

if ($_POST) {
    $channel_name = $_POST['channel_name'];
    $new_subscribers_list = "";
    $channel_id = null;

    foreach ($channels as $chan) {
        if (strcmp($chan['Name'], $channel_name) == 0) {
            $channel_id = $chan['Id'];
            $subscribersList = preg_split("/\,/", $chan['Subscribers']);
            $subscribed = false;

            foreach ($subscribersList as $subscr) {
                if (!empty($subscr)) {
                    $parts = preg_split("/\-/", $subscr);
                    $subscriberId = trim($parts[0]);
                    $date = isset($parts[1]) ? $parts[1] : date('d.m.Y', strtotime('+1 year'));

                    if (strcmp($user_id, $subscriberId) === 0) {
                        $subscribed = true;
                        $new_subscribers_list .= $subscriberId . "-" . "15.06.2025" . ",";
                    } else {
                        $new_subscribers_list .= $subscriberId . "-" . $date . ",";
                    }
                }
            }

            if (!$subscribed) {
                $new_subscribers_list .= $user_id . "-" . "15.06.2025" . ",";
            }

            if ($channel_id !== null) {
                $update_stmt = $db->prepare("UPDATE Channels SET Subscribers = :subscribers WHERE Id = :id");
                $update_stmt->bindParam(':subscribers', $new_subscribers_list);
                $update_stmt->bindParam(':id', $channel_id);
                $update_stmt->execute();
                
                header("Location: subscriptions.php");
                exit();
            }
        }
    }
}


?>

<html>
    <head>
        <title> subscriptions </title>
    </head>

    <body>
        <?php if (isset($_SESSION['loggedInUser'])): ?>
            <table border='1'>
                    <tr> <th> name </th> <th> description </th> </tr> 
                    <?php foreach ($subscriptions as $subscr): ?>
                        <tr> 
                            <td> <?php echo $subscr['Name']; ?> </td>
                            <td> <?php echo $subscr['Description']; ?> </td>
                        </tr> 
                    <?php endforeach ?>
                </table>
        <?php endif; ?>

        <form method="post">
            <p> channel: <input type="text" name="channel_name"> </p>
            <button type="submit"> subscribe </button>
        </form>

        <a href='index.php'> home </a>
    </body>
</html>