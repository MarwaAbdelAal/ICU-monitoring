from asyncio.windows_events import NULL
from flask import Flask , request , Response
from flask_cors import CORS
from flask_pymongo import PyMongo
from flask import jsonify
import numpy as np


# Create flask & cors instance 
app = Flask(__name__)
cors = CORS()
cors.init_app(app)

# Connect to database 
mongodb_client = PyMongo(app, uri="mongodb://localhost:27017/patient_data")
db = mongodb_client.db


temp_reading  =np.ones(1000).tolist()
press_reading =np.ones(1000).tolist()

state=[]
state.append({"temp_state" :'ON', "pressure_state" :'ON' })

@app.route("/state",methods=["POST"])
def save_state():
    status = request.get_json()
    temp_state =status ["temp"]
    pressure_state= status["pressure"] 

    state[0]={"temp_state" :temp_state , "pressure_state" : pressure_state }
    # print(state[0]["temp_state"])
    # print(state[0]["pressure_state"])
    return state[0]
    

@app.route('/patient_data',methods=['GET'])
def patient_data():
    ID = request.args.get('ID')
    print(state[0])
    if state[0]["temp_state"] == 'ON':
        if state[0]['pressure_state']  == 'ON':
            response = db.vital_signs.find_one({"_id": ID})

        else:
            response = jsonify(_id=ID,temp =db.vital_signs.find_one({"_id": ID})["temp"],pressure = np.zeros(1000).tolist())
    else:
        if state[0]["pressure_state"]  == "ON":
            response = jsonify(_id=ID,temp = np.zeros(1000).tolist(), pressure=db.vital_signs.find_one({"_id": ID})["pressure"])
        else:
            response = jsonify(_id=ID,temp = np.zeros(1000).tolist(), pressure=np.zeros(1000).tolist())

    return response


@app.route("/recieve_data" , methods =["GET"])
def get_data():

       ID = request.args.get("ID")
       press_reading.append(int(request.args.get("pressure")))
       temp_reading.append(int(request.args.get("temp")))

    #    Check if ID is existed or we will update 
       ID_exist = db.vital_signs.find_one({"_id": ID})

       if (ID_exist) :
            newvalues = { "$set": {"_id": ID, "temp": temp_reading, "pressure": press_reading} }
            db.vital_signs.update_one({"_id": ID}, newvalues)

       else:
            db.vital_signs.insert_one({ "_id": ID, "temp": temp_reading, "pressure": press_reading})

       return jsonify("UPTodate_data")


if __name__ == "__main__":
    app.run(host='0.0.0.0', port= 8090,debug=True)
