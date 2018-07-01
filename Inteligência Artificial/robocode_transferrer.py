import os
import time


file_path = "/home/concatto/robocode/robots/concatto/NeuralBot.data/track.csv"
target_path = "/home/concatto/robo_data.csv"

while True:
	statinfo = os.stat(file_path)

	print("File size: %s" % statinfo.st_size)

	if statinfo.st_size > 10000: # file is full
		new_data = []
		with open(file_path, "r") as data_file:
			new_data = data_file.readlines()

		with open(target_path, "a") as target_file:
			for line in new_data:
				target_file.write(line)

		# Open for writing then close, erasing the file's contents
		open(file_path, "w").close()

	time.sleep(1)
