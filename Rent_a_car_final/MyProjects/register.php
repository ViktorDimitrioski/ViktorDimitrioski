<!-- REGISTER -->
<?
session_start();
?>
<!DOCTYPE html>
<html>
<head>
	<title>Register</title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" type="text/css" href="css\style-top.css">
	<link rel="stylesheet" a href="css\style-register.css">
	<link rel="stylesheet" a href="css\font-awesome.min.css">
</head>
<body>
	<?php
	include('html\topnav.html');
	?>
<style>
	.container{
		width: 500px;
		height: 1200px;
		text-align: center;
		margin: 0 auto;
		background-color: rgba(44, 62, 80,0.7);
		margin-top: 100px;
	}
	input[type="text"],input[type="password"],input[type="email"]{
		margin-top: 30px;
		height: 45px;
		width: 300px;
		font-size: 18px;
		margin-bottom: 20px;
		background-color: #fff;
		padding-left: 40px;
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
			<div class="form-input">
				<input type="password" name="rpassword" placeholder="repeat password" required>
			</div>
			<div class="form-input">
				<input type="email" name="email" placeholder="E-mail" required>
			</div>
			<div class="form-input">
				<input type="text" name="firstname" placeholder="First name" required>
			</div>
			<div class="form-input">
				<input type="text" name="lastname" placeholder="Last name" required>
			</div>
			<div class="form-input">
				<input type="text" name="country" placeholder="Country(optional)">
			</div>
			<div class="form-input">
				<input type="text" name="city" placeholder="City(optional)" >
			</div>
			<div class="form-input">
				<input type="text" name="address" placeholder="Address(optional)" >
			</div>
			<input type="submit" name="submit" type="submit" value="REGISTER" class="btn-login" required>
		</form>
		<br><hr>Already have an account?
		<a href="login.php"><h3>Log in</h3></a>

		<?php

		require_once "dbconfig.php";
		mysqli_set_charset($db,'utf8');

		if(isset($_POST['username']) && isset($_POST['password']) && isset($_POST['email']) && isset($_POST['firstname']) && isset($_POST['lastname'])){
			if(($_POST['password']!=$_POST['rpassword'])){
				echo '<span style="color: red;"/>Passwords do not match</span>';
				exit();
			}
				$uname=$_POST['username'];
				$password=$_POST['password'];
				$email=$_POST['email'];
				$fname=$_POST['firstname'];
				$lname=$_POST['lastname'];
				$country=$_POST['country'];
				$city=$_POST['city'];
				$address=$_POST['address'];

				$_SESSION['firstname']=$fname;
				$_SESSION['lastname']=$lname;

				$salt1 = "gmh*!";
				$salt2 = "op@&";

				$token = hash('ripemd128',"$salt1$password$salt2",FALSE);


				$sql = "INSERT INTO user (username, password, email, firstname,lastname,city,country,address)
				VALUES ('$uname', '$token', '$email', '$fname','$lname','$city','$country','$address')";

				$result=mysqli_query($db,$sql);

				if($result){
						echo '<meta http-equiv="refresh" content="2; url=login.php">';
						echo '<span style="color: green;"/>Registration Complete</span>';
						exit();
				}
				else{
						echo '<span style="color: red;"/>Username or email already exists</span>';
						exit();
				}

		}
		?>

	</div><br><br>

</body>
</html>
