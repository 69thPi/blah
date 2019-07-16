import math as m
"""
dat[] patamater legend:
index    value
 [0]      t [hh,mm,ss]
 [1]      Crs
 [2]      Del n
 [3]      M0
 [4]      Cuc
 [5]      e
 [6]      Cus
 [7]      rt(a)
 [8]      t_oe
 [9]      Cic
[10]      OMEGA
[11]      Cis
[12]      I0
[13]      Crc
[14]      omega
[15]      OMEGA_dot
[16]      I_dot
SUBTRACT 1 INDEX FROM ALL
"""
om_dot_e = 7.2921151467e-05
mu = 3.986005e14

def gCtric(dat):
    #lvl 1
    a = m.pow(dat[7],2)
    no = m.sqrt(mu/m.pow(a,3))
    #lvl 2
    n = no + dat[2]
    t= dat[0][0]*3600 + dat[0][1]*60 + dat[0][2] #no of seconds
    tk = t - dat[8]
    if(tk < -302400):
        tk+= 604800
    elif (tk >302400):
        tk-= 604800
    #lvl 3
    Mk = dat[3] + (n * tk)
    #lvl 4
    Ek = Mk +dat[5]*m.sin(Mk + dat[5]*m.sin(Mk)) ## check ## M,M1,M0 value taken same ## two iterations only as ecc is negligible ~0.001
    #lvl 5
    fk = m.atan((m.sqrt(1-m.pow(dat[5],2)) * m.sin(Ek))/(m.cos(Ek)-dat[5]))
    phi_K = fk +dat[14]
    #lvl 6
    del_Uk = dat[6]* m.sin(2*phi_K) + dat[4]* m.cos(2*phi_K)
    del_Rk = dat[13] *m.cos(2*phi_K) + dat[1] * m.sin(2*phi_K)
    #lvl 7
    del_Ik = dat[9]* m.cos(2*phi_K) +dat[11] *m.sin(2*phi_K)
    uk =phi_K +del_Uk
    rk = a * (1 - dat[5] * m.cos(Ek)) + del_Rk
    #lvl 8
    ik = dat[12] + del_Ik + dat[16]*tk
    #lvl 9
    x_dash = rk * m.cos(uk)
    y_dash = rk * m.sin(uk)
    Om_k = dat[10] +(dat[15] -om_dot_e)* tk - (om_dot_e*dat[8])
    #lvl 10
    x = x_dash * m.cos(Om_k) - y_dash * m.cos(ik)* m.sin(Om_k)
    y = x_dash * m.sin(Om_k) - y_dash * m.cos(ik)* m.cos(Om_k)
    z = y_dash * m.sin(ik)
    final = [x,y,z,tk]
    return final

    
    
