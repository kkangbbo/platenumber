import cv2
import pytesseract
import time
import os
import serial

sp  = serial.Serial('COM3', 9600, timeout=1)

pytesseract.pytesseract.tesseract_cmd = r'C:/Program Files/Tesseract-OCR/tesseract'

output_folder = 'C:/platenumber/captured_images/'

os.makedirs(output_folder, exist_ok=True)

capture = cv2.VideoCapture(1)

capture_interval = 5

start_time = time.time()

try:
    while True:
        current_time = time.time()

        if current_time - start_time >= capture_interval:
            ret, frame = capture.read()

            if ret:
                filename = f"{output_folder}{time.strftime('%Y%m%d_%H%M%S')}.jpg"
                cv2.imwrite(filename, frame)

                start_time = current_time

                result = pytesseract.image_to_string(frame, lang='kor')
                print(result)
                print(result[0:2])
                print(result[5:9])
                
                tx_dat = "num"+ result[0:2] + "  " + result[5:9] + "        " + "\n"
                sp.write(tx_dat.encode())

                cv2.imshow("Captured Image", frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

finally:
    capture.release()
    cv2.destroyAllWindows()
