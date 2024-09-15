import os
import cv2
import time
import signal 
from PIL import Image
from pathlib import Path
from ultralytics import YOLO
 


model = YOLO("ai/fire.pt")
image_files = ["img/left.jpg", "img/right.jpg", "img/front.jpg"]
ppid = os.getppid()


def sigusr1_handler(signum, frame): 
    for image_file in image_files:

        if not os.path.isfile(image_file):
            os.kill(ppid, signal.SIGUSR1);
            return

        img = Image.open(image_file)
 
        results = model(img)
        result = results[0]

        if len(result) > 0 and len(result[0].boxes.xyxy) > 0:
            output_path = Path(image_file).stem + '.txt'
            print(output_path)

            with open(output_path, 'w') as f:
                for box in result[0].boxes.xyxy.cpu().numpy():
                    xmin, ymin, xmax, ymax = box  # Unpack the coordinates
                    f.write("{:.2f} {:.2f}\n".format((xmax-xmin)/2.0, (ymax-ymin)/2.0))

    os.kill(ppid, signal.SIGUSR1);


signal.signal(signal.SIGUSR1, sigusr1_handler)
os.kill(ppid, signal.SIGUSR1)

while(1):
    time.sleep(1)
