#ifndef __SHARP_DUST_H
#define __SHARP_DUST_H

#define SAMPLING_TIME	280
#define DELTA_TIME		40
#define SLEEP_TIME		9680
#define PAUSE	 200
#define NB_MEAS 10 

class SharpDustClass
{
	private:
		int ledPin;			//Digital pin for LED power
		int measurePin; 	//Analog pin for measurement
		float range ;       // external voltage ADC
		
	public:
		SharpDustClass();
		void begin(int led, int mea , float rang );
		float measure(void);
		float fmap(float x, float in_min, float in_max, float out_min, float out_max);
};

extern SharpDustClass SharpDust;
#endif	//__SHARP_DUST_H