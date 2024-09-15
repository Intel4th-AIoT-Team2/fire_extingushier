import os
import cv2
import time
import signal 
from PIL import Image
from pathlib import Path
from ultralytics import YOLO
 


model = YOLO("fire.pt")
image_folder = 'img' 
image_files = ["left.jpg", "right.jpg", "front.jpg"]
ppid = os.getppid()


def sigusr1_handler(signum, frame): 
    for image_file in image_files:
        image_path = os.path.join(image_folder, image_file)
        img = Image.open(image_path)
        results = model(img)
        result = results[0]

        if len(result) > 0 and len(result[0].boxes.xyxy) > 0:
            output_path = Path(image_path).stem + '.txt'
            output_path = os.path.join(image_folder, output_path)

            print(output_path)
            with open(output_path, 'w') as f:
                for box in result[0].boxes.xyxy.cpu().numpy():
                    xmin, ymin, xmax, ymax = box  # Unpack the coordinates
                    f.write("{:.2f} {:.2f} {:.2f} {:.2f}\n".format(xmin, ymin, xmax, ymax))
    os.kill(ppid, signal.SIGUSR1);

signal.signal(signal.SIGUSR1, sigusr1_handler)
os.kill(ppid, signal.SIGUSR1);

while(1):
    time.sleep(1)
