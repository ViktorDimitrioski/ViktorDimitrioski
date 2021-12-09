<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="css\style-top.css">

    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <title>My account</title>
  </head>
  <body>
<style>.my-account{
	width: 1000px;
	height: 950px;
	text-align: center;
	margin: 0 auto;
	background-color: rgba(44, 62, 80,0.7);
	margin-top: 60px;
}

.my-account img{
	width: 150px;
	height: 150px;
	margin-top: -60px;
}</style>

    <?php
    include('html\topnav.html');
    if(!isset($_SESSION)){
    session_start();
    }
    require_once "dbconfig.php";

    $sql1="select * from user where username='".$_SESSION['username']."' limit 1";
    $result1=mysqli_query($db,$sql1);

      while ( $row1 = mysqli_fetch_row($result1) ){
        $_SESSION['country']=(htmlentities($row1[7]));
        $_SESSION['city']=(htmlentities($row1[6]));
        $_SESSION['address']=(htmlentities($row1[8]));
      }
      

    ?>
    <div class="container">
      <div class="my-account">
        <img src="img/logo.png">
        <?php   echo "<h2>" . $_SESSION['firstname'] ." ".$_SESSION['lastname'] . "</h2>"; ?><hr>

        <p align="left">&nbsp&nbspUsername:<?php echo "<b>&nbsp" .$_SESSION['username']."</b>";?></p>
        <p align="left" >&nbsp&nbspE-mail :<?php echo "<b>&nbsp" .$_SESSION['email']."</b>";?></p>
        <p align="left">&nbsp&nbspCountry :<?php echo "<b>&nbsp".$_SESSION['country']."</b>";?></p>
        <p align="left" >&nbsp&nbspCity :<?php echo "<b>&nbsp".$_SESSION['city']."</b>"?></p>
        <p align="left" >&nbsp&nbspAddress :<?php echo "<b>&nbsp".$_SESSION['address']."</b>"?></p>
        <h4><p align="left">&nbsp<a href="settings.php"><span style="color: purple;"/>Change your password</span></a></p></h4>

        <hr>
        <p align="center"><h3>Reservation</h3></p><br>
        <table style="width:100%">
          <tr>
            <?php

            $sql="select id_reserv,bookings.car_id,cars.car_id,date_from,date_to,pick_up,return_loca,brand,model
                  from bookings
                  JOIN cars ON user_name='".$_SESSION['username']."' and bookings.car_id=cars.car_id";
            $result=mysqli_query($db,$sql);
            echo '<table style="width:100%">
            <th><h4>Reservation </th>
            <th><h4>Brand</th>
            <th><h4>Model</th>
            <th><h4>Date From</th>
            <th><h4>Date to</th>
            <th><h4>Pick up location</th>
            <th><h4>Return location</th>
            </tr>';
            while ($row = mysqli_fetch_row($result)){
              $_SESSION['id_reserv']=(htmlentities($row[0]));
              $_SESSION['car_id']=(htmlentities($row[1]));
              $_SESSION['date_from']=(htmlentities($row[3]));
              $_SESSION['date_to']=(htmlentities($row[4]));
              $_SESSION['pick_up']=(htmlentities($row[5]));
              $_SESSION['return_loca']=(htmlentities($row[6]));
              $_SESSION['brand']=(htmlentities($row[7]));
              $_SESSION['model']=(htmlentities($row[8]));

//.$_SESSION['id_reserv'].
//.$_SESSION['brand'].
echo '<th><h5>'.$_SESSION['id_reserv'].'</th>
<th><h5>'.$_SESSION['brand'].'</th>
<th><h5>'.$_SESSION['model'].'</th>
<th><h5>'.$_SESSION['date_from'].'</th>
<th><h5>'.$_SESSION['date_to'].'</th>
<th><h5>'.$_SESSION['pick_up'].'</th>
<th><h5>'.$_SESSION['return_loca'].'</th>
</tr>';
    }
    ?>
    </table><br>';
    <p align="left" style="margin-left:10px;"><b>Cancel reservation:</b><br>
    <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="POST">
      <p align="left" style="margin-left:10px;"><input type="number" name="cancel" placeholder="Reservation number.." required/>
        &nbsp<input type="submit" name="submit" value="submit" style="background-color: #4CAF50;  font-size: 16px;  border: double;"/>
      </form>

    <?php

    if(isset($_POST['submit'])){

    //if(!isset($_SESSION)){
    //session_start();
    //}
    //$id=$_SESSION['id'];
    $reserve=$_POST['cancel'];
    $sql="DELETE FROM bookings WHERE bookings.id_reserv ='".$reserve."'";
    //$sql="delete from bookings where id_reserv='".$reserve."' and user_id='".$id."'";
    $result=mysqli_query($db,$sql);
    echo '<meta http-equiv="refresh" content="0; url=myaccount.php">';
    }
    ?>

    <hr>
        <p align="center"><h3>Canceled Reservations</h3></p><br>
        <table style="width:100%">

        <tr>
            <?php

            if(!isset($_SESSION)){
          session_start();
          }

            $sql="select reserv_id,username,datefrom,dateto,from_loc,to_loc,action
                  from canceled_resrv where username='".$_SESSION['username']."'";//where user_id='".$_SESSION['id']."'";
            $result=mysqli_query($db,$sql);
            echo '<table style="width:100%">
            <th><h4>Reservation </th>
            <th><h4>Username</th>
            <th><h4>Date From</th>
            <th><h4>Date To</th>
            <th><h4>Pick up location</th>
            <th><h4>Return location</th>
            <th><h4>Action</th>
            </tr>';
            while ($row = mysqli_fetch_row($result)){
              $_SESSION['id_reserv']=(htmlentities($row[0]));
              $_SESSION['username']=(htmlentities($row[1]));
              $_SESSION['date_from']=(htmlentities($row[2]));
              $_SESSION['date_to']=(htmlentities($row[3]));
              $_SESSION['pick_up']=(htmlentities($row[4]));
              $_SESSION['return_loca']=(htmlentities($row[5]));
              $_SESSION['action']=(htmlentities($row[6]));

//.$_SESSION['id_reserv'].
//.$_SESSION['brand'].
echo '<th><h5>'.$_SESSION['id_reserv'].'</th>
<th><h5>'.$_SESSION['username'].'</th>
<th><h5>'.$_SESSION['date_from'].'</th>
<th><h5>'.$_SESSION['date_to'].'</th>
<th><h5>'.$_SESSION['pick_up'].'</th>
<th><h5>'.$_SESSION['return_loca'].'</th>
<th><h5 style="color:#DC143C";><b>'.$_SESSION['action'].'</b></h5></th>

</tr>';
    }
    ?>
    </table><br>';

  </body>
</html>
