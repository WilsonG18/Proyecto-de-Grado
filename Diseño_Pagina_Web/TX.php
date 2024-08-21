<?php
/*This file should receive a link somethong like this: http://noobix.000webhostapp.com/TX.php?unit=1&b1=1
If you paste that link to your browser, it should update b1 value with this TX.php file. Read more details below.
The ESP will send a link like the one above but with more than just b1. It will have b1, b2, etc...
*/
/*Este archivo debería recibir un enlace parecido a este: http://noobix.000webhostapp.com/TX.php?unit=1&b1=1
Si pegas ese enlace en tu navegador, debería actualizar el valor b1 con este archivo TX.php. Lee más detalles a continuación.
El ESP enviará un enlace como el anterior pero con más que solo b1. Tendrá b1, b2, etc...
*/

//We loop through and grab variables from the received the URL
//Recorremos y tomamos variables de la URL recibida

//Save the received value to the hey variable. Save each cahracter after the "&"
//Guarda el valor recibido en la variable hey. Guarda cada carácter después del "&"
foreach($_REQUEST as $key => $value)  

{
	//Now we detect if we recheive the id, the password, unit, or a value to update
	//Ahora detectamos si recibimos el id, la contraseña, unidad o un valor a actualizar
if($key =="id"){
$unit = $value;
}	
if($key =="pw"){
$pass = $value;
}	
if($key =="un"){
$update_number = $value;
}
	
if($update_number == 1)
{
	if($key =="n1"){
		$sent_nr_1 = $value;
	}			
}
else if($update_number == 2)
{
	if($key =="n2"){
	$sent_nr_2 = $value;
	}			
}
else if($update_number == 3)
{
	if($key =="n3"){
	$sent_nr_3 = $value;
	}			
}
else if($update_number == 4)
{
	if($key =="n4"){
	$sent_nr_4 = $value;
	}			
}	
	
else if($update_number == 5)
	{
	if($key =="b6"){
	$sent_bool_1 = $value;
	}	
	if($key =="b7"){
	$sent_bool_2 = $value;
	}	
	if($key =="b8"){
	$sent_bool_3 = $value;
	}	
	if($key =="b9"){
	$sent_bool_4 = $value;
	}	
}
}//End of foreach
//Fin de foreach

//We include the database_connect.php which has the data for the connection to the database
//Incluimos el database_connect.php que tiene los datos para la conexión a la base de datos
include("database_connect.php"); 	


// Check  the connection
//Comprueba la conexión
if (mysqli_connect_errno()) {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

//Now we update the values in database
//Ahora actualizamos los valores en la base de datos


//If the received data is for SENT_NUMBER_1, we update that value
//Si los datos recibidos son para SENT_NUMBER_1, actualizamos ese valor
if($update_number == 1)	
	{
		mysqli_query($con,"UPDATE ESPtable2 SET SENT_NUMBER_1 = $sent_nr_1 WHERE id=$unit AND PASSWORD=$pass");	
	}
else if($update_number == 2)	//The same and so on...  // Lo mismo y así sucesivamente ...
	{
		mysqli_query($con,"UPDATE ESPtable2 SET SENT_NUMBER_2 = $sent_nr_2 WHERE id=$unit AND PASSWORD=$pass");	;	
	}
else if($update_number == 3)
	{
		mysqli_query($con,"UPDATE ESPtable2 SET SENT_NUMBER_3 = $sent_nr_3 WHERE id=$unit AND PASSWORD=$pass");	;	
	}
else if($update_number == 4)
	{
		mysqli_query($con,"UPDATE ESPtable2 SET SENT_NUMBER_4 = $sent_nr_4 WHERE id=$unit AND PASSWORD=$pass");	;	
	}

else if($update_number == 5)
	{
		mysqli_query($con,"UPDATE ESPtable2 SET SENT_BOOL_1 = $sent_bool_1, SENT_BOOL_2 = $sent_bool_2, SENT_BOOL_3 = $sent_bool_3, SENT_BOOL_4 = $sent_bool_4
		WHERE id=$unit AND PASSWORD=$pass");	;	
	}



//In case that you need the time from the internet, use this line
//En caso de que necesites la hora de internet, utiliza esta línea
date_default_timezone_set('UTC');

//This will return 1:23 as 123
//Esto devolverá 1:23 como 123
$t1 = date("gi"); 	

//Get all the values form the table on the database
//Obtener todos los valores de la tabla en la base de datos

//table select is ESPtable2, must be the same on yor database
//La tabla seleccionada es ESPtable2, debe ser la misma en su base de datos
$result = mysqli_query($con,"SELECT * FROM ESPtable2");	

//Loop through the table and filter out data for this unit id equal to the one taht we've received. 
//Recorre la tabla y filtra los datos para ver si esta unidad es igual a la que hemos recibido.
while($row = mysqli_fetch_array($result)) {
if($row['id'] == $unit){
	
		//We update the values for the boolean and numebers we receive from the Arduino, then we echo the boolean
		//and numbers and the text from the database back to the Arduino
		//Actualizamos los valores de los booleanos y los números que recibimos de Arduino, luego enviamos los booleanos
		//y los números y el texto de la base de datos a Arduino
		$b1 = $row['RECEIVED_BOOL1'];	
		$b2 = $row['RECEIVED_BOOL2'];	
		$b3 = $row['RECEIVED_BOOL3'];
		$b4 = $row['RECEIVED_BOOL4'];	
		$b5 = $row['RECEIVED_BOOL5'];
		$b6 = $row['RECEIVED_BOOL6'];
		
		$n1 = $row['RECEIVED_NUM1'];	
		$n2 = $row['RECEIVED_NUM2'];	
		$n3 = $row['RECEIVED_NUM3'];
		$n4 = $row['RECEIVED_NUM4'];	
		$n5 = $row['RECEIVED_NUM5'];
		$n6 = $row['RECEIVED_NUM6'];
		
		$n7 = $row['TEXT_1'];
		
		//Next line will echo the data back to the Arduino
		//La siguiente línea reflejará los datos en el Arduino.
		echo " _t1$t1##_b1$b1##_b2$b2##_b3$b3##_b4$b4##_b5$b5##_b6$b6##_n1$n1##_n2$n2##_n3$n3##_n4$n4##_n5$n5##_n6$n6##_n7$n7##";
	
}


}// End of the while loop	// Fin del bucle while
?>
