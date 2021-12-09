
<!DOCTYPE html>
<html>
<head>
	<title> Login</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" type="text/css" href="css\style-top.css">
	<link rel="stylesheet" a href="css\style.css">
	<link rel="stylesheet" a href="css\font-awesome.min.css">
</head>
<body>
	
	<?php
	include('html\topnav.html');
	?>

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
		<br><hr>
		<a href="register.php"><span style="color: blue;"/><h3>Register</h3></span></a>

		<?php

		require_once "dbconfig.php";
		mysqli_set_charset($db,'utf8');

		if(isset($_POST['username']) && isset($_POST['password'])){

				$uname=$_POST['username'];
				$password=$_POST['password'];
				//$fname=$_POST['firstname'];
				//$lname=$_POST['lastname'];

				$salt1 = "gmh*!";
  			$salt2 = "op@&";
  			$token = hash('ripemd128',"$salt1$password$salt2");

				$sql="select * from user where username='".$uname."'AND password='".$token."'  limit 1";

				$result=mysqli_query($db,$sql);
				while ( $row = mysqli_fetch_row($result) ) {
				$id=(htmlentities($row[0]));
				$email=(htmlentities($row[3]));
				$fname=(htmlentities($row[4]));
				$lname=(htmlentities($row[5]));
				$city=(htmlentities($row[6]));
				$country=(htmlentities($row[7]));
				$address=(htmlentities($row[8]));
				}

				if(mysqli_num_rows($result)==1){
          if(!isset($_SESSION)){
          session_start();
          }
          			$_SESSION['loggedin'] = true;
					$_SESSION['id'] = $id;
          			$_SESSION['username'] = $uname;
					$_SESSION['firstname']=$fname;
					$_SESSION['lastname']=$lname;
					$_SESSION['email']=$email;
					$_SESSION['country']=$country;
					$_SESSION['city']=$city;
					$_SESSION['address']=$address;
					$_SESSION['username'] = $uname;
					$_SESSION['password'] = $password;


						echo '<span style="color: green;"/>You Have Successfully Logged in</span>';
						echo '<meta http-equiv="refresh" content="1; url=index.php">';
						exit();
				}
				else{
						echo '<span style="color: red;"/>You Have Entered Incorrect Password or Username</span>';
						exit();
				}

		}
		?>

	</div><br><br>

</body>
</html>
