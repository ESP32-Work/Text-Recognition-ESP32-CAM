# Text Recognition using ESP32-CAM and OCR

## Table of Contents
1. [Overview](#overview)
2. [Requirements](#requirements)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Code Explanation](#code-explanation)
    - [Esp Code](#esp-code)
    - [Python Code](#python-code)
6. [Demo](#demo)
7. [Libraries Used](#libraries-used)
8. [Extension for VS Code](#extension-for-vs-code)
9. [Clone and Implementation](#clone-and-implementation)
10. [Contributing](#contributing)
11. [License](#license)

## Overview
This project utilizes an ESP32-CAM module to capture images, perform Optical Character Recognition (OCR) using Tesseract, and display the live stream with extracted text. The ESP32-CAM serves the images through a local web server, and a Python script on the client side processes the stream for text extraction.

## Requirements
- ESP32-CAM module
- Arduino IDE or PlatformIO extension for VS Code
- Python
- Tesseract OCR
- OpenCV library for Python

## Installation
1. Clone this repository.
2. Upload the code to the ESP32-CAM using Arduino IDE or PlatformIO in VS Code.
3. Ensure Python is installed on your system.
4. Install required Python libraries using:
    ```bash
    pip install numpy 
    pip install opencv-python 
    ```
5. Install Tesseract OCR. Refer to [Tesseract Installation Guide](https://github.com/tesseract-ocr/tesseract).
    ```bash
    sudo apt install tesseract-ocr -y
    pip install pytesseract
    ```

## Usage
1. Power up the ESP32-CAM and connect to its access point (AP) with the provided SSID and password.
2. Run the Python script on your local machine.
3. The live stream with extracted text will be displayed on your screen.

## Code Explanation

### Esp32 Code
The code configures the ESP32-CAM, sets up a web server, and handles different image resolutions. It uses the `esp32cam` library to capture images and serve them through HTTP.

Snippet:
```cpp
// Arduino Code Snippet
// (Refer to the full Arduino code in main.cpp)
#include <WebServer.h>
#include <WiFi.h>
#include <esp32cam.h>
#include <SPI.h>
#include <Wire.h>

// ...

void serveJpg() {
  // Capture image and serve as JPEG
}

// ...
```
### Python Code
The Python script reads the live stream from the ESP32-CAM, performs OCR using Tesseract, and displays the stream with extracted text using OpenCV.
Snippet:
```python
# Python Code Snippet
# (Refer to the full Python code in main.py)
import cv2
import urllib.request
import numpy as np
import pytesseract

# ...

while True:
    # Read live stream from ESP32-CAM
    img_resp = urllib.request.urlopen(url)
    imgnp = np.array(bytearray(img_resp.read()), dtype=np.uint8)
    frame = cv2.imdecode(imgnp, -1)

    # Extract text using Tesseract
    text = pytesseract.image_to_string(frame, config='--psm 6')

    # ...

    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break

cv2.destroyAllWindows()
```

## Demo

[Screencast from 12-14-2023 01:27:30 AM.webm](https://github.com/ESP32-Work/Text-Recognition-ESP32-CAM/assets/81290322/b9acfa72-a46f-4536-a052-0e22f2cb0e27)

## Libraries Used
- WebServer
- WiFi
- esp32cam
- OpenCV
- Pytesseract

## Extension for VS Code
To develop and upload code to ESP32 using VS Code, install the PlatformIO extension.

## Clone and Implementation
```bash
git clone https://github.com/ESP32-Work/Text-Recognition-ESP32-CAM
```

Open the project in VS Code with PlatformIO extension installed. Upload the Arduino code to the ESP32-CAM and run the Python script.

Move to the directory containing the python script. Ensure that it is executable.
```bash
chmod +x webcam.py
``` 
Run the script.
```bash
python webcam.py  or ./webcam.py
```

## Contributing
Contributions are welcome! Open an issue or create a pull request to contribute.

## License
This project is licensed under the [MIT](LICENSE) License.

