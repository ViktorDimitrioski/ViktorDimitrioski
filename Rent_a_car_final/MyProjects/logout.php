<?php
session_start();
session_destroy();
header('Location: login.php');
echo '<div class="container">You have loged out</div>';
exit;
?>
