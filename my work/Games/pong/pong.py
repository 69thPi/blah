'''
Name : Pong
Date : 26/05/2020
Time : 9:55 PM
Author : Tanmay
'''

import pygame as p
import random
 
p.init()

white = (255,255,255)
black = (0, 0, 0)
orange= (255,165,0)
red = (200, 0, 0)
blue = (0,100,255)

unit = 14#change for magnification

playScreen = p.display.set_mode((0,0),p.FULLSCREEN)
scr_width, scr_height = p.display.get_surface().get_size()

clk = p.time.Clock()

font_h0 = p.font.Font("Starlight.ttf", 300)#main header
font_h1 = p.font.Font("ARDARLING.ttf", 150)#Big score
font_h2 = p.font.Font("Star Trek Enterprise Future.ttf", 70)#small score
font_h3 = p.font.Font("ARHERMANN.ttf", 30)#small texts
 
def disp_message(winner):
    msg1 = font_h1.render("GAME OVER", True, black)
    playScreen.blit(msg1, [scr_width / 6, scr_height / 4.5])
    if winner in ('RED'):        
        msg2 = font_h1.render("RED WINS", True, red)
        msg3 = font_h3.render("Press 'A' to play again & 'Esc' to exit.", True, blue)
        playScreen.blit(msg2, [scr_width / 4.2, scr_height / 2.5])
    else:
        msg2 = font_h1.render("BLUE WINS", True, blue)
        msg3 = font_h3.render("Press 'A' to play again & 'Esc' to exit.", True,red)
        playScreen.blit(msg2, [scr_width / 5.2, scr_height / 2.5])
    playScreen.blit(msg3, [scr_width / 3.2, scr_height / 1.5])

def intro_scr():
    playScreen.fill(black)
    msg1 = font_h2.render("WELCOME TO", True, blue)
    msg2 = font_h0.render("PONG", True, red)
    msg3 = font_h3.render("Use w/s & arrow keys for play     Hit enter to play",True,orange)
    playScreen.blit(msg1, [scr_width / 2.6, scr_height / 4])
    playScreen.blit(msg2, [scr_width / 3.3, scr_height /2.9])
    playScreen.blit(msg3, [scr_width / 4.2, scr_height / 1.5])
    p.display.update()
 
def gameflow():
    winner = 'RED'
    intro= True
    while intro==True:
        intro_scr()
        for event in p.event.get():
                if event.type == p.KEYDOWN:
                    if event.key == p.K_RETURN:
                        intro=False
                    elif event.key ==p.K_ESCAPE:
                        p.quit()
                        exit(0)
    gamePlay = False
    close_prmt = False
    speed = 20
    pad1=[0,0]
    pad2=[scr_width-unit,0]
    pad_len=10*unit
    x_pos = round(scr_width /(2*unit))*unit
    y_pos =pad1[1]=pad2[1]= round(scr_height/(2*unit))*unit
    pad1[1]-=pad_len/2
    pad2[1]-=pad_len/2
 
    del_x = random.choice([1,-1])*unit
    del_y = random.choice([1,-1])*unit
        
    while not gamePlay:
        while close_prmt == True:
            playScreen.fill(white)
            disp_message(winner)
            p.display.update()
 
            for event in p.event.get():
                if event.type == p.KEYDOWN:
                    if event.key == p.K_ESCAPE:
                        gamePlay = True
                        close_prmt = False
                    if event.key == p.K_a:
                        gameflow()
 
        for event in p.event.get():
            if event.type == p.QUIT:
                gamePlay = True
            if event.type == p.KEYDOWN:
                if event.key == p.K_ESCAPE:
                    close_prmt=True
        keys = p.key.get_pressed()
        if keys[p.K_w]:
            pad1[1]-=unit
        elif keys[p.K_s]:
            pad1[1]+=unit
        if keys[p.K_UP]:
            pad2[1]-=unit
        elif keys[p.K_DOWN]:
            pad2[1]+=unit
 
        if x_pos < (2.5*unit) or x_pos >= scr_width-(2*unit):
            if y_pos>pad1[1] and y_pos<(pad1[1]+pad_len):
                del_x*=-1
            elif y_pos>pad2[1] and y_pos<(pad2[1]+pad_len):
                del_x*=-1
            else:
                if x_pos < (2.5*unit):
                    winner='BLUE'
                close_prmt = True

        if y_pos < 1.5*unit or y_pos >= scr_height-unit :
            del_y *=-1

        if pad1[1] < 0 :
            pad1[1] = 0
        elif pad1[1] >scr_height-pad_len:
            pad1[1] = scr_height-pad_len
        if pad2[1] < 0 :
            pad2[1] = 0
        elif pad2[1] >scr_height-pad_len:
            pad2[1] = scr_height-pad_len
            
        x_pos += del_x
        y_pos += del_y
        
        playScreen.fill(black)
        p.draw.circle(playScreen,orange,[x_pos,y_pos],unit/1.5,0) # 1 for circle outline
        p.draw.rect(playScreen,red,p.Rect(pad1[0],pad1[1],unit,pad_len),1)
        p.draw.rect(playScreen,blue,p.Rect(pad2[0],pad2[1],unit,pad_len),1)
 
        p.display.update()
        
        clk.tick(speed)
 
    p.quit()
    exit(0)

if __name__=='__main__':
    gameflow()
