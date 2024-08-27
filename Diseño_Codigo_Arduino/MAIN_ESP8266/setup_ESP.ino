boolean setup_ESP(){//devuelve un '1' si tiene éxito
  
  ESP8266.print("AT\r\n");// Envíe solo 'AT' para asegurarse de que el ESP esté respondiendo
    //Esta función read_until_... se usa para encontrar una palabra clave en la respuesta del ESP; más sobre esto más adelante y en la función misma
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),5000,0))//busque la palabra clave "OK" con un tiempo de espera de 5 segundos
    Serial.println("ESP CHECK OK");
  else
    Serial.println("ESP CHECK FAILED");
  serial_dump_ESP();//Esto simplemente lee todo lo que hay en el buffer y lo que todavía viene del ESP

   ESP8266.print("AT+RST\r\n");// Reinícialo, quién sabe en qué estado estaba, es mejor empezar de nuevo.
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),5000,0))//ve a buscar la palabra clave "Listo"; tarda unos segundos más en completarse
    Serial.println("ESP RESET OK");//dependiendo de la versión de FW en el ESP, a veces el Ready está con una r minúscula - ready
  else
    Serial.println("ESP RESET FAILED"); 
  serial_dump_ESP();

  
   ESP8266.print("AT+CWMODE=");// establece el CWMODE
   ESP8266.print(CWMODE);//solo envía lo que está configurado en la constante
   ESP8266.print("\r\n");
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),5000,0))//ve a buscar la palabra clave "OK"
    Serial.println("ESP CWMODE SET");
  else
    Serial.println("ESP CWMODE SET FAILED"); //Probablemente fallará, ya que se devuelve un 'sin cambios' si ya está configurado; sería bueno verificar dos palabras
  serial_dump_ESP();  
   
   //Aquí es donde se configuran el SSID y la contraseña
   ESP8266.print("AT+CWJAP=\"");// Establezca el SSID AT+CWJAP="SSID", "PW"
   ESP8266.print(SSID_ESP);//forma constante
   ESP8266.print("\",\"");
   ESP8266.print(SSID_KEY);//forma constante
   ESP8266.print("\"\r\n");
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),10000,0))//ve a buscar la palabra clave "OK"
    Serial.println("ESP SSID SET OK");
  else
    Serial.println("ESP SSID SET FAILED");   
  serial_dump_ESP();
  
  //Esto verifica y almacena la dirección IP
  Serial.println("CHECKING FOR AN IP ADDRESS");
  ESP8266.print("AT+CIFSR\r\n");//comando para recuperar la dirección IP del ESP
  if(read_until_ESP(keyword_rn,sizeof(keyword_rn),10000,0)){//busque el primer \r\n después del eco AT+CIFSR - tenga en cuenta que el modo es '0', la dirección IP está justo después de esto
  if(read_until_ESP(keyword_rn,sizeof(keyword_rn),1000,1)){//busca el segundo \r\n y almacena todo lo que recibe, modo='1'
    //almacena la dirección IP en su variable, ip_address[]
    for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_rn)+1); i++)//Eso <=... va a requerir algo de explicación, vea las siguientes líneas
       ip_address[i] = scratch_data_from_ESP[i];//Completa la dirección IP con los datos recibidos
        //i=1 porque i=0 es la longitud de los datos encontrados entre las dos palabras clave, PERO esto incluye la longitud de la segunda palabra clave, por lo que i<= a la longitud menos
        //tamaño de la palabra clave, pero recuerda, sizeof() devolverá uno extra, que se restará, así que lo agregué nuevamente en +1
    ip_address[0] = (scratch_data_from_ESP[0]-sizeof(keyword_rn)+1);//Almacena la longitud de la dirección IP en [0], lo mismo que antes
    Serial.print("IP ADDRESS = " + ip_address[0]);//imprimirlo para verificar
    for(int i=1; i<=ip_address[0]; i++)//enviar la dirección ip
    Serial.print(ip_address[i]);
    Serial.println("");
  }}//if first \r\n
  else
  Serial.print("IP ADDRESS FAIL");
  serial_dump_ESP();

 
   ESP8266.print("AT+CIPMUX=");// Establecer la CIPMUX
   ESP8266.print(CIPMUX);//de constante
   ESP8266.print("\r\n");
  if(read_until_ESP(keyword_OK,sizeof(keyword_OK),5000,0))//ve a buscar la palabra clave "OK" o "sin cambios"
    Serial.println("ESP CIPMUX SET");
  else
    Serial.println("ESP CIPMUX SET FAILED"); 
  serial_dump_ESP();


 

 //¡Eso es todo! Se podría hacer anidando todo junto, de modo que si algo falla, devuelva '0', y si llega hasta el final, devuelva '1'... bueno, ¿no?
  
  
}//configurar ESP
