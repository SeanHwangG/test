import cv2
import numpy as np


def save_memory(data_path, algo="BS"):
  cap = cv2.VideoCapture(data_path)
  _, back = cap.read()

  back = cv2.cvtColor(back, cv2.COLOR_BGR2GRAY)
  back = cv2.GaussianBlur(back, (0, 0), 1)    # remove noise from background

  if algo == "MA":
    fback = back.astype(np.float32)
  elif algo == "MOG":
    bs = cv2.createBackgroundSubtractorMOG2()

  while True:
    _, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # remove noise from background
    gray = cv2.GaussianBlur(gray, (0, 0), 1.0)

    if algo == "MA":
      cv2.accumulateWeighted(gray, fback, 0.01)
      back = fback.astype(np.uint8)
    elif algo == "MOG":
      diff = bs.apply(gray)
      back = bs.getBackgroundImage()

    diff = cv2.absdiff(gray, back)
    _, diff = cv2.threshold(diff, 30, 255, cv2.THRESH_BINARY)

    cnt, _, stats, _ = cv2.connectedComponentsWithStats(diff)
    for i in range(1, cnt):
      x, y, w, h, s = stats[i]
      if s < 80:
        continue
      cv2.rectangle(frame, (x, y, w, h), (255, 255, 255), 2)

    cv2.imshow('fgmask', frame)

    if cv2.waitKey(2) == 27:
      break


def capture_video():
  cap = cv2.VideoCapture('data/play.mov')

  while cap.isOpened():
    _, frame = cap.read()
    cv2.imshow('frame', frame)
    key = cv2.waitKey(-1)
    if key == ord('q'):
      break


save_memory("data/play.mov")
