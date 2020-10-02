
# Plus d'infos et mise en place du script : https://youtu.be/E2Jvn0DYJkY

from gpiozero import LED
from time import sleep

red = LED(16)
amber = LED(20)
green = LED(21)

green.on()
amber.off()
red.off()

while True:
    sleep(10)
    green.off()
    amber.on()
    sleep(2)
    amber.off()
    red.on()
    sleep(10)
    amber.on()
    sleep(2)
    green.on()
    amber.off()
    red.off()
