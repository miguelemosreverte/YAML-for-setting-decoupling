import os
import time
import sys
from os.path import join
import yaml
from datetime import datetime
import shutil

class ProfileReporter:

	def __init__(self):
		# Read YAML file
		with open("commands.yaml", 'r') as stream:
			data_loaded = yaml.load(stream)
			self.output_dir = data_loaded["output_dir"]
			self.save = data_loaded["save"]
			self.filenames = data_loaded["filenames"]
			self.commands = data_loaded["commands"]
			self.transformations = data_loaded["transformations"]
			self.cleanup = data_loaded["cleanup"]

		self.create_output_folder()
		self.apply_commands_transformations()

	def create_output_folder(self):
		if not os.path.exists(self.output_dir):
			os.makedirs(self.output_dir)
		self.output_dir = self.output_dir + datetime.now().strftime("%H:%M:%S.%f") + "/"
		if not os.path.exists(self.output_dir):
			os.makedirs(self.output_dir)

	def apply_commands_transformations(self):
		for filename in self.filenames:
			for command_category in self.commands:
				for command_name in self.commands[command_category]:
					command = self.commands[command_category][command_name]
					for commands_transformation in self.transformations:
						command =\
							eval(commands_transformation
							.replace("command", command)
							.replace("input_source_filename", filename)
							.replace("input_report_filename", self.output_dir + os.path.splitext(filename)[0]+'.txt'))
					self.commands[command_category][command_name] = command

	def run_main(self):
		for filename in self.filenames:
			for command in self.commands["main"]:
				self.run_command(self.commands["main"][command], filename)
		self.run_cleanup()

	def run_command(self,command, filename):
		output_file =  os.path.splitext(filename)[0]+'.txt'
		command_title = 'echo "'+'-'*50+'\n'+command+'\n";'
		command = self.save\
			.replace("command", command_title + command)\
			.replace("output_file", self.output_dir + output_file)
		os.system(command)

	def run_report(self, output_report_file):
		for item in os.listdir(self.output_dir):
			commands = "( insert_commands_here ) >> " +  self.output_dir + output_report_file
			report_commands =  ";".join(
				[self.commands["report"][key] for key in self.commands["report"]]
				) + ";"
			os.system(commands.replace("insert_commands_here", report_commands))

	def run_cleanup(self):
		extensions = self.cleanup["extensions"]
		dir = "./"
		for item in os.listdir(dir):
		    for extension in extensions:
			    if item.endswith(extension):
				os.remove(join(dir, item))

if __name__ == "__main__":
	MyProfileReporter = ProfileReporter()
	MyProfileReporter.run_main()
	MyProfileReporter.run_report("sinopsis.txt")
