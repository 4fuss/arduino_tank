//using keybord input (w,s) to control tank caterpillar
//motor is controlled by H-Bridge

//motor
const int caterpillar1 = 2;
const int caterpillar2 = 3;
const int caterpillarPower = 9;
const int turret1 = 4;
const int turret2 = 5;
const int turretPower = 10;

//keybord
unsigned long serialIdle = 0; 
unsigned long lastHit = 0; //resets while getting a byte
byte inByte =0;
byte lastByte =0;


void setup(){
  Serial.begin(9600);
  pinMode(caterpillar1, OUTPUT);
  pinMode(caterpillar2, OUTPUT);
  pinMode(caterpillarPower, OUTPUT);
  pinMode(turret1, OUTPUT);
  pinMode(turret2, OUTPUT);
  pinMode(turretPower, OUTPUT);
}

void loop(){
  if(Serial.available()){    
    inByte = Serial.read(); 
    if (inByte != lastByte) {
      switch (inByte) {
        case 119:
          caterpillar(1); //move caterpillar forward
          break;
        case 115:
          caterpillar(0); //move caterpillar back
          break;
        case 97:
          turret(0); //turn turret left
          break;
        case 100:
          turret(1); //turn turret right
          break;
      }
    }
    lastByte = inByte;    
    serialIdle = 0;
    lastHit = millis();
  }else{
    if (lastByte > 0){
      serialIdle = millis() - lastHit;
    }
  }  
  if (serialIdle > 500){
    digitalWrite(caterpillarPower, LOW); //stop caterpillar
    digitalWrite(turretPower, LOW); //stop turret 
    lastByte = 0;
    serialIdle = 0;
  }    
}

void caterpillar(int ff){
  digitalWrite(caterpillarPower, HIGH);
  if (ff == 1) {
    digitalWrite(caterpillar1, HIGH);
    digitalWrite(caterpillar2, LOW);    
  }else{
    digitalWrite(caterpillar1, LOW);
    digitalWrite(caterpillar2, HIGH);    
  }
}

void turret(int side){
  digitalWrite(turretPower, HIGH);
  if (side == 1){
    digitalWrite(turret1, HIGH);
    digitalWrite(turret2, LOW);
  }else{
    digitalWrite(turret1, LOW);
    digitalWrite(turret2, HIGH);    
  }
}





