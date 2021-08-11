<?php
include 'db_connection.php';
$conn = OpenCon();
echo "Connected Successfully";

//index.php?sno=serialno&locn=stn_no&chng=NULL  #new entry
//index.php?sno=serialno&locn=stn_no&chng=2     #new station.
//index.php?sno=serialno&locn=0&chng=2     #product ready.


$change= isset($_GET['chng']) ? $_GET['chng'] : NULL;

if(isset($_GET['sno'])){ //check if empty entry
  if (isset($change)){
    $sql = "UPDATE livestock SET StNo='".$_GET['locn']."'  WHERE  SNo='".$_GET['sno']."' ";
    if ($conn->query($sql) === TRUE) {
      echo "\n Record updated successfully\n";
    }
  } else {
    $sql = "INSERT INTO livestock VALUES ('".$_GET['sno']."','".$_GET['locn']."')";
    if ($conn->query($sql) === TRUE) {
      echo "\n Record inserted successfully\n";
    }}}
else{echo "\n no data";}

CloseCon($conn);
?>
