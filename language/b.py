import argparse
from threading import Thread
# from CountsPerSec import CountsPerSec
import cv2
from datetime import datetime


class CountsPerSec:
  def __init__(self):
    self._start_time = datetime.now()
    self._num_occurrences = 0

  def increment(self):
    self._num_occurrences += 1

  def countsPerSec(self):
    return self._num_occurrences / (datetime.now() - self._start_time).total_seconds()


class VideoShow:
  def __init__(self, frame=None):
    self.frame = frame
    self.stopped = False

  def start(self):
    Thread(target=self.show, args=()).start()
    return self

  def show(self):
    while not self.stopped:
      cv2.imshow("Video", self.frame)
      if cv2.waitKey(1) == ord("q"):
        self.stopped = True

  def stop(self):
    self.stopped = True


def noThreading(source=0):
  cap = cv2.VideoCapture(source)
  cps = CountsPerSec()

  while True:
    (grabbed, frame) = cap.read()
    if not grabbed or cv2.waitKey(1) == ord("q"):
      break

    cv2.putText(frame, f"{cps.countsPerSec():.0f} iterations/sec", (10, 450), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (255, 255, 255))
    cv2.imshow("Video", frame)
    cps.increment()


def threadVideoShow(source=0):
  cap = cv2.VideoCapture(source)
  (grabbed, frame) = cap.read()
  video_shower = VideoShow(frame).start()
  cps = CountsPerSec()

  while True:
    (grabbed, frame) = cap.read()
    if not grabbed or video_shower.stopped:
      video_shower.stop()
      break

    frame = putIterationsPerSec(frame, cps.countsPerSec())
    video_shower.frame = frame
    cps.increment()


if __name__ == "__main__":
  threadVideoShow()
