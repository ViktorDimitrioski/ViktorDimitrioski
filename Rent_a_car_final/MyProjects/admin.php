<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title>Admin</title>
  </head>
  <body>
<style>
    .container{
    	width: 1000px;
    	height: 1000px;
    	margin: 0 auto;
    	background-color: rgba(44, 62, 80,0.7);
    	margin-top: 60px;


}
    }
</style>
<style>
table, th, td {
border: 1px;
border-color: white;
text-align: left;}
</style>

    <?php
    include("html/admin-header.html");
    ?>
    <div class="container">
      <form class="" action="<?php echo $_SERVER['PHP_SELF']; ?>" method="POST">
      <h2><p align="center">Car management</p></h2><br>
      Car Brand: <input type="text" name="brand" >
      Car Model: <input type="text" name="model" ><br><br>
      No. persons: <input type="text" name="persons" >
      Transmission: <input type="text" name="transmission" ><br><br>
      Price per day: <input type="text" name="price" >
      Luggage: <input type="text" name="luggage" ><br><br>
      Conditioning:<input type="text" name="conditioning"><br><br>
      Car Image:<br><input type="file" name="image"><br>
      &nbsp&nbsp<input type="submit" name="submit" value="Insert into database" style="background-color: #4CAF50;  font-size: 16px;  border: double;">
      <br><hr><br>
      </form>
    <?php

    require_once "dbconfig.php";

    $sql="select * from cars";

    $result=mysqli_query($db,$sql);

    echo '<form class="" action="'.$_SERVER['PHP_SELF'].'" method="POST">
    <table style="width:100%">
      <tr>
  <th>Car ID</th>
  <th>Brand</th>
  <th>Model</th>
  <th>Persons</th>
  <th>Transmission</th>
  <th>Price</th>
  <th>Luggage</th>
  <th>Conditioning</th>
  </tr>';

    while ( $row = mysqli_fetch_row($result)){
    $car_id=(htmlentities($row[0]));
    $brand=(htmlentities($row[1]));
    $model=(htmlentities($row[2]));
    $persons=(htmlentities($row[3]));
    $transmission=(htmlentities($row[4]));
    $price=(htmlentities($row[5]));
    $luggage=(htmlentities($row[6]));
    $conditioning=(htmlentities($row[7]));


  echo '<tr>
  <td>'.$car_id.'</td>
  <td>'.$brand.'</td>
  <td>'.$model.'</td>
  <td>'.$persons.'</td>
  <td>'.$transmission.'</td>
  <td>'.$price.'</td>
  <td>'.$luggage.'</td>
  <td>'.$conditioning.'</td>
  </tr>';
    }

    ?>
  </table><br>
      Remove car:<input type="number" name="car_id" value="remove" placeholder="Car ID" />
      <input type="submit" name="submit1" value="remove" style="background-color: #4CAF50;  font-size: 16px;  border: double;"/>
    </form>
    <hr>

      <h2><p align="center">Rented cars</p></h2><br>
      
      <?php 
      require_once "dbconfig.php";

    $sql="select * from bookings";

    $result=mysqli_query($db,$sql);
    echo '<form class="" action="'.$_SERVER['PHP_SELF'].'" method="POST">
    <table style="width:100%">
      <tr>
  <th>ID Resrv</th>
  <th>User ID</th>
  <th>Car ID</th>
  <th>Username</th>
  <th>Date from</th>
  <th>Date to</th>
  <th>From</th>
  <th>Return location</th>
  </tr>';

    while ( $row = mysqli_fetch_row($result)){
    $car_id=(htmlentities($row[0]));
    $brand=(htmlentities($row[1]));
    $model=(htmlentities($row[2]));
    $persons=(htmlentities($row[3]));
    $transmission=(htmlentities($row[4]));
    $price=(htmlentities($row[5]));
    $luggage=(htmlentities($row[6]));
    $conditioning=(htmlentities($row[7]));


  echo '<tr>
  <td>'.$car_id.'</td>
  <td>'.$brand.'</td>
  <td>'.$model.'</td>
  <td>'.$persons.'</td>
  <td>'.$transmission.'</td>
  <td>'.$price.'</td>
  <td>'.$luggage.'</td>
  <td>'.$conditioning.'</td>
  </tr>';
    }

    ?>
  </table><br>
      
      
       Cancel reservation:<input type="number" name="rsv_id" value="remove" placeholder="ID reserv" />
      <input type="submit" name="submit2" value="Submit" style="background-color: #4CAF50;  font-size: 16px;  border: double;"/>
      </form>

  </div>
    <?php

    require_once "dbconfig.php";

    if(isset($_POST['submit'])){
      $brand=$_POST['brand'];
      $model=$_POST['model'];
      $persons=$_POST['persons'];
      $transmission=$_POST['transmission'];
      $price=$_POST['price'];
      $luggage=$_POST['luggage'];
      $conditioning=$_POST['conditioning'];
      $image=$_POST['image'];

      $sql = "INSERT INTO cars (brand, model, persons, transmission,price,luggage,air_conditioning,image)
      VALUES ('$brand', '$model', '$persons', '$transmission','$price','$luggage','$conditioning','$image')";

      $result=mysqli_query($db,$sql);

      if($result){
        echo '<p>SUCCESS</p>';
        echo '<meta http-equiv="refresh" content="1; url=admin.php">';
      }else{
        echo 'FAIL';
        echo '<meta http-equiv="refresh" content="1; url=admin.php">';
      }
    }
    ?>
    <?php
    if(isset($_POST['submit1'])){

  $car_id=$_POST['car_id'];
  //$sql = "DELETE FROM cars WHERE car_id='$car_id'";
  $sql="delete from cars where car_id='".$car_id."'";
  $result=mysqli_query($db,$sql);

  if($result){
    echo '<meta http-equiv="refresh" content="0; url=admin.php">';
  }else{
    echo 'FAIL';
    echo '<meta http-equiv="refresh" content="0; url=admin.php">';
  }
}
     ?>

     <?php
    if(isset($_POST['submit2'])){

  $rsv_id=$_POST['rsv_id'];
  //$sql = "DELETE FROM cars WHERE car_id='$car_id'";
  $sql="delete from bookings where id_reserv='".$rsv_id."'";
  $result=mysqli_query($db,$sql);

  if($result){
    echo '<meta http-equiv="refresh" content="0; url=admin.php">';
  }else{
    echo 'FAIL';
    echo '<meta http-equiv="refresh" content="0; url=admin.php">';
  }
}
     ?>
  </body>
</html>
