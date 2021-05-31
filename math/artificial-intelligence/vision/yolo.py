import sys
import numpy as np
import cv2

model = 'data/yolov3.weights'
config = 'data/yolov3.cfg'
class_labels = 'data/coco.names'
confThreshold = 0.5
nmsThreshold = 0.4
img_files = ['data/dog.jpg', 'data/person.jpg', 'data/sheep.jpg', 'data/kite.jpg']

net = cv2.dnn.readNet(model, config)

classes = []
with open(class_labels, 'rt') as f:
    classes = f.read().rstrip('\n').split('\n')

colors = np.random.uniform(0, 255, size=(len(classes), 3))

# ['yolo_82', 'yolo_94', 'yolo_106']
layer_names = net.getLayerNames()
output_layers = [layer_names[i[0] - 1] for i in net.getUnconnectedOutLayers()]

for f in img_files:
    img = cv2.imread(f)

    blob = cv2.dnn.blobFromImage(img, 1/255., (320, 320), swapRB=True)
    net.setInput(blob)
    outs = net.forward(output_layers)   # [(507 * 85), (2028, 85), (8112, 85)]
    h, w = img.shape[:2]

    class_ids, confidences, boxes = [], [], []

    for out in outs:
        for detection in out:
            # detection: 4(bounding box) + 1(objectness_score) + 80(class confidence)
            scores = detection[5:]
            class_id = np.argmax(scores)
            confidence = scores[class_id]
            if confidence > confThreshold:
                cx, cy = int(detection[0] * w), int(detection[1] * h)
                bw, bh = int(detection[2] * w), int(detection[3] * h)

                boxes.append([int(cx - bw / 2), int(cy - bh / 2), bw, bh])
                confidences.append(float(confidence))
                class_ids.append(int(class_id))

    indices = cv2.dnn.NMSBoxes(boxes, confidences, confThreshold, nmsThreshold)

    for i in indices:
        i = i[0]
        sx, sy, bw, bh = boxes[i]
        label = f'{classes[class_ids[i]]}: {confidences[i]:.2}'
        color = colors[class_ids[i]]
        cv2.rectangle(img, (sx, sy, bw, bh), color, 2)
        cv2.putText(img, label, (sx, sy - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.7, color, 2, cv2.LINE_AA)

    t, _ = net.getPerfProfile()
    label = f'Inference time: {(t * 1000.0 / cv2.getTickFrequency()):.2f} ms'
    cv2.putText(img, label, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 1, cv2.LINE_AA)

    cv2.imshow('img', img)
    cv2.waitKey()

cv2.destroyAllWindows()
