#include "Arduino.h"
#include "controles.h"
#include "lm35.h"

float tempPadrao;
float ganho = 5;
int manual_HEAT;
int manual_FAN;
int ganho_heat    = 0;
int ganho_fan     = 0;
int estado_heat   = 0;
int estado_fan    = 0;
int estado_driver = 0;

void inicia_controlador()
{
  tempPadrao  = 25.0;
  manual_HEAT = 50;
  manual_FAN  = 50;
  pinMode(HEAT,   OUTPUT);
  pinMode(FAN,    OUTPUT);
  pinMode(ENABLE, OUTPUT);
  analogWrite (HEAT,   0);
  analogWrite (FAN,    0);
  digitalWrite(ENABLE, 0);
}

void estado_atual()
{
  if (tempPadrao > temperatura)
  {
    estado_heat = 1;
    estado_fan  = 0;
  }
  else if (tempPadrao < temperatura)
  {
    estado_heat = 0;
    estado_fan  = 1;
  }
  else
  {
    estado_heat = 0;
    estado_fan  = 0;
  }
}

void automatico_heatpwm()
{
	ganho_heat = (tempPadrao - temperatura) * ganho;
	if (ganho_heat > HEAT_MAX)
	{
		ganho_heat = HEAT_MAX;
	}
	analogWrite(HEAT, ganho_heat);
	analogWrite(FAN , 0);
}

void automatico_fanpwm()
{
	ganho_fan = (tempPadrao + temperatura) * ganho;
	if (ganho_fan < FAN_MIN)
	{
		ganho_fan = FAN_MIN;
	  analogWrite(FAN , ganho_fan);
	}
	else if (ganho_fan > FAN_MAX)
	{
		ganho_fan = FAN_MAX;
	  analogWrite(FAN , ganho_fan);
	}
	else
	{
	  analogWrite(FAN, ganho_fan);
	}
	analogWrite(HEAT, 0);
}
