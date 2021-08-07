# Design

> Term

* Tech debt: temporarily speed up for new features, but gradually slow your progress
  * business pressure, lack of understanding of consequence of it, lack of tests / documentation / interactions
  * delayed refactoring, long-term simultaneous development, lack of compliance monitoring, incompetence
* Refactor: Seperate commit with new functionality
  * Rule of three (start refactor after 3 similar things), adding new feature of others, fixing a bug, code review

{% tabs %}
{% tab title='python' %}

```py
""" 1. Replace temp with Query """
# BAD
def calculateTotal():
  basePrice = quantity * itemPrice
  if basePrice > 1000:
    return basePrice * 0.95
  else:
    return basePrice * 0.98

class Report:
  def sendReport(self):
    nextDay = Date(self.previousEnd.getYear(), self.previousEnd.getMonth(), self.previousEnd.getDate() + 1)

# Good
def calculateTotal():
  if basePrice() > 1000:
    return basePrice() * 0.95
  else:
    return basePrice() * 0.98

def basePrice():
  return quantity * itemPrice

class Report:
  def sendReport(self):
    newStart = self._nextDay(self.previousEnd)

  def _nextDay(self, arg):
    return Date(arg.getYear(), arg.getMonth(), arg.getDate() + 1)

""" 2. Split temporary varialbe """
# BAD
temp = 2 * (height + width)
print(temp)
temp = height * width
print(temp)

# Good
perimeter = 2 * (height + width)
print(perimeter)
area = height * width
print(area)

# 3. Shorter codes
""" BAD """
class PizzaDelivery:
  def getRating(self):
    return 2 if self.moreThanFiveLateDeliveries() else 1

  def moreThanFiveLateDeliveries(self):
    return self.numberOfLateDeliveries > 5

""" GOOD """
class PizzaDelivery:
  def getRating(self):
    return 2 if self.numberOfLateDeliveries > 5 else 1
```

{% endtab %}
{% endtabs %}

{% link 'tinyurl' %}

{% link 'pastebin' %}

> Reference

* [Refactoring Guru](https://refactoring.guru/refactoring/techniques/composing-methods)

## Management

{% link 'classroom' %}

{% link 'parking-lots' %}

{% link 'library' %}

## Purchase

{% link 'atm' %}

{% link 'movie-ticket' %}

## Request Based

{% link 'tinyurl' %}

{% link 'pastebin' %}

## Video

{% link 'youtube' %}
