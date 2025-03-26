# Description: a log of the process

*02/27/2025:*
- I have been doing this project for a week now.
- I had to put it off for a day or so, but have started to get somewhere into the process of building my inverse function
- This requires me to break down the matrix into L&U in order to push them into row-echelon form and solve 
- Right now I am in the process of finding the pivot values and determining whether elimination needs to be performed on that column before continuing

*03/12/2025:*
- I have left this project for a while now (about 2-3 weeks)... I'm now forcing myself to write this at 9:48PM on a Wednesday night.
- This project will go on. I will not be deterred.
- This probably reads like something out of a sci-fi horror game where you find the scientist's log, but its not that deep, LA is just hard
---
- Ok so i worked on this for an hour and made a little progress on LU Decomp.
- Check the C++ Notes for %d vs %f for formatting when doing int division. Also printf vs cout for structured output formatting.
- We were able to get to the point right before assigning the values into the L matrix, but we did calculate all of them for the first column correctly
- we've got the right idea, but something is wrong

*03/18/2025:*
- once again forcing myself to do this late at night. This just how it be my dude.
- you figured out the issue regarding why the LU Decomp was outputting that weird float value, its because you aren't updating U before updating L again.
- - the idea is commented in the code

*03/19/2025:*
- i somehow only work at this right before i go to bed
- going to try to finish the LU decomp
- HA... that didn't happen. HOWEVER, I do think we figured out part of the issue. 
>> the reason the U doesn't update correctly is because you're dividing by the wrong multiplier term
>> I'm not sure you can update U in that same loop

*03/25/2025:*
- i started earlier tonight (at 8pm)
- finished doing this at 10:15. Rewrote my algorithm for LU decomp for simplicity.
- we now create a vector of multipliers to reference during the operation (this is slow, but let's just get something down first before optimizing)
- I SUCCESSFULLY UPDATED THE U ON THE FIRST COLUMN.
- - this has taken like a month of lackluster effort to do lol

Next steps:
- finish elimination step.
- test and evaluate.
- 