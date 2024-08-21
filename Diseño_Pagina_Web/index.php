<?php
//This line will make the page auto-refresh each 15 seconds
//Esta línea hará que la página se actualice automáticamente cada 15 segundos
$page = $_SERVER['PHP_SELF'];
$sec = "15";
?>


<html>
<head>
<!--//I've used bootstrap for the tables, so I inport the CSS files for taht as well...-->
<!--//He utilizado bootstrap para las tablas, así que también importo los archivos CSS para eso...-->
<meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">		
<!-- Latest compiled and minified CSS -->
 <!-- Último CSS compilado y minimizado -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
<!-- jQuery library -->
 <!-- Biblioteca jQuery -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<!-- Latest compiled JavaScript -->
 <!-- Último JavaScript compilado -->
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js"></script>
</head>
	
		
<body>    
<?php
//We include the database_connect.php which has the data for the connection to the database
//Incluimos el database_connect.php que tiene los datos para la conexión a la base de datos
include("database_connect.php"); 


//Check the connection
//Comprueba la conexión
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
//Again, we grab the table out of the database, name is ESPtable2 in this case
//Nuevamente, tomamos la tabla de la base de datos, el nombre es ESPtable2 en este caso
$result = mysqli_query($con,"SELECT * FROM ESPtable2");//table select


//Now we create the table with all the values from the database	  
//Ahora creamos la tabla con todos los valores de la base de datos

echo '<span style="font-size: 40px;"><b>Indicadores Booleanos.</b></span>';

echo "<table class='table' style='font-size: 30px;'>
	<!-- // Este mensaje esta comentado.
	<thead>
		<tr>
		<th>Boolean Indicators</th>	
		</tr>
	</thead>	
	-->
	
    <tbody>
      <tr class='active'>
        <td>PASILLO</td>
        <td>Lampara 1</td>
        <td>Lampara 2 </td>
		<td>Lampara 3 </td>
		<td>Lampara 4</td>
        <td>Lampara 5 </td>	
		<td>Lampara 6 </td>	
      </tr>  
		";
		  
//loop through the table and print the data into the table
//recorre la tabla e imprime los datos en la tabla
while($row = mysqli_fetch_array($result)) {
	
   echo "<tr class='success'>"; 	
    $unit_id = $row['id'];
    echo "<td>" . $row['id'] . "</td>";
	
    $column1 = "RECEIVED_BOOL1";
    $column2 = "RECEIVED_BOOL2";
    $column3 = "RECEIVED_BOOL3";
    $column4 = "RECEIVED_BOOL4";
    $column5 = "RECEIVED_BOOL5";
	$column6 = "RECEIVED_BOOL6";
	
    $current_bool_1 = $row['RECEIVED_BOOL1'];
	$current_bool_2 = $row['RECEIVED_BOOL2'];
	$current_bool_3 = $row['RECEIVED_BOOL3'];
	$current_bool_4 = $row['RECEIVED_BOOL4'];
	$current_bool_5 = $row['RECEIVED_BOOL5'];
	$current_bool_6 = $row['RECEIVED_BOOL6'];

	if($current_bool_1 == 1){
    $inv_current_bool_1 = 0;
	$text_current_bool_1 = "ON";
	$color_current_bool_1 = "#6ed829";
	}
	else{
    $inv_current_bool_1 = 1;
	$text_current_bool_1 = "OFF";
	$color_current_bool_1 = "#e04141";
	}
	
	
	if($current_bool_2 == 1){
    $inv_current_bool_2 = 0;
	$text_current_bool_2 = "ON";
	$color_current_bool_2 = "#6ed829";
	}
	else{
    $inv_current_bool_2 = 1;
	$text_current_bool_2 = "OFF";
	$color_current_bool_2 = "#e04141";
	}
	
	
	if($current_bool_3 == 1){
    $inv_current_bool_3 = 0;
	$text_current_bool_3 = "ON";
	$color_current_bool_3 = "#6ed829";
	}
	else{
    $inv_current_bool_3 = 1;
	$text_current_bool_3 = "OFF";
	$color_current_bool_3 = "#e04141";
	}
	
	
	if($current_bool_4 == 1){
    $inv_current_bool_4 = 0;
	$text_current_bool_4 = "ON";
	$color_current_bool_4 = "#6ed829";
	}
	else{
    $inv_current_bool_4 = 1;
	$text_current_bool_4 = "OFF";
	$color_current_bool_4 = "#e04141";
	}
	
	
	if($current_bool_5 == 1){
    $inv_current_bool_5 = 0;
	$text_current_bool_5 = "ON";
	$color_current_bool_5 = "#6ed829";
	}
	else{
    $inv_current_bool_5 = 1;
	$text_current_bool_5 = "OFF";
	$color_current_bool_5 = "#e04141";
	}


	if($current_bool_6 == 1){
	$inv_current_bool_6 = 0;
	$text_current_bool_6 = "ON";
	$color_current_bool_6 = "#6ed829";
	}
	else{
	$inv_current_bool_6 = 1;
	$text_current_bool_6 = "OFF";
	$color_current_bool_6 = "#e04141";
	}
	
	
	echo "<td><form action= update_values.php method= 'post'>
  	<input type='hidden' name='value2' value=$current_bool_1   size='15' >	
	<input type='hidden' name='value' value=$inv_current_bool_1  size='15' >	
  	<input type='hidden' name='unit' value=$unit_id >
  	<input type='hidden' name='column' value=$column1 >
  	<input type= 'submit' name= 'change_but' style=' margin-left: 25%; margin-top: 10%; font-size: 30px; text-align:center; background-color: $color_current_bool_1' value=$text_current_bool_1></form></td>";
	     
	
	echo "<td><form action= update_values.php method= 'post'>
  	<input type='hidden' name='value2' value=$current_bool_2   size='15' >	
	<input type='hidden' name='value' value=$inv_current_bool_2  size='15' >	
  	<input type='hidden' name='unit' value=$unit_id >
  	<input type='hidden' name='column' value=$column2 >
  	<input type= 'submit' name= 'change_but' style=' margin-left: 25%; margin-top: 10%; font-size: 30px; text-align:center; background-color: $color_current_bool_2' value=$text_current_bool_2></form></td>";
	
	
	echo "<td><form action= update_values.php method= 'post'>
  	<input type='hidden' name='value2' value=$current_bool_3   size='15' >	
	<input type='hidden' name='value' value=$inv_current_bool_3  size='15' >	
  	<input type='hidden' name='unit' value=$unit_id >
  	<input type='hidden' name='column' value=$column3 >
  	<input type= 'submit' name= 'change_but' style=' margin-left: 25%; margin-top: 10%; font-size: 30px; text-align:center; background-color: $color_current_bool_3' value=$text_current_bool_3></form></td>";
	
	
	echo "<td><form action= update_values.php method= 'post'>
  	<input type='hidden' name='value2' value=$current_bool_4   size='15' >	
	<input type='hidden' name='value' value=$inv_current_bool_4  size='15' >	
  	<input type='hidden' name='unit' value=$unit_id >
  	<input type='hidden' name='column' value=$column4 >
  	<input type= 'submit' name= 'change_but' style=' margin-left: 25%; margin-top: 10%; font-size: 30px; text-align:center; background-color: $color_current_bool_4' value=$text_current_bool_4></form></td>";
	
	
	echo "<td><form action= update_values.php method= 'post'>
  	<input type='hidden' name='value2' value=$current_bool_5   size='15' >	
	<input type='hidden' name='value' value=$inv_current_bool_5  size='15' >	
  	<input type='hidden' name='unit' value=$unit_id >
  	<input type='hidden' name='column' value=$column5 >
  	<input type= 'submit' name= 'change_but' style=' margin-left: 25%; margin-top: 10%; font-size: 30px; text-align:center; background-color: $color_current_bool_5' value=$text_current_bool_5></form></td>";
	

	echo "<td><form action= update_values.php method= 'post'>
  	<input type='hidden' name='value2' value=$current_bool_6   size='15' >	
	<input type='hidden' name='value' value=$inv_current_bool_6  size='15' >	
  	<input type='hidden' name='unit' value=$unit_id >
  	<input type='hidden' name='column' value=$column6 >
  	<input type= 'submit' name= 'change_but' style=' margin-left: 25%; margin-top: 10%; font-size: 30px; text-align:center; background-color: $color_current_bool_6' value=$text_current_bool_6></form></td>";


	echo "</tr>
	  </tbody>"; 
	
}
echo "</table><hr>";	
?>
		
		
<!--
//Again for the second table for numeric controls. We create the table with all the values from the database			
//De nuevo para la segunda tabla de controles numéricos. Creamos la tabla con todos los valores de la base de datos.
-->

<?php
include("database_connect.php");

if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
$result = mysqli_query($con,"SELECT * FROM ESPtable2");//table select

echo '<span style="font-size: 40px;"><b>Controles Numericos.</b></span>';

echo "<table class='table' style='font-size: 30px;'>
	<!-- //Esto esta comentado
	<thead>
		<tr>
		<th>Numeric controls</th>	
		</tr>
	</thead>
	-->
	
    <tbody>
      <tr class='active'>
        <td>Control 1</td>
        <td>Control 2</td>
        <td>Control 3</td>
		<td>Control 4 </td>
		<td>Control 5 </td>
      </tr>  
		";
		  
while($row = mysqli_fetch_array($result)) {

 	echo "<tr class='success'>";
   	
    $column6 = "RECEIVED_NUM1";
    $column7 = "RECEIVED_NUM2";
    $column8 = "RECEIVED_NUM3";
    $column9 = "RECEIVED_NUM4";
    $column10 = "RECEIVED_NUM5";
	
    $current_num_1 = $row['RECEIVED_NUM1'];
	$current_num_2 = $row['RECEIVED_NUM2'];
	$current_num_3 = $row['RECEIVED_NUM3'];
	$current_num_4 = $row['RECEIVED_NUM4'];
	$current_num_5 = $row['RECEIVED_NUM5'];	
	
		
	echo "<td><form action= update_values.php method= 'post'>
  	<input type='text' name='value' style='width: 120px;' value=$current_num_1  size='15' >
  	<input type='hidden' name='unit' style='width: 120px;' value=$unit_id >
  	<input type='hidden' name='column' style='width: 120px;' value=$column6 >
  	<input type= 'submit' name= 'change_but' style='width: 120px; text-align:center;' value='cargar'></form></td>";
	
        	
  	echo "<td><form action= update_values.php method= 'post'>
  	<input type='text' name='value' style='width: 120px;' value=$current_num_2  size='15' >
  	<input type='hidden' name='unit' style='width: 120px;' value=$unit_id >
  	<input type='hidden' name='column' style='width: 120px;' value=$column7 >
  	<input type= 'submit' name= 'change_but' style='text-align:center' value='cargar'></form></td>";
	

	echo "<td><form action= update_values.php method= 'post'>
  	<input type='text' name='value' style='width: 120px;' value=$current_num_3  size='15' >
  	<input type='hidden' name='unit' style='width: 120px;' value=$unit_id >
  	<input type='hidden' name='column' style='width: 120px;' value=$column8 >
  	<input type= 'submit' name= 'change_but' style='text-align:center' value='cargar'></form></td>";
	

	echo "<td><form action= update_values.php method= 'post'>
  	<input type='text' name='value' style='width: 120px;' value=$current_num_4  size='15' >
  	<input type='hidden' name='unit' style='width: 120px;' value=$unit_id >
  	<input type='hidden' name='column' style='width: 120px;' value=$column9 >
  	<input type= 'submit' name= 'change_but' style='text-align:center' value='cargar'></form></td>";
	

	echo "<td><form action= update_values.php method= 'post'>
  	<input type='text' name='value' style='width: 120px;' value=$current_num_5  size='15' >
  	<input type='hidden' name='unit' style='width: 120px;' value=$unit_id >
  	<input type='hidden' name='column' style='width: 120px;' value=$column10 >
  	<input type= 'submit' name= 'change_but' style='text-align:center' value='cargar'></form></td>";
	
	echo "</tr>
	  </tbody>"; 
	
}
echo "</table><hr>";		
?>
		
<!--
//Again for the third table for text send. We create the table with all the values from the database	
//Nuevamente para la tercera tabla para envío de texto. Creamos la tabla con todos los valores de la base de datos.
-->

<?php

include("database_connect.php");

if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}
$result = mysqli_query($con,"SELECT * FROM ESPtable2");//table select

echo '<span style="font-size: 40px;"><b>Imprimir en Pantalla.</b></span>';
		
echo "<table class='table' style='font-size: 30px;'>
	<!-- //Esto esta comentado
	<thead>
		<tr>
		<th>Send Text to Noobix</th>	
		</tr>
	</thead>
	-->

	<tbody>
		<tr class='active'>
		<td>Escriba su texto aqui:</td>        
		</tr>  
		";

while($row = mysqli_fetch_array($result)) {

 	 echo "<tr class='success'>";	
	
    $column11 = "TEXT_1"; 
    $current_text_1 = $row['TEXT_1'];
	
		
	echo "<td><form action= update_values.php method= 'post'>
  	<input style='width: 100%;' type='text' name='value' value=$current_text_1  size='100'>
  	<input type='hidden' name='unit' value=$unit_id >
  	<input type='hidden' name='column' value=$column11 >
  	<input type= 'submit' name= 'change_but' style='text-align:center' value='Enviar'></form></td>";
	
    echo "</tr>
	  </tbody>";      
	
}
echo "</table><hr>";
?>
				
		
<!-- 
//Again for the forth table.
//Otra vez para la cuarta taba.	
-->

<?php
include("database_connect.php");

if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

$result = mysqli_query($con,"SELECT * FROM ESPtable2");//table select

echo '<span style="font-size: 40px;"><b>Indicadores de Activacion.</b></span>';

echo "<table class='table' style='font-size: 30px;'>
	<!-- //Esto esta comentado
	<thead>
		<tr>
		<th>Boolean Indicators</th>	
		</tr>
	</thead>
	-->
	
    <tbody>
      <tr class='active'>
        <td>PASILLO</td>
        <td>Indicador 1</td>
        <td>Indicador 2 </td>
		<td>Indicador 3 </td>
		<td>Indicador 4 </td>
      </tr>  
		";
	  
	
	
while($row = mysqli_fetch_array($result)) {

 	$cur_sent_bool_1 = $row['SENT_BOOL_1'];
	$cur_sent_bool_2 = $row['SENT_BOOL_2'];
	$cur_sent_bool_3 = $row['SENT_BOOL_3'];
	$cur_sent_bool_4 = $row['SENT_BOOL_4'];
	

	if($cur_sent_bool_1 == 1){
    $label_sent_bool_1 = "label-success";
	$text_sent_bool_1 = "Active";
	}
	else{
    $label_sent_bool_1 = "label-danger";
	$text_sent_bool_1 = "Inactive";
	}
	
	
	if($cur_sent_bool_2 == 1){
    $label_sent_bool_2 = "label-success";
	$text_sent_bool_2 = "Active";
	}
	else{
    $label_sent_bool_2 = "label-danger";
	$text_sent_bool_2 = "Inactive";
	}
	
	
	if($cur_sent_bool_3 == 1){
    $label_sent_bool_3 = "label-success";
	$text_sent_bool_3 = "Active";
	}
	else{
    $label_sent_bool_3 = "label-danger";
	$text_sent_bool_3 = "Inactive";
	}


	if($cur_sent_bool_4 == 1){
	$label_sent_bool_4 = "label-success";
	$text_sent_bool_4 = "Active";
	}
	else{
	$label_sent_bool_4 = "label-danger";
	$text_sent_bool_4 = "Inactive";
	}
	 
		
	  echo "<tr class='info'>";
	  $unit_id = $row['id'];
        echo "<td>" . $row['id'] . "</td>";	
		echo "<td>
		<span class='label $label_sent_bool_1'>"
			. $text_sent_bool_1 . "</td>
	    </span>";
		
		echo "<td>
		<span class='label $label_sent_bool_2'>"
			. $text_sent_bool_2 . "</td>
	    </span>";
		
		echo "<td>
		<span class='label $label_sent_bool_3'>"
			. $text_sent_bool_3 . "</td>
	    </span>";

		echo "<td>
		<span class='label $label_sent_bool_4'>"
			. $text_sent_bool_4 . "</td>
	    </span>";

	  echo "</tr>
	  </tbody>"; 
      

}
echo "</table><hr>";
?>
		
	
<!--	
//Again for the fifth table.
//Otra vez para la quinta tabla.
-->

<?php

include("database_connect.php");

if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

$result = mysqli_query($con,"SELECT * FROM ESPtable2");//table select

echo '<span style="font-size: 40px;"><b>Indicadores Numericos.</b></span>';

echo "<table class='table' style='font-size: 30px;'>
	<!-- //Esto esta comentado
	<thead>
		<tr>
		<th>Integer Indicators</th>	
		</tr>
	</thead>
	-->
	
    <tbody>
      <tr class='active'>
        <td>Valor Recibido 1</td>
        <td>Valor Recibido 2</td>
        <td>Valor Recibido 3 </td>
		<td>Valor Recibido 4 </td>
      </tr>  
		";
		  

while($row = mysqli_fetch_array($result)) {

 	echo "<tr class='info'>";
    
	echo "<td>" . $row['SENT_NUMBER_1'] . "</td>";
	echo "<td>" . $row['SENT_NUMBER_2'] . "</td>";
	echo "<td>" . $row['SENT_NUMBER_3'] . "</td>";
	echo "<td>" . $row['SENT_NUMBER_4'] . "</td>";

	echo "</tr>
	</tbody>"; 

	
}
echo "</table><hr>";
?>
