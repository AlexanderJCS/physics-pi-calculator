# physics-pi-calculator
<h2>Explanation</h2>
This calculator simulates is a simulation using perfectly elastic collisions to calculate pi and counts all of the collisions. The number will be pi.<br>

<h2>Inspiration</h2>
This calculator was inspired by 3Blue1Brown's video explaining how the algorithm works:<br>
https://www.youtube.com/watch?v=jsYwFizhncE&t=0s<br>

<h2>How to use</h2>
1. Choose the amount of digits of pi you want to calculate by changing the constant digits.<br>
2. Choose the hitbox of the small object. This prevents one block teleporting through another and does not affect performance.<br>
3. Choose the step, or how small the increments of movement is. <b>This affects performance negatively as the number increases</b><br>
4. Choose the start velocity of the large object. This must be a negative number. The lower the number, the less likely it is to teleport through another object. <b>This affects performance negatively as the number decreases.</b>
