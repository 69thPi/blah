const char index_html[] PROGMEM = R"rawliteral(<!DOCTYPE HTML>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Flickr</title>

<style>
* {
  box-sizing: border-box;
  font-family: cursive;
}
.invisible{
  opacity: 0;
  width: 0;
  height: 0;
}

.row{
  margin:5px;
  padding:5px;
  display: flex;
}

.mid{
  margin:auto;
}
.btn {
  padding: 15px 25px;
  text-align: center;
  outline: none;
  border-radius: 15px;
  box-shadow: 2px 5px gray;
  border: 2px solid black;
  background-color: white;
  color: black;
  padding: 14px 28px;
  font-size: 16px;
  cursor: pointer;
}

/*blue*/
.blue {
  border-color: #2196F3;
  color: dodgerblue
}

.blue:active {
  background-color: #2196F3;
  box-shadow: 2px 3px #666;
  transform: translateY(2px);
}

.blue:hover {
  background: #2196F3;
  color: white;
}

/* Orange */
.orange {
  border-color: #ff9800;
  color: orange;
}

.orange:hover {
  background: #ff9800;
  color: white;
}
.orange:active {
  background-color: #ff9800;
  box-shadow: 2px 3px #666;
  transform: translateY(2px);
}

/* Red */
.red {
  border-color: #f44336;
  color: red
}

.red:hover {
  background: #f44336;
  color: white;
}
.red:active {
  background-color: #f44336;
  box-shadow: 2px 3px #666;
  transform: translateY(2px);
}
</style>

</head>

<body>
  <div>
     <div class="row">
      <form class= "mid" action="/get">
      <h1> &#128161;
      <input class="invisible" type="text" name="SW_1" value="1" readonly>
      <input class="btn blue" type="submit" value="Toggle"></h1></form>
    </div>

    <div class="row">
      <form class="mid" action="/get">
      <h1> &#128268;
      <input class="invisible" type="text" name="SW_2" value="1" readonly>
      <input class="btn orange" type="submit" value="Toggle"></h1></form>
    </div>

    <div class="row">
      <form class="mid" action="/get">
      <h1>&#10044;
      <input class="invisible "type="text" name="SW_3" value="1" readonly>
      <input class="btn red" type="submit" value="Toggle"></h1></form>
    </div>
</div>


</body>
</html>
)rawliteral";
