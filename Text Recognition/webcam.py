# import cv2



# cap = cv2.VideoCapture(0)

# while cap.isOpened():
#     ret, frame = cap.read()
#     if ret:
#         cv2.imshow('frame', frame)
#         if cv2.waitKey(1) == ord('q'):
#             break
#     else:
#         break

import cv2
import urllib.request
import numpy as np

# change the IP address below according to the
# IP shown in the Serial monitor of Arduino code
url='http://192.168.4.1/cam-lo.jpg'

cv2.namedWindow("ESP32-CAM Live Stream", cv2.WINDOW_AUTOSIZE)

while True:
    img_resp = urllib.request.urlopen(url)
    imgnp = np.array(bytearray(img_resp.read()), dtype=np.uint8)
    frame = cv2.imdecode(imgnp, -1)

    cv2.imshow("ESP32-CAM Live Stream", frame)
    
    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        break

cv2.destroyAllWindows()
