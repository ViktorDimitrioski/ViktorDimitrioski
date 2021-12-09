<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="css\style-top.css">
    <link rel="stylesheet type="text/css href="css\style-register.css">


    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <title>Settings</title>
  </head>
  <body>

    <?php
    include('html\topnav.html');
    ?>
    <style>
    	.container{
    		width: 500px;
    		height: 500px;
    		text-align: center;
    		margin: 0 auto;
    		background-color: rgba(44, 62, 80,0.7);
    		margin-top: 100px;
    	}
    	</style>

    	<div class="container">
    	<img src="img/logo.png"/>
    		<form method="POST" action="<?php echo $_SERVER['PHP_SELF']; ?>">

    			<div class="form-input">
    				<input type="password" name="old_password" placeholder="old password" >
    			</div>
    			<div class="form-input">
    				<input type="password" name="new_password" placeholder="new password" >
    			</div>
          <div class="form-input">
    				<input type="password" name="new_password1" placeholder="confirm password" >
    			</div>

    			<input type="submit" name="submit" type="submit" value="SUBMIT" class="btn-login" required>
    		</form>

    		<?php

        if(!isset($_SESSION)){
        session_start();
        }

    		require_once "dbconfig.php";

    		if(isset($_POST['old_password']) && isset($_POST['new_password']) && isset($_POST['new_password1']) && isset($_POST['submit'])){
          if(($_POST['new_password']!=$_POST['new_password1'])){
            echo "passwords do not match";
            exit();
          }
    				$password=$_POST['new_password'];

            $salt1 = "gmh*!";
            $salt2 = "op@&";

            $token = hash('ripemd128',"$salt1$password$salt2",FALSE);

    				$sql = "UPDATE user SET  password='$token'
              where username='".$_SESSION['username'] ."'";

    				$result=mysqli_query($db,$sql);

    				if($result){

    						echo '<span style="color: green;"/>Completed</span>';
    						exit();
    				}
    				else{
    						echo '<span style="color: red;"/>Fail</span>';
    						exit();
    				}

    		}
    		?>

    	</div><br><br>

  </body>
</html>
