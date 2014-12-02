<a name="Title" />
# Creating Your First Internet Connected Device #

<a name="Overview" />
## Overview ##

The **"Internet of Things" (IoT)** is a hot topic these days.  Basically it is about enabling the things we use in day-to-day life to communicate with us, and to be controlled by us in new and exciting ways.  By making everyday things "smart" and connecting them to the Internet, we can gain significantly more value out of those things as well as do things with them that were just never possible before.  

As an example, think about a "smart" mouse trap.  Dr. Andy Stanford-Clark, and IBM Distinguished engineer did just that.  He wired is mouse traps up to some micro-controllers so that the traps could "tweet" when they were tripped.  [You can watch a video of Dr. Stanford-Clark talking about his mouse traps here](http://youtu.be/s9nrm8q5eGg?t=2m21s): http://youtu.be/s9nrm8q5eGg?t=2m21s (the link takes you directly to the mouse trap part, but the entire video is very interesting).

Of course, it doesn't just have to be about making old things better, it can also be about making things that have never existed before.  Think of products like the new **[Microsoft Band](http://www.microsoft.com/Microsoft-Band/)** (http://www.microsoft.com/Microsoft-Band/)!  A quick review of the **["Technology"](https://www.kickstarter.com/discover/categories/technology)** (https://www.kickstarter.com/discover/categories/technology) category on Kikstarter and you'll see hundreds of new product ideas.

In this walkthrough I'll show you how to get started on an IoT adventure of your own by helping you create an Internet Enabled RGB (Red, Gree, Blue) Light.  You can then control that light using any thing that can make an HTTP call: A Web Page, A Phone App, Another IoT device....

The microcontroller development board we'll use in this walkthrough is the **["Spark Core"](https://www.spark.io/dev-kits)** from [Spark.io](http://spark.io) .  Why did we choose the Spark Core?  Well it is relatively in-expensive ($39 USD at the time this was written) but it comes with WiFi capabilities built in, and a free cloud backend that allows you to expose your Spark Core's functionality on the internet.  If you used an Arduino or a Raspberry Pi instead, you'd still have to pay for the WiFi shield or adapter, and setup some internet backed for it.  

![00010-SparkCore](images/00010-sparkcore.png?raw=true "Spark Core")

---

<a name="tasks" />
## Tasks ##

In this walkthrough we will

1. [Review the inventory of parts you need, and give you links to purchase them if needed](#inventory)
1. [Setup and "Claim" your Spark Core](#claimcore)
1. [Connect the RGB LED up to the Spark Core](#ConnectLED)
1. [Deploy the code to control the RGB LED](#deployCode)
1. [Test the Spark Core and RGB LED](#testCode)
1. [Control the RGB LED from a Web Site](#webSite)
1. [Deploy the Web Site to Azure](#deployToAzure)

---

<a name="inventory" />
## Inventory ##

You'll need a few parts for this walkthrough.  Gather the following parts before proceeding with the subsequent steps:


![00020-Inventory](images/00020-inventory.png?raw=true "Inventory")

|Item #|Qty|Description|Cost|Link
|------|---|-----------|----|----
|1|1|**Spark Core** Dev Kit with Chip Antenna|$39.00|https://www.spark.io/dev-kits#
|2|1|**Breadboard** - Included with Spark Core Dev Kit|$0.00|--
|3|1|**USB Cable** - Included with Spark Core Dev Kit|$0.00|--
|4|1|**RGB LED** - I got 50 for $3.43 on Amazon.com|$3.43|http://www.amazon.com/gp/product/B005VMDROS/
|5|5|**Male to Male Jumper Wires**|$5.50|http://www.amazon.com/RioRand-Breadboard-Jumper-Wire-75pcs/dp/B0040DEI9M/
|6|1|**WiFi Network** with known SSID and Password. Could be WiFi available where you are, or perhaps connection from your phone, or a WiFi hotspot|$0.00|
|7|1|**White Ping Pong Ball** (Optional) - I found a pack of 12 on Amazon for $5.00|$5.00|http://www.amazon.com/Ping-Pong-Balls-White-12ct/dp/B005EGKNBQ/
|8|1|**Free Azure Website** (Not Pictured, Optional)|$0.00|http://azure.microsoft.com/en-us/documentation/services/websites/

A few notes on the above:

1. The **"RGB LED"** can be purchased anywhere, you don't need 50 of them, just 1, and you don't have to get them from Amazon.  If you are a college student, try checking with your Schools Electrical Engineering professors to see if they have some! RGB LED's come in two flavors, **"Common Anode"** or **"Common Cathode"** the code we use below will work with either, but you do need to know what kind you have.    

1. The **"Male to Male Jumper Wires"** can be any 20-22 Gauge solid core wire. You can trim the insulation off the ends of a short length of "hookup" wire if you have any avaiable.  Again, if you are at a school try checking with your teachers or professors.  

1. Any **"White Ping Pong Ball"** will work.  You don't need 12 of them, and you don't need to buy them from Amazon. The ping pong ball just helps to diffuse the light from the LED and makes it easier to see the colors from a distance. If you can't find one, you can still complete the project below.  

1. The **"WiFi Network"** needs to be a WEP, WPA, or WPA2 secured network that you know the SSID and password for.  This may be a problem at some locations where the WiFi access requires a web page to complete the sign in process. If you have the ability to share the internet connection from your cell phone, or if you have access to a WiFi hostpot device like a Verizon MiFi those may be a better choice than trying to use the event location's wifi network.  

1. The **"Free Azure Website"** requires that you have an active subscription.  You can use a **[Free Trial](http://azure.microsoft.com/en-us/pricing/free-trial/)** even, or perhaps an account you created using a **"Windows Azure Pass"**

---

<a name="claimcore" />
## Setup and "Claim" your Spark Core ##

Before you can deploy code to your Spark Core, you first need to create a Spark account, connect your core to the WiFi network, and claim your core.  These steps are the same for any Spark Core related project so we have documented them seperately. If you haven't already configured and claimed your Spark Core, follow the instructions in the **[Spark Core Configuration](https://github.com/mspcontent/Spark-Core-Configuration)** repository.  

![01010-SparkCoreConfiguration](images/01010-sparkcoreconfiguration.png?raw=true "Spark Core Configuration")

Specifically, make sure to follow the steps for: 

- [Install the Spark Core USB Driver for Windows](https://github.com/mspcontent/Spark-Core-Configuration#install-the-spark-core-usb-driver-for-windows)
- [Install Node.js](https://github.com/mspcontent/Spark-Core-Configuration#install-nodejs)
- [Install the Spark-CLI](https://github.com/mspcontent/Spark-Core-Configuration#install-the-spark-cli)
- [Create a Spark Build Account](https://github.com/mspcontent/Spark-Core-Configuration#create-a-spark-build-account)
- [Claim your Spark Core](https://github.com/mspcontent/Spark-Core-Configuration#claim-your-spark-core)
- (OPTIONALLY) [Configure the Spark Core's WiFi](https://github.com/mspcontent/Spark-Core-Configuration#configure-the-spark-cores-wifi) 
- (OPTIONALLY) [Identify your Spark Core](https://github.com/mspcontent/Spark-Core-Configuration#identify-your-spark-core)
- (OPTIONALLY) [Deploy Code to Your Spark Core](https://github.com/mspcontent/Spark-Core-Configuration#identify-your-spark-core) 

---

<a name="ConnectLED" />
## Connect the RGB LED up to the Spark Core ##

RGB LEDs are a special kind of LED (**L**ight **E**mitting **D**iode).  They are actually three LEDs in One package: A Red LED, a Green LED and a Blue LED.  Normal LED only has two "legs", an **"anode"** (+) and a **"cathode"** (-).  You connect the anode to a positive voltage (say +3.3Vdc for a Spark Core), and the cathode is connected to ground (GND, or 0Vdc). RGB LEDS have four legs.  One leg is either a ***common anode***, or a ***common cathode***.  The other legs are the individual anodes or cathodes for the Red, Green, and Blue colors.  If your RGB LED has a common anode (+), then the other legs are the cathodes for the Red, Green and Blue colors.  If, on the other hand, your RGB LED has a single common cathode, then the other legs are the anodes for the Red, Green and Blue colors.  You need to know what "kind" of RGB LED you have, common anode, or common cathode, because it will determine how you wire it up, as well as how you drive it. 

![02005-RGBLED](images/02005-rgbled.png?raw=true "RGB LED")

Based on the RGB LED type that you have (common anode, or common cathode), complete the wiring as described below.  You can skip the current limiting resistors if you like.  Of course, if you try it and you fry your RGB LED, reconnect a new one using the current limiting resistors. 

<a name="common-anode-rgb-leds" />
### Common Anode RGB LEDs  ###

**"Common Anode"** RGB LEDs have a single "common" anode. You connect the Anode to the Voltage supply (+3.3Vdc in the case of the Spark Core). You would then connect the R,G & B legs each to their own Pulse Width Modulation (PWM) capable PIN on the Spark Core (with appropriate current limiting resistors of course). PWM signals 0-255 on each pin vary that color from all the way on (0) to all the way off (255). Yes, you read that right. a PWM value of 0 turns that color all the way on, and a value of 255 turns that color all the way off. This is because the LED has a common anode connected to 3V. A PWM value of 255 basically means the pin is at 3.3V, and there is no voltage differential (no color) between the pin and the Anode. When the PWM value on a pin is 0, there is a 3.3V voltage drop relative to the common Anode, and the color is shown at full brightness. PWM values between 0 and 255 will show the color at a brightness relative to the PWM value.  Following is an example of a Spark Core connected directly to a common anode RGB LED.  The 330Ω resistors are **"current limiting"** resistors that help prevent damage to the RGB LEDs.  Notice that the common anode on the RGB LED connects to the **"3V3"** pin (3.3Vdc) on the Spark Core:

![02010-CommonAnodeCircuit](images/02010-commonanodecircuit.png?raw=true "Common Anode Circuit")

While the use of the current limiting resistors is recommended, you can usually skip their use (at least for quick demos like this) and just connect to the pins directly:

![02020-CommonAnodeNoResistors](images/02020-commonanodenoresistors.png?raw=true "Common Anode Circuit with no Resistors")

<a name="common-cathode-rgb-leds" />
### Common Cathode RGB LEDs ###

Common Cathode RGB LEDs have a single, "common", Cathode.  You connect the Cathode to ground (GND) on the Spark Core.  You would then connect the R,G & B legs each to their own PWM capable digital PIN on the Spark Core (with appropriate current limiting resistors of course).  PWM signals 0-255 on each pin vary that color from all the way off (0) to all the way on (255).  This seems to make more sense than the inverted value-to-brightness relationship on the Common Anode LEDs.  PWN values 0-255 cause a relative brightness on that pin color from all the way off (0) to all the way on (255).  Here is an example of a Common Cathode circuit. Notice that the common cathode connects to the **"GND"** pin (ground) on the Spark Core:

![02030-CommonCathodeCircuit](images/02030-commoncathodecircuit.png?raw=true "Common Cathode Circuit")

And again, the same circuit with the current limiting resistors omitted:

![02040-CommonCathodeNoResistors](images/02040-commoncathodenoresistors.png?raw=true "Common Cathode Circuit with no Resistors")

Finally, here is an example of a Common Anode RGB LED connected without the current limiting resitors:

![02050-CommonAnodeRGBLedWiredUpNoResistors](images/02050-commonanodergbledwiredupnoresistors.png?raw=true "Common Anode RGB LED Wired Up with No Resistors")
---

<a name="deployCode" />
## Deploy the code to control the RGB LED ##

1. In your web browser, login in to [Spark Build](http://spark.io/build) (http://spark.io/build). 

1. Make sure that the Spark Core you want to flash is connected to the cloud and is [breathing cyan](https://vine.co/v/OmOAlMg17Y9).  If you need help configuring and claiming your spark core, refer to the [Spark Core Configuration](https://github.com/mspcontent/Spark-Core-Configuration) walkthrough.

1. In the Spark Build IDE, switch to the **"CODE"** If you already have an app in your Spark account, click the **"CREATE NEW APP"** button.  If you don't any any apps already, the **"CREATE NEW APP"** button won't be there, and you will be given a new app by default:

	![03010-CreateNewApp](images/03010-createnewapp.png?raw=true "Create New App")

1. In the Spark Build IDE, if this is your first app, you need only enter the name.  We'll assume a name of **"rgbledlamp"**:

	![03020-NameApp](images/03020-nameap.png?raw=true "Name App")

1. Copy the following code and paste it into the code window (replacing the code that is already there).  Note that you can also get a copy of the source code from the [rgbledlamp/rgbledlamp.cpp](./rgbledlamp/rgbledlamp.cpp) file in this repository.

	> **Note:** The code is pretty heavily documented so read through it to gain an understanding of what it does.  However, when it is deployed to the Spark Core, you will be able to call the **setRgb** function from the internet to set the R,G,B (0,0,0 - 255,255,255) color to display.  


	````C++
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
	````

1. Once you have pasted the code in, click the **"Save"** button in the Spark Build IDE to save your app:

	![03030-SaveApp](images/03030-saveapp.png?raw=true "Save App")

1. Then click the **"Verify"** button to compile your code:

	![03040-VerifyApp](images/03040-verifyap.png?raw=true "Verify App")

1. Finally, flash the code to your spark core using the **"Flash"** button:

	![03050-FlashApp](images/03050-flashap.png?raw=true "Flash App")

1. Verify that everything worked successfully.  If you have any errors, read them, address them, then re-save, verify and flash the code. 

	> **Note:** The RGB LED on the actual Spark Core should flash purple while the code is being updated, then return to "breathing cyan" when it is complete. 

---

<a name="testCode" />
## Test the Spark Core and RGB LED ##

Now that you have deployed your code to the Spark Core, you can test it.  There are a number of ways to test it.  For each of the following methods, you will need to know your Spark Core's Name, Core ID, and Access Token.  Refer to [Identify Your Spark Core]( https://github.com/mspcontent/Spark-Core-Configuration#identify-your-spark-core) if you need help finding those values.  Once you know those, you can test your code using:

- [The Spark-cli](#testing-with-the-spark-cli)
- [curl](#testing-with-curl)
- [REST client](#testing-with-a-rest-client)

Note, this is also a good time to stick that Ping Pong Ball on top of your RGB LED to help see the colors.  Just poke a hole in the ping pong ball, and slip it over the top of your RGB LED:

![04005-RGBLEDWithPingPongBall](images/04005-rgbledwithpingpongbal.png?raw=true "RGB LED with Ping Pong Ball")

<a name="testing-with-the-spark-cli" />
### Testing with the Spark-CLI ###

The easiest way to test your new Spark Core and it's setRgb function is with the Spark-cli.  

1.  Open a Command Prompt as administrator (right-click on the Start Menu and select **"Command Prompt (Admin)"** from the pop-up menu:

	![04010-OpenCommandPrompt](images/04010-opencommandprompt.png?raw=true "Open Command Prompt")

1. In the command prompt window if you are not already logged in to your spark account at the command line issue the `spark login` ([docs](http://docs.spark.io/cli/#running-from-source-advanced-spark-login)) command, and follow the prompts to enter your Spark credentials (email and password):

	![04020-SparkLogin](images/04020-sparklogin.png?raw=true "Spark Login")

1. Now, you can use the `spark call` ([docs](http://docs.spark.io/cli/#running-from-source-advanced-spark-call)) command to call the setRgb function on your Spark Core and pass in an R,G,B value:

	`spark call rgbledlamp setRgb 255,0,0` addresses the `rgbledlamp` Spark Core, calls the `setRgb` function, and passes in the R,G,B command `255,0,0` (red):

	![04030-SparkCall](images/04030-sparkcal.png?raw=true "Spark Call")

	The above `spark call` commands yielded the following RGB colors:

	![04040-RGBColors](images/04040-rgbcolors.png?raw=true "RGB Colors")

1. If the colors aren't coming out right for you, check the following:

	- Ensure that you identified the proper RGB LED type (common anode or common cathode).  You can try changing the commonType variable to a zero or a one on line 4 of the code.  
	- Ensure that you have correctly identified and wired the RGB LED legs to PWM capable pins on the Spark Core.  The code assumes that the Red leg is wired to A7, green to A6, and blue to A5.  If you wired the legs wrong the colors will be wrong.  If you use send a command of 255,0,0 to set the color to red, but get blue or green instead, that is a good indicator that you have the LED legs connected in the wrong order.  
	- If you used pins other than A7,A6, and A5 you need to modify the redPin, grnPin and bluPin variable values on lines 11-13 of the code.
	- Ensure that the RGB LED legs are wired to PWM capable pins.  On the Spark Core, those are pins D0,D1,A0,A1,A4,A5,A6, & A7 .  

1. You can also retrieve the value of the **rgb** variable that is exposed to the cloud.  Use the `spark get` ([docs](http://docs.spark.io/cli/#running-from-source-advanced-spark-get)) function like this:

	![04050-SparkGet](images/04050-sparkget.png?raw=true "Spark Get")
	

<a name="testing-with-curl" />
### Testing with curl ###

Curl (http://curl.haxx.se/) is a popular, cross-platform, command link http client.  It allows you to make http requests from scripts and batch files, or just ad hoc requests from the command line.   

1. If you don't already have curl downloaded on your machine, you can get it from here: http://curl.haxx.se/download.html .  ***Make sure to get an SSL capable version***.  Here is a direct link to the Win64-Generic download page: http://curl.haxx.se/latest.cgi?curl=win64-ssl-sspi. Download the .zip file, unblock it, and extract it to `c:\curl` on your computer.  

1. We'll use curl to issue an http request against the Spark cloud REST API. The REST API allows us to call the functions we have exposed on our Spark Core, or to retrieve variable values, etc. The format of the rest call is:

	`https://api.spark.io/v1/devices/<coreid>/<function>`

1. You then need to pass along data for the access token (access_token) and command string (args, or params)

1. at the command prompt, type the following command, but replaceing <ID> and <TOKEN> with your core id and access token:

	> **Note:** The `-k` paramter in the following commands allows **"insecure"** access via the https protocol.  

	`curl https://api.spark.io/v1/devices/<ID>/setRgb -d access_token=<TOKEN> -d args=0,255,0 -k`

	For example, if your core id was 1234 and your token was ABCD:

	`curl https://api.spark.io/v1/devices/1234/setRgb -d access_token=ABCD -d args=0,255,0 -k`

1. You can also retrieve the value of your rgb variable using curl with this command:

	`curl https://api.spark.io/v1/devices/<ID>/rgb?access_token=<TOKEN> -k`

	Again, with Core ID 1234, and Access Token ABCD it would look like:

	`curl https://api.spark.io/v1/devices/1234/rgb?access_token=ABCD -k`

1. The following screen shot shows an example of calling the setRGB function using curl, then retrieving the rgb variable value using curl:

	![04060-CurlSamples](images/04060-curlsamples.png?raw=true "Curl Samples")


<a name="testing-with-a-rest-client" />
### Testing with a REST Client ###

A third way to test your Spark Core code is with a generic REST client, like the  ["Advanced Rest Client" app for Chrome](http://chromerestclient.appspot.com/):

![04070-AdvancedRestClient](images/04070-advancedrestclient.png?raw=true "Advanced REST Client")

---

<a name="webSite" />
## Control the RGB LED from a Web Site ##

The next steps use **"Visual Studio"** to open and run a web site locally.  If you don't already have visual studio installed, you can download a free copy of **"Visual Studio Community Edition"** from http://visualstudio.com 

1. Open Visual Studio, and from the menu bar, select **"File"** | **"Open"** | **"Web Site..."**

	![05010-OpenWebSite](images/05010-openwebsite.png?raw=true "Open Web Site")

1. Then browse to the **"rgbledweb"** folder in this repo, and click **"Open"**:

	![05020-RGBLedWeb](images/05020-rgbledweb.png?raw=true "RGBLEDWeb")

1. Once it is open, immediately, save it to create a solution file, and accept the default location and name unless you prefer to save the solution file elsewhere:
	
	![05030-SaveSolution](images/05030-savesolution.png?raw=true "Save Solution File")

1. In the Visual Studio **"Solution Explorer"** window, double click on the **"index.html"** file to open it.  Then, on lines 102 and 106 replace the **"&lt;ID&gt;"** and **"&lt;TOKEN&gt;"** placeholder's with your Spark Core's Core ID and access token:

	![05040-ReplacePlaceHolders](images/05040-replaceplaceholders.png?raw=true "Replace Place Holders")

1. For example, if your Core ID is **1234** and your Access Token is **ABCD**:

	`<input type="text" id="coreId" class="txtInput" value="<ID>">`

    and

	`<input type="text" id="accessToken" class="txtInput" value="<TOKEN>">`

	becomes

	`<input type="text" id="coreId" class="txtInput" value="1234">`

    and

	`<input type="text" id="accessToken" class="txtInput" value="ABCD">`

1. Next, locate the markup for the R,G, and B inputs (lines 117,121 & 125).  These will become sliders that you can use to drag the R,G, and B values from 0 to 255:

	![05050-RGBSliders](images/05050-rgbsliders.png?raw=true "RGB Sliders")

1. Further down, on lines 139 and 144 are the **localRgb** div, and the **coreRgb** span.  The **localRgb** div is used to display the RGB color that you selected locally using the R, G, and B sliders.  The **"coreRgb"** span is used to display the RGB value retrieved via the 'rgb' variable on the Spark Core:

	![05060-RGBDisplays](images/05060-rgbdisplays.png?raw=true "RGB Displays")

1. If you continue down in the index.html document, you come to the JavaScript code that makes up the core functionality of the page.  The code is pretty well documented so you should read through it to gain an understanding of what it does.  However, we'll discuss two main functions here; the `onSlideStop` function and the `getValuesFromSpark` function.

1. The onSlideStop function is called whenever one of the R,G, or B sliders is moved by the user.  When the movement is done, this function is called.  Here are a few key points in the code though:

	- Lines 189-190 retrieve the CoreID and Access Token from the fields we modified above.  

	- Line 203 reads the values from the R,G, and B sliders into the `localRed`, `localGrn` and `localBlu` variables.

	- Line 207 uses the `localRed`, `localGrn` and `localBlu` variables to populate the `command` variable with a command in the `R,G,B` format required by the Spark Core's `setRgb` function.

	- Line 211 creates the url for the setRgb function rest call

	- Line 219 makes the ajax (http) call to the setRgb function, and passes along the access token and command string.  When that call completes, the RGB LED on the Spark Core show now reflect the color selected by the R,G, and B sliders.


	````JavaScript
	/This function is called by the slider controls
	//slideStop event
	var onSlideStop = function () {

	  //If a post is already in progress, exit
	  if (posting)
		 return;

	  //Get the current coreId and Access token from the form fields.
	  coreId = $('#coreId').val().trim();
	  accessToken = $('#accessToken').val().trim();

	  //We need valid coreId and accessToken values to proceed
	  if (coreId === "" || accessToken === "") {
		 window.alert("You must supply the Spark Core's Core ID and Access Token");
		 return;
	  }

	  //Set the posting flag to true to prevent any parallel posts from occurring
	  posting = true;

	  //Retrieve the local RGB values from the slider controls
	  //And update the RGB display color
	  getLocalValuesFromSliders();

	  //Build the command string that will be passed to the spark core's
	  //setRgb function.  The command will be in the format of "r,g,b"
	  var command = localRed + ',' + localGrn + ',' + localBlu;

	  //Create the url for the spark core's setRgb function with the
	  //required coreId value.
	  var url = "https://api.spark.io/v1/devices/" + coreId + "/setRgb";

	  //Show the ajax_loader div to indicate that the post has begun
	  //the div overlays the slider controls and prevents the sliders
	  //from being changed while the update is in progress. This
	  $('#ajax_loader').show();

	  //Create a jQuery.ajax request to post the new RGB values to the setRgb function
	  $.ajax({
		 type: "POST",
		 url: url,
		 data: {
			access_token: accessToken,
			args: command
		 },
	  }).then(function () {
		 //Then set the posting flag to false so another post can run
		 posting = false;
		 //hide the ajax_loader div
		 $('#ajax_loader').hide();
	  });
	};
	````
1. The `getValuesFromSpark` function retrieves the value of the Spark Core's rgb value then updates the R,G, and B sliders to match.  

	- Lines 243-244 retrieve the Core ID and Access Token from the form fields

	- Line 253 builds the url of the REST api call for the rgb variable

	- Line 259 makes the ajax call and passes along the access token as data

	- Lines 269-272 parses the JSON value of the rgb variable into the local `coreRed`, `coreGrn` and `coreBlu` variables

	- Line 275 calls the `setSliderValues()' function to update the local sliders to match the values on the Core. This helps one user see the value that another user has set on the Core. 

	- Line 278 updates the local coreRgb span to show the values retrieved from Spark Core.  

	````JavaScript
	//This function retrieves the Spark Core's rgb variable value
	function getValuesFromSpark() {

	  //If a post is in progress, exit.
	  //We don't want to override the current post
	  if (posting)
		 return;

	  //Get the current coreId and Access token from the form fields.
	  coreId = $('#coreId').val().trim();
	  accessToken = $('#accessToken').val().trim();

	  //We need valid coreId and accessToken values to proceed
	  if (coreId === "" || accessToken === "") {
		 return;
	  }

	  //Set the url that will be posted to.  This is the URL exposed by the Spark Core
	  //via the Spark Cloud
	  var url = "https://api.spark.io/v1/devices/" + coreId + "/rgb";

	  //Show the "coreLoader" animated gif to give a visual clue that the update is being done
	  $('#coreLoader').show();

	  //Use a jQuery.ajax request to request the variable value from the URL
	  $.ajax({
		 type: "GET",
		 url: url,
		 data: {
			access_token: accessToken
		 },
	  }).then(function (data) {
		 //Then, extract the r, g, and b values returned:
		 //The rgb variable actually returns a JSON string with the r,g,b values
		 //So we need to take the string, parse it as JSON, and extract the values
		 var rgb = $.parseJSON(data.result);
		 coreRed = rgb.r;
		 coreGrn = rgb.g;
		 coreBlu = rgb.b;

		 //Update the local sliders with the values retrieved from the core
		 setSliderValues(coreRed, coreGrn, coreBlu);

		 //Update the display of the Core's RGB values
		 $('#coreRgb').text("Core (r,g,b): (" + coreRed + "," + coreGrn + "," + coreBlu + ")");

		 //Hide the animated coreLoader gif to indicate the update is complete
		 $('#coreLoader').hide();
	  });

	  return true;
	}
	````

1. There are some other cool functions in there, but you are left to review the code on your own. 

1. In Visual Studio, from the menu bar, select 

	![05070-StartDebugSession](images/05070-startdebugsession.png?raw=true "Start Debug Session")

1. The web page should run in the browser, and look something like following screen shot.  Move the R, G, and B sliders and verify that the color is updating correctly on the RGB LED connected to your Spark Core:

	![05080-RunningInBrowser](images/05080-runninginbrowser.png?raw=true "Running in Browser")

1. If you have problems, try a couple of things:

	- Make sure you entered the correct Core ID and Access Token values.  Refer to [Identify Your Spark Core]( https://github.com/mspcontent/Spark-Core-Configuration#identify-your-spark-core) if you need help finding those values.

	- Make sure that your computer is connected to the Internet

---

<a name="deployToAzure" />
## Deploy the Web Site to Azure ##

Ok, so if everything worked, that's pretty cool, but only you can use the web page.  It would be cooler if anybody could use the web page to update the color on the RGB LED.  To do that, we need to get the web site published up to the "cloud" so other's can get to it.  We'll use **[Microsoft Azure](http://azure.microsoft.com)** for this. Make sure that you have an active Azure subscription before you continue. 

1. In the Visual Studio **"Solution Explorer"** window, right click on the **"rgbledweb"** web site and select **""** from the pop-up menu:

	![06010-PublishWeb](images/06010-publishweb.png?raw=true "Publish Web")

1. In the **"Publish Web"** window, select **"Microsoft Azure Websites"** and click **"Next"**

	![06020-MicrosoftAzureWebsites](images/06020-microsoftazurewebsites.png?raw=true "Microsoft Azure Web Sites")

1. In the **"Select Existing Website"** window, if you aren't already signed into to your Azure Subscription, click the **"Sign In..."** button, and then login with the credentials associated with your Azure Subscription: 

	![06030-SignIn](images/06030-signi.png?raw=true "Sign In")

	![06040-EnterCredentials](images/06040-entercredentials.png?raw=true "Enter Credentials")

1. Once you are signed in, in the **"Select Existing Website"** window, click the **"New..."** button to create a new Azure Web Site

	![06050-New](images/06050-new.png?raw=true "New")

1. In the **"Create Site on Microsoft Azure"** window, complete the **"Site name"**, **"Subscription"**, and **"Region"** and **"Database server"** fields and click **"Create"**:

	- **"Site name"**: The site name must be a valid, unique hostname.  In the screenshot, **"rgbledweb"** is used.  You will need to use something different that is uniqe.  Perhaps appending your initials to the end of rgbwebled.  The fully qualified DNS name for your website then will be **"&lt;Site name&gt;.azurewebsites.net"** where **"&lt;Site name&gt;"** is whatever you put in the **"Site name"** field. 

	- **"Subscripton"**: You will only be asked to choose a subscription if you have more than one.  If you do, choose the one that you want this website to be associated with. 

	- **"Region"**: Choose a region that is close to you.  For example, if you are in Caifornia, **"West US"** would be a good choice. 

	- **"Database server"**: The rgbledweb application does not need a database server, so you can leave it at **"No database"**

	- When you click the **"Create"** button, an empty website is provisioned for you in Azure.  When we are done with the wizard, the contents of our site will then be deployed into it.

	![06060-CreateSite](images/06060-createsite.png?raw=true "Create Site")

1. Back in the **"Publish Web"** window's **"Connection"** page, first, note the **"Destination URL"**. This will be the URL that you want to share with others to allow them to access the site and remotely control the RGB LED.  Then click **"Next"** to continue:

	![06070-Connection](images/06070-connection.png?raw=true "Connection")

1. On the **"Settings"** page accept the default values, and click **"Next"**:
	
	![06080-Settings](images/06080-settings.png?raw=true "Settings")

1. On the **"Preview"** page, click **"Publish"**:

	![06090-Publish](images/06090-publish.png?raw=true "Publish")

1. You can monitor the publish process in the **"Output"** and **"Web Publish Activity"** windows:

	![06100-OutputWindow](images/06100-outputwindow.png?raw=true "Output Window")

	![06110-WebPublishActivityWindow](images/06110-webpublishactivitywindow.png?raw=true "Web Publish Activity Window")

1. When the publishing process is complete, your browswer window should open and load the newly published site. If not, you can open your own browser, and point to URL you noted previously:

	![06120-AzureWebSite](images/06120-azurewebsite.png?raw=true "Azure Web Site")

1. Share this with your audience, and let them use the website to control the RGB LED color! Cool! 
