<?php
//This file will get the values when you click any of the ON/OFF buttons or change buttons on the index.php file
//We get that value and send it to the datapase table and by that update the values
//Este archivo obtendrá los valores cuando haga clic en cualquiera de los botones ON/OFF o de cambio en el archivo index.php
//Obtenemos ese valor y lo enviamos a la tabla de la base de datos y, de esa manera, actualizamos los valores

//Get the value
//Obtener el valor
$value = $_POST['value'];		

//Get the id if the unit where we want to update the value
//Obtener el id de la unidad donde queremos actualizar el valor
$unit = $_POST['unit'];			

//Which coulumn of the database, could be the RECEIVED_BOOL1, etc...
//¿Qué columna de la base de datos, podría ser el BOOL RECIBIDO 1, etc...
$column = $_POST['column'];		

//connect to the database
//conectarse a la base de datos

//We include the database_connect.php which has the data for the connection to the database
//We include the database_connect.php which has the data for the connection to the database
include("database_connect.php"); 

// Check the connection
//Comprueba la conexión
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

//Now update the value sent from the post (ON/OFF, change or send button)
//Ahora actualiza el valor enviado desde el post (botón ON/OFF, cambiar o enviar)
mysqli_query($con,"UPDATE ESPtable2 SET $column = '{$value}'
WHERE id=$unit");

//go back to the interface
//volver a la interfaz
header("location: index.php");
?>