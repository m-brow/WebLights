// Basic web server written in Node.js

const express = require('express')
const bodyParser = require('body-parser')
const path = require('path')
const app = express()
const port = 80

app.use(express.static('public'))   // Host static HTML files
app.use( bodyParser.json() );       // to support JSON-encoded bodies
app.use(bodyParser.urlencoded({     // to support URL-encoded bodies
  extended: true
}));

// Gloabl state of ALL lights
state = "0&0&0&"
light_state = true
last_red = 0
last_green = 0
last_blue = 0

// Send state
app.get('/state', (request, response) => {
  response.send(state)
})

app.post('/state', (request, response) => {

  if (request.body.lights_off) {
      red = 0
      green = 0
      blue = 0

  }

  // lights on
  if (request.body.red) {
    red = request.body.red
    green = request.body.green
    blue = request.body.blue
  }

  console.log(request.body)

  state = red + "&" + green + "&" + blue + "&"

  console.log('New state is: ' + state)

  // Redirect to home page
  response.redirect("/")
})

app.get('/', (request, response) => {
  response.sendFile(path.join(__dirname + '/index.html'))
})

app.listen(port, (err) => {
  if (err) {
    return console.log('something bad happened', err)
  }

  console.log(`server is listening on ${port}`)
})
