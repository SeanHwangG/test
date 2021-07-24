from rest_framework import viewsets

from task import models
from .serializers import TaskSerializer


class TaskViewSet(viewsets.ModelViewSet):
  queryset = models.Task.objects.all()
  serializer_class = TaskSerializer
