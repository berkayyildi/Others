<a href="http://localhost/?action=view&client_id=berkay">NORMAL USAGE</a> - - 
<!--<a href="http://localhost/?client_id=berkay%26action=hacked&action=delete">HPP VERSION</a> -->

<br><br>

<?php
if ($_GET['client_id'] AND $_GET['action']){
    echo "Client ID:" . $_GET["client_id"];
    echo "<br><br>";
    echo "Action:" . $_GET['action'];

    echo "
        <br><br>
        <a href=\"?action=view&client_id={$_GET["client_id"]}\">View</a> - - 
        <a href=\"?action=delete&client_id={$_GET["client_id"]}\">Delete</a>
    ";
}
?>
