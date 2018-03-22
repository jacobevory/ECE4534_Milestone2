
import socket
import os
import json
import ast
import MySQLdb
db = MySQLdb.connect("localhost", "wes", "pi", "ece4534")
curs = db.cursor()
dictCurs = db.cursor(MySQLdb.cursors.DictCursor)
#curs.execute("TRUNCATE TABLE serverdb")


def insMotor(mes, seq, d1, s1, d2, s2):
        curs.execute("""INSERT INTO motorTable (msg, seq, dil, dir, spl, spr) VALUES (%s, %s, %s, %s, %s, %s)""", (mes, seq, d1, d2, s1, s2))

def insColor(mes, seq, col):
        curs.execute("""INSERT INTO colorTable (msg, seq, red) VALUES (%s, %s, %s)""", (mes, seq, col))

def insLine(mes, seq, l1, l2, l3, l4, l5, l6, l7, l8):
        curs.execute("""INSERT INTO lineTable (msg, seq, li1, li2, li3, li4, li5, li6, li7, li8) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s)""", (mes, seq, l1, l2, l3, l4, l5, l6, l7, l8))

def insIR(mes, seq, id1, iu1, id2, iu2):
        curs.execute("""INSERT INTO irTable (msg, seq, id1, iu1, id2, iu2) VALUES (%s, %s, %s, %s, %s, %s)""", (mes, seq, id1, iu1, id2, iu2))


def printheader():
        os.system('cls')
        print ('Welcome to the Motor Encoder Demo\n\n')
        return


host = ''
port = 3000
backlog = 5
size = 1024
dataL = 0
dataR = 0

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host, port))
s.listen(backlog)

print ('server started and listening')

while True:
        client, address = s.accept()
        while True:
                data = client.recv(size)
                if data:
                        jdata = data.decode('ascii')
                        json = ast.literal_eval(jdata)
                        print(json)
                        #json holds json dictionary
                        #post motor
                        if json["typ"] == "m":
                                #insert JSON into db
                                insMotor(json["rid"], json["seq"], json["dil"], json["spl"], json["dir"], json["spr"])
                                r = "{\"msg\":\"6\",\"seq\":\"" + json["seq"] +  "\"}"
                                client.send(r.encode("ascii"))
                                print("in motor\n")
                        #post color
                        elif json["typ"] == "c":
                                #insert JSON into db
                                insColor (json["rid"], json["seq"], json["col"])
                                r = "{\"msg\":\"6\",\"seq\":\"" + json["seq"] +  "\"}"
                                client.send(r.encode("ascii"))
                                print("in color\n")
						#color
                        elif json["typ"] == "l":
                                 #insert JSON into db
                                insLine(json["rid"], json["seq"], json["li1"], json["li2"], json["li3"], json["li4"], json["li5"], json["li6"], json["li7"], json["li8"])
                                r = "{\"msg\":\"6\",\"seq\":\"" + json["seq"] +  "\"}"
                                client.send(r.encode("ascii"))
                                print("inLine\n")
                        #post ir
                        elif json["typ"] == "d":
                                #insert JSON into db
                                insIR(json["rid"], json["seq"], json["id1"], json["iu1"], json["id2"], json["iu2"])
                                r = "{\"msg\":\"6\",\"seq\":\"" + json["seq"] +  "\"}"
                                client.send(r.encode("ascii"))
                                print("in ir\n")
                        #get ir
                        elif json["typ"] == "r":
                                row = curs.execute("SELECT * FROM irTable")
                                client.send(r.encode("ascii"))
                                print ("in request \n")


client.close()
