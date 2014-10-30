<a name="Title" />
# Creating Your First Internet Connected Device #

<a name="Overview" />
## Overview ##

The **"Internet of Things" (IoT)** is a hot topic these days.  Basically it is about enabling the things we use in day-to-day life to communicate with us, and to be controlled by us in new and exciting ways.  By making everyday things "smart" and connecting them to the Internet, we can gain significantly more value out of those things as well as do things with them that were just never possible before.  

In this walk through, I'll show you use to use a simple microcontroller from http://spark.io called the [Spark Core](https://www.spark.io/dev-kits) to control an RGB LED.  

As an example, think about a "smart" mouse trap.  Dr. Andy Stanford-Clark, and IBM Distinguished engineer did just that.  He wired is mouse traps up to some micro-controllers so that the traps could "tweet" when they were tripped.  [You can watch a video of Dr. Stanford-Clark talking about his mouse traps here](http://youtu.be/s9nrm8q5eGg?t=2m21s): http://youtu.be/s9nrm8q5eGg?t=2m21s (the link takes you directly to the mouse trap part, but the entire video is very interesting).  In Andy's own words though: 

_"Now, mouse traps 101; once a mouse trap's gone off its no use anymore, it won't catch any more mice until you reset it. So what you really want is a monitor that will tell you exactly when the mouse trap's gone off. This is a perfect Internet of Things application. So we connect sensors to the mouse trap, which run a little voltage through the mouse trap and detect when the mouse trap's set, and when it goes off. Then when the mouse trap goes off it breaks the circuit. A little computer at the top there detects that the mouse trap's gone off. It sends a message out called a 'mouse event'. That gets sent off to the Internet, and I get a message on my phone saying, 'Mouse trap in your study's gone off'.  This works fantastically.  It's caught dozens and dozens of mice over the last two years, and it works really well.  And to me this is a classic example of retro-fitting existing technology with Internet of Things automation so we can give it a new lease on life, and make it more useful."_

Of course, it doesn't just have to be about making old things better, it can also be about making things that have never existed before.  Think of products like the new **[Microsoft Band](http://www.microsoft.com/Microsoft-Band/)** (http://www.microsoft.com/Microsoft-Band/), quadcopters and drones, like those from [3DR](3dr.com) (http://3dr.com), Environmental sensors like those from [CubeSensors](http://cubesensors.com) (http://cubesensors.com).  There are THOUSANDS of new devices coming out all the time.  
