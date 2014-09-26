The goal of this little project is to maintain in real time the number of stars the player has in Super Mario 64. This is the number in the top right:

![alt tag](https://googledrive.com/host/0B_WJBlETj-zLSDE2cjFqUHk3QlU/mario.png)

The general strategy is to collect a bunch of frames for each star value, find the pixels that don't change in color, infer these to be the pixels comprising the star number, and use them to predict the star number when it isn't known.
