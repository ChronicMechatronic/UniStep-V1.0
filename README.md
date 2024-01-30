# UniStep-V1.0
![UniStep v1 0 -removebg-preview](https://github.com/ChronicMechatronic/UniStep-V1.0/assets/145880075/98b1077d-8fa5-47b7-91a5-7d166e3af7d9)


UniStep is a simple, low-cost, translating stepper motor driver allowing you to use cheaply manufactured unipolar steppers frequently found in e-waste for any kind of CNC project like 3D printers, 
without doing the usual unipolar-to-bipolar mod needed in order to use common bipolar drivers like the A4988. 
Driving them in their original unipolar configuration makes the motors a lot quieter as current limiting relies on the internal phase resistance of the motor rather than a noisy PWM signal in constant current control.
Of course unipolar motors also have a number of disadvantages over their bipolar hybrid counterparts, (notably: lower max speeds, faster torque drop-off at high speeds, commonly low resolution of only 48 steps/revolution) making them 
indesirable for 3D printing and laser cutting (basically all direct belt drive applications). For many low-stake automation tasks they're usually sufficient though and being able to reuse e-waste is worth something as well, so this translating driver makes it easier.

Taking step/direction and enable input signals UniStep is fully compatible with the well established A4988 ecosystem, allowing to easily retrofit existing hardware.


Specifications:

-A4988 hardware compatible

-Max. voltage: 28V

-Max. current per phase: 0.5A (plenty for all unipolar motors I've so far come across)

-Microstepping mode: halfsteps (can be changed to fullsteps in software, though I'm not sure know why you'd ever do that)


Pinout diagram:
![pinout small](https://github.com/ChronicMechatronic/UniStep-V1.0/assets/145880075/11034483-9812-49d4-b43b-2fc7ca13730b)


Notes:
Since current is purely limited by the motor's phase resistance, the supply voltage must be matched to the motor. Otherwise overheating may occur.
