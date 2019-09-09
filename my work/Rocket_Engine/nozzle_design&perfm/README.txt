'foo5.py' is the main program

AIM: The aim of this program subset is to allow a choice of nozzle dimensions by 
      designing nozzles at altitudes defined by the user for a given set of 
      combustion chamber configuration and thrust conditions.

USE: 1.Upon setting the values for combustion chamber pressure, temperature, 
                                            avg. mol mass and gamma for the exhaust
                                            Thrust required and max operation altitude
                                            in file rocketEngine.py
      2.you can then call the method mk_noz(args), where the argument is the interval altitude at which you want your 
        engines to be designed.
      3.finally, build and run the program.
      #The output will be a graph which plots the performance of each nozzle designed vs. the flight altitude (from earth's surface)
     
** "2067000-2861-123-28-1300-5.png" is an example data plot. and the data is stored in the file 'Eng1.xlsx'
    the image format shows that the data is for
    chamber pressure=2.067 MPa
    chamber temperature=2861 K
    gamma= 1.23
    avg. mol. mass=28
    Thrust =1300 N
    and interval of 5kms
    
    the data stored in the excel file has odd rows corresponding to engine specs and even rows contain the values of Cf for
    the row just preceding it.
    the odd rows have the engine specs in the following format:
         press ratio
         throat area
         expansion ratio
         avg. mol mass
         gamma
         exhaust velocity at optimal expansion
         Coeff of force for optimal expansion
         ignored value
         height for which the nozzle was designed (gives optimal expansion, P_exit=P_ambient)

developers notes::
rocketEngine.py contains the combustion chamber properties and
in future versions will be a part of class 'engine'.
 what this program does is calculates the nozzle dimensions
 and plots its performance (Cf) over the whole range of altitude
 
what this tells us essentially is that what nozzle expansion ratio
is best suited for what altitude and for how much of a range can it be used;
without major decrements in the thrust capacity.

# this program assumes that 1D isentropic flow without any shocks
# this program does not account for flow separation and plots the
data for ONLY optimal expansion pressure ratios and higher.

the flow separation occurs usually when the exit pressure is 10-40% of the
ambient pressure (the separation is symmetric) and the flow velocity can be
calculated using the effective area this forms and the mass conservation.
*there will be compression shocks towards the end of a nozzle in case of an
over-expansion and there will be expansion shocks at the exit of the nozzle.

*to get the nozzle geometry from this data
one needs to assume a proper correction factor for conical nozzles
and one needs to carry out a shock wave analysis for bell shaped nozzles to
allow minimum losses due to compression shocks in the nozzle.
