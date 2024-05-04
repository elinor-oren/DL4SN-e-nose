# e-Nose Guide

## Materials 
- [Arduino BLE 33 Sense TinyML kit (including Arduino shield)](https://store.arduino.cc/products/arduino-tiny-machine-learning-kit) 
- [MiCS-4514 gas sensor](https://www.dfrobot.com/product-2417.html?)
- [LCD1602 RGB Module](https://www.waveshare.com/wiki/LCD1602_RGB_Module#Arduino)
- Two ribbon cables

## Step 1 - Hardware (Schematic)
- Use the TinyML shield
- Replace the wires in the ribbon cable to align with the sensors
- Plug the screen and sensor into the shield's designated I2C ports

<img width="300" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/8c5e0a38-0a81-4057-8932-e8cab2e2af9b">


## Step 2 - Software  
- Download the .zip libraries from `Enclosure` and add them to your Arduino Libraries.
- Run the I2C test in `Enclosure` to see their respective addresses. You can change the sensor's address in the sketch if these conflict.  


## Data Recording + Processing 
- Copy and paste your Serial data into a textfile.
- Open the `script` in a Google Colabs window.
- Update textfile and csv pathways to your desired locations.
- Download your csv and upload it to a new Edge Impulse project. 

While you can use the data in this repository, it is likely that different environmental conditions and inconsistent sensor calibrations will lead to poor model performance. The `Data` directory contains the csv serial readings for each of the following alcohols:
- `Wine` (with subdirectories for `Malbec`, `Pinot` and `Rose`)
- `Whisky`
- `Gin`
- `Cider`

## Step 3 - Enclosure 
### VERSION 1
Trace your cut path in the lid of the pringles can. Cut out the hole and stab many other holes to allow airflow. 

<img width="300" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/a8a20b77-52b0-401f-aba9-1cce1b13d7a4">

Tape the sensor to the lid so that it shuts and holds your sensor in place -- be sure to put the tape on the edges (where the screws would be) to avoid interference with any sensitive bits. Stab a hole through the body and thread your cord through, plugging in the microcontroller. 

<img width="300" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/89bec896-b178-4fc4-9783-150c7c52cc74">
<img width="400" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/f602cd0a-7c9f-40ba-a064-3efd1fd24a1d">


Stab another hole through for the screen!

<img width="300" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/13061e97-c882-4517-a6eb-4317f27346a7">

### VERSION 2


### VERSION 3 
I used this [silicon Nose](https://www.ebay.co.uk/itm/145295751329?itmmeta=01HVXNMCHZ8KGK0GGV8Z2GHS6R&hash=item21d44d38a1:g:Vy8AAOSw-yNkVZCK&itmprp=enc%3AAQAJAAAAwEWTiv1N7NhbQHs9xv63O8Waj910Ukqseyj91WGtLgOsRKBoYNx3G6Gk2mD%2BknRUXcXGrI%2FKl16ihUVEB6Ar1URZ9zAwifkcEMb1HRQMY1vs%2Bovb8PbnkUVV9A7j4WGwu7r%2BRCY4aHnjCX%2FWRDWEKYhxsj7ER%2Fz%2F5cm%2BJw%2B6UJM%2F%2BJhoiYAjLT5vxQ8lRYS8bqd%2Fr3RNwdgkpYJzEqBn26otbQ2goEvLy9NiUbmHqT%2BvHT5wdic1J5pq%2BnHO1kMCZg%3D%3D%7Ctkp%3ABk9SR-LJ0bXfYw) and hollowed it out at the nostrils to allow airflow. You'll need a [fan](https://www.amazon.co.uk/GeeekPi-Raspberry-40x40x10mm-Brushless-Cooling/dp/B07X93XGBD/ref=sr_1_3?dib=eyJ2IjoiMSJ9.gIX_5-Ek9jmqn-oMgRQbUzfCEbXl8AOk9R9FbPVlrXu89InTdW4qWoyRR4LnSZH7aCEuDkGmvQSiO_NMIzQEucCxF45EZq_53ypcev6F_m-IMYjBiRvGOtvwDo08wz_mFHwarUVFCKrPpIqbsnyO04prc58vYwhwCP568U2z0bJy1C9ydCdO0xSbOoEdQ5J1IjUvO2Vu-aeZgE2m1vCzjYzelkyjcHtOjPvcH6vQPl8.ai3uFgwUXF7e7-GA447rRGnQfUfreAuunwGTfgzIvJ4&dib_tag=se&keywords=5v%2Bfan&qid=1709905437&sr=8-3&th=1) for this one because the sensor doesn't pick up the vapors through the nose.  

<img width="400" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/d96cb534-f60c-45d7-be46-1d4654b4558a">
<img width="250" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/710b01ce-5c5b-42e8-816f-87c67f7153ed">

### VERSION 4 
3D Printed Enclosure 
Adapted from - https://www.thingiverse.com/thing:5758850


## Step 4 - Upload the Model 

