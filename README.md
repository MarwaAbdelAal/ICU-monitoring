# ICU_monitoring

### Create database using MongoDB

#### Download MongDB 
[From here] (https://www.mongodb.com/try/download/community)

#### Use MongoDB Shell (mongosh)   in Compass or use terminal with next commands 

```
mongo
use patient_data( yourDB_name)
db.vital_signs(your collection_name).insertOne({ "_id": 1, "temp": ["47, 46, 48, 39"], "pressure":  ["47, 46, 48, 39"] });
```

#### Run Server 
```
python monnitoring.py
```
