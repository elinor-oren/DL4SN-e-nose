IMAGE 

# Using Machine Learning to Create an e-Nose 

The GitHub repository can be found here.
The Edge Impulse models can be cloned from here:
- [Pinot & Rose](https://studio.edgeimpulse.com/public/370763/live).
- [Spirits](https://studio.edgeimpulse.com/public/390002/live)

## Introduction
- an overview of what the project does
- your inspiration for making the project 
- examples that it is based on.

The applications are broad from providing health assessments, such as analyzing fecal VOCs for IBS/IBD detection (Ahmed et al., 2013), analyzing breath glucose for diabetes, or analyzing 

- facilitate quality assurance, product/brand fingerprinting, and spoilage detection of products, where trained experts and experienced aficionados can easily tell the difference between whiskies from their scents. But it is quite difficult for most consumers, especially amateurs.

In systems of connected environments, they have been used to support sustainable harvesting and agricultural systems, identifying when an individual tree may be ready for harvesting.

HOW DO THEY WORK

These gas sensors, or e-noses, do not identify the individual molecules. "most gas sensors on the market, although aimed at (and most sensitive towards) a single chemical, react to a wide range of chemicals. With this array of different sensors you have a vector of correlated quantities and you need to do PCA or some other processing to convert it into a usable "fingerprint". Then you match that fingerprint to a database of known "smells". 


I took inspiration from [Benjamin Cabe's nose](https://blog.benjamin-cabe.com/2021/08/03/how-i-built-a-connected-artificial-nose)

## Research Question
Imperceptible subtleties and patterns are picked up by machines all the time, but given a brief "sniff" exposure, can we train a model to classify "gourmet" fooditems that have a similar smell and only have minute differences in odor? 

*Tip: probably 1 or 2 sentences*

## Device Overview
The E-Nose project is composed of the following primary components:

1. Gas Sensor: This is the X sensor, capturing four types of gases X, Y, Z, and O to , to create a gaseous fingerprint. The the variation (min, max, average, etc.) of the concentration of each gas

chart of how many ppm of each gas is captured

2. Processing Unit: An Arduino Nano 33 BLE collects the sensor data and used to build a database on the Edge Impulse platform, where a deep learning model is trained to recognize the odor. After training, the model is exported as a TensorFlow Lite Arduino library, which is then deployed back on the Arduino Nano 33 BLE for real-time processing. It uses this model to classify the alchol or coffee beans.

3. Visual Output: An LCD screen displays the classification of the data.
   
4. Enclosure: The enclosure 

Thinking back to the various application diagrams you have seen through the module - how would you describe an overview of the building blocks of your project - how do they connect, what do the component parts include.

## Application Overview



## Data
### Data Collection

The training database uses the serial output readings of from my sensor. After initiating the sensor and collecting 25-30 mins of data per stimuli, I copied the serial monitor readings to a textfile. To ensure the data's revelance, I collected data directly from bottle and from a cup and in different temperatures to have a wide range of conditions. In further experiments I used a wide mouthed jar as I felt this was most representative of use. I collected roughly equal amounts of each class to have a balanced dataset. Appropriately sized, and Well-formatted. 

The variation in gas concentration allowed for improved feature selection. 

### Data Cleaning

After collection, the serial data needed to be reformatted into an csv to be readable by EdgeImpulse. This data could sometimes contain unnecessary readings like "warming up" or "0.0," which necessitated that I create a python cleaning script in codelabs. 

### Data Organization



*Tip: probably ~200 words and images of what the data 'looks like' are good!*

## Model
This is a Deep Learning project! What model architecture did you use? Did you try different ones? Why did you choose the ones you did?

*Tip: probably ~200 words and a diagram is usually good to describe your model!*

## Experiments
What experiments did you run to test your project? What parameters did you change? How did you measure performance? Did you write any scripts to evaluate performance? Did you use any tools to evaluate performance? Do you have graphs of results? 

*Tip: probably ~300 words and graphs and tables are usually good to convey your results!*

## Results and Observations
Synthesis the main results and observations you made from building the project. Did it work perfectly? Why not? What worked and what didn't? Why? What would you do next if you had more time?  

*Tip: probably ~300 words and remember images and diagrams bring results to life!*

## Future Developments 

## Bibliography
*If you added any references then add them in here using this format:*

1.Ahmed, I., Greenwood, R., Ben, Ratcliffe, N.M. and Probert, C.S. (2013). An Investigation of Fecal Volatile Organic Metabolites in Irritable Bowel Syndrome. PloS one, [online] 8(3), pp.e58204–e58204. doi:https://doi.org/10.1371/journal.pone.0058204.

2. Hampson, M. (2022). This E-Nose Sniffs Out the Good Whiskey. [online] IEEE Spectrum. Available at: https://spectrum.ieee.org/electronic-nose-whiskey.
3. 

4. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

5. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

*Tip: we use [https://www.citethisforme.com](https://www.citethisforme.com) to make this task even easier.* 

----

## Declaration of Authorship

I, Elinor Oren, confirm that the work presented in this assessment is my own. Where information has been derived from other sources, I confirm that this has been indicated in the work.


*Digitally Sign by typing your name here*

ASSESSMENT DATE
