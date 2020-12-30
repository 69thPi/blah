The notations as depicted in the image attached.

On solving the kinematics for a given direction
vector we get the values of the 3 wheel vectors.
These values are printed in the console &
shown in the plot screen.

Click to set the direction vector.
To fit the graph into range, set the variable
'range_lim'.

Ref for kineamtics::
[X]=inv([A])*[B]
[X] = transpose([v1,v2,v3])
[B] = [v_res*sin(theta),
       v_res*cos(theta),
       Omega_zAxis]
inv([A])=[ .58 -.33 .33
	  -.58 -.33 .33
	   0    .66 .33]
[A]=[  .866 -.866 0
      -.5   -.5   1
      1      1    1]
