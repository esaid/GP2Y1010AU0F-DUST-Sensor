#include "Arduino.h"
#include "SharpDust.h"
#include "pins_arduino.h"

SharpDustClass::SharpDustClass()
{
}

void SharpDustClass::begin(int led, int mea , float rang )
{
	ledPin = led;
	measurePin = mea;
	range = rang ;
	pinMode(measurePin, INPUT);

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, HIGH);
}

float SharpDustClass::measure(void)
{
	
	float calcVoltage = 0;
	float average  = 0;
	unsigned long sum = 0 ;
	unsigned int voMeasured[NB_MEAS]  ;
	
  for(int i=0; i< NB_MEAS; i++) {
	digitalWrite(ledPin, LOW);
	delayMicroseconds(SAMPLING_TIME);
	
	voMeasured[i] = analogRead(measurePin)  ;
    sum += voMeasured[i] ;
	Serial.println(voMeasured[i]);
	Serial.println(sum) ;
	delayMicroseconds(DELTA_TIME);
	
	digitalWrite(ledPin, HIGH);
	delayMicroseconds(SLEEP_TIME);
	delay (PAUSE) ;
  } 
	average = sum / NB_MEAS ;
	Serial.print("  Average : ") ;
    Serial.println(average) ;
  
	calcVoltage = fmap(average, 0, 1023, 0.0, range );
	// courbe de la droite selon le constructeur y = 5.8 x + 0.6 
    // avec x = en volts et y en mg/m3  soit x = (y - 0.6) / 5.8
	if (calcVoltage < 0.6 ) calcVoltage = 0.6 ;
    Serial.print("  calcVoltage : ") ;
    Serial.println(calcVoltage) ; 	
	calcVoltage = (calcVoltage - 0.6) / 5.8 ;
	
	//return 0.17 * calcVoltage - 0.1;
	return calcVoltage*1000 ;
}


float SharpDustClass::fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


SharpDustClass SharpDust;