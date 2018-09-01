# J6 Bigknob
This is the main firmware for the J6 Bigknob USB-MIDI controller, based on the Teensy platform (Arduino Compatable)

## Features
- 4x Keyswitches
- 2x Rotary Encoders
- 1x 3 way switch
- 1x 3.5mm TRS Jack for footpedal


<img src="https://i.imgur.com/eoUi0Af.jpg" />

## Download

Download + extract the repo to a local folder.
##### Windows
------------
** Via Git**
	[Download Git for Windows](https://git-scm.com/download/win "Download Git for Windows")
	Then via command line / powershell
`	D:\Arduino> git clone https://github.com/litruv/BigKnob.git BigKnob`

##### MacOS
------------
[Download Git fot MacOS](https://git-scm.com/download/mac "Download Git fot MacOS")
	Then via terminal
` $ git clone https://github.com/litruv/BigKnob.git BigKnob`

##### Linux
------------
`$ git clone https://github.com/litruv/BigKnob.git BigKnob`

##### General
------------
[![Download Repo Zip](https://i.imgur.com/Ij76c4Q.png "Download Repo Zip")](https://i.imgur.com/Ij76c4Q.png "Download Repo Zip")

## Usage

Download + Install **Arduino IDE**
https://www.arduino.cc/en/Main/Software

Download + Install **Teensyduino** 
https://www.pjrc.com/teensy/td_download.html

Open **BigKnob.ino** in **Arduino IDE**

Edit knob steps as needed (steps per tick)
```
//Knob Steps
int SmallKnob = 6;
int BigKnob = 1;
```

Change the board type to Teensy LC
![](https://i.imgur.com/QVNE8Xh.png)

Change the USB type to Serial + MIDI
![](https://i.imgur.com/cNiXUd4.png)

Might need to change port (I don't need to for mine)

Upload. 

## Acknowledgements
Portions of this software were developed at http://www.pjrc.com/
Those portions licensed under MIT License Agreement, (the "License"); You may not use these files except in compliance with the License.
You may obtain a copy of the License at: http://opensource.org/licenses/MIT
Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions
and limitations under the License.
Portions Copyright (c) 2012-2018 http://www.pjrc.com/
