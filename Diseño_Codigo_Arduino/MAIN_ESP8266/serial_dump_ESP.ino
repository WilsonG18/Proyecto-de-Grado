//Función bastante simple: lee todo lo que está en el búfer serial y lo que viene y se deshace de ello.
void serial_dump_ESP(){
  char temp;
  while(ESP8266.available()){
    temp =ESP8266.read();
    delay(1);//Podría jugar con este valor si se producen desbordamientos de búfer
  }//while
  //Serial.println("DUMPED");
  
  
}//volcado de serie
