import math
import sys
import decimal

def fm1():
	return "{who} turned {age} this year.".format(who="she", age=88)

def fm2():
	return "The {who} was {0} last week".format(12, who="Nick")

def fm3():
	stock=["I", "luli", "he", "lxm"]
	ss2=["dosomething", "findsomething"]
	return "{0[0]} am writting the name {0[1]}, and {1[1]}".format(stock, ss2)

def fm4():
	return "math.pi={0.pi} sys.maxunicode=={1.maxunicode}".format(math,sys)

def fm5():
	return "{0} {0!s} {0!r} {0!a}".format(decimal.Decimal("1.234567890"))

def fm6():
	s="My Python Format"
	print("{0}".format(s))
	print("{0:30}".format(s))#minimum with 30
	print("{0:>30}".format(s))#right align,minimun with 30
	print("{0:^30}".format(s))#middle align,minimum with 29
	print("{0:-^30}".format(s))#fill -, align center, minimum with 30
	print("{0:.<30}".format(s))#fill .,align left,minimum 30
	print("{0:.10}".format(s))#maxsize 10



def fm_exmaple():
	print(fm1())
	print(fm2())
	print(fm3())
	print(fm4())
	print(fm5())
	fm6()
fm_exmaple()