def multipliers(number) :
	list_of_dividors = {}
	dividor = 2
	power = 1
	while number != 1:
		if number % dividor == 0:
			list_of_dividors[dividor] = power
			number /= dividor
			dividor = 2
			power += 1
		else:
			dividor += 1
			power = 1
	return list_of_dividors

def traceNumber(number) :
	dict_of_dividors = {}
	for x in xrange(2, number + 1):
		dict_of_dividors[x] = multipliers(x)
	
	return dict_of_dividors

## main program
s = raw_input('--> ')
number = int(s)
l = traceNumber(number)
print l
