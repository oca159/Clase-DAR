#!/usr/bin/env python
import netifaces as nif
from ipcalc import IP, Network

def main():
    mi_ip = nif.ifaddresses('wlan0')[2][0]['addr']
    mi_mascara = nif.ifaddresses('wlan0')[2][0]['netmask']
    broadcast = nif.ifaddresses('wlan0')[2][0]['broadcast']
    print mi_ip, mi_mascara, broadcast
    
if __name__ == '__main__':
	main()