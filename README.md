# e-Nose Guide

## Materials 
- Arduino BLE 33 Sense + shield 
- [MiCS-4514 gas sensor](https://www.dfrobot.com/product-2417.html?)
- [LCD1602 RGB Module](https://www.waveshare.com/wiki/LCD1602_RGB_Module#Arduino)
- Two ribbon cables

## Step 1 - Hardware (Schematic)
- Use the TinyML shield
- Replace the wires in the ribbon cable to align with the sensors 

## Step 2 - Software  
- Download the required libraries from `Enclosure` and add them to your Arduino Libraries.

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
<img width="576" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/a8a20b77-52b0-401f-aba9-1cce1b13d7a4">

Tape the sensor to the lid so that it shuts and holds your sensor in place -- be sure to put the tape on the edges (where the screws would be) to avoid interference with any sensitive bits. Stab a hole through the body and thread your cord through. 

<img width="300" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/89bec896-b178-4fc4-9783-150c7c52cc74">
<img width="400" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/f602cd0a-7c9f-40ba-a064-3efd1fd24a1d">

### VERSION 2


### VERSION 3 
I used this [silicon Nose](https://www.ebay.co.uk/itm/145295751329?itmmeta=01HVXNMCHZ8KGK0GGV8Z2GHS6R&hash=item21d44d38a1:g:Vy8AAOSw-yNkVZCK&itmprp=enc%3AAQAJAAAAwEWTiv1N7NhbQHs9xv63O8Waj910Ukqseyj91WGtLgOsRKBoYNx3G6Gk2mD%2BknRUXcXGrI%2FKl16ihUVEB6Ar1URZ9zAwifkcEMb1HRQMY1vs%2Bovb8PbnkUVV9A7j4WGwu7r%2BRCY4aHnjCX%2FWRDWEKYhxsj7ER%2Fz%2F5cm%2BJw%2B6UJM%2F%2BJhoiYAjLT5vxQ8lRYS8bqd%2Fr3RNwdgkpYJzEqBn26otbQ2goEvLy9NiUbmHqT%2BvHT5wdic1J5pq%2BnHO1kMCZg%3D%3D%7Ctkp%3ABk9SR-LJ0bXfYw) and hollowed it out at the nostrils to allow airflow. You'll need a fan for this one because the sensor doesn't pick up the vapors through the nose.  

<img width="400" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/d96cb534-f60c-45d7-be46-1d4654b4558a">
<img width="250" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/710b01ce-5c5b-42e8-816f-87c67f7153ed">

### VERSION 4 
3D Printed Enclosure 
Adapted from - https://www.thingiverse.com/thing:5758850


## Step 4 - Upload the Model 

