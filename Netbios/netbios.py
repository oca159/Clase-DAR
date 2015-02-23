#!/usr/bin/env python
import netifaces as nif

def main():
	mi_ip = nif.ifaddresses('wlan0')[2][0]['addr']
	mi_mascara = nif.ifaddresses('wlan0')[2][0]['netmask']
	broadcast = nif.ifaddresses('wlan0')[2][0]['broadcast']
	print mi_ip, mi_mascara, broadcast
	pass

if __name__ == '__main__':
	main()


"""def mac_for_ip(ip):
    for i in nif.interfaces():
        addrs = nif.ifaddresses(i)
        try:
            if_mac = addrs[nif.AF_LINK][0]['addr']
            if_ip = addrs[nif.AF_INET][0]['addr']
        except IndexError, KeyError: #ignore ifaces that dont have MAC or IP
            if_mac = if_ip = None
        if if_ip == ip:
            return if_mac
    return None"""
