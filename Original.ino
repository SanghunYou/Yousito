//Pines para el motor
int in1 = 3;   
int in2 = 4;

//Pines de los botones
int sube= 12;  //subida
int baja= 9;  //bajada
int autom=13; //automatico

int var_sube;
int var_baja;
int var_autom;

//Pin del fin de carrera
int paro1=7;
int paro2=8;

int var_paro1;
int var_paro2;

//Pin de los infrarrojo
int infra1= 5;
int infra2= 10;

int var_infra1;
int var_infra2;

int cambio1=1;
int cambio2=1;
int protocolo=1;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(sube,INPUT);
  pinMode(baja,INPUT);
  pinMode(autom,INPUT);

  pinMode(paro1,INPUT);
  pinMode(paro1,INPUT);

  pinMode(infra1,INPUT);
  pinMode(infra2,INPUT);

  Serial.begin(9600);


}

void ciclo()
{
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

void alto()
{
  protocolo==1;
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(300);
  if (protocolo==1)
    {
      Serial.println("OBJETO DETECTADO");
      delay(1000);
      Serial.println("PARO DE EMERGENCIA");  
      delay(1000);
      protocolo=0;
    }
  else if (var_paro1==1 && cambio1==1)
    {
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

void loop() {
  var_sube=digitalRead(sube);
  var_baja=digitalRead(baja);
  var_autom=digitalRead(autom);

  var_paro1=digitalRead(paro1);
  var_paro2=digitalRead(paro2);  

  var_infra1=digitalRead(infra1);  
  var_infra2=digitalRead(infra2);  
  
  
  
  // Modo Manual
//Subida
if ((var_paro1==1) && (var_sube==0))
{
  //Sube
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(300);
}
else
  {
  digitalWrite(in1, LOW) ;
  digitalWrite(in2, LOW);
  delay(300);
  }

//Bajada
if ((var_paro2==1) && (var_baja==0))
  {
    //Baja
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(300);
  } 
else
  {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(300);
  }



  // Modo automatico
if (var_autom==0)
{
  if (var_infra1==1)
  {
    ciclo();
  }
  else
  {
    alto();
  } 
}


}

