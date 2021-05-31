import pygame


pygame.init()

WIN_SIZE = 500
win = pygame.display.set_mode((WIN_SIZE, WIN_SIZE))
pygame.display.set_caption("First Game")

walkRight = [pygame.image.load('image/R1.png'), pygame.image.load('image/R2.png'), pygame.image.load('image/R3.png'), pygame.image.load('image/R4.png'),
             pygame.image.load('image/R5.png'), pygame.image.load('image/R6.png'), pygame.image.load('image/R7.png'), pygame.image.load('image/R8.png'), pygame.image.load('image/R9.png')]
walkLeft = [pygame.image.load('image/L1.png'), pygame.image.load('image/L2.png'), pygame.image.load('image/L3.png'), pygame.image.load('image/L4.png'),
            pygame.image.load('image/L5.png'), pygame.image.load('image/L6.png'), pygame.image.load('image/L7.png'), pygame.image.load('image/L8.png'), pygame.image.load('image/L9.png')]
bg = pygame.image.load('image/bg.jpg')
char = pygame.image.load('image/standing.png')

x, y = 50, 300
width, height = 40, 60
vel = 5

jumping, left, right = False, False, False
walk_tick, jump_tick = 0, 10
run = True

while run:
  pygame.time.delay(10)

  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      run = False

  keys = pygame.key.get_pressed()

  if keys[pygame.K_LEFT] and x > vel:
    x -= vel
    left, right = True, False

  elif keys[pygame.K_RIGHT] and x < WIN_SIZE - vel - width:
    x += vel
    left, right = False, True

  else:  # If character is not moving set both left and right false and reset the animation counter (walk_tick)
    left, right = False, False
    walk_tick = 0

  if jumping:
    if jump_tick >= -10:
      y -= (jump_tick * abs(jump_tick)) * 0.5
      jump_tick -= 1
    else:
      jump_tick = 10
      jumping = False
  elif keys[pygame.K_SPACE]:
    jumping, left, right = True, False, False
    walk_tick = 0

  win.blit(bg, (0, 0))
  if walk_tick + 1 >= 27:
    walk_tick = 0

  if left:
    win.blit(walkLeft[walk_tick // 3], (x, y))  # // 3 to ensure each image is shown 3 times every animation
    walk_tick += 1
  elif right:
    win.blit(walkRight[walk_tick // 3], (x, y))
    walk_tick += 1
  else:
    win.blit(char, (x, y))  # If the character is standing still

  pygame.display.update()

pygame.quit()
