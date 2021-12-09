<?php
if(!isset($_SESSION)){
  session_start();
}
if (isset($_SESSION['loggedin']) && $_SESSION['loggedin'] == true) {
    echo "You are already logged in " . $_SESSION['username'] . "!";
} else {
  
	include("login-user.php");

}
?>
