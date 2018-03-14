from flask import Flask, jsonify, request
import json
import MySQLdb

db = MySQLdb.connect("localhost","wes","pi","ece4534")
curs = db.cursor()
curs.execute("TRUNCATE TABLE temp")

x=0

app = Flask(__name__)

@app.route('/motor', methods = ['GET','POST'])
def test_Json():
        if request.method == "POST":
                print (request.headers)
                print(request.get_data())
                d1 = request.get_json(force = True)['direct1']
                print("d1: " + d1)
                d2 = request.get_json(force = True)['direct2']
                d3 = request.get_json(force=True)['speed1']
                d4 = request.get_json(force=True)['speed2']
                #print( "y = " + y)
                curs.execute("""INSERT INTO motorvals (direct1, direct2, speed1, speed2) VALUES (%s, %s, %s, %s)""",(d1,d2,d3,d4))
                db.commit()
                return  jsonify(status="received")

#               return  json.dump({"status":"received"})

                #       print('exception')
                #       db.rollback()
                #       return jsonify({"status": "not received"})
        elif request.method == "GET":
                #try:
                #print(request.get_json(force = True))
                        print ('in get')
                        curs.execute("SELECT * FROM motorvals ORDER BY id DESC LIMIT 1")
                        row = curs.fetchone()
                        return jsonify({'status': row})
                #except:
                        return jsonify({'status': 'failed to get'})
						
if __name__ == '__main__':
        app.run(debug=True, host='0.0.0.0',threaded=True)

