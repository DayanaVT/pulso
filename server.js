
const express = require('express');
const path = require('path');
const app = express();
const port = 3000;

app.use(express.json());
let eventos = [];


app.post('/api/evento', (req, res) => {
  const evento = {
    boton: req.body.boton,
    timestamp: req.body.timestamp
  };
  eventos.push(evento);
  console.log("Evento recibido:", evento);
  res.status(200).send("Evento recibido");
});

app.get('/api/evento', (req, res) => {
  res.json(eventos);
});

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

app.listen(port, () => {
  console.log(`Servidor escuchando en http://localhost:${port}`);
});
