def get_int(msg):
	while True:
		try:
			i=int(input(msg))
			return i
		except ValueError as err:
			print(err)
print("Your Age Is:", get_int("Input Your Age:"))

