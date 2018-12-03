# EntranceAutomation

This is the original use case:
### for the guest
When the guest arrives, he/she should enter the door number of the host by the keyboard and then the bell in the host's house will ring. After the identity of the visitor is confirmed using the phone of the system, the host presses the bottom and then the locked door downstairs will be open. Then the visitor can walk in.
### for the host
When the host needs to go out or come back home, he/she has to use a RF key to open the door.
### for the administator
Remote manage all the RF keys, including enable the key or disable it.

## TARGET
And my target is remake the subsystem in my house in order to control it remotely for the first step and then to make all this automatic which I don't have to 

## Detailed Needs
1. Control it inside the house
* Hack the original system
* Automated open
* Automated open only once when the control switch is turned on
2. Control it from local internet web page
3. Control it from internet web page
4. Control it on my phone
5. Control it automately depending on my position

## Hace the subsystem
It could be inferred from the PCB and the frame that the top-left switch is for the hook action and the one on the right-bottom is the unlock action which is exactly the same with the print.

So here is the simplest way to hack this subsystem. Add an additional path for each of the two switches, so the control logic could be taken over by any MCU that is responsible for it.

decoder chip is HT12D. encoder chip is HT12E(which is I infer).

when someone visits, device downstairs will launch the knocking by sending:
    [sync head(12x"000" and 1x"001" )] [A0-A7][D0-D3]
which in total 13 data signals. And "001" represents '1', "011" is '0'.

For HT12D, if 3 out of 4 times of code matched, VT output high, Dout is latched, till Din is no longer active.

address set on board is 0101 1011 as it could be seen from PCB:
![address setting on PCB](./resource/PCB_front.jpeg)
![address setting on PCB](./resource/PCB_back.jpeg)

wave measured is:
1(guiding code) 0101 1011 1100 as it could be seen from oscilloscope:
![someone knock on 502 door](./resource/oscilloscope_wave.jpeg)
and my door number is 502 so it's matched correctly.

so here is the way of decoding the knocking signal on my own MCU:
record the 1.5 times the width of the sync head and use it as the mark. when the width of the upcoming signal is less than the mark, a '1' is received otherwise is a '0'.

when pickup the Vdd powers the PCB?
when open door button is pressed, the Vdd would be 0V otherwise is 13.56V as measured