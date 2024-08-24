boolean connect_ESP(){//devuelve 1 si tuvo éxito o 0 si no


  Serial.println("CONNECTING");
  //o 443 para HTTPS
  //enshare.000webhostapp.co
  ESP8266.print("AT+CIPSTART=0,\"TCP\",\"www.noobix.000webhostapp.com\",80\r\n");//Conéctese a su servidor web

  
  //read_until_ESP(palabra clave, tamaño de la palabra clave, tiempo de espera en ms, guardar datos 0-no 1-sí 'más sobre esto más adelante')
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),5000,0)){//ve a buscar 'OK' y regresa
  serial_dump_ESP();//deshazte de todo lo demás que viene
  Serial.println("CONNECTED");// Yay, conectada
  ESP8266.print("AT+CIPSEND=0,");//enviar AT+CIPSEND=0, tamaño de la carga útil
  ESP8266.print(payload_size);//el tamaño de la carga útil
  serial_dump_ESP();//Todo se refleja, así que deshazte de ello.
  ESP8266.print("\r\n\r\n");// Termine ese comando con un retorno de carro y un nuevo avance de línea
  
  if(read_until_ESP(keyword_carrot,sizeof(keyword_carrot),5000,0)){//vaya a esperar el caracter ">', ESP listo para la carga útil
    Serial.println("READY TO SEND");
    
    Serial.println(payload_size);
    
    for(int i=0; i<payload_size; i++)
    {//imprime la carga útil al ESP
    ESP8266.print(payload[i]);


    
    Serial.print(payload[i]);    

    }

    /*
    Serial.println(""); 
    Serial.println(payload_size); 
    Serial.println("");
    */
    
    if(read_until_ESP(keyword_sendok,sizeof(keyword_sendok),5000,0)){//vaya a esperar 'ENVIAR OK'
    Serial.println("SENT");//yay, fue enviado
    return 1;//Sal de aquí, los datos están a punto de salir volando del ESP
  }// recibí el ENVÍO OK
    else// ENVIAR OK
  Serial.println("FAILED TO SEND");
  
  }//conseguí la zanahoria de atrás >
  else
  Serial.println("FAILED TO GET >");
  
  }//Primero OK
  else{
  Serial.println("FAILED TO CONNECT");//Algo salió mal
  setup_ESP();//opcional, esto configurará el módulo e intentará repararse a sí mismo: conectarse a SSID, configurar CIPMUX, etc.
  }
  
}// FUNCIÓN DE CONEXIÓN ANULADA
