const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Hoki SmartLamp</title>
    <link rel="manifest" href="manifest.json" />
    <link rel="shortcut icon" href="/favicon.ico" type="image/x-icon" />
    <link rel="icon" href="/favicon.ico" type="image/x-icon" />
    <style>
      :root {
        --bg: #212121;
        --disabled: #4d4d4d;
      }
      * {
        padding: 0;
        margin: 0;
      }
      body {
        height: 100%;
        width: 100%;
        overflow: hidden !important;
        background-color: var(--bg);
        font-weight: 100;
        color: #f0f0f0;
        font-family: Verdana, Geneva, Tahoma, sans-serif;
      }
      header {
        padding: 20px 30px;
      }
      header h1 {
        font-weight: 100;
        font-size: 1.7em;
        text-transform: uppercase;
      }
      header svg {
        margin-top: 3.5px;
      }
      header.flex {
        justify-content: space-between;
      }
      button:hover {
        filter: brightness(0.9);
        cursor: pointer;
      }
      button:focus {
        /* filter: bright(0.8); */
        outline: none;
      }
      button:disabled {
        background-color: var(--disabled);
      }
      .btn {
        font-weight: 100 !important;
        width: 100%;
        padding: 15px 20px;
        border: 0;
        border-radius: 2px;
        color: white;
        font-weight: bold;
        text-transform: uppercase;
        font-size: 1em;
      }
      .cancel {
        flex: 0;
        background-color: #e82020;
        margin-right: 20px;
      }
      .manual {
        flex: 0;
        background-color: #6f6f6f;
        margin-right: 20px;
      }
      .apply {
        flex: 1;
        background-color: #0f8db3; /* flex: 2; */
      }
      #edit {
        background-color: transparent;
        outline: none;
        border: none;
      }
      .power {
        padding: 15px 0;
        border: 0;
        width: 100%;
        height: 60px; /* border-radius: 100%; */
        background-color: #e62a2a;
        color: white;
        font-weight: bold;
      }
      .power p {
        font-size: 1rem;
        font-weight: 400;
        padding: 0 10px;
        margin: auto;
      }
      .power.off {
        background-color: var(--disabled);
      }
      .container {
        padding: 8vw;
      }
      .body {
        height: 65vh;
        position: relative;
        display: flex;
      }
      .row-color {
        display: flex;
        width: 84vw;
        height: calc(84vw * 80 / 100);
      }
      .row-color .left {
        width: 80%; /* height: 100%; */
      }
      .row-color .right {
        width: 20%;
      }
      .flex {
        display: flex;
      }
      .inline-flex {
        display: inline-flex;
      }
      .color-picker {
        position: relative;
        width: 100%;
        height: 100%;
      }
      .color-picker canvas {
        width: 100%;
        height: 100%;
      }
      .color-picker::before {
        content: "";
        width: 60%;
        border-radius: 100%;
        height: 60%;
        background-color: var(--bg);
        position: absolute;
        transform: translate(34%, 34%);
      }
      .remove-before::before {
        content: none;
      }
      #inner-picker {
        position: absolute;
        left: 50%;
        top: 50%;
        display: inline-block;
        width: 55%;
        height: 55%;
        border: 10px var(--bg) solid;
        transform: translate(-50%, -50%);
        background: rgba(255, 0, 0, 1);
        border-radius: 100%;
      }
      .slider {
        height: 85%;
        width: 75%;
        -webkit-appearance: slider-vertical;
      }
      #red {
        background-image: linear-gradient(90deg, black, #ff0000);
      }
      #green {
        background-image: linear-gradient(90deg, black, #00ff00);
      }
      #blue {
        background-image: linear-gradient(90deg, black, #0000ff);
      }
      .rgb input[type="range"] {
        -webkit-appearance: none;
        margin: 10px 0;
        width: 100%;
        border-radius: 2px;
      }
      input[type="range"]:disabled {
        background: var(--disabled) !important;
      }
      .rgb input[type="range"]:focus {
        outline: none;
      }
      .rgb input[type="range"]::-webkit-slider-runnable-track {
        width: 100%;
        height: 7px;
        cursor: pointer;
      }
      .rgb input[type="range"]::-webkit-slider-thumb {
        height: 20px;
        width: 20px;
        border-radius: 50%;
        background: #fff;
        box-shadow: 0 0 4px 0 rgba(0, 0, 0, 1);
        cursor: pointer;
        -webkit-appearance: none;
        margin-top: -6px;
      }
      #color-slider label {
        display: block;
      }
      #color-slider input {
        width: 100%;
      }
      #color-preview {
        width: 100%;
        height: 10px;
        background-color: red;
        border-radius: 2px;
      }
      .text-center {
        text-align: center;
      }
      .hide {
        display: none !important;
      }
      .hidden {
        opacity: 0 !important;
        visibility: hidden !important;
        transition: 0.7s all;
      }
      .modal,
      .loading {
        opacity: 1;
        position: fixed;
        z-index: 10;
        visibility: visible;
        top: 0;
        left: 0;
        width: 100vw;
        height: 100vh;
        background-color: rgba(0, 0, 0, 0.5);
        backdrop-filter: blur(3px);
        display: flex;
        transition: 0.35s all;
      }
      input[type="text"], input[type="password"] {
        outline: none;
        background-color: rgba(60, 60, 60, 0.5);
        width: 100%;
        padding: 10px 15px;
        border: 1px solid #555;
        border-radius: 2px;
        color: #fff;
        box-sizing: border-box;
      }
      .isnothex {
        border-color: red !important;
      }
      .modal .container {
        background-color: var(--bg);
        border-radius: 2px;
        width: 84vw;
        margin: auto 6vw;
        box-shadow: 2px 2px 15px rgba(0, 0, 0, 0.7); /* transition: 1s display; */
      }
      .modal h3 {
        font-weight: 100;
      }
      .ml-1 {
        margin-left: 10px;
      }
      .ml-2 {
        margin-left: 20px;
      }
      .ml-3 {
        margin-left: 30px;
      }
      .mt-1 {
        margin-top: 10px;
      }
      .mt-2 {
        margin-top: 20px;
      }
      .mt-3 {
        margin-top: 30px;
      }
      .my-auto {
        margin-top: auto;
        margin-bottom: auto;
      }
      footer {
        width: 100%;
        position: absolute;
        bottom: 0;
      }
      .loader {
        margin: auto;
        border: 5px solid #ffffffa6;
        border-radius: 50%;
        width: 10vw;
        height: 10vw;
        -webkit-animation: spin 2s linear infinite; /* Safari */
        animation: spin 2s linear infinite;
        border-top: 5px solid #ffffff;
        border-bottom: 5px solid #ffffff;
      }
      @keyframes spin {
        0% {
          transform: rotate(0deg);
        }
        100% {
          transform: rotate(360deg);
        }
      }
    </style>
  </head>
  <body>
    <header class="flex">
      <h1>Hoki SmartLamp</h1>
      <button id="edit" onclick="modalEdit()">
        <svg
          xmlns="http://www.w3.org/2000/svg"
          fill="white"
          width="24"
          height="24"
          viewBox="0 0 24 24"
        >
          <path
            d="M14.078 7.061l2.861 2.862-10.799 10.798-3.584.723.724-3.585 10.798-10.798zm0-2.829l-12.64 12.64-1.438 7.128 7.127-1.438 12.642-12.64-5.691-5.69zm7.105 4.277l2.817-2.82-5.691-5.689-2.816 2.817 5.69 5.692z"
          />
        </svg>
      </button>
    </header>
    <div class="modal hidden" id="edit">
      <div class="container">
        <h3>Edit Color</h3>
        <p class="mt-1">Edit dengan kode warna</p>
        <input
          type="text"
          placeholder="contoh: #e62a2a"
          name="hex"
          id="hex"
          class="mt-2"
        />
        <div class="flex mt-2">
          <button class="btn cancel" onclick="modalEdit()">Cancel</button>
          <button class="btn apply" onclick="applyChange()">Apply</button>
        </div>
      </div>
    </div>
    <div class="loading"><div class="loader"></div></div>
    <div class="container body">
      
      <div class="modal hidden" id="wifi_connect">
        <div class="container">
          <h3>Connect to your WiFi</h3>
          <form action="/wifi/set" method="post">
            <input type="text" name="ssid" id="" placeholder="SSID" class="mt-2">
            <input type="password" name="password" id="" placeholder="Password" class="mt-2">
            <div class="flex mt-2">
              <button type="submit" class="btn apply">Connect</button>
            </div>
          </form>
        </div>
      </div>
      
      <form action="/data/set" method="POST" id="submitForm" class="my-auto">
        <div class="row-color">
          <div class="left">
            <div class="color-picker">
              <canvas id="colors" onmousemove="echoColor(event)"></canvas>
              <div id="inner-picker"></div>
              <div id="color-slider">
                <div class="mt-2 rgb">
                  <label for="red">Red</label>
                  <input
                    type="range"
                    name="red"
                    id="red"
                    min="0"
                    max="255"
                    value="255"
                  />
                </div>
                <div class="mt-2 rgb">
                  <label for="green">Green</label>
                  <input
                    type="range"
                    name="green"
                    id="green"
                    min="0"
                    max="255"
                    value="0"
                  />
                </div>
                <div class="mt-2 rgb">
                  <label for="blue">Blue</label>
                  <input
                    type="range"
                    name="blue"
                    id="blue"
                    min="0"
                    max="255"
                    value="0"
                  />
                </div>
                <div id="color-preview" class="mt-3"></div>
              </div>
            </div>
          </div>
          <div class="right text-center">
            <input
              type="range"
              name="bright"
              id="bright"
              min="0"
              max="100"
              value="255"
              class="slider ml-1"
            />
            <svg
              fill="white"
              width="24"
              height="24"
              xmlns="http://www.w3.org/2000/svg"
              fill-rule="evenodd"
              clip-rule="evenodd"
              class="ml-1 mt-1"
            >
              <path
                d="M13 24h-2c-.288 0-.563-.125-.753-.341l-.576-.659h4.658l-.576.659c-.19.216-.465.341-.753.341zm1.867-3c.287 0 .52.224.52.5s-.233.5-.52.5h-5.734c-.287 0-.52-.224-.52-.5s.233-.5.52-.5h5.734zm-2.871-17c2.983 0 6.004 1.97 6.004 5.734 0 1.937-.97 3.622-1.907 5.252-.907 1.574-1.843 3.201-1.844 5.014h1.001c0-3.286 3.75-6.103 3.75-10.266 0-4.34-3.502-6.734-7.004-6.734-3.498 0-6.996 2.391-6.996 6.734 0 4.163 3.75 6.98 3.75 10.266h.999c.001-1.813-.936-3.44-1.841-5.014-.938-1.63-1.908-3.315-1.908-5.252 0-3.764 3.017-5.734 5.996-5.734zm9.428 7.958c.251.114.362.411.248.662-.114.251-.41.363-.662.249l-.91-.414c-.252-.114-.363-.41-.249-.662.114-.251.411-.362.662-.248l.911.413zm-18.848 0c-.251.114-.362.411-.248.662.114.251.41.363.662.249l.91-.414c.252-.114.363-.41.249-.662-.114-.251-.411-.362-.662-.248l-.911.413zm18.924-2.958h-1c-.276 0-.5-.224-.5-.5s.224-.5.5-.5h1c.276 0 .5.224.5.5s-.224.5-.5.5zm-18-1c.276 0 .5.224.5.5s-.224.5-.5.5h-1c-.276 0-.5-.224-.5-.5s.224-.5.5-.5h1zm16.818-3.089c.227-.158.284-.469.126-.696-.157-.227-.469-.283-.696-.126l-.821.57c-.227.158-.283.469-.126.696.157.227.469.283.696.126l.821-.57zm-16.636 0c-.227-.158-.284-.469-.126-.696.157-.227.469-.283.696-.126l.821.57c.227.158.283.469.126.696-.157.227-.469.283-.696.126l-.821-.57zm13.333-3.033c.134-.241.048-.546-.193-.68-.241-.135-.546-.048-.68.192l-.488.873c-.135.241-.048.546.192.681.241.134.546.048.681-.193l.488-.873zm-10.03 0c-.134-.241-.048-.546.193-.68.241-.135.546-.048.68.192l.488.873c.135.241.048.546-.192.681-.241.134-.546.048-.681-.193l-.488-.873zm5.515-1.378c0-.276-.224-.5-.5-.5s-.5.224-.5.5v1c0 .276.224.5.5.5s.5-.224.5-.5v-1z"
              />
            </svg>
          </div>
        </div>
        <br />
        <div class="flex mt-3">
          <button type="button" class="btn manual" onclick="manualOption()">
            Manual
          </button>
          <button type="submit" class="btn apply" onclick="submitColor()">
            Apply
          </button>
        </div>
      </form>
    </div>
    <footer class="text-center">
      <form action="/power/set" method="post">
        <input type="text" name="power" id="power" hidden />
        <button type="submit" class="power" onclick="powerClicked()">
          <div class="inline-flex">
            <svg
              xmlns="http://www.w3.org/2000/svg"
              width="24"
              height="24"
              viewBox="0 0 24 24"
            >
              <path
                style="fill: white"
                d="M14 12h-4v-12h4v12zm4.213-10.246l-1.213 1.599c2.984 1.732 5 4.955 5 8.647 0 5.514-4.486 10-10 10s-10-4.486-10-10c0-3.692 2.016-6.915 5-8.647l-1.213-1.599c-3.465 2.103-5.787 5.897-5.787 10.246 0 6.627 5.373 12 12 12s12-5.373 12-12c0-4.349-2.322-8.143-5.787-10.246z"
              />
            </svg>
            <p>ON</p>
          </div>
        </button>
      </form>
    </footer>
    <script src="app.js"></script>
    <script>
      window.addEventListener("load", () => {
        registerServiceWorker();
      });
      function registerServiceWorker() {
        if ("serviceWorker" in navigator) {
          navigator.serviceWorker
            .register("/sw.js")
            .then((reg) => {
              console.log("Service Worker registered successfully");
            })
            .catch((e) =>
              console.error("Error during service worker registration:", e)
            );
        } else {
          console.warn("Service Worker is not supported");
        }
      }
    </script>
  </body>
</html>
)=====";

const char app_js[] PROGMEM = R"=====(
  let canvas = document.getElementById("colors");
  let graphics = canvas.getContext("2d");
  canvas.height = canvas.offsetHeight;
  canvas.width = canvas.offsetWidth;
  var CX = canvas.width / 2,
    CY = canvas.height / 2,
    sx = CX,
    sy = CY;
  for (var i = 0; i < 360; i += 0.1) {
    var rad = (i * (2 * Math.PI)) / 360;
    graphics.strokeStyle = "hsla(" + i + ", 100%, 50%, 1.0)";
    graphics.beginPath();
    graphics.moveTo(CX, CY);
    graphics.lineTo(CX + sx * Math.cos(rad), CY + sy * Math.sin(rad));
    graphics.stroke();
  }
  canvas.addEventListener("onmouseover", (e) => {
    echoColor(e);
  });

  let power = true;
  let buttonPower = document.querySelector(".power");
  let red = document.getElementById("red");
  let green = document.getElementById("green");
  let blue = document.getElementById("blue");
  let bright = document.querySelector(".slider");
  let apply = document.querySelectorAll(".apply")[1];

  let ip_local = "http://192.168.4.1"; // ganti sama IP baru kalau udah dibuat mode AP
  fetch(ip_local + "/power") 
    .then((response) => response.json())
    .then((json) => {
      power = json.power;
      
      buttonPower.firstElementChild.lastElementChild.innerText = power ? "ON" : "OFF";
      bright.disabled = red.disabled = green.disabled = blue.disabled = apply.disabled = !power
      if (!power) {
        buttonPower.classList.add("off");
      } else {
        buttonPower.classList.remove("off");
      }
    });
  fetch(ip_local + "/data")
    .then((response) => response.json())
    .then((json) => {
      red.value = json.red;
      green.value = json.green;
      blue.value = json.blue;
      bright.value = json.bright;
      setColor({
        red: json.red,
        green: json.green,
        blue: json.blue,
        bright: (json.bright * 1) / 100,
      });
      loadingState("off");
    });
  fetch(ip_local + "/wifi")
    .then((response) => response.json())
    .then((json) => {
      if (json.status == "disconnected") {
        document.getElementById("wifi_connect").classList.remove("hidden");
      }
    });

  
  function loadingState(status) {
    let newLoading = document.createElement("div");
    let loader = document.createElement("div");
    newLoading.classList.add("loading");
    loader.classList.add("loader");
    newLoading.appendChild(loader);
    if (status) {
      document.body.removeChild(document.querySelector(".loading"));
    } else document.body.appendChild(newLoading);
  }
  function powerClicked() {
    loadingState();
    power = !power;
    document.getElementById("power").value = power;
  }
  let modalClass = document.getElementById("edit");
  let showEdit = false;
  function modalEdit() {
    showEdit = !showEdit;
    if (showEdit) modalClass.classList.remove("hidden");
    else modalClass.classList.add("hidden");
  }
  window.onclick = function (event) {
    if (event.target == modalClass) {
      showEdit = !showEdit;
      modalClass.classList.add("hidden");
    }
  };
  function setColor(value) {
    document.getElementById(
      "inner-picker"
    ).style.backgroundColor = `rgba(${value.red}, ${value.green}, ${value.blue}, ${value.bright})`;
    document.getElementById(
      "color-preview"
    ).style.backgroundColor = `rgba(${value.red}, ${value.green}, ${value.blue}, ${value.bright})`;
  }
  red.addEventListener("input", (e) => {
    setColor({
      red: e.target.value,
      green: green.value,
      blue: blue.value,
      bright: (bright.value * 1) / 100,
    });
  });
  green.addEventListener("input", (e) => {
    setColor({
      red: red.value,
      green: e.target.value,
      blue: blue.value,
      bright: (bright.value * 1) / 100,
    });
  });
  blue.addEventListener("input", (e) => {
    setColor({
      red: red.value,
      green: green.value,
      blue: e.target.value,
      bright: (bright.value * 1) / 100,
    });
  });
  bright.addEventListener("input", (e) => {
    let value = (e.target.value * 1) / 100;
    let r = red.value;
    let g = green.value;
    let b = blue.value;
    setColor({ red: r, green: g, blue: b, bright: value });
  });
  function echoColor(e) {
    var imgData = graphics.getImageData(e.layerX, e.layerY, 2, 2);
    let r = imgData.data[0];
    let g = imgData.data[1];
    let b = imgData.data[2];
    let brightValue = (bright.value * 1) / 100;
    if (r != 0 || g != 0 || b != 0) {
      document.getElementById("red").value = r;
      document.getElementById("green").value = g;
      document.getElementById("blue").value = b;
      setColor({ red: r, green: g, blue: b, bright: brightValue });
    }
  }
  function hexToRgb(hex) {
    var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
    return result
      ? {
          red: parseInt(result[1], 16),
          green: parseInt(result[2], 16),
          blue: parseInt(result[3], 16),
        }
      : 1;
  }
  let hex = document.getElementById("hex");
  hex.addEventListener("input", (e) => {
    let value = e.target.value.match(/^#[a-fA-F0-9]{6}$/g);
    let button = document.querySelector(".apply");
    if (!value) {
      hex.classList.add("isnothex");
      button.disabled = true;
    } else {
      hex.classList.remove("isnothex");
      button.disabled = false;
    }
  });
  function applyChange() {
    let brightValue = (bright.value * 1) / 100;
    let value = hexToRgb(hex.value);
    try {
      document.getElementById("red").value = value.red;
      document.getElementById("green").value = value.green;
      document.getElementById("blue").value = value.blue;
      document.getElementById(
        "inner-picker"
      ).style.backgroundColor = `rgba(${value.red}, ${value.green}, ${value.blue}, ${brightValue})`;
      modalEdit();
    } catch {}
  }
  function submitColor() {
    loadingState();
    let set = {
      red: red.value,
      green: green.value,
      blue: blue.value,
      bright: bright.value,
    };
    // localStorage.setItem("lamp", JSON.stringify(set));
  }
  let hiddenColors = false;
  let color_slider = document.getElementById("color-slider");
  color_slider.classList.add("hide");
  function manualOption() {
    hiddenColors = !hiddenColors;
    let inner_picker = document.getElementById("inner-picker");
    let colorbg = document.querySelector(".color-picker");
    let color = document.getElementById("colors");
    document.querySelector(".manual").innerText = hiddenColors
      ? "BACK"
      : "MANUAL";
    if (hiddenColors) {
      color_slider.classList.remove("hide");
      color.classList.add("hide");
      inner_picker.classList.add("hide");
      colorbg.classList.add("remove-before");
    } else {
      color_slider.classList.add("hide");
      color.classList.remove("hide");
      inner_picker.classList.remove("hide");
      colorbg.classList.remove("remove-before");
    }
  }
)=====";