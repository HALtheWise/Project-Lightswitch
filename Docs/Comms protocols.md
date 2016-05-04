# Bluetooth protocols
 All communications happen at 9600 baud

## Computer to Lightswitch
* `a` -> turn light on
* `b` -> turn light off

## Lightswitch to computer
* Every second, transmit `k` if status is good.
* After completing the execution of a valid command, echo it back.