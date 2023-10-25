# Titration-Calculator
This is a work-related project that calculates titrant volumes for buffer solutions (still in progress)  

Introduction: 
One of the main tasks for a buffer technician in a biochemistry laboratory is that of titration. This almost always involves a time consuming process of the careful addition of an acid or base, i.e. the titrant. 
As a current buffer technician, I had the idea that I would be at a great advantage if I could standardize the titration process by predicting necessary titrant volumes. 

Program Overview:

1) Reading from two CSV files listing the most common buffers currently made in my specific lab, this program creates a multidimensional vector containing: 
a) a buffer name, its target pH, and its associated titrant. 
b) a list of all of its ingredients
c) each ingredient's Molecular Weight, concentration in milimolar, and its unit amount.

2) The user is prompted to enter a name from the list of available buffers and their final buffer volume.
3) Utilizing the Henderson Hasselbach Equation, the recipe's associated pKa (i.e. HEPES pKa = 7.5) 
   and some analytical assumptions of the reactions between HEPES and the titrant, a final volume is calculated.
  a) ratio = pow(10,(buffers[index].pH - buffers[index].pKa))
  b) [A-]/[HA] 
  c)Let our weak acid == an unknown volume, giving us our ratio in this form: 
  d) = L_A-/L_HA 
  e) answer = ratio * (volume - answer) == 
  f) answer = (ratio * volume) / (1 + ratio)


Limitations

Given the complex nature of the compound chemical interactions that occur in biochemical buffers, it is a very difficult problem to solve analytically, let alone to systematically solve for all biochemical buffers. 
Thus, with this program being a prototype, it makes a few assumptions about the buffer making process. 
  1. Given that the list of our most popular buffers is quite small, I have reduced the number of buffers that this program can process. 
  2. The basis of the program's calculations lies in the Henderson Hasselbalch equation, utilizing the pKa of the only buffering ingredient found in each of our most popular buffers: HEPES (pKa = 7.55).

Conclusion:

Using experimental observation, the accuracy of this application has been confirmed to be very close to the necessary titrant volumes. On average, the ratio of titrant volume to total buffer volume is 0.4mL:1000mL. 
This shows that the formula, is in the least, helpful in giving one an idea of how much titrant volume they should account for. 
With that said, a simple average ratio could be just as helpful in aiding the titration process. However, an increasing database of vectors/ ingredients and their interactions could provide insight into more predictive methods of modeling. 
 
 
Happy Titrating! 
