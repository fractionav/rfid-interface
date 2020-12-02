#include"rfid1.h"

// create a variable type of RFID1
RFID1 rfid;

// Setup pins used for MISO
int PINS[] = {31,33,35,37,39,41,43,45};


void setup()
{
  Serial.begin(115200); //initialize the serial  

  Serial.println("start;");
}



void loop()
{
  String slot[8];
  String temp;


  for (int i=0;i<8;i++)
  {
    slot[i]=readCard(PINS[i]);
   
    if(slot[i].length() < 0)  //ensure returned value is not blank
    {
      slot[i] = "00000000";   //otherwise drop an all zero value in
    }
  
    if(i<7)
    {
      temp = temp + slot[i] + ",";
    }
    else
    {
      temp = temp + slot[i] + ";";
    }
  
  }

//Output the result
  Serial.println(temp);
  
}


String readCard(int PIN){

  String temp;
  uchar serNum[5]; // array to store your ID
  uchar status;
  uchar str[MAX_LEN];

  rfid.begin(2, 4, 5, PIN, 3, 6);//rfid.begin(IRQ_PIN,SCK_PIN,MOSI_PIN,MISO_PIN,NSS_PIN,RST_PIN)
  delay(10);
  rfid.init();
   
// Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK)
  {
    return("ffffffff");
  }
  
//Prevent conflict, return the 4 bytes Serial number of the card
  status = rfid.anticoll(str);

  if (status == MI_OK)
  {
    memcpy(serNum, str, 5);
    for(int i=0; i<4; i++)
    {
      char buf[3];
      sprintf (buf, "%02x", serNum[i]);
      temp = temp + buf;  
    }
    return(temp);
  }
  else
  {
    return("conflict");
  }



  delay(10);

  rfid.halt(); //command the card   +into sleep mode

}
