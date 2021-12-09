<?php
$db = mysqli_connect("localhost","pma", "", "rent a car");
if (mysqli_connect_errno()){
    echo 'Failled to connect to MySql: '.mysql_connect_error();
};
?>
