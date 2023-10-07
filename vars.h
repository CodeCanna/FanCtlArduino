const int FAN_SPEED_OFF = 0;
const int FAN_SPEED_LOW = 60;
const int FAN_SPEED_MEDIUM = 75;
const int FAN_SPEED_HIGH = 100;

struct {
  String SSID = "ChimkenChonkJr";
  String PASS = "froogal&julz4ever@home";
  //String SSID = "Mr.Wifi";
  //String PASS = "Wz7mzuz6xb289E";
} NetworkConfig;

struct {
  String FAN_ON = "ON";
  String FAN_OFF = "OFF";
} FanStates;

/*
constexpr struct FanSpeeds {
  const int OFF = 0;
  const int LOW = 60;
  const int MEDIUM = 75;
  const int HIGH = 100;
};
*/

String fanControlPage = R"END(
<!DOCTYPE html>
<html>
  <head>
    <title>Living Room fan Controls</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html body {
        margin: 0;
        padding: 0;
        border: 0;
        background-color: green;
      }
      
      body {
        width: 100%;
        height: 100%;
      }
      
      div#container h1 {
        text-align: center;
      }
      
      div.buttonForm {
        display: inline-block;
      }
      
      div#formContainer {
        text-align: center;
      }
      
      div.buttonForm form button {
        width: 10rem;
        height: 10rem;
        margin: 0.5rem;
        font-size: 3rem;
        box-shadow: 10px 10px black;
        border-radius: 1rem;
      }
      
      div.buttonForm form button:active {
        box-shadow: 0 0;
        transform: translate(10px, 10px);
      }
      
      div.buttonForm form button:hover {
        cursor: pointer;
      }
      
      /* Button Colors */
      div#zero form button {
        background-color: black;
        color: white;
      }
      
      div#one form button {
        background-color: purple;
        color: white;
      }
      
      div#two form button {
        background-color: blue;
        color: white;
      }
      
      div#three form button {
        background-color: red;
      }
      
      div#four form button {
        background-color: orange;
      }
      
      div #five form button {
        background-color: yellow;
      }
    </style>
  </head>
  <body>
    <div id="container">
      <h1>Fan Controls</h1>
      <div id="formContainer">
        <div id="zero" class="buttonForm">
          <form action="/off">
            <button type="submit">0</button>
          </form>
        </div>
        <div id="two" class="buttonForm">
          <form action="/low">
            <button type="submit">1</button>
          </form>
        </div>
        <div id="three" class="buttonForm">
          <form action="/medium">
            <button type="submit">2</button>
          </form>
        </div>
        <div id="four" class="buttonForm">
          <form action="/high">
            <button type="submit">3</button>
          </form>
        </div>
      </div>
    </div>
  </body>
</html>
)END";

#define PWM_PIN 4