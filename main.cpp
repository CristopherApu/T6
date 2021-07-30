/*T6*/


// Agregamos variables
	
	// TMP36
	int sensorRead = 0;
	float temp = 0.0;
	// DC
	const int MotorPin1 = 5;
	const int MotorPin2 = 6;
	// Potenciometro
	int pot;
	int setPoint;
	int error;
	int potReq;
	// HC-SR04
	int trigger = 9;
	int echo = 8;
	float t_d_e;
    float d;


void setup() {
  
// Comunicación serial
  Serial.begin(9600);
	// DC
  	pinMode(MotorPin1, OUTPUT);
  	pinMode(MotorPin2, OUTPUT);
  	pinMode(potReq, OUTPUT);
  	// HC-SR04
  	pinMode(trigger, OUTPUT);
  	pinMode(echo, INPUT);
  
}


void loop() {
	// Calculamos la distancia
    digitalWrite        (trigger, LOW);
    delay               (2);
    digitalWrite        (trigger, HIGH);
    delay               (10);
    digitalWrite        (trigger, LOW);
    t_d_e               = pulseIn (echo, HIGH);
    d                   = (t_d_e / 2) / 29.15;
    // Escalamos nuestro potenciometro a temperatura °C
  	sensorRead = analogRead(3);
  	pot = analogRead(1);
  	setPoint = (pot / 102.3) + 20;
  	//Obtenemos la temperatura con la siguiente formula:
  	temp = ( sensorRead * (500.0 / 1023.0) ) - 50.0;
  	// Calculamos lo que falta para llegar al setPoint
  	error = setPoint - temp;
  	// Limitamos la ejecucion del motor
  	if (error > 0){
 	 digitalWrite(MotorPin1, LOW);
 	 digitalWrite(MotorPin2, LOW);
     //Serial.println("La temperatura es demasiado baja");
    } else {
	// Indicamos la potencia requerida
  	potReq = 20 * abs(error);
	// Nos aseguramos que 255 sea el máximo
  	if (potReq > 255){
  		potReq = 255;
   	}
  	// Aseguramos la distancia del aparato
  	if (d < 15){
 	 	potReq = 0;
 	} else {
 		// Encendemos el ventilador
  		digitalWrite(MotorPin1, HIGH);
 		digitalWrite(MotorPin2, LOW);
 		analogWrite(11, potReq);
    }
   }
  	// Imprimimos por pantalla algunos datos
  	Serial.print("| ");	
  	Serial.print(d);
  	Serial.print(" cm");
  	Serial.print(" | ");
  	Serial.print(temp);
  	Serial.print(" grados en el ambiente");
  	Serial.print(" | ");
  	Serial.print(setPoint);
  	Serial.print(" grados requeridos");
  	Serial.print(" | ");	
  	Serial.print(potReq);
  	Serial.println(" potencia del ventilador |");
  	delay(500);
}
