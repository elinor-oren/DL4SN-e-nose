# e-Nose Guide

## Materials 
- Arduino BLE 33 Sense + shield 
- [MiCS-4514 gas sensor](https://www.dfrobot.com/product-2417.html?)
- [LCD1602 RGB Module](https://www.waveshare.com/wiki/LCD1602_RGB_Module#Arduino)
- Two ribbon cables

## Step 1 - Hardware (Schematic)
- Use the TinyML shield
- Replace the wires in the ribbon cable 

## Step 2 - Software  
- Download the library as a zipped file here `https://github.com/DFRobot/DFRobot_MICS/tree/master` and add it to your Arduino Libraries.

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
Enclosure Adapted from - https://www.thingiverse.com/thing:5758850

I used [Silicon Nose](https://www.ebay.co.uk/itm/145295751329?itmmeta=01HVXNMCHZ8KGK0GGV8Z2GHS6R&hash=item21d44d38a1:g:Vy8AAOSw-yNkVZCK&itmprp=enc%3AAQAJAAAAwEWTiv1N7NhbQHs9xv63O8Waj910Ukqseyj91WGtLgOsRKBoYNx3G6Gk2mD%2BknRUXcXGrI%2FKl16ihUVEB6Ar1URZ9zAwifkcEMb1HRQMY1vs%2Bovb8PbnkUVV9A7j4WGwu7r%2BRCY4aHnjCX%2FWRDWEKYhxsj7ER%2Fz%2F5cm%2BJw%2B6UJM%2F%2BJhoiYAjLT5vxQ8lRYS8bqd%2Fr3RNwdgkpYJzEqBn26otbQ2goEvLy9NiUbmHqT%2BvHT5wdic1J5pq%2BnHO1kMCZg%3D%3D%7Ctkp%3ABk9SR-LJ0bXfYw) and hollowed it out. 


