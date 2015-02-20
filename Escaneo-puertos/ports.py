#!/usr/bin/env python
import socket, sys

def uso():
	print("Uso: %s IP PUERTO" % (sys.argv[0]))
	print("Ejemplo: %s 127.0.0.1 1-1024" % (sys.argv[0]))
	print("Ejemplo: %s 127.0.0.1 80" % (sys.argv[0]))
	sys.exit()

def main():
	if (len(sys.argv) != 3):
		uso()
	ip = sys.argv[1]
	puertos = sys.argv[2]
	conexionTCP = socket.socket()
	conexionUDP = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	lpuertos = puertos.split("-")
	lpuertos =  map(int, lpuertos)
	inicio = lpuertos[0]
	dTCP = {}
	dUDP = {}
	with open("servicios.csv") as f:
		for linea in f:
			cad = linea.rstrip().split(",")
			if "tcp" in cad:
				dTCP[cad[1]] = cad[0]
			else:
				dUDP[cad[1]] = cad[0]
	if len(lpuertos) == 1:
		fin = inicio
	else:
		fin = lpuertos[1]
	for i in range(inicio,fin+1):
		try:
			conexionTCP.connect( (ip, i) )
			print ("Puerto TCP: %s %s" % (i, dTCP[str(i)]))
		except:
				pass
		try:
			conexionUDP.connect(ip, i)
			print ("Puerto UDP: %s %s" % (i, dUDP[str(i)]))
		except:
			pass
	conexionTCP.close()	
	conexionUDP.close()	
	pass

if __name__ == '__main__':
	main()