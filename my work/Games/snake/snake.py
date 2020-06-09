'''
Name : Snake
Date : 23/05/2020
Time : 12:25 PM
Author : tanmay
'''

import pygame as p
import random
 
p.init()
 
white = (255, 255, 255)
black = (0, 0, 0)
orange= (255,165,0)
red = (200, 0, 0)
green = (0, 255, 0)
blue = (0,100,255)
 
unit = 14 #change for magnification

playScreen = p.display.set_mode((0,0),p.FULLSCREEN)
scr_width, scr_height = p.display.get_surface().get_size()

clk = p.time.Clock()

font_h0 = p.font.Font("Starlight.ttf", 300)#main header
font_h1 = p.font.Font("ARDARLING.ttf", 150)#Big score
font_h2 = p.font.Font("Star Trek Enterprise Future.ttf", 70)#small score
font_h3 = p.font.Font("ARHERMANN.ttf", 30)#small texts
 
def rand_coord(ran):
    value = round(random.randrange(0, ran-unit)/unit)*unit
    return value

def disp_score(score):
    disp = font_h2.render(str(score), True, red)
    playScreen.blit(disp, [15,5])
    
def disp_message(point):
    msg1 = font_h1.render("GAME OVER", True, red)
    msg2 = font_h1.render("Score:"+str(point), True, black)
    msg3 = font_h3.render("Press 'A' to play again & 'Esc' to exit.", True, blue)
    playScreen.blit(msg1, [scr_width / 6, scr_height / 4.5])
    playScreen.blit(msg2, [scr_width / 4.2, scr_height / 2.5])
    playScreen.blit(msg3, [scr_width / 3.2, scr_height / 1.5])
  

def draw_snake(body):
    p.draw.rect(playScreen, red, [body[0][0], body[0][1], unit, unit])
    try:
        p.draw.rect(playScreen, red, [body[-1][0], body[-1][1], unit, unit])
    except:
        pass
    for x in body[:-1]:
        p.draw.rect(playScreen, orange, [x[0], x[1], unit, unit])

def intro_scr():
    playScreen.fill(black)
    msg1 = font_h2.render("WELCOME TO", True, blue)
    msg2 = font_h0.render("SNAKE", True, red)
    msg3 = font_h3.render("Use arrow keys for play     Hit enter to play",True,orange)
    playScreen.blit(msg1, [scr_width / 2.6, scr_height / 4])
    playScreen.blit(msg2, [scr_width / 4.1, scr_height /2.9])
    playScreen.blit(msg3, [scr_width / 3.7, scr_height / 1.5])
    p.display.update()
 
def gameflow():
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
    speed = 15
 
    x_pos = round(scr_width /(2*unit))*unit
    y_pos = round(scr_height/(2*unit))*unit 
 
    del_x = 0
    del_y = 0
    
    body = []
    snakey = 1 #snake length
    
    fx = rand_coord(scr_width) #food
    fy = rand_coord(scr_height)
    
    while not gamePlay:
        while close_prmt == True:
            playScreen.fill(white)
            disp_message(snakey-1)
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
                elif event.key == p.K_LEFT:
                    del_x = -unit
                    del_y = 0
                elif event.key == p.K_RIGHT:
                    del_x = unit
                    del_y = 0
                elif event.key == p.K_UP:
                    del_y = -unit
                    del_x = 0
                elif event.key == p.K_DOWN:
                    del_y = unit
                    del_x = 0
 
        if x_pos < 0 or x_pos >= scr_width-unit or y_pos < 0 or y_pos >= scr_height-unit :
            close_prmt = True
        x_pos += del_x
        y_pos += del_y
        
        playScreen.fill(black)
        p.draw.rect(playScreen, green, [fx, fy, unit, unit])
        
        head = [x_pos,y_pos]
        body.append(head) 
        if len(body) > snakey:
            del body[0]
 
        for x in body[:-1]: #collision check
            if x == head:
                close_prmt = True
 
        draw_snake(body)
        disp_score(snakey - 1)
 
        p.display.update()
 
        if x_pos == fx and y_pos == fy: #collision check
            fx = rand_coord(scr_width)
            fy = rand_coord(scr_height)
            snakey += 1
 
        clk.tick(speed)
 
    p.quit()
    exit(0)

if __name__=='__main__':
    gameflow()
