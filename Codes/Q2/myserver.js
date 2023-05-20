
// Import the required packages
var http = require('http');
var express = require('express');
const bodyParser = require('body-parser');
const mysql = require('mysql');
const sensor = require('node-dht-sensor');

// Create an instance of Express.js
var app = express();


app.use(express['static'](__dirname ));


// Configure the body-parser middleware
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

// Configuring the MySQL database connection
const connection = mysql.createConnection({
  host: '192.168.1.100',
  port: '3306',
  user: '',
  password: '',
  database: ''
});

//--------------------------- NOTE : YOU NEED TO HAVE A TABLE IN THE DATABASE ALREADY FOR THIS TO WORK ------------
/*
CREATE TABLE sensor_data_test (
    id INT AUTO_INCREMENT PRIMARY KEY,
    temperature FLOAT NOT NULL,
    humidity FLOAT NOT NULL
);
*/

// Connecting to the MySQL database
connection.connect((err) => {
  if (err) throw err;
  console.log('Connected to the MySQL database!');
});


// Definng the API endpoint to collect the DHT sensor data
app.get('/inputs/:id', (req, res) => {
  // Read the sensor data
  sensor.read(11, 4, (err, temperature, humidity) => { // this is getting data from dht sensor
    if (err) {
      console.error(err);
      return res.status(500).send({ error: 'Failed to read sensor data' });
    }
    // converting the data into a JSON format
    const data = {
      temperature: temperature.toFixed(2),
      humidity: humidity.toFixed(2)
    };
    connection.connect((err) => {
        // if (err) throw err;
         console.log('Connected to the MySQL database!');
         var sql = "INSERT INTO sensor_data_test (temperature, humidity) VALUES ('" + temperature + "', '"+humidity + "')";
             connection.query(sql, function (err, result) { // sql query to insert collected value
             if (err) throw err;
             console.log("1 record inserted");
             });
       });
    res.status(200).send(data); // sending data to request
  });
 
});


// Express route for any other unrecognised incoming requests
app.get('*', function(req, res) {
  res.status(404).send('Unrecognised API call');
});

// Express route to handle errors
app.use(function(err, req, res, next) {
  if (req.xhr) {
    res.status(500).send('Oops, Something went wrong!');
  }
  else {
    next(err);
  }
});

app.listen(3000);
console.log('REST API program running on port 3000');