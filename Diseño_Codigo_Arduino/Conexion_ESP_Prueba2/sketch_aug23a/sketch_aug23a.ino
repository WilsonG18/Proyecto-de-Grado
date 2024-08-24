#include <SoftwareSerial.h>
 
#define DEBUG true
 
SoftwareSerial esp8266(2,3);   // Haz que la línea RX de Arduino sea el pin 2, y que la línea TX de Arduino sea el pin 3.
                              // Esto significa que debes conectar la línea TX del esp al pin 2 de Arduino
                              // y la línea RX del esp al pin 3 de Arduino

void setup()
{
  Serial.begin(9600);
  esp8266.begin(9600);        // La velocidad en baudios de tu ESP puede ser diferente
  
  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  pinMode(10,OUTPUT);
  digitalWrite(10,LOW);
   
  sendCommand("AT+RST\r\n",2000,DEBUG);                               // módulo de reinicio
  sendCommand("AT+CWMODE=1\r\n",1000,DEBUG);                          // configurar como punto de acceso
  sendCommand("AT+CWJAP=\"mySSID\",\"myPassword\"\r\n",3000,DEBUG);
  delay(10000);
  sendCommand("AT+CIFSR\r\n",1000,DEBUG);                             // obtener dirección ip
  sendCommand("AT+CIPMUX=1\r\n",1000,DEBUG);                          // configurar para múltiples conexiones
  sendCommand("AT+CIPSERVER=1,80\r\n",1000,DEBUG);                    // turn on server on port 80
  
  Serial.println("Server Ready");
}
 
void loop()
{
  if(esp8266.available())                                             // comprobar si el esp está enviando un mensaje
  {
 
    
    if(esp8266.find("+IPD,"))
    {
     delay(1000);                                                     // Esperar a que se llene el búfer serial (leer todos los datos seriales)
                                                                      // Obtener el ID de conexión para que luego podamos desconectarnos
     int connectionId = esp8266.read()-48;                            // resta 48 porque la función read() devuelve
                                                                      // el valor decimal ASCII y 0 (el primer número decimal) comienza en 48
          
     esp8266.find("pin=");                                            // avanza el cursor a "pin="
          
     int pinNumber = (esp8266.read()-48);                             // obtener el primer número, es decir, si el pin es 13, entonces el primer número es 1
     int secondNumber = (esp8266.read()-48);
     if(secondNumber>=0 && secondNumber<=9)
     {
      pinNumber*=10;
      pinNumber +=secondNumber; // obtener el segundo número, es decir, si el número PIN es 13, entonces el segundo número es 3, luego se suma al primer número
     }
     
     digitalWrite(pinNumber, !digitalRead(pinNumber));                // alternar pin  
     
                                                                      // Crea una cadena que se envía de vuelta al dispositivo que solicita el cambio de PIN
     String content;
     content = "Pin ";
     content += pinNumber;
     content += " is ";
     
     if(digitalRead(pinNumber))
     {
       content += "ON";
     }
     else
     {
       content += "OFF";
     }
     
     sendHTTPResponse(connectionId,content);
     
     // hacer comando de cierre
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId;                                      // agregar id de conexión
     closeCommand+="\r\n";
     
     sendCommand(closeCommand,1000,DEBUG);                            // cerrar conexión
    }
  }
}
 
/*
* Nombre: sendData
* Descripción: Función utilizada para enviar datos al ESP8266.
* Parámetros: command - los datos/comandos a enviar; timeout - el tiempo de espera para una respuesta; debug - imprimir en la ventana serial?(true = yes, false = no)
* Devuelve: La respuesta del esp8266 (si hay una respuesta)
*/
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    int dataSize = command.length();
    char data[dataSize];
    command.toCharArray(data,dataSize);
           
    esp8266.write(data,dataSize);                                     // envía el carácter leído al esp8266
    if(debug)
    {
      Serial.println("\r\n====== HTTP Response From Arduino ======");
      Serial.write(data,dataSize);
      Serial.println("\r\n========================================");
    }
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // El esp tiene datos, por lo que muestra su salida en la ventana serial
        char c = esp8266.read(); // lee el siguiente caracter.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
 
/*
* Nombre: sendHTTPResponse
* Descripción: Función que envía una respuesta HTTP 200, HTML UTF-8
*/
void sendHTTPResponse(int connectionId, String content)
{
     
     // construir respuesta HTTP
     String httpResponse;
     String httpHeader;
     // Encabezado HTTP
     httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n"; 
     httpHeader += "Content-Length: ";
     httpHeader += content.length();
     httpHeader += "\r\n";
     httpHeader +="Connection: close\r\n\r\n";
     httpResponse = httpHeader + content + " "; // There is a bug in this code: the last character of "content" is not sent, I cheated by adding this extra space
     sendCIPData(connectionId,httpResponse);
}
 
/*
* Nombre: sendCIPDATA
* Descripción: envía un comando CIPSEND=<connectionId>,<data>
*
*/
void sendCIPData(int connectionId, String data)
{
   String cipSend = "AT+CIPSEND=";
   cipSend += connectionId;
   cipSend += ",";
   cipSend +=data.length();
   cipSend +="\r\n";
   sendCommand(cipSend,1000,DEBUG);
   sendData(data,1000,DEBUG);
}
 
/*
* Nombre: sendCommand
* Descripción: Función utilizada para enviar datos al ESP8266.
* Parámetros: command - los datos o comandos a enviar; timeout - el tiempo de espera para una respuesta; debug - imprimir en la ventana serial?(true = yes, false = no)
* Devuelve: La respuesta del esp8266 (si hay una respuesta)
*/
String sendCommand(String command, const int timeout, boolean debug)
{
    String response = "";
           
    esp8266.print(command);                                             // envía el carácter leído al esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // El esp tiene datos, por lo que muestra su salida en la ventana serial
        char c = esp8266.read();                                       // lee el siguiente caracter.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}