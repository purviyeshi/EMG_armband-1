 # PCB DESIGNING


- #### FRONT SIDE OF AMPLIFYING CIRCUIT
![5](https://github.com/anuj-akotkar/EMG_armband/assets/142881764/369ab82d-9d62-4684-b055-73af755ac7d9)



- ##### ROUTING

![4](https://github.com/anuj-akotkar/EMG_armband/assets/142881764/94f1a58e-78a8-4aff-a28c-015e642e3655)

- #### The "REF," "IN-," and "IN+" connectors located on the left side of the PCB should be appropriately connected to their respective reference, detection, and muscle electrodes. This ensures that each electrode is correctly linked to the corresponding input for precise signal acquisition and processing.


- #### The 3.7V and GND connector pins on the left side of the PCB should be connected to the circuit's power source, typically a battery supply. This connection provides the necessary power to operate the circuit effectively.

- #### EMG muscle signals vary in amplitude: at rest, they're in the microvolt (µV) to tens of µV range, during normal contractions, from tens of µV to hundreds of µV (µV to mV), and during intense contractions, they can reach millivolts (mV). Amplification and signal processing should handle this range in EMG signal acquisition.

- #### The ESP32 ADCs can measure analog voltages from 0 V to Vref. the Vref varies, the median is 1.1 V. In order to convert voltages larger than Vref, input voltages can be attenuated before being input to the ADCs. There are 4 available attenuation options, the higher the attenuation is, the higher the measurable input voltage could be.

![aaj11](https://github.com/anuj-akotkar/EMG_armband/assets/142881764/ec010e59-6558-46d8-9f62-02c731cb0ef0)



- ### ESP-32 INTREGATED WITH AMPLIFYING CIRCUIT
 

- ##### FRONT SIDE 

![PCB 1](https://github.com/anuj-akotkar/EMG_armband/assets/142881764/5ae5bfeb-3d9a-4ff8-8014-8ce76c889157)

- ##### BACK SIDE
![PCB 22](https://github.com/anuj-akotkar/EMG_armband/assets/142881764/019d3fa1-b4b1-4f74-b5e9-c5bbf57d336c)


- #### ROUTING

![PCB 33](https://github.com/anuj-akotkar/EMG_armband/assets/142881764/65367758-304d-4888-98a7-cf505d569bae)

##### TO DESIGN PCB ,WE USE KICAD SOFTWARE.

