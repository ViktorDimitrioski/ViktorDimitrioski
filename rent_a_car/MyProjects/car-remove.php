<?php
require_once "dbconfig.php";

if(isset($_POST['submit1'])){

  $car_id=$_POST['car_id'];
  //$sql = "DELETE FROM cars WHERE car_id='$car_id'";
  $sql="delete from cars where car_id='".$car_id."'";
  $result=mysqli_query($db,$sql);

  if($result){
    echo '<meta http-equiv="refresh" content="1; url=admin.php">';
  }else{
    echo 'FAIL';
    echo '<meta http-equiv="refresh" content="1; url=admin.php">';
  }
}
 ?>
