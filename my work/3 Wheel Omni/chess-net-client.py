import requests
import socket

ip = socket.gethostbyname(socket.gethostname()).split(".")
print(ip)
url="http://"+ip[0]+"."+ip[1]+"."+ip[2]+"."+"50"

def send_data(piece="WKi",move="a4"):
    while(True):
        response=requests.get(url+"/get?"+piece+"="+move)
        if response.status_code==200:
            break
    return True

send_data()
