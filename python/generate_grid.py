import random
def get_int(msg, minimum, default):
	while True:
		try:
			strNum=input(msg)
			if not strNum and default is not None:
				return default
			nNum = int(strNum)
			if nNum < minimum:
				print("Input must >= minimum")
				continue
			return nNum
		except ValueError as e:
			print(e)

def main():
	rows=get_int("Input Row Number:", 10, None)
	columes=get_int("Input Colume Number:", 10, 20)

	minimum=get_int("Input Mininum Number:", -100000, None)
	maximum=get_int("Input Maximum Number:", 10000000, abs(minimum) * 2)

	row=0
	while row < rows:
		line=""
		colume=0
		while colume < columes:
			i=random.randint(minimum, maximum)
			s=str(i)
			while len(s) < 10:
				s = " " + s
			line += s
			colume += 1
		print(line)
		row += 1

main()

