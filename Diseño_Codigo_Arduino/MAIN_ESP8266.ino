//Incluya la biblioteca necesaria, utilizaremos una comunicación serial más suave con el ESP8266
#include <SoftwareSerial.h>
#include <avr/power.h>

//Configuración de LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  //A veces la dirección del LCD no es 0x3f. Cámbiela a 0x27 si no funciona.


//Definir el usado
#define ESP8266_RX 10  //Conecta el pin TX del ESP a este pin RX del Arduino
#define ESP8266_TX 11  //Conecta el pin TX del Arduino al pin RX del ESP  

int LED1 = 2;
int LED2 = 3;
int LED3 = 4;
int LED4 = 5;
int LED5 = 6;
int Potentiometer_1 = A0;
int Potentiometer_2 = A1;
int Potentiometer_3 = A2;
int Potentiometer_4 = A3;
int switch1 = 7;
int switch2 = 8;
int switch3 = 9;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////Variables que debes cambiar según tus valores/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Agrega tus datos: SSID + CLAVE + host + ubicación + id + contraseña
//////////////////////////////////////////////
const char SSID_ESP[] = "MiFibra-4132";         //Da el nombre EXACTO de tu WIFI
const char SSID_KEY[] = "vzP5anY5";             //Agrega la contraseña de esa conexión WIFI
const char* host = "noobix.000webhostapp.com";  //Agrega el host sin "www" Ejemplo: electronoobs.com
String NOOBIX_id = "99999";                     //Este es el ID que tienes en tu base de datos, he usado 99999 porque hay un máximo de 5 caracteres
String NOOBIX_password = "12345";               //Agrega la contraseña de la base de datos, también máximo 5 caracteres y solo valores numéricos
String location_url = "/TX.php?id=";            //ubicación de su archivo PHP en el servidor. En este caso, TX.php se encuentra directamente en la primera carpeta del servidor
                                                //Si tienes los archivos en una carpeta diferente, agrégalos también, Ejemplo: "/ESP/TX.php?id=" Donde la carpeta es ESP
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//Variables utilizadas en el código
String url = "";
String URL_withPacket = "";    
unsigned long multiplier[] = {1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
//MODES for the ESP
const char CWMODE = '1';//CWMODE 1=ESTACIÓN, 2=APMODE, 3=AMBOS
const char CIPMUX = '1';//CWMODE 0=Conexión única, 1=Conexiones múltiples


//Defina las funciones utilizadas más adelante en el código, gracias a Kevin Darrah, canal de YT: https://www.youtube.com/user/kdarrah1234
boolean setup_ESP();
boolean read_until_ESP(const char keyword1[], int key_size, int timeout_val, byte mode);
void timeout_start();
boolean timeout_check(int timeout_ms);
void serial_dump_ESP();
boolean connect_ESP();
void connect_webhost();
unsigned long timeout_start_val;
char scratch_data_from_ESP[20];//el primer byte es la longitud de bytes
char payload[200];
byte payload_size=0, counter=0;
char ip_address[16];


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Variable a ENVIAR a la BASE DE DATOS
bool sent_bool_1 = 0;
bool sent_bool_2 = 0;
bool sent_bool_3 = 0;
int  sent_nr_1 = 0;
int  sent_nr_2 = 0;
int  sent_nr_3 = 0;
int  sent_nr_4 = 0;
int  sent_nr_5 = 0;

//Variable RECIBIDA de la BASE DE DATOS
bool received_bool_1 = 0;
bool received_bool_2 = 0;
bool received_bool_3 = 0;
bool received_bool_4 = 0;
bool received_bool_5 = 0;
int  received_nr_1 = 0;
int  received_nr_2 = 0;
int  received_nr_3 = 0;
int  received_nr_4 = 0;
int  received_nr_5 = 0;
String received_text = "";


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////



//Almacena los caracteres recibidos en estas variables
char t1_from_ESP[5];  //Para tiempo desde la web
char d1_from_ESP[2];  //Para received_bool_2
char d2_from_ESP[2];  //Para received_bool_2
char d3_from_ESP[2];  //Para received_bool_3
char d4_from_ESP[2];  //Para received_bool_4
char d5_from_ESP[2];  //Para received_bool_5
char d9_from_ESP[6];  //Para received_nr_1
char d10_from_ESP[6]; //Para received_nr_2
char d11_from_ESP[6]; //Para received_nr_3
char d12_from_ESP[6]; //Para received_nr_4
char d13_from_ESP[6]; //Para received_nr_5
char d14_from_ESP[300]; //Para received_text 


//DEFINE PALABRAS CLAVE AQUÍ
const char keyword_OK[] = "OK";
const char keyword_Ready[] = "Ready";
const char keyword_no_change[] = "no change";
const char keyword_blank[] = "#&";
const char keyword_ip[] = "192.";
const char keyword_rn[] = "\r\n";
const char keyword_quote[] = "\"";
const char keyword_carrot[] = ">";
const char keyword_sendok[] = "SEND OK";
const char keyword_linkdisc[] = "Unlink";

const char keyword_t1[] = "t1";
const char keyword_b1[] = "b1";
const char keyword_b2[] = "b2";
const char keyword_b3[] = "b3";
const char keyword_b4[] = "b4";
const char keyword_b5[] = "b5";
const char keyword_n1[] = "n1";
const char keyword_n2[] = "n2";
const char keyword_n3[] = "n3";
const char keyword_n4[] = "n4";
const char keyword_n5[] = "n5";
const char keyword_n6[] = "n6";
const char keyword_doublehash[] = "##";


SoftwareSerial ESP8266(ESP8266_RX, ESP8266_TX);// rx tx



void setup(){// INICIO DE CONFIGURACIÓN

  lcd.init();                 //Iniciar la pantalla LCD
  lcd.backlight();            //Activar luz de fondo 
  
  //Modos de pines para ESP TX/RX
  pinMode(ESP8266_RX, INPUT);
  pinMode(ESP8266_TX, OUTPUT);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);

  pinMode(Potentiometer_1, INPUT);
  pinMode(Potentiometer_2, INPUT);
  pinMode(Potentiometer_3, INPUT);
  pinMode(Potentiometer_4, INPUT);

  pinMode(switch1, INPUT);
  pinMode(switch2, INPUT);
  pinMode(switch3, INPUT);
    
  
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  digitalWrite(LED5,LOW);
  

  
  ESP8266.begin(9600);//velocidad de transmisión predeterminada para ESP
  ESP8266.listen();//no es necesario a menos que se utilicen otras instancias seriales de software
  Serial.begin(9600); //para estado y depuración
  
  delay(2000);//retraso antes de empezar
  setup_ESP();// Ve a configurar la ESP
 
}




void loop(){

  sent_nr_1 = analogRead(Potentiometer_1);
  sent_nr_1 = analogRead(Potentiometer_2);
  sent_nr_1 = analogRead(Potentiometer_3);
  sent_nr_1 = analogRead(Potentiometer_4);
  
  sent_bool_1 = digitalRead(switch1);
  sent_bool_2 = digitalRead(switch2);
  sent_bool_3 = digitalRead(switch3);
  
  send_to_server_1(); 
  digitalWrite(LED1,received_bool_1);
  digitalWrite(LED2,received_bool_2); 
  digitalWrite(LED3,received_bool_3); 
  digitalWrite(LED4,received_bool_4); 
  digitalWrite(LED5,received_bool_5);  

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("N1: "); lcd.print(received_nr_1); lcd.print("  N2: "); lcd.print(received_nr_2);
  lcd.setCursor(0,1);
  lcd.print("N3: "); lcd.print(received_nr_3); lcd.print("  N4: "); lcd.print(received_nr_4);    
  delay(1000);//5 segundos entre intentos


  /*
  send_to_server_2();
  digitalWrite(LED1,received_bool_1);
  digitalWrite(LED2,received_bool_2); 
  digitalWrite(LED3,received_bool_3); 
  digitalWrite(LED4,received_bool_4); 
  digitalWrite(LED5,received_bool_5);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("N1: "); lcd.print(received_nr_1); lcd.print("  N2: "); lcd.print(received_nr_2);
  lcd.setCursor(0,1);
  lcd.print("N3: "); lcd.print(received_nr_3); lcd.print("  N4: "); lcd.print(received_nr_4);  
  delay(1000);
  send_to_server_3();
  digitalWrite(LED1,received_bool_1);
  digitalWrite(LED2,received_bool_2); 
  digitalWrite(LED3,received_bool_3); 
  digitalWrite(LED4,received_bool_4); 
  digitalWrite(LED5,received_bool_5);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("N1: "); lcd.print(received_nr_1); lcd.print("  N2: "); lcd.print(received_nr_2);
  lcd.setCursor(0,1);
  lcd.print("N3: "); lcd.print(received_nr_3); lcd.print("  N4: "); lcd.print(received_nr_4);  
  delay(1000);
  send_to_server_4();
  digitalWrite(LED1,received_bool_1);
  digitalWrite(LED2,received_bool_2); 
  digitalWrite(LED3,received_bool_3); 
  digitalWrite(LED4,received_bool_4); 
  digitalWrite(LED5,received_bool_5);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("N1: "); lcd.print(received_nr_1); lcd.print("  N2: "); lcd.print(received_nr_2);
  lcd.setCursor(0,1);
  lcd.print("N3: "); lcd.print(received_nr_3); lcd.print("  N4: "); lcd.print(received_nr_4);   
  delay(1000);
  */

  
  send_to_server_5();
  digitalWrite(LED1,received_bool_1);
  digitalWrite(LED2,received_bool_2); 
  digitalWrite(LED3,received_bool_3); 
  digitalWrite(LED4,received_bool_4); 
  digitalWrite(LED5,received_bool_5);
  

  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(received_text);
  
  delay(1000);

}//Fin del bucle principal
