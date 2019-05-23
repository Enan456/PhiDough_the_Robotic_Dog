// SparkFun CCS811 Arduino Library - Version: Latest
#include <SparkFunCCS811.h>

//breadboarded stuff
#define dir 5
#define EN 12

//Declare pin functions Front
#define fstp 4
#define fMS1 8
#define fMS2 11

//Declare pin functions center
#define cstp 3
#define cMS1 7
#define cMS2 10

//Declare pin functions back
#define bstp 2
#define bMS1 6
#define bMS2 9

//Declare variables for functions
int x;
int y;
int state;
int stepper;

//air quality (aq)
#define CCS811_ADDR 0x5B //Default I2C Address
//#define CCS811_ADDR 0x5A //Alternate I2C Address
CCS811 myCCS811(CCS811_ADDR);
int aCO2;
int aVOC;

void setup()
{
    //front
    pinMode(fstp, OUTPUT);
    pinMode(fMS1, OUTPUT);
    pinMode(fMS2, OUTPUT);
    //center
    pinMode(cstp, OUTPUT);
    pinMode(cMS1, OUTPUT);
    pinMode(cMS2, OUTPUT);
    //back
    pinMode(bstp, OUTPUT);
    pinMode(bMS1, OUTPUT);
    pinMode(bMS2, OUTPUT);
    resetEDPins(); //Set step, direction, microstep and enable pins to default states
    myCCS811.begin();
    if (myCCS811.dataAvailable())
    {
        myCCS811.readAlgorithmResults();
        aCO2 = myCCS811.getCO2();
        aVOC = myCCS811.getTVOC();
    }

    //led
    digitalWrite(LED_BUILTIN, HIGH);
}

//Main loop
void loop()
{
    // int tempCO2 = 0;
    // int tempVOC = 0;
    // digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
    // if (myCCS811.dataAvailable())
    // {
    //     myCCS811.readAlgorithmResults();
    //     tempCO2 = myCCS811.getCO2();
    //     tempVOC = myCCS811.getTVOC();
    //     if (aCO2 < tempCO2 || aVOC < tempVOC)
    //     {
    //         blink();
    //     }
    // }
    // StepForwardDefault();
    // resetEDPins();
    blink();
}

//Default microstep mode function
void StepForwardDefault()
{
    digitalWrite(dir, LOW);   //Pull direction pin low to move "forward"
    for (x = 1; x < 500; x++) //Loop the forward stepping enough times for motion to be visible
    {
        digitalWrite(fstp, HIGH); //Trigger one step forward
        digitalWrite(cstp, HIGH); //Trigger one step forward
        digitalWrite(bstp, HIGH); //Trigger one step forward
        delay(1);
        digitalWrite(fstp, LOW); //Pull step pin low so it can be triggered again
        digitalWrite(cstp, LOW); //Pull step pin low so it can be triggered again
        digitalWrite(bstp, LOW); //Pull step pin low so it can be triggered again
        delay(1);
    }
}
//Reset Easy Driver pins to default states
void resetEDPins()
{
    digitalWrite(dir, LOW);
    digitalWrite(EN, HIGH);

    digitalWrite(fstp, LOW);
    digitalWrite(fMS1, LOW);
    digitalWrite(fMS2, LOW);

    digitalWrite(cstp, LOW);
    digitalWrite(cMS1, LOW);
    digitalWrite(cMS2, LOW);

    digitalWrite(bstp, LOW);
    digitalWrite(bMS1, LOW);
    digitalWrite(bMS2, LOW);
}

void blink()
{
    for (x = 1; x < 500; x++)
    {
        digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
        delay(100);                      // wait for a second
        digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
        delay(100);                      // wait for a second
    }
}
