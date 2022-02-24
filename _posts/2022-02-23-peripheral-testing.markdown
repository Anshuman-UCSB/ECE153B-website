---
layout: post
title:  "Peripheral Testing"
date:   2022-02-23 04:08:40 +0000
categories: updates
---

First real update!

All of our components have arrived, and we went through and tested each component. We checked to see which ones are able to be run from the GPIO pins, and which ones needed more power. We started setting up our codebase, with code for LED lighting. We are planning on using systick interrupts to keep track of miliseconds in real time, so we can use that for accurate sleep and delay functions.  

Here is the led buttons we are planning on using on 5V power  
![5V button](/assets/2.23.22/button1.jpg)

After setting up the code for the GPIO pins, here is two of them running on different periods.  
![Button gifs](/assets/2.23.22/twobuttongif.gif)

We decided to try to use GPIO port C, with pins 0, 1, 2, and 3 for the 4 main buttons.  

On Friday the tape and solder iron will come, and we will start building the physical model with cardboard boxes.  
