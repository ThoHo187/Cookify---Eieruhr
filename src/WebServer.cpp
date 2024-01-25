// WebServer.cpp
#include "WebServer.h"

const char* htmlContent = R"rawliteral(
<!DOCTYPE html>
<html lang="de">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Eieruhr</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin: 20px;
        }
        .timer-container {
            display: flex;
            align-items: center;
            justify-content: center;
            background-color: #ccc;
            padding: 10px;
            border-radius: 5px;
            margin-top: 20px;
        }
        label {
            margin-right: 10px;
        }
        .timer {
            font-size: 24px;
            margin-right: 10px;
        }
        .start-button, .stop-button {
            padding: 10px;
            font-size: 16px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }
        .start-button {
            background-color: #4CAF50;
            color: white;
        }
        .stop-button {
            background-color: #FF0000;
            color: white;
        }
        .checkmark {
            display: none;
            background-color: #4CAF50;
            height: 25px;
            width: 25px;
            border-radius: 50%;
            margin-left: 10px;
        }
    </style>
</head>
<body>

    <h1>Cookify - Eieruhr</h1>

    <!-- Timerfelder wiederholen -->
    <div class="timer-container" id="timer1">
        <label for="eiInput">1) Expressreis:</label>
        <div class="timer">01:00</div>
        <button class="start-button" onclick="toggleTimer('timer1', 60)">Start</button>
        <div class="checkmark" id="checkmark1">&#10003;</div>
    </div>

    <!-- Wiederholte Timerfelder -->
    <div class="timer-container" id="timer2">
        <label for="eiInput">2) Eier weich:</label>
        <div class="timer">02:00</div>
        <button class="start-button" onclick="toggleTimer('timer2', 120)">Start</button>
        <div class="checkmark" id="checkmark2">&#10003;</div>
    </div>

    <div class="timer-container" id="timer3">
        <label for="eiInput">3) Eier mittel:</label>
        <div class="timer">03:00</div>
        <button class="start-button" onclick="toggleTimer('timer3', 180)">Start</button>
        <div class="checkmark" id="checkmark3">&#10003;</div>
    </div>

    <div class="timer-container" id="timer4">
        <label for="eiInput">4) Eier hart:</label>
        <div class="timer">04:00</div>
        <button class="start-button" onclick="toggleTimer('timer4', 240)">Start</button>
        <div class="checkmark" id="checkmark4">&#10003;</div>
    </div>

    <div class="timer-container" id="timer5">
        <label for="eiInput">5) Schwarztee:</label>
        <div class="timer">05:00</div>
        <button class="start-button" onclick="toggleTimer('timer5', 300)">Start</button>
        <div class="checkmark" id="checkmark5">&#10003;</div>
    </div>

    <div class="timer-container" id="timer6">
        <label for "eiInput">6) Dehnen:</label>
        <div class="timer">06:00</div>
        <button class="start-button" onclick="toggleTimer('timer6', 360)">Start</button>
        <div class="checkmark" id="checkmark6">&#10003;</div>
    </div>

    <div class="timer-container" id="timer7">
        <label for="eiInput">7) Powerworkout:</label>
        <div class="timer">07:00</div>
        <button class="start-button" onclick="toggleTimer('timer7', 420)">Start</button>
        <div class="checkmark" id="checkmark7">&#10003;</div>
    </div>

    <div class="timer-container" id="timer8">
        <label for="eiInput">8) Pizza:</label>
        <div class="timer">08:00</div>
        <button class="start-button" onclick="toggleTimer('timer8', 480)">Start</button>
        <div class="checkmark" id="checkmark8">&#10003;</div>
    </div>

    <div class="timer-container" id="timer9">
        <label for="eiInput">9) Nudeln:</label>
        <div class="timer">09:00</div>
        <button class="start-button" onclick="toggleTimer('timer9', 540)">Start</button>
        <div class="checkmark" id="checkmark9">&#10003;</div>
    </div>

    <div class="timer-container" id="timer10">
        <label for="eiInput">10) Studytime:</label>
        <div class="timer">10:00</div>
        <button class="start-button" onclick="toggleTimer('timer10', 600)">Start</button>
        <div class="checkmark" id="checkmark10">&#10003;</div>
    </div>

    <script>
        var timers = {};
        var checkmarks = {};

        function toggleTimer(timerId, initialTime) {
            if (!timers[timerId]) {
                startTimer(timerId, initialTime);
            } else {
                stopTimer(timerId);
            }
        }

        function startTimer(timerId, initialTime) {
            var timeInSeconds = initialTime;
            var minutes, seconds;

            var timerElement = document.getElementById(timerId).getElementsByClassName('timer')[0];
            var startButton = document.getElementById(timerId).getElementsByClassName('start-button')[0];
            var checkmark = document.getElementById(timerId).getElementsByClassName('checkmark')[0];

            timers[timerId] = setInterval(function () {
                if (timeInSeconds <= 0) {
                    stopTimer(timerId);
                    showCheckmark(checkmark);
                } else {
                    minutes = Math.floor(timeInSeconds / 60);
                    seconds = timeInSeconds % 60;
                    displayTime(timerElement, minutes, seconds);
                    timeInSeconds--;
                }
            }, 1000);

            startButton.innerText = "Stop";
            startButton.classList.remove('start-button');
            startButton.classList.add('stop-button');

            hideCheckmark(checkmark);
        }

        function stopTimer(timerId) {
            clearInterval(timers[timerId]);

            var startButton = document.getElementById(timerId).getElementsByClassName('start-button')[0];

            startButton.innerText = "Start";
            startButton.classList.remove('stop-button');
            startButton.classList.add('start-button');

            // Optional: Resetze die Zeit auf die ursprüngliche Zeit
            var initialTime;
            switch (timerId) {
                case 'timer1':
                case 'timer2':
                    initialTime = 180;
                    break;
                case 'timer3':
                case 'timer4':
                    initialTime = 120;
                    break;
                case 'timer5':
                case 'timer6':
                    initialTime = 90;
                    break;
                case 'timer7':
                    initialTime = 60;
                    break;
                default:
                    initialTime = 180;
            }

            displayTime(timerId, Math.floor(initialTime / 60), initialTime % 60);
        }

        function displayTime(timerElement, minutes, seconds) {
            timerElement.innerHTML = `${padZero(minutes)}:${padZero(seconds)}`;
        }

        function padZero(num) {
            return (num < 10 ? "0" : "") +

 num;
        }

        function showCheckmark(checkmark) {
            checkmark.style.display = "block";
        }

        function hideCheckmark(checkmark) {
            checkmark.style.display = "none";
        }
    </script>
<br>
Vera Löwe, Philip Schwengsbier, Thomas Hofbeck
</body>
</html>
)rawliteral";

//Ende Webserver.cpp