# Plus d'infos et mise en place du script : https://youtu.be/E2Jvn0DYJkY

from gpiozero import LED
from time import sleep

led = LED(21)

while True:
    led.on()
    sleep(1)
    led.off()
    sleep(1)
