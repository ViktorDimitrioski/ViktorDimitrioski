<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="css\style-top.css">
    <link rel="stylesheet" a href="css\style-contact.css">
    <link rel="stylesheet" a href="css\font-awesome.min.css">

    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <title>Contact us</title>
  </head>
  <body>
<style>
.container{
	width: 500px;
	height: 700px;
	text-align: center;
	margin: 0 auto;
	background-color: rgba(44, 62, 80,0.7);
	margin-top: 160px;
}
</style>
    <?php
    include('html/topnav.html');
    ?>

    <div class="container">
      <form method="POST" action="<?php echo $_SERVER['PHP_SELF']; ?>" charset="utf-8">
        <img src="img/contact.jpg"/>
        <div class="form-input">
          <input type="text" name="fname" placeholder="First name"/>
        </div>
        <div class="form-input">
          <input type="text" name="lname" placeholder="Last name" required>
        </div>
        <div class="form-input">
          <input type="text" name="ph_number" placeholder="Phone number" required>
        </div>
        <div class="form-input">
          <input type="email" name="email" placeholder="E-mail" required>
        </div>
          <textarea name="message" rows="5" cols="46" placeholder="Message..." optional></textarea>
        <div class="form-input">
          <br>
        <input type="submit" name="submit" type="submit" value="SEND" class="btn-login" required>
        </div>
      </form>
      <br><hr>
      <?php

      require_once "dbconfig.php";
      mysqli_set_charset($db,'utf8');
      date_default_timezone_set('Europe/Skopje');

      if(isset($_POST['submit'])){

          $uname=$_POST['fname'];
          $lname=$_POST['lname'];
          $ph_number=$_POST['ph_number'];
          $email=$_POST['email'];
          $msg=$_POST['message'];
          $date=date("Y/m/d");


          $sql = "INSERT INTO contactus (firstname, lastname, ph_number, email,message,date_submit)
  				VALUES ('$uname', '$lname', '$ph_number', '$email','$msg','$date')";


          $result=mysqli_query($db,$sql);

          if($result){
            echo '<span style="color:green;text-align:center;font-size:20px;">Your Messege was sent!</span>';
          }

      }
      ?>

    </div><br><br>

  </body>
</html>
