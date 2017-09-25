import os
import subprocess
import shutil
import sys
import argparse

def get_filename(filename_with_extension):
	return os.path.splitext(filename_with_extension)[0]
def get_command_output(command):
	ps = subprocess.Popen(command,shell=True, stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
	output = ps.communicate()[0]
	return output
def get_time_from_execution(complete_filename):
	print complete_filename
	command = "head -n 7 " + complete_filename + " | tail -n 1;"
	return get_command_output(command)

if __name__ == "__main__":
	parser = argparse.ArgumentParser()
	parser.add_argument('NTimes', type=int)
	args = parser.parse_args()

	output_dir = "report/"
	if os.path.exists(output_dir):
		shutil.rmtree(output_dir)

	for n in range(0,args.NTimes):
		os.system("python test.py")

	time_per_execution = {}
	for item in os.listdir("."):
		if item.endswith(".c"):
			time_per_execution[get_filename(item)] = []

	for root, dirs, files in os.walk("report"):
	    for file in files:
			if get_filename(file) in time_per_execution:
				time_per_execution[get_filename(file)]\
				.append(get_time_from_execution(os.path.join(root,file)))

	def get_number(string):
		result = [word for word in string.split(" ")
			if unicode(word.rstrip(), 'utf-8').isnumeric()][0]
		return int(result)

	with open ("final_report.txt", "w") as f:
		for key in time_per_execution:
			f.write(key + ":\n\n")
			times = [get_number(string_result) for string_result in time_per_execution[key]]
			for time_it_took in times:
				f.write(str(time_it_took) + "\n")

			f.write("avg: " + str(sum(times) / len(times)) + " nanoseconds\n")
			f.write('-' * 50 + "\n")
