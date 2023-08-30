/*
 * primary HTML for the OV2640 camera module
 */

const uint8_t index_ov2640_html[] = R"=====(<!doctype html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width,initial-scale=1">
    <title>ESP32 OV2640</title>
    <link rel="icon" type="image/png" sizes="32x32" href="/favicon-32x32.png">
    <link rel="icon" type="image/png" sizes="16x16" href="/favicon-16x16.png">
    <link rel="stylesheet" type="text/css" href="/style.css">
    <style>

    </style>
  </head>

  <body>
    <section class="main">
      <div id="logo">
        <label for="nav-toggle-cb" id="nav-toggle" style="float:left;">&#9776;&nbsp;&nbsp;Settings&nbsp;&nbsp;&nbsp;&nbsp;</label>
        <button id="swap-viewer" style="float:left;" title="Swap to simple viewer">Simple</button>

        <button id="toggle-stream" style="float:left;" class="hidden">Start Stream</button>
        <div id="wait-settings" style="float:left;" class="loader" title="Waiting for camera settings to load"></div>
      </div>
      <div id="content">
        <div class="hidden" id="sidebar">
          <input type="checkbox" id="nav-toggle-cb" checked="checked">
            <nav id="menu">
              <div class="input-group hidden" id="lamp-group" title="Flashlight LED.&#013;&#013;Warning:&#013;Built-In lamps can be Very Bright! Avoid looking directly at LED&#013;Can draw a lot of power and may cause visual artifacts, affect WiFi or even brownout the camera on high settings">
                <label for="lamp">Light</label>
                <div class="range-min">Off</div>
                <input type="range" id="lamp" min="0" max="100" value="0" class="default-action">
                <div class="range-max"><span style="font-size: 125%;">&#9888;</span>Full</div>
              </div>
              </div>
              <div class="input-group" id="preferences-group">
                <label for="prefs" style="line-height: 2em;">Preferences</label>
                <button id="reboot" title="Reboot the camera module">Reboot</button>
                <button id="save_prefs" title="Save Preferences on camera module">Save</button>
                <button id="clear_prefs" title="Erase saved Preferences on camera module">Erase</button>
              </div>
              <div class="input-group" id="cam_name-group">
                <label for="cam_name">
                <a href="/dump" title="System Info" target="_blank">Name</a></label>
                <div id="cam_name" class="default-action"></div>
              </div>
              <div class="input-group" id="code_ver-group">
                <label for="code_ver">
                <a href="https://github.com/easytarget/esp32-cam-webserver"
                  title="ESP32 Cam Webserver on GitHub" target="_blank">Firmware</a></label>
                <div id="code_ver" class="default-action"></div>
              </div>
              <div class="input-group hidden" id="stream-group">
                <label for="stream_url" id="stream_link">Stream</label>
                <div id="stream_url" class="default-action">Unknown</div>
              </div>
            </nav>
        </div>
        <figure>
          <div id="stream-container" class="image-container hidden">
            <div class="close close-rot-none" id="close-stream">×</div>
            <img id="stream" src="">
          </div>
        </figure>
      </div>
    </section>
  </body>

  <script>
  document.addEventListener('DOMContentLoaded', function (event) {
    var baseHost = document.location.origin;
    var streamURL = 'Undefined';
    var viewerURL = 'Undefined';

    const header = document.getElementById('logo')
    const settings = document.getElementById('sidebar')
    const waitSettings = document.getElementById('wait-settings')
    const lampGroup = document.getElementById('lamp-group')

    const streamGroup = document.getElementById('stream-group')
    const camName = document.getElementById('cam_name')
    const codeVer = document.getElementById('code_ver')
    // const rotate = document.getElementById('rotate')
    const view = document.getElementById('stream')
    const viewContainer = document.getElementById('stream-container')
    const stillButton = document.getElementById('get-still')
    const streamButton = document.getElementById('toggle-stream')
    const closeButton = document.getElementById('close-stream')
    const streamLink = document.getElementById('stream_link')
    const framesize = document.getElementById('framesize')

    const swapButton = document.getElementById('swap-viewer')
    const savePrefsButton = document.getElementById('save_prefs')
    const clearPrefsButton = document.getElementById('clear_prefs')
    const rebootButton = document.getElementById('reboot')
    const minFrameTime = document.getElementById('min_frame_time')

    const hide = el => {
      el.classList.add('hidden')
    }
    const show = el => {
      el.classList.remove('hidden')
    }

    const disable = el => {
      el.classList.add('disabled')
      el.disabled = true
    }

    const enable = el => {
      el.classList.remove('disabled')
      el.disabled = false
    }

    const updateValue = (el, value, updateRemote) => {
      updateRemote = updateRemote == null ? true : updateRemote
      let initialValue
      if (el.type === 'checkbox') {
        initialValue = el.checked
        value = !!value
        el.checked = value
      } else {
        initialValue = el.value
        el.value = value
      }

      if (updateRemote && initialValue !== value) {
        updateConfig(el);
      } else if(!updateRemote){
        if(el.id === "aec"){
          value ? hide(exposure) : show(exposure)

        } else if(el.id === "lamp"){
          if (value == -1) {
            hide(lampGroup)
            hide(autolampGroup)
          } else {
            show(lampGroup)
            show(autolampGroup)
          }
        } else if(el.id === "cam_name"){
          camName.innerHTML = value;
          window.document.title = value;
          console.log('Name set to: ' + value);
        } else if(el.id === "code_ver"){
          codeVer.innerHTML = value;
          console.log('Firmware Build: ' + value);
        
        } else if(el.id === "min_frame_time"){
          min_frame_time.value = value;
        } else if(el.id === "stream_url"){
          streamURL = value;
          viewerURL = value + 'view';
          stream_url.innerHTML = value;
          stream_link.setAttribute("title", `Open the standalone stream viewer :: ${viewerURL}`);
          stream_link.style.textDecoration = "underline";
          stream_link.style.cursor = "pointer";
          streamButton.setAttribute("title", `Start the stream :: ${streamURL}`);
          show(streamGroup)
          console.log('Stream URL set to: ' + streamURL);
          console.log('Stream Viewer URL set to: ' + viewerURL);
        }
      }
    }

    var rangeUpdateScheduled = false
    var latestRangeConfig

    function updateRangeConfig (el) {
      latestRangeConfig = el
      if (!rangeUpdateScheduled) {
        rangeUpdateScheduled = true;
        setTimeout(function(){
          rangeUpdateScheduled = false
          updateConfig(latestRangeConfig)
        }, 150);
      }
    }

    function updateConfig (el) {
      let value
      switch (el.type) {
        case 'checkbox':
          value = el.checked ? 1 : 0
          break
        case 'range':
        case 'number':
        case 'select-one':
          value = el.value
          break
        case 'button':
        case 'submit':
          value = '1'
          break
        default:
          return
      }

      const query = `${baseHost}/control?var=${el.id}&val=${value}`

      fetch(query)
        .then(response => {
          console.log(`request to ${query} finished, status: ${response.status}`)
        })
    }

    document
      .querySelectorAll('.close')
      .forEach(el => {
        el.onclick = () => {
          hide(el.parentNode)
        }
      })

    // read initial values
    fetch(`${baseHost}/status`)
      .then(function (response) {
        return response.json()
      })
      .then(function (state) {
        document
          .querySelectorAll('.default-action')
          .forEach(el => {
            updateValue(el, state[el.id], false)
          })
        hide(waitSettings);
        show(settings);
        show(streamButton);
        //startStream();
      })

 

    const stopStream = () => {
      window.stop();
      streamButton.innerHTML = 'Start Stream';
      streamButton.setAttribute("title", `Start the stream :: ${streamURL}`);
      hide(viewContainer);
    }

    const startStream = () => {
      view.src = streamURL;
      view.scrollIntoView(false);
      streamButton.innerHTML = 'Stop Stream';
      streamButton.setAttribute("title", `Stop the stream`);
      show(viewContainer);
    }

    // Attach actions to controls

    streamLink.onclick = () => {
      stopStream();
      window.open(viewerURL, "_blank");
    }

    closeButton.onclick = () => {
      stopStream();
      hide(viewContainer);
    }

    streamButton.onclick = () => {
      const streamEnabled = streamButton.innerHTML === 'Stop Stream'
      if (streamEnabled) {
        stopStream();
      } else {
        startStream();
      }
    }

    // Attach default on change action
    document
      .querySelectorAll('.default-action')
      .forEach(el => {
        el.onchange = () => updateConfig(el)
      })

    // Update range sliders as they are being moved
    document
      .querySelectorAll('input[type="range"]')
      .forEach(el => {
        el.oninput = () => updateRangeConfig(el)
      })



    // Detection and framesize


    framesize.onchange = () => {
      updateConfig(framesize)
    }

    minFrameTime.onchange = () => {
      updateConfig(minFrameTime)
    }



    swapButton.onclick = () => {
      window.open('/?view=simple','_self');
    }

    savePrefsButton.onclick = () => {
      if (confirm("Save the current preferences?")) {
        updateConfig(savePrefsButton);
      }
    }

    clearPrefsButton.onclick = () => {
      if (confirm("Remove the saved preferences?")) {
        updateConfig(clearPrefsButton);
      }
    }

    rebootButton.onclick = () => {
      if (confirm("Reboot the Camera Module?")) {
        updateConfig(rebootButton);
        // Some sort of countdown here?
        hide(settings);
        hide(viewContainer);
        header.innerHTML = '<h1>Rebooting!</h1><hr>Page will reload after 30 seconds.';
        setTimeout(function() {
          location.replace(document.URL);
        }, 30000);
      }
    }

  })
  </script>

  <style>
  body {
    font-family: Arial,Helvetica,sans-serif;
    background: #181818;
    color: #EFEFEF;
    font-size: 16px
  }

  a {
    color: #EFEFEF;
    text-decoration: underline
  }

  h2 {
    font-size: 18px
  }

  section.main {
    display: flex
  }

  #menu,section.main {
    flex-direction: column
  }

  #menu {
    display: none;
    flex-wrap: nowrap;
    color: #EFEFEF;
    width: 380px;
    background: #363636;
    padding: 8px;
    border-radius: 4px;
    margin-top: -10px;
    margin-right: 10px;
  }

  figure {
    padding: 0px;
    margin: 0;
    margin-block-start: 0;
    margin-block-end: 0;
    margin-inline-start: 0;
    margin-inline-end: 0
  }

  figure img {
    display: block;
    max-width: 100%;
    width: auto;
    height: auto;
    border-radius: 4px;
    margin-top: 8px;
  }

  section#buttons {
    display: flex;
    flex-wrap: nowrap;
    justify-content: space-between
  }

  #nav-toggle {
    cursor: pointer;
    display: block
  }

  #nav-toggle-cb {
    outline: 0;
    opacity: 0;
    width: 0;
    height: 0
  }

  #nav-toggle-cb:checked+#menu {
    display: flex
  }

  #quality {
      transform: rotateY(180deg);
  }

  .input-group {
    display: flex;
    flex-wrap: nowrap;
    line-height: 22px;
    margin: 5px 0
  }

  .input-group>label {
    display: inline-block;
    padding-right: 10px;
    min-width: 47%
  }

  .input-group input,.input-group select {
    flex-grow: 1
  }

  .range-max,.range-min {
    display: inline-block;
    padding: 0 5px
  }

  button {
    display: block;
    margin: 3px;
    padding: 0 8px;
    border: 0;
    line-height: 28px;
    cursor: pointer;
    color: #fff;
    background: #ff3034;
    border-radius: 5px;
    font-size: 16px;
    outline: 0
  }

  button:hover {
    background: #ff494d
  }

  button:active {
    background: #f21c21
  }

  button.disabled {
    cursor: default;
    background: #a0a0a0
  }

  input[type=range] {
    -webkit-appearance: none;
    width: 0;
    height: 22px;
    background: #363636;
    cursor: pointer;
    margin: 0
  }

  input[type=range]:focus {
    outline: 0
  }

  input[type=range]::-webkit-slider-runnable-track {
    width: 100%;
    height: 2px;
    cursor: pointer;
    background: #EFEFEF;
    border-radius: 0;
    border: 0 solid #EFEFEF
  }

  input[type=range]::-webkit-slider-thumb {
    border: 1px solid rgba(0,0,30,0);
    height: 22px;
    width: 22px;
    border-radius: 50px;
    background: #ff3034;
    cursor: pointer;
    -webkit-appearance: none;
    margin-top: -11.5px
  }

  input[type=range]:focus::-webkit-slider-runnable-track {
    background: #EFEFEF
  }

  input[type=range]::-moz-range-track {
    width: 100%;
    height: 2px;
    cursor: pointer;
    background: #EFEFEF;
    border-radius: 0;
    border: 0 solid #EFEFEF
  }

  input[type=range]::-moz-range-thumb {
    border: 1px solid rgba(0,0,30,0);
    height: 22px;
    width: 22px;
    border-radius: 50px;
    background: #ff3034;
    cursor: pointer
  }

  input[type=range]::-ms-track {
    width: 100%;
    height: 2px;
    cursor: pointer;
    background: 0 0;
    border-color: transparent;
    color: transparent
  }

  input[type=range]::-ms-fill-lower {
    background: #EFEFEF;
    border: 0 solid #EFEFEF;
    border-radius: 0
  }

  input[type=range]::-ms-fill-upper {
    background: #EFEFEF;
    border: 0 solid #EFEFEF;
    border-radius: 0
  }

  input[type=range]::-ms-thumb {
    border: 1px solid rgba(0,0,30,0);
    height: 22px;
    width: 22px;
    border-radius: 50px;
    background: #ff3034;
    cursor: pointer;
    height: 2px
  }

  input[type=range]:focus::-ms-fill-lower {
    background: #EFEFEF
  }

  input[type=range]:focus::-ms-fill-upper {
    background: #363636
  }

  input[type=text] {
    border: 1px solid #363636;
    font-size: 14px;
    height: 20px;
    margin: 1px;
    outline: 0;
    border-radius: 5px
  }

  .switch {
    display: block;
    position: relative;
    line-height: 22px;
    font-size: 16px;
    height: 22px
  }

  .switch input {
    outline: 0;
    opacity: 0;
    width: 0;
    height: 0
  }

  .slider {
    width: 50px;
    height: 22px;
    border-radius: 22px;
    cursor: pointer;
    background-color: grey
  }

  .slider,.slider:before {
    display: inline-block;
    transition: .4s
  }

  .slider:before {
    position: relative;
    content: "";
    border-radius: 50%;
    height: 16px;
    width: 16px;
    left: 4px;
    top: 3px;
    background-color: #fff
  }

  input:checked+.slider {
    background-color: #ff3034
  }

  input:checked+.slider:before {
    -webkit-transform: translateX(26px);
    transform: translateX(26px)
  }

  select {
    border: 1px solid #363636;
    font-size: 14px;
    height: 22px;
    outline: 0;
    border-radius: 5px
  }

  .image-container {
    position: relative;
    min-width: 160px;
    transform-origin: top left
  }

  .close {
    position: absolute;
    z-index: 99;
    background: #ff3034;
    width: 16px;
    height: 16px;
    border-radius: 100px;
    color: #fff;
    text-align: center;
    line-height: 18px;
    cursor: pointer
  }

  .close-rot-none {
    left: 5px;
    top: 5px;
  }

  .close-rot-left {
    right: 5px;
    top: 5px;
  }

  .close-rot-right {
    left: 5px;
    bottom: 5px;
  }

  .hidden {
    display: none
  }

  .inline-button {
    line-height: 20px;
    margin: 2px;
    padding: 1px 4px 2px 4px;
  }

  .loader {
    border: 0.5em solid #f3f3f3; /* Light grey */
    border-top: 0.5em solid #000000; /* white */
    border-radius: 50%;
    width: 1em;
    height: 1em;
    -webkit-animation: spin 2s linear infinite; /* Safari */
    animation: spin 2s linear infinite;
  }

  @-webkit-keyframes spin {   /* Safari */
    0% { -webkit-transform: rotate(0deg); }
    100% { -webkit-transform: rotate(360deg); }
  }

  @keyframes spin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
  }

  @media (min-width: 800px) and (orientation:landscape) {
    #content {
      display:flex;
      flex-wrap: nowrap;
      align-items: stretch
    }
  }
</style>
</html>)=====";

size_t index_ov2640_html_len = sizeof(index_ov2640_html)-1;
