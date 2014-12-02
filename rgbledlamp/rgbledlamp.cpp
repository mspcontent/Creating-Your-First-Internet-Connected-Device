//Set the commonType variable based on your RGB LED type
// 0 = Common Cathode
// 1 = Common Anode
int commonType = 1;

//Set the pin numbers that will be connected to the
//RGB LED's Red, Green and Blue leads
//If you connected your RGB LED legs to different pins
//update the values below.  Make sure to connect the 
//RGB LED legs to PWM capable pins: D0,D1,A0,A1,A4,A5,A6, or A7
int redPin = A7;
int grnPin = A6;
int bluPin = A5;

//We'll use the red, grn, and blu variables to represent
//the amount of each color we want to show:
//
//      0 = No color
//    255 = Full color
//  1-254 = Color proportional to value
// 
//We'll use "Pulse Width Modulation" (PWM) Capable pins 
//on the Spark Core to supply the appropriate voltages to the 
//pins based on the red,grn,and blue values.
int red = 0;
int grn = 0;
int blu = 0;

//Create a character array that will hold the r,g,b values
//This variable will be published via the spark cloud to
//allow the client web page to verify that the Spark is
//displaying the appropriate colors
char rgb[38];

//The updating flag will be used to prevent simultaneous
//executions of the setRgb function
bool updating = false;

//The mapValue(value) function maps the desired pin value 
//between 0 and 255 based on the //RGB LED "common" type 
//(common anode or common cathode).
//For Common Cathode RGB LEDs the pin voltage is the same 
//As the color value (color value 0 = PWM pin value 0, 255=255).  
//For Common Anode RGB LEDs, we need to invert the color 
//value (color value 0 = PWM pin value 255, 255=0)
int mapValue(int value) {

  //first make sure the incoming value is between 0 and 255
  value = min(max(value,0),255);

  //Then if the commonType is 1 (common anode) invert the value
  //by subtracting it from 255.   
  //For common cathode RGB LEDs, 0 = OFF, 255 = ON
  //For common anode RGB LEDs, 0 = ON and 255 = OFF
  value = (commonType == 0) ? value : 255-value;

  return value;
}

//The setRgbVariable function populates the rgb variable (declared above)
//that will be published via the Spark Cloud.  
void setRgbVariable() {
    //Create a JSON string with the r,g,b values in it
    String rgbJson = "{\"r\":\"" + String(red) + "\",\"g\":\"" + String(grn) + "\",\"b\":\"" + String(blu) + "\"}";
    //Then copy the string into the rgb variable that is published to the cloud
    rgbJson.toCharArray(rgb,38);
}

//The setRgb(command) function is the actual function that is called via
//the Internet to set the RGB color on the LED.  
//The "command" string argument is in the form of R,G,B
//Where 0 implies none of that color, and 255 implies all of that color.
//         0,0,0 = Black
//   255,255,255 = White
//       255,0,0 = Red
//       0,255,0 = Green
//     255,0,255 = Purple
//   128,128,128 = Gray
//           ... = etc.
int setRgb(String command) {

    //If another update is in progrees, abort the update
    //We only want to set one color at a time.  If multiple
    //calls to this function are made via the internet at the same 
    //time, only the very first one is run.  
    if(updating){
        //exit, and return 0 to the caller indicating failure
        return 0;
    }

    //Set the updating flag to true to prevent
    //another update from running while this one is still
    //in process.
    updating = true;

    //Get the length of the string, and find the location of the first and last commas
    int len = command.length();
    int firstComma = command.indexOf(',');
    int lastComma = command.lastIndexOf(',');

    //Check the values of the first and last comma positions
    //If they don't look appropriate, abort
    if(firstComma <= 0 || lastComma <= 0 || lastComma >= len) {
        //exit, and return 0 to the caller indicating failure
        return 0;
    }

    //Parse the rgb string values out of the command...
    String rStr = command.substring(0,firstComma);
    String gStr = command.substring(firstComma + 1,lastComma);
    String bStr = command.substring(lastComma + 1);

    //Convert the rgb string values to their integer values
    red = rStr.toInt();
    grn = gStr.toInt();
    blu = bStr.toInt();

    //Write the rgb integer values out to the RGB LED
    //This uses the mapValue(value) function to map the color
    //value to the appropriate PWM pin value based on the 
    //RGB LED type, Common Cathode or Common Anode.
    analogWrite(redPin,mapValue(red));
    analogWrite(grnPin,mapValue(grn));
    analogWrite(bluPin,mapValue(blu));

    //Update the rgb variable that is readable via the cloud
    setRgbVariable();

    //Report the rgb variable value to the serial monitor
    Serial.println(rgb);

    //Set the updating flag to false so the next update can run
    updating = false;

    //Return a 1 to the caller, indicating success
    return 1;
}

//The setup() method runs once at the beginning of the 
void setup() {

    //Set the redPin, grnPin, and bluPin pins as OUTPUT pins
    pinMode(redPin,OUTPUT);
    pinMode(grnPin,OUTPUT);
    pinMode(bluPin,OUTPUT);

    //Turn the RGB LED off (mapping based on common anode or cathode)
    analogWrite(redPin,mapValue(0));
    analogWrite(grnPin,mapValue(0));
    analogWrite(bluPin,mapValue(0));

    //Initialize the rgb variable....
    setRgbVariable();

    //Expose the rgb variables on the Spark Cloud
    Spark.variable("rgb", &rgb, STRING);

    //Expose the setRgb function on the Spark Cloud
    Spark.function("setRgb",setRgb);

    //Initialize serial communication with the host
    //This is used for debug purposes only
    //and allows a host connected via usb to monitor the
    //spark using the Spark-CLI command:
    //
    // spark serial monitor
    Serial.begin(9600);
}

//The loop() method runs repeatedly as long as the program 
//is running.
void loop() {
    //We don't do anything in the loop() method
    //The RGB LED colors only gets set when the setRgb function
    //gets called via the Internet.
}
