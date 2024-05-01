IMAGE 

# Using Machine Learning to Create an e-Nose 

The GitHub repository can be found [here](https://github.com/elinor-oren/DL4SN-e-nose).

The Edge Impulse models can be cloned from here:
- Model 1: [Pinot & Rose](https://studio.edgeimpulse.com/public/370763/live).
- Model 2: [Spirits](https://studio.edgeimpulse.com/public/390002/live)

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

1. Gas Sensor: This is the X sensor, capturing six types of gases X, Y, Z, and O to , to create a gaseous fingerprint. The the variation (min, max, average, etc.) of the concentration of each gas.
   Gas                   Range 
- Carbon Monoxide (CO): Range is 1 – 1000 ppm
- Nitrogen Dioxide (NO2): Range is 0.05 – 10 ppm
- Ethanol (C2H5OH): Range is 10 – 500 ppm
- Hydrogen (H2): Range is 1 – 1000 ppm
- Ammonia (NH3): Range is 1 – 500 ppm
- Methane (CH4): Range is above 1000 ppm

2. Processing Unit: An Arduino Nano 33 BLE collects the sensor data and used to build a database on the Edge Impulse platform, where a deep learning model is trained to recognize the odor. After training, the model is exported as a TensorFlow Lite Arduino library, which is then deployed back on the Arduino Nano 33 BLE for real-time processing. It uses this model to classify the alchol or coffee beans.

3. Visual Output: An LCD screen displays the classification of the data.
   
4. Enclosure: The enclosure 

Thinking back to the various application diagrams you have seen through the module - how would you describe an overview of the building blocks of your project - how do they connect, what do the component parts include.

## Application Overview



## Data
### Data Collection

The training database uses the serial output readings of from my sensor. After initiating the sensor and collecting 25-30 mins of data per stimuli, I copied the serial monitor readings to a textfile. To ensure the data's robustness, I collected data directly from bottle, from a cup, and in different temperatures to ensure the model works in a wider range of conditions. In further experiments I used a wide mouthed jar as I felt this was most representative of use. I collected roughly equal amounts of each class to have a balanced dataset. 

The variation in gas concentration allowed for improved feature selection. This serial output formatting facilitated conversion to csv: 

`[timestamp],[CO average],[CH4 average],[C2H5OH average],[H2 average],[NH3 average],[NO2 average],[CO min],[CH4 min],[C2H5OH min],[H2 min],[NH3 min],[NO2 min],[CO max],[CH4 max],[C2H5OH max],[H2 max],[NH3 max],[NO2 max]`

### Data Cleaning

After collection, the serial data needed to be reformatted into an csv to be readable by EdgeImpulse. This data could sometimes contain unnecessary readings like "warming up" or "0.0," which necessitated that I create a python cleaning script in codelabs. 

### Data Organization
I used the 60/20/20 split for training, validation, and testing data. Edge Impulse automatically did this for me. 
What model architecture did you use? Did you try different ones? Why did you choose the ones you did?


*Tip: probably ~200 words and images of what the data 'looks like' are good!*

## Model Iterations 
My model's parameters included:

- Epochs (20 or 50 training cycles).
- Final layer neurons (0 or 32).

I did not use any DSP blocks because the standard ones were geared towards time-series data. Rather than 

### Wine Classifier Model 
#### Test 1: 
Confirming model sensitivity to my data.  
- Data:

Overfitting 

#### Test 2 

- Data: 


### Alcohol Classifier Model 
### Test 1 

What did I do differently?
- Increased amount of data 
- Updated my holder
- Recorded Iterations / Experiments
- Only 12 input axes - removed 6 input axes (CH4 and NO2 data) thanks to Martin's advice! 

For this test, I used the following parameters for my impulse block:

<img width="600" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/3dd86c47-b3ff-45f1-be63-6e33698749ac">


When using the feature explorer on my data, we can see that the higher percentage alcohols are poorly differentiated and all overlapping. So, as expected, this produced a highly inaccurate model. 

<img width="180" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/e7a99cd4-79d8-49ad-a504-881a2945030b">
<img width="400" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/7559cfd4-400a-49fd-8794-9bd58786517b">

I wanted to figure out whether I could remove more axes to at least improve accuracy but the EdgeImpulse feature rankings were nondescript and unhelpful. Upon Martin's suggestion, I could use some kind of regression analysis to determine which axes to remove. 

#### Linear Regression 
My goal was to use the type of beverage as a categorical dependent variable to see which features are most important in distinguising the three types of alcohol using the [scikit-learn](https://scikit-learn.org/stable/index.html) `linear_model` in google Colab. From there, my coefficient analysis showed me that my NO2 data had even less influence on the alcohol type than my timestamps! (You can upload your files and access the script [here](https://colab.research.google.com/drive/1EfYz-UCEDjvid-uTBobtLptgC90SV4kT?usp=sharing))

##### Interpreting the Coefficients:
In this linear regression model, the coefficients indicate how a unit change in each feature is expected to influence the dependent variable (the type of beverage). Even just upon reviewing the data with the naked eye, it was obvious to remove CH4 and NO2 before this model. The more interesting element was the range in importance of H2 data and the relative unimportance of ethanol content.

- NH3max (0.02847629): An increase in the maximum recorded level of NH3 (ammonia) is associated with an increase in the label value. 
- COavg (0.02533769): Higher average levels of CO (carbon monoxide) tend to increase the label value, indicating a possible distinguishing feature for different substances.
- NH3avg (-0.02169604): Higher average ammonia levels are associated with a decrease in the label value. 
- COmax (-0.01397733): A higher maximum CO level tends to decrease the label value.
- NO2avg, NO2min, NO2max: These coefficients are extremely close to zero, suggesting that the levels of NO2 (nitrogen dioxide) have virtually no linear influence on the label in my model.

<img width="200" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/cba5849f-fbb8-4e97-98ed-01a55857e474">

##### Checking for linearity:
After reading more, I realized that using a linear regression may not be appropriate. The actual model should ideally be a "multinomial logistic regression model," as I was using more than two categories as my dependent variable. As such, I decided to check for non-linearity in my data with residual analysis to check for non-linear patterns. After fitting the model, predictions for the training data are made, and residuals (the differences between actual and predicted values) are calculated. From here, I used a Residuals vs. Fitted Values Plot to check if there are any apparent patterns in the residuals.

<img width="200" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/88f8c815-25bc-40ff-ba88-489573d17e12">

I think that I'm getting these three distinct lines because of the nature of my data and that using a logistic regression might better be able to find the probability of category membership.

#### Multinomial Logistic Regression 
Multinomial logistic regression provides a more nuanced interpretation by showing how each predictor affects the log-odds of being in each specific class relative to a reference class (SPSS Analysis, 2024). I saw that a 70/30 data split was common for smaller datasets, like mine, and updated this split to use more testing data. 

##### Interpreting the Coefficients:

Each row in the coefficient table corresponds to one class relative to the `Label 0` baseline, which I set as gin:

<img width="600" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/2cbf3a59-ac57-4840-a2d9-49961a4469b9">


Class 0 (Gin, assuming it's the baseline):
- No coefficients since it's the baseline comparison for the other classes.

Class 1 (Whisky) vs. Class 0 (Gin):
- COavg (0.004650): Positive coefficient implies increasing CO average levels increase the odds of being whisky over gin.
- NH3avg (-0.105235): Strong negative relationship suggesting higher ammonia averages greatly reduce the odds of the sample being whisky over gin.

Class 2 (Malbec) vs. Class 0 (Gin):
- CH4avg (0.008222): Indicates an increase in methane average levels increases the likelihood of being malbec compared to gin.
- NH3avg (0.083771): Higher ammonia averages increase the odds of being malbec over gin, opposite of its effect on whisky.

##### Accuracy and Performance:

### Test 2 

What did I do differently?
- Reduced features to 6 input axes - only used NH3(avg, max, min) and CO(avg, max, min)!
  
<img width="539" alt="image" src="https://github.com/elinor-oren/DL4SN-e-nose/assets/127933946/856d77b3-ea74-4ad7-a3c8-d385edb5ca67">


### Coffee Bean Classifier 
  

## Results and Observations
Synthesis the main results and observations you made from building the project. Did it work perfectly? Why not? What worked and what didn't? Why? What would you do next if you had more time? Reflection on how the project could be improved are presented, and feedback from the crit is included.

## Future Developments 

## Bibliography
*If you added any references then add them in here using this format:*

1.Ahmed, I., Greenwood, R., Ben, Ratcliffe, N.M. and Probert, C.S. (2013). An Investigation of Fecal Volatile Organic Metabolites in Irritable Bowel Syndrome. PloS one, [online] 8(3), pp.e58204–e58204. doi:https://doi.org/10.1371/journal.pone.0058204.

2. Hampson, M. (2022). This E-Nose Sniffs Out the Good Whiskey. IEEE Spectrum. https://spectrum.ieee.org/electronic-nose-whiskey.
3. SPSS Analysis (2024). Multinomial Logistic Regression in SPSS - Explained with Example. Statistical Analysis Services For Academic Researches. Available at: https://spssanalysis.com/multinomial-logistic-regression-in-spss/.

‌

4. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

5. Last name, First initial. (Year published). Title. Edition. (Only include the edition if it is not the first edition) City published: Publisher, Page(s). http://google.com

*Tip: we use [https://www.citethisforme.com](https://www.citethisforme.com) to make this task even easier.* 

----

## Declaration of Authorship

I, Elinor Oren, confirm that the work presented in this assessment is my own. Where information has been derived from other sources, I confirm that this has been indicated in the work.


*Digitally Sign by typing your name here*

ASSESSMENT DATE
