foo5 is the main flow program
aim: the aim of this subset is to allow a choice of nozzle dimensions for a

given set of combustion chamber settings and thrust requirements.


rocketEngine contains the combustion chamber properties and
in future versions will be a part of class engine.
 what this program does is calculates the nozzle dimensions
 and plots its performance (Cf) over the whole range of altitude
 
what this tells us essentially is that what nozzle expansion ratio
is best suited for what altitude or for how much of a range can it be used for
without major degrade in the thrust capacity.

# this program assumes that 1D isotropic flow without any shocks
# this program does not account for flow separation and plots the
data for ONLY optimal expansion and beyond.
the flow separation occurs usually when the exit pressure is 10-40% of the

ambient pressure (the separation is symmetric) and the flow velocity can be

calculated using the effective area this forms and the mass conservation.

*there will be compression shocks towards the end of a nozzle in case of an
over-expansion and there will be expansion shocks at the exit of the nozzle.

*to get the nozzle geometry from this data
one needs to assume a proper correction factor for conical nozzles
and one needs to carry out a shock wave analysis for bell shaped nozzles to
allow minimum losses due to compression shocks in the nozzle.