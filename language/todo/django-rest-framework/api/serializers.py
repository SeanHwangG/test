from rest_framework import serializers
from task import models


class TaskSerializer(serializers.ModelSerializer):
  class Meta:
    fields = ('id', 'title', 'description')
    model = models.Task
