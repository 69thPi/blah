convo = [['hello sir','im fine thank you'],['hey bud','how are you']]

def UpdateText(content,name):
    if name==1:
        convo[0].append(content)
    else:
        convo[1].append(content)

if __name__=='__main__':
    UpdateText('no',2)
    print(convo[1])
