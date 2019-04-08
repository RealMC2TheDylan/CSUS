#include <Sabertooth.h>

Sabertooth ST(128); 

int TickR=0;
int TickL=0;
int power = 0;
int t;
int t1;
int e;
int p=0;
                                        
void setup()
{
  SabertoothTXPinSerial.begin(9600); // 9600 is the default baud rate for Sabertooth packet serial.
  ST.motor(1,0);
  ST.motor(2,0);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  attachInterrupt(digitalPinToInterrupt(3),countL,FALLING);
  t=millis();
}

/*speed
 * 125 161/500
 * 120 167/500
 * 
 * 110 181/500
 * 
 * 100 200/500
 * 95  210/500
 * 90  222/500
 * 85  235/500
 * 80  251/500
 * 75  267/500
 * 70  287/500
 * 65  310/500
 * 60  336/500
 * 55  367/500
 * 50  405/500
 * 45  450/500
 * 40  510/500
 * 35  585/500
 * 30  685/500
 * 25  830/500
 * 20 1050/500
 * 15 1420/500
 * 10 2230/500
 * 5  5000/500
 *  
 */


void loop()
{
  ST.motor(2,p);
  Serial.print("\ne =");
  Serial.print(e);
  while(p<100)
  {
    ST.motor(1,p);
    p++;
    }
  while(p>0)
  {
    ST.motor(1,p);
    p--;
    }
    delay(5000);
}

void spd()
{
  t1=millis();
  e=t1-t;
  t=t1;
  }


void countL()
{
  TickL++;
  if(TickL%500==0)
  {
    spd();
    }
  }
