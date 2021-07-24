from threading import Thread
import spam

groups = []
for i in range(5):
  groups.append([str(val) for val in range(i)])

threads = [Thread(target=spam.print_list, args=(group, )) for group in groups]
[t.start() for t in threads]
[t.join() for t in threads]
