# e-Nose Guide

## Materials 
- Arduino BLE 33 Sense
- [MiCS-4514 gas sensor](https://www.dfrobot.com/product-2417.html?)

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
- `Wine` (with subdirectories for `Pinot` and `Rose`)
- `Whisky`
- `Gin`

## 
