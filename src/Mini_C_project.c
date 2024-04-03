/*
 ============================================================================
 Name        : Mini_C_project.c
 Author      : Ibraam Wahba
 Description : Vehicle Control system
 ============================================================================
 */

#include <stdio.h>

#define TurnOnTheVehicleEngine 'a'
#define TurnOffTheVehicleEngine 'b'
#define QuitTheSystem 'c'
#define red 'R'
#define green 'G'
#define orange 'O'

enum EngineState  {off,on};
enum choices  {TurnOffTheEngine=1,TheTrafficLight,TemperatureSensor,EngineTemperatureSensor};

/*Functions declaration*/
void Ask();
void DisplaySensorsMenu();
void RoomTemperature(int* sensor,char* AC,int* temp);
void SetTheTrafficLightColor(int* speed);
void EngineTemperature(char* TempController,int* EngineTempSensor,int* EngineTemp);
void DisplayTheCurrentVehicleState();

/*Global variables*/
char Engine = off ,EngineTemperatureController=off;
int VehicleSpeed = 0;
int RoomTemp = 0,EngineTemp=0;
char AC_State = off;
unsigned char counter = 0;
int main(void)
{
	char UserChoice = 0;
	int EngineTempSensor=0;
	int TemperatureSensorRead = 25;
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	while(1)
	{
		while(!(UserChoice == QuitTheSystem ||UserChoice == TurnOffTheVehicleEngine ||UserChoice == TurnOnTheVehicleEngine))
		{
			Ask();
			scanf(" %c",&UserChoice);
			if(UserChoice == QuitTheSystem)
			{
				printf("\n Quitting the System");
				return 0 ;   /*Quit program*/
			}
			else if(UserChoice ==TurnOffTheVehicleEngine)
			{
				printf("\n Turning off the vehicle engine\n");
				Engine = off ; /*Turn off engine */
				UserChoice = 0;
			}
			else if(UserChoice ==TurnOnTheVehicleEngine)
			{
				printf("\n Turning on the vehicle engine\n");
				Engine = on ; /*Turn on engine*/
				UserChoice = 0;
				while(Engine == on)
				{
					while(!(UserChoice == TurnOffTheEngine ||UserChoice == TheTrafficLight ||UserChoice == TemperatureSensor||UserChoice == EngineTemperatureSensor))
					{
						UserChoice = 0;
						DisplaySensorsMenu();
						scanf(" %d",&UserChoice);
					}
					if(UserChoice == TurnOffTheEngine)
					{
						printf("\n Turning off the vehicle engine\n");
						Engine = off ;
						UserChoice = 0;
						//	break;
					}
					else if(UserChoice == TheTrafficLight)
					{
						SetTheTrafficLightColor(&VehicleSpeed);
						UserChoice = 0;
						counter ++;
					}
					else if(UserChoice == TemperatureSensor)
					{
						RoomTemperature(&TemperatureSensorRead,&AC_State,&RoomTemp);
						UserChoice = 0;
						counter ++;
					}
					else if(UserChoice == EngineTemperatureSensor)
					{
						EngineTemperature(&EngineTemperatureController,&EngineTempSensor,&EngineTemp);
						UserChoice = 0;
						counter ++;
					}
					else
					{
						printf("\nPlease enter a valid choice\n");
						UserChoice = 0;
					}


					if(VehicleSpeed==30)
					{
						AC_State = on;
						RoomTemp = RoomTemp*(5/4) +1 ;
						EngineTemperatureController = on;
						EngineTemp = EngineTemp*(5/4) +1 ;
					}
					if(counter == 3)
					{
						counter = 0;
						DisplayTheCurrentVehicleState();
					}
				}
			}
			else
			{
				printf("\nPlease enter a valid choice\n");
			}
		}
	}

	return 0;
}

void Ask()
{
	printf("\na. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
}
void DisplaySensorsMenu()
{
	printf("\n1. Turn off the engine\n");
	printf("2. Set the traffic light color\n");
	printf("3. Set the room temperature (Temperature Sensor)\n");
	printf("4. Set the engine temperature (Engine Temperature Sensor)\n");

}
void SetTheTrafficLightColor(int* speed)
{
	char Color = 0;

	while(!(Color == green ||Color == orange ||Color == red))
	{
		printf("\n Please enter the traffic light color\nG for green\nO for orange\nR for red");
		scanf(" %c",&Color);
		if(Color == green)
		{
			*speed = 100 ; /*Vehicle speed = 100 KM/hour*/
		}
		else if(Color == orange)
		{
			*speed = 30 ; /*Vehicle speed = 30 KM/hour*/
		}
		else if(Color == red)
		{
			*speed = 0 ; /*Vehicle speed = 0 KM/hour*/
		}
		else
		{
			printf("\nPlease enter a valid choice\n");
		}

	}
}
void RoomTemperature(int* sensor,char* AC,int* temp)
{
	printf("\nPlease enter temperature sensor read. ");
	scanf(" %d",(int*)sensor);
	if(*sensor<10)
	{
		*AC = on ;
		*temp = 20 ;
	}
	else if(*sensor>30)
	{
		*AC = on ;
		*temp = 20 ;
	}
	else
	{
		*AC = off ;
	}
}
void EngineTemperature(char* TempController,int* EngineTempSensor,int* EngineTemp)
{
	printf("\n Please enter engine temperature\n");
	scanf(" %d",(int*)EngineTemp);
	if(*EngineTempSensor <100)
	{
		*TempController = on;
		*EngineTemp = 125;
	}
	else if(*EngineTempSensor >150)
	{
		*TempController = on;
		*EngineTemp = 125;
	}
	else
	{
		*TempController = off;
	}
}
void DisplayTheCurrentVehicleState()
{
	printf("Engine state is: ");
	if(Engine==on)
	{
		printf("ON\n");
	}
	else{printf("OFF\n");}

	printf("AC state is: ");
	if(AC_State==on)
	{
		printf("ON\n");
	}
	else{printf("OFF\n");}

	printf("Vehicle Speed is: %d KM/hour\n",VehicleSpeed);
	printf("Room Temperature is: %d C\n",RoomTemp);

	printf("Engine Temperature Controller State is: ");
	if(EngineTemperatureController==on)
	{
		printf("ON\n");
	}
	else{printf("OFF\n");}

	printf("Engine Temperature Controller State is %d C ",EngineTemp);

}
