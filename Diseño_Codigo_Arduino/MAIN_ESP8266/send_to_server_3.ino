void send_to_server_3(){
//Tenemos una variable cambiante aquí, por lo que primero debemos construir nuestro paquete URL
/*URL_withPacket = URL_webhost;//pull in the base URL
URL_withPacket += String(unit_id);//unit id value
URL_withPacket += "&sensor=";//unit id 1
URL_withPacket += String(sensor_value);//sensor value
URL_withPacket += payload_closer;*/

url = location_url;
url += NOOBIX_id;
url += "&pw=";
url +=  NOOBIX_password;//valor del sensor
url += "&un=3";
url += "&n3=";
url +=  String(sent_nr_3);//valor del sensor


URL_withPacket = ""; 

URL_withPacket = (String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");




/*
URL_withPacket += "Host: www.electronoobs.com\r\n";  
URL_withPacket += "Connection: close\r\n\r\n";  
  */
  /// Esto crea la URL de carga útil: no es realmente necesario aquí, pero es muy útil cuando se agregan diferentes matrices a la carga útil.
  counter=0;//realiza un seguimiento del tamaño de la carga útil
  payload_size=0;
  for(int i=0; i<(URL_withPacket.length()); i++){//Esta vez usamos una cadena, así que usamos .length()
    payload[payload_size+i] = URL_withPacket[i];//construir la carga útil
    counter++;//incrementar el contador
  }//for int
  payload_size = counter+payload_size;//El tamaño de la carga útil es solo el valor del contador; hablaremos más sobre esto cuando necesitemos desarrollar la carga útil con más datos
    //for(int i=0; i<payload_size; i++)//imprime la carga útil al ESP
    //Serial.print(payload[i]);   


   
  if(connect_ESP()){//Esto llama a 'connect_ESP()' y espera un '1' de vuelta si tiene éxito
    //Bien, ya estamos listos para buscar datos
    //Primero, necesitamos analizar los datos devueltos _t1123##_d15##_d210##

 
  //Serial.println("connected ESP"); 
  if(read_until_ESP(keyword_t1,sizeof(keyword_t1),5000,0)){//ve a buscar t1 y luego detente
  if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//Nuestros datos son los siguientes, así que cambiamos el modo a '1' y nos detenemos en ##
  //Obtuvimos nuestros datos, así que los almacenamos rápidamente en d1
  for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)//vea 'configuración' y cómo se hizo esto con la dirección IP para obtener más información
  t1_from_ESP[i] = scratch_data_from_ESP[i];
  t1_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);
  
  //Todavía tenemos más datos que obtener de este flujo, ahora queremos d1
   if(read_until_ESP(keyword_b1,sizeof(keyword_b1),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d1_from_ESP[i] = scratch_data_from_ESP[i];
   d1_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);

   if(read_until_ESP(keyword_b2,sizeof(keyword_b2),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d2_from_ESP[i] = scratch_data_from_ESP[i];
   d2_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);

   if(read_until_ESP(keyword_b3,sizeof(keyword_b3),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d3_from_ESP[i] = scratch_data_from_ESP[i];
   d3_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);

   if(read_until_ESP(keyword_b4,sizeof(keyword_b4),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d4_from_ESP[i] = scratch_data_from_ESP[i];
   d4_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);

   if(read_until_ESP(keyword_b5,sizeof(keyword_b5),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d5_from_ESP[i] = scratch_data_from_ESP[i];
   d5_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);

   

   if(read_until_ESP(keyword_n1,sizeof(keyword_n1),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d9_from_ESP[i] = scratch_data_from_ESP[i];
   d9_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);

   if(read_until_ESP(keyword_n2,sizeof(keyword_n2),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d10_from_ESP[i] = scratch_data_from_ESP[i];
   d10_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);

   if(read_until_ESP(keyword_n3,sizeof(keyword_n3),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d11_from_ESP[i] = scratch_data_from_ESP[i];
   d11_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);

   if(read_until_ESP(keyword_n4,sizeof(keyword_n4),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d12_from_ESP[i] = scratch_data_from_ESP[i];
   d12_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);

   if(read_until_ESP(keyword_n5,sizeof(keyword_n5),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d13_from_ESP[i] = scratch_data_from_ESP[i];
   d13_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);

   if(read_until_ESP(keyword_n6,sizeof(keyword_n6),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d14_from_ESP[i] = scratch_data_from_ESP[i];
   d14_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);


   
   //Ahora que tenemos nuestros datos, vamos a esperar a que se desconecte la conexión.
   //- El ESP eventualmente devolverá 'Desvincular'
   //delay(10);
   Serial.println("FOUND DATA & DISCONNECTED");
   serial_dump_ESP();//Ahora podemos limpiar el buffer y leer lo que aún esté allí
    //Veamos cómo se ven los datos

   Serial.println("");
   Serial.print("Time ");
   if(t1_from_ESP[0] > 3){
   Serial.print(t1_from_ESP[1]);
   Serial.print(t1_from_ESP[2]);
   Serial.print(":");
   Serial.print(t1_from_ESP[3]);
   Serial.println(t1_from_ESP[4]);  
   }
   else{
   Serial.print(t1_from_ESP[1]);
   Serial.print(":");
   Serial.print(t1_from_ESP[2]);
   Serial.println(t1_from_ESP[3]);  
   }
                          
   Serial.print("RECEIVED_BOOL_1 = ");//imprime los datos del LED y conviértelos en números enteros
   received_bool_1 = 0;
   for(int i=1; i<=d1_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_bool_1 = received_bool_1 + ((d1_from_ESP[i] - 48) * multiplier[d1_from_ESP[0] - i]);
   }
   Serial.println(received_bool_1);  
                          
   Serial.print("RECEIVED_BOOL_2 = ");//imprime los datos del LED y conviértelos en números enteros
   received_bool_2 = 0;
   for(int i=1; i<=d2_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_bool_2 = received_bool_2 + ((d2_from_ESP[i] - 48) * multiplier[d2_from_ESP[0] - i]);
   }
   Serial.println(received_bool_2);    
   
   Serial.print("RECEIVED_BOOL_3 = ");//imprime los datos del LED y conviértelos en números enteros
   received_bool_3 = 0;
   for(int i=1; i<=d3_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_bool_3 = received_bool_3 + ((d3_from_ESP[i] - 48) * multiplier[d3_from_ESP[0] - i]);
   }
   Serial.println(received_bool_3);     

   Serial.print("RECEIVED_BOOL_4 = ");//imprime los datos del LED y conviértelos en números enteros
   received_bool_4 = 0;
   for(int i=1; i<=d4_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_bool_4 = received_bool_4 + ((d4_from_ESP[i] - 48) * multiplier[d4_from_ESP[0] - i]);
   }
   Serial.println(received_bool_4); 

   Serial.print("RECEIVED_BOOL_5 = ");//imprime los datos del LED y conviértelos en números enteros
   received_bool_5 = 0;
   for(int i=1; i<=d5_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_bool_5 = received_bool_5 + ((d5_from_ESP[i] - 48) * multiplier[d5_from_ESP[0] - i]);
   }
   Serial.println(received_bool_5); 

   

   Serial.print("RECEIVED_NUMBER_1 = ");//imprime los datos del LED y conviértelos en números enteros
   received_nr_1 = 0;
   for(int i=1; i<=d9_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_nr_1 = received_nr_1 + ((d9_from_ESP[i] - 48) * multiplier[d9_from_ESP[0] - i]);
   }
   Serial.println(received_nr_1); 

   Serial.print("RECEIVED_NUMBER_2 = ");//imprime los datos del LED y conviértelos en números enteros
   received_nr_2 = 0;
   for(int i=1; i<=d10_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_nr_2 = received_nr_2 + ((d10_from_ESP[i] - 48) * multiplier[d10_from_ESP[0] - i]);
   }
   Serial.println(received_nr_2); 

   Serial.print("RECEIVED_NUMBER_3 = ");//imprime los datos del LED y conviértelos en números enteros
   received_nr_3 = 0;
   for(int i=1; i<=d11_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_nr_3 = received_nr_3 + ((d11_from_ESP[i] - 48) * multiplier[d11_from_ESP[0] - i]);
   }
   Serial.println(received_nr_3); 

   Serial.print("RECEIVED_NUMBER_4 = ");//imprime los datos del LED y conviértelos en números enteros
   received_nr_4 = 0;
   for(int i=1; i<=d12_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_nr_4 = received_nr_4 + ((d12_from_ESP[i] - 48) * multiplier[d12_from_ESP[0] - i]);
   }
   Serial.println(received_nr_4); 

   Serial.print("RECEIVED_NUMBER_5 = ");//imprime los datos del LED y conviértelos en números enteros
   received_nr_5 = 0;
   for(int i=1; i<=d13_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_nr_5 = received_nr_5 + ((d13_from_ESP[i] - 48) * multiplier[d13_from_ESP[0] - i]);
   }
   Serial.println(received_nr_5); 

   Serial.print("RECEIVED_TEXT_1 = ");//imprime los datos del LED y conviértelos en números enteros
   received_text = "";
   for(int i=1; i<=d14_from_ESP[0]; i++){
   //Serial.print(d12_from_ESP[i]);
   received_text = received_text + d14_from_ESP[i];
   }
   Serial.println(received_text); 
   
   
   Serial.println("");
   //¡¡eso es todo!! 
   }//##
   }//n6 text 1
   }//##
   }//n5
   }//##
   }//n4
   }//##
   }//n3
   }//##
   }//n2
   }//##
   }//n1
   }//##
   }//b5
   }//##
   }//b4                    
   }//##
   }//b3
   }//##
   }//b2
   }//##
   }//b1
   }//##
   }//t1


  
  
/*
  //Serial.println("connected ESP"); 
  //we still have more data to get out of this stream, now we want d1
   if(read_until_ESP(keyword_n3,sizeof(keyword_n3),5000,0)){//lo mismo que antes - primer d1
   if(read_until_ESP(keyword_doublehash,sizeof(keyword_doublehash),5000,1)){//ahora ## y modo=1
   for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1); i++)
   d11_from_ESP[i] = scratch_data_from_ESP[i];
   d11_from_ESP[0] = (scratch_data_from_ESP[0]-sizeof(keyword_doublehash)+1);
   //now that we have our data, go wait for the connection to disconnect 
   //- the ESP will eventually return 'Unlink'
   //delay(10);
   Serial.println("FOUND DATA & DISCONNECTED");
   serial_dump_ESP();//now we can clear out the buffer and read whatever is still there
   //let's see how the data looks
                       
   Serial.print("SENT_NUMBER_3 = ");//imprime los datos del LED y conviértelos en números enteros
   sent_nr_3_feedback = 0;
   for(int i=1; i<=d11_from_ESP[0]; i++){
   //Serial.print(d11_from_ESP[i]);
   sent_nr_3_feedback = sent_nr_3_feedback + ((d11_from_ESP[i] - 48) * multiplier[d11_from_ESP[0] - i]);
   }
   Serial.println(sent_nr_3_feedback);                         
   Serial.println("");
   //that's it!!                        
   }//##
   }//d2
              
    */
  }//conectar ESP


}//conectar el servidor web
