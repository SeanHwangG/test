# Game

## Keyboard

{% tabs %}
{% tab title='python' %}

```py
import pygame

pygame.init()
win = pygame.display.set_mode((500, 500))
pygame.display.set_caption("First game")
x, y = 50, 50
width, height, vel = 30, 30, 5
run = True
while run:
  pygame.time.delay(100)
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      run = False
    keys = pygame.key.get_pressed()

    if keys[pygame.K_LEFT]:
      x -= vel
    if keys[pygame.K_RIGHT]:
      x += vel
    if keys[pygame.K_UP]:
      y -= vel
    if keys[pygame.K_DOWN]:
      y += vel

  win.fill((0, 0, 0))
  pygame.draw.rect(win, (255, 0, 0), (x, y, width, height))
  pygame.display.update()
```

{% endtab %}
{% endtabs %}

{% repo '2048' %}
{% repo 'snake' %}

## Turn based

{% include '.game.prob' %}
