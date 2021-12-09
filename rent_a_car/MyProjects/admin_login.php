<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <link rel="stylesheet" type="text/css" href="css\admin_login.css">

    <title>Admin</title>
  </head>
  <body>
    <?php
    include('html\admin-header.html');
    ?>
    <style>
    .container{
    	width: 500px;
    	height: 450px;
    	text-align: center;
    	margin: 0 auto;
    	background-color: #001f3f;
    	margin-top: 90px;
    }
    .form-input::before{
    	content: "\f007";
    	font-family: "FontAwesome";
    	padding-left: 07px;
    	padding-top: 40px;
    	position: absolute;
    	font-size: 25px;
    	color: #2980b9;
    }
    </style>
    <div class="container">
  	<img src="img/logo.png"/>
  		<form method="POST" action="<?php echo $_SERVER['PHP_SELF']; ?>">
  			<div class="form-input">
  				<input type="text" name="username" placeholder="Enter the User Name"/>
  			</div>
  			<div class="form-input">
  				<input type="password" name="password" placeholder="password" required>
  			</div>
  			<input type="submit" name="submit" type="submit" value="LOGIN" class="btn-login" required>
  		</form>

      <?php

  		require_once "dbconfig.php";
      mysqli_set_charset($db,'utf8');

  		if(isset($_POST['username']) && isset($_POST['password']) && isset($_POST['submit'])){

  				$admin_uname=$_POST['username'];
  				$admin_pasw=$_POST['password'];

          $salt1 = "gmh*!";
          $salt2 = "op@&";
          $token = hash('ripemd128',"$salt1$admin_pasw$salt2");

  				$sql="select username, password, id, user_id
                from user, admin
                where user.username='".$admin_uname."'AND user.password='".$token."' and user.id=admin.user_id
                group by user_id limit 1";

  				$result=mysqli_query($db,$sql);

          if(mysqli_num_rows($result)==1){
  						echo '<span style="color: green;"/>You Have Successfully Logged in</span>';
  					 	echo '<meta http-equiv="refresh" content="1; url=admin.php">';
  						exit();
            }
              else{
  						echo '<span style="color: red;"/>You Have Entered Incorrect Password or Username</span>';
  						exit();
            }


  		}
  		?>

  </body>
</html>
