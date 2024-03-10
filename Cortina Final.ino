//////////////////////////////////Pines//////////////////////////////////
//Pines para el motor
int in1 = 1;   
int in2 = 2;

//Pines de los botones
int sube= 3;  //subida
int baja= 4;  //bajada
int autom=5; //automatico

//Pin del fin de carrera
int paro1=6;
int paro2=7;

//Pin de los infrarrojo
int infra1= 8;
int infra2= 9;

//Pin de usuario
int usuario=10;

//Pin de pantalla


//////////////////////////////////Variables//////////////////////////////////
//Define tus variables

int var_sube;
int var_baja;
int var_autom;

int var_paro1;
int var_paro2;

int var_infra1;
int var_infra2;

int var_usuario;

int cambio1=1;
int cambio2=1;
int protocolo=1;

int alarma=0;

//////////////////////////////////void Setup//////////////////////////////////
void setup() {
  //Establece la velocidad de conexión con el monitor serie
  Serial.begin(9600);

  //Establece el pin del sensor como entrada
  pinMode(sube,INPUT);
  pinMode(baja,INPUT);
  pinMode(autom,INPUT);

  pinMode(paro1,INPUT);
  pinMode(paro1,INPUT);

  pinMode(infra1,INPUT);
  pinMode(infra2,INPUT);

  pinMode(usuario,INPUT);

  //Establece la interrupción para el sensor con la siguiente sintaxis:
  //attachInterrupt(digitalPinToInterrupt(pin_del_sensor), función_que_debe_hacer, RISING);
  attachInterrupt(digitalPinToInterrupt(infra1), protocol, CHANGE);
  attachInterrupt(digitalPinToInterrupt(infra2), protocol, CHANGE);

  //Establece los pines del motor como salida
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}



///////////////////////////////////función que realiza la acción de la interrupción//////////////////////////////////
void protocol()
{
  //Inserta tu código aqui de lo que quieres que se realice cuando se detecte un obstaculo
  protocolo==1;
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(300);
  if (protocolo==1)
    {
      alarma=alarma+1;
      delay(7000);
      Serial.println("OBJETO DETECTADO");
      delay(1000);
      Serial.println("PARO DE EMERGENCIA");  
      delay(1000);
      protocolo=0;
      cambio1=1;
    }
  else if (var_paro1==1 && cambio1==1)
    {
      //Sube
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      delay(300);
    }
  else
    { 
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      delay(300);
      cambio1=0;
    }

}



//////////////////////////////////leer tipo de usuario//////////////////////////////////
int usu_ario()
{
  //lee el pin de operador y de supervisor
  var_usuario=digitalRead(usuario);

  //Implementa un condicional para leer el tipo de usuario
  if(var_usuario == 0)
  {
    Serial.println("Modo Supervisor");
    return 0;
  }
  else if(var_usuario== 1)
  {
    Serial.println("Modo Operador");
    return 1;
  }
  else
  {
    Serial.println(" ");
    return 2;
  }
}



//////////////////////////////////Modo Manual//////////////////////////////////
void manual()
{
  Serial.println("Modo Manual");

  //lee los pines para subir y bajar la cortina
  var_sube=digitalRead(sube);
  var_baja=digitalRead(baja);
  //Paro de carrera
  var_paro1=digitalRead(paro1);
  var_paro2=digitalRead(paro2);  

  //Comenzamos con los motores apagados
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  //Creamos un condicional para detectar el boton de subir y el boton de bajar
  if(var_paro1 == 1 && var_sube == 0)
  {
    //Sube
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(300);
  }
  else if(var_paro2 == 1 && var_baja == 0)
  {
    //Baja
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(300); 
  }
}


//////////////////////////////////Modo automático//////////////////////////////////
void automatico()
{
  Serial.println("Modo Automatico");

  if (var_paro1==1 && cambio1==1)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(300);
  }
  else
  { 
    cambio1=0;
    cambio2=1;
    delay(500);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(300);
    if (var_paro2==1 && cambio2==1)
    {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(300);
    }
    else
    {
    cambio2=0;
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(300);
    cambio1=1;
    }
  }

}

//////////////////////////////////Modo operador//////////////////////////////////
void modo_operador()
{
  Serial.println("Modo Operador");
  delay(1000);
  //Leer los botones de manual y automático
  var_autom = digitalRead(autom);

  //Crear un condicional para realizar el modo manual o el modo automático
  if(var_autom == 1)
  {
    manual(); 
  }
  else if(var_autom == 0)
  {
    automatico();
  }
}


//////////////////////////////////Modo supervisor//////////////////////////////////
void modo_supervisor()
{
  Serial.println("Modo Operador");
  delay(1000);
  Serial.print("Numero de alarmas: ");
  delay(1000);
  Serial.println(alarma);
  delay(1000);
  modo_operador();
}

//////////////////////////////////void loop//////////////////////////////////
void loop() {
  //declarar una variable tipo entero que lea el tipo de usuario
  int tipo_usuario;

  tipo_usuario = usu_ario();
  //Serial.print("Tipo de usuario: ");
  //Serial.println(variable_tipo_usuario);

  //Crear un condicional para seleccionar operador o supervisor
  if(tipo_usuario == 0)
  {
    modo_supervisor();
  }
  else if(tipo_usuario == 1)
  {
    modo_operador();
  }

}
