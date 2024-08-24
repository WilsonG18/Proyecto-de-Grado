

//Esta función busca una palabra clave recibida del ESP
// const char keyword1[] = la palabra clave que esta función buscará y devolverá '1' cuando la encuentre
// int key_size = tamaño de esa palabra clave - sizeof()
// int timeout_val - tiempo de espera si no se encuentra la palabra clave (en milisegundos 5000=5seg)
// modo byte - si es '1', esta función guardará cada byte recibido en 'scratch_data_from_ESP[]' con una longitud de 'scratch_length' - útil para analizar entre palabras clave
boolean read_until_ESP(const char keyword1[], int key_size, int timeout_val, byte mode){
  timeout_start_val=millis();//para el tiempo de espera
  char data_in[20];//este es el buffer - si la palabra clave es más larga que 20, entonces incremente esto
  int scratch_length=1;//la longitud de la matriz de datos scratch
  key_size--;//ya que vamos a obtener un carácter adicional de sizeof()
 
 // RELLENAR EL BUFFER
 for(byte i=0; i<key_size; i++){//Solo necesitamos un buffer tan largo como la palabra clave
  
            //control de tiempo
            while(!ESP8266.available()){//esperar hasta que se envíe un nuevo byte desde el ESP: una buena manera de mantenerse en sintonía con el puerto serie
              if((millis()-timeout_start_val)>timeout_val){//Si no sucede nada dentro del período de tiempo de espera, salga de aquí
                Serial.println("timeout 1");
                return 0;//esto finalizará la función
              }//se acabó el tiempo
            }// while !avail
  
    data_in[i]=ESP8266.read();// guarda el byte en el buffer 'data_in[]
    //Serial.write(data_in[i]);
    if(mode==1){//Esto guardará todos los datos en scratch_data_from
      scratch_data_from_ESP[scratch_length]=data_in[i];//comienza en 1
      scratch_data_from_ESP[0]=scratch_length;// [0] se utiliza para contener la longitud de la matriz
      scratch_length++;//incrementar la longitud
    }//modo 1
    
  }//for i
  
//EL BÚFER ESTÁ LLENO, ASÍ QUE COMIENZA A INTRODUCIR DATOS NUEVOS Y A SALIR DATOS ANTIGUOS
  while(1){//Permanezca aquí hasta que se encuentre la palabra clave o se agote el tiempo de espera

    //recorre todo el buffer y busca la palabra clave
    //esta comprobación está aquí, por si acaso lo primero que salió del ESP fue la palabra clave, lo que significa que el buffer en realidad estaba lleno con la palabra clave
     for(byte i=0; i<key_size; i++){
       if(keyword1[i]!=data_in[i])//Si no coincide, salga de la búsqueda ahora
       break;//Sal de aquí
       if(i==(key_size-1)){//Hemos llegado hasta el final de la palabra clave sin romperla, ¡debe ser una coincidencia!
       return 1; //¡Devuelve un 1 y sal de aquí!
       }//if
     }//for byte i
     

    //comienza a rodar el buffer
    for(byte i=0; i<(key_size-1); i++){// tamaño de clave 1 porque todo se desplaza - ver siguiente línea
      data_in[i]=data_in[i+1];// entonces los datos en 0 se convierten en los datos en 1, y así sucesivamente... el último valor es donde colocaremos los nuevos datos
  }//for
 
         
           //control de tiempo
            while(!ESP8266.available()){// lo mismo que se hizo en el buffer
              if((millis()-timeout_start_val)>timeout_val){
                Serial.println("timeout 2");
                return 0;
              }//timeout
            }// while !avail
    
   
   
    data_in[key_size-1]=ESP8266.read();//guarda los nuevos datos en la última posición del buffer

    
    //Serial.write(data_in[key_size-1]);

    
      if(mode==1){//Continuar guardando todo si esto está configurado
      scratch_data_from_ESP[scratch_length]=data_in[key_size-1];
      scratch_data_from_ESP[0]=scratch_length;
      scratch_length++;

      //Serial.write(scratch_data_from_ESP[0]);
    }//mode 1
    
    // SOLO PARA DEPURACIÓN
//if(ESP8266.overflow())
//Serial.println("*OVER");
    
    
  }//while 1

  
  
  
}//leer hasta ESP
